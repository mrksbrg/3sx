"""Run a bounded deterministic gameplay comparison before relevant commits."""

import os
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

TOOLS_DIR = Path(__file__).resolve().parent
sys.path.insert(0, str(TOOLS_DIR))

from compare_stress_replays import TraceRun, first_difference, read_complete_trace, run_trace

REPO_ROOT = TOOLS_DIR.parent
GAME_SOURCE_PREFIX = "src/sf33rd/Source/Game/"
SOURCE_SUFFIXES = {".c", ".h"}
DEFAULT_FIRST_SEED = 1
DEFAULT_SEEDS = 10
DEFAULT_FRAMES = 1800
DEFAULT_TIMEOUT = 300


def staged_game_sources() -> list[str]:
    result = subprocess.run(
        ["git", "diff", "--cached", "--name-only", "--diff-filter=ACMR"],
        cwd=REPO_ROOT,
        check=True,
        capture_output=True,
        text=True,
    )
    return [
        path
        for path in result.stdout.splitlines()
        if path.startswith(GAME_SOURCE_PREFIX) and Path(path).suffix in SOURCE_SUFFIXES
    ]


def executable_candidates(build_dir: Path, platform: str = sys.platform) -> list[Path]:
    if platform == "darwin":
        return [build_dir / "3SX.app" / "Contents" / "MacOS" / "3SX", build_dir / "3sx"]

    if platform == "win32":
        return [build_dir / "Debug" / "3sx.exe", build_dir / "3sx.exe"]

    return [build_dir / "3sx", build_dir / "Debug" / "3sx"]


def executable_in(build_dir: Path) -> Path:
    candidates = executable_candidates(build_dir)
    return next((path for path in candidates if path.is_file()), candidates[0])


def configured_path(variable: str, default: Path) -> Path:
    value = os.environ.get(variable)
    return Path(value) if value else default


def configured_positive_int(variable: str, default: int) -> int:
    value = os.environ.get(variable)

    if value is None:
        return default

    try:
        result = int(value)
    except ValueError as error:
        raise RuntimeError(f"{variable} must be a positive integer") from error

    if result <= 0:
        raise RuntimeError(f"{variable} must be a positive integer")

    return result


def replay_required(changed: list[str]) -> bool:
    return bool(changed) or os.environ.get("THREESX_REPLAY_GUARD_FORCE") == "1"


def cmake_binary() -> str:
    configured = os.environ.get("CMAKE")

    if configured:
        return configured

    discovered = shutil.which("cmake")

    if discovered:
        return discovered

    windows_candidates = [
        Path("C:/msys64/mingw64/bin/cmake.exe"),
        Path("/c/msys64/mingw64/bin/cmake.exe"),
    ]
    return str(next((path for path in windows_candidates if path.is_file()), "cmake"))


def build_candidate(build_dir: Path) -> None:
    command = [cmake_binary(), "--build", str(build_dir), "--parallel", "--config", "Debug"]
    subprocess.run(command, cwd=REPO_ROOT, check=True)


def missing_build_message(baseline: Path, candidate: Path) -> str:
    return (
        "Replay gate needs Debug builds with deterministic tracing.\n"
        f"  baseline missing: {baseline}\n"
        f"  candidate missing: {candidate}\n"
        "Create build-replay-main from main and build-replay from the working branch, "
        "or set THREESX_REPLAY_GUARD_BASELINE, THREESX_REPLAY_GUARD_CANDIDATE, "
        "and THREESX_REPLAY_GUARD_BUILD_DIR."
    )


def preserve_failure_traces(source: Path, destination: Path, seed: int) -> Path:
    target = destination / f"seed-{seed}"

    if target.exists():
        shutil.rmtree(target)

    target.parent.mkdir(parents=True, exist_ok=True)
    shutil.copytree(source, target)
    return target


def compare_builds(baseline: Path, candidate: Path) -> int:
    first_seed = configured_positive_int("THREESX_REPLAY_GUARD_FIRST_SEED", DEFAULT_FIRST_SEED)
    seed_count = configured_positive_int("THREESX_REPLAY_GUARD_SEEDS", DEFAULT_SEEDS)
    frames = configured_positive_int("THREESX_REPLAY_GUARD_FRAMES", DEFAULT_FRAMES)
    timeout = configured_positive_int("THREESX_REPLAY_GUARD_TIMEOUT", DEFAULT_TIMEOUT)
    failures = configured_path("THREESX_REPLAY_GUARD_FAILURE_DIR", REPO_ROOT / "build-replay-failures")
    compared_states = 0

    with tempfile.TemporaryDirectory(prefix="3sx-precommit-replay-") as directory:
        output = Path(directory)

        for seed in range(first_seed, first_seed + seed_count):
            seed_output = output / f"seed-{seed}"

            try:
                baseline_trace = run_trace(TraceRun(baseline, seed, frames, timeout), seed_output / "baseline")
                candidate_trace = run_trace(TraceRun(candidate, seed, frames, timeout), seed_output / "candidate")
            except RuntimeError as error:
                traces = preserve_failure_traces(seed_output, failures, seed)
                print(f"Replay gate failed for seed {seed}: {error}", file=sys.stderr)
                print(f"  traces: {traces}", file=sys.stderr)
                return 2

            baseline_rows = read_complete_trace(baseline_trace)
            candidate_rows = read_complete_trace(candidate_trace)
            difference = first_difference(baseline_rows, candidate_rows)

            if difference is not None:
                index, baseline_row, candidate_row = difference
                traces = preserve_failure_traces(seed_output, failures, seed)
                print(f"Replay gate failed: seed {seed} diverged.", file=sys.stderr)
                print(f"  trace row: {index}", file=sys.stderr)
                print(f"  baseline:  {baseline_row}", file=sys.stderr)
                print(f"  candidate: {candidate_row}", file=sys.stderr)
                print(f"  traces:    {traces}", file=sys.stderr)
                return 1

            compared_states += len(baseline_rows)
            print(f"Replay seed {seed} passed: {len(baseline_rows)} deterministic states are identical.")

    print(f"Replay gate passed: {seed_count} seeds and {compared_states} deterministic states are identical.")
    return 0


def main() -> int:
    changed = staged_game_sources()

    if not replay_required(changed):
        print("Replay gate skipped: no staged gameplay source changes.")
        return 0

    candidate_build = configured_path("THREESX_REPLAY_GUARD_BUILD_DIR", REPO_ROOT / "build-replay")
    baseline = configured_path(
        "THREESX_REPLAY_GUARD_BASELINE", executable_in(REPO_ROOT / "build-replay-main")
    )
    candidate = configured_path("THREESX_REPLAY_GUARD_CANDIDATE", executable_in(candidate_build))

    try:
        build_candidate(candidate_build)
    except (OSError, subprocess.CalledProcessError) as error:
        print(f"Replay gate failed to build candidate: {error}", file=sys.stderr)
        return 2

    if not baseline.is_file() or not candidate.is_file():
        print(missing_build_message(baseline, candidate), file=sys.stderr)
        return 2

    try:
        return compare_builds(baseline, candidate)
    except RuntimeError as error:
        print(f"Replay gate failed to run: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
