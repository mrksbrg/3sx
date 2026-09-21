#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H

#include <stdbool.h>

/// The settings the config file knows. Their names in the file are in config.c's
/// default table, one per key, in this order.
typedef enum ConfigKey {
    CFG_KEY_FULLSCREEN,
    CFG_KEY_WINDOW_WIDTH,
    CFG_KEY_WINDOW_HEIGHT,
    CFG_KEY_SCALEMODE,
    CFG_KEY_SCANLINES,
    CFG_DRAW_PLAYERS_ABOVE_HUD,
    CFG_ARCADE_BALANCE,
    CFG_KEY_COUNT
} ConfigKey;

/// Initialize config system
void Config_Init();

/// Destroy resources used by config system
void Config_Destroy();

/// Get the value associated with the given key as a `bool`
/// @return The value associated with `key` if `key` is among entries and the value's type is `bool`, `false` otherwise
bool Config_GetBool(ConfigKey key);

/// Get the value associated with the given key as an `int`
/// @return The value associated with `key` if `key` is among entries and the value's type is `int`, `0` otherwise
int Config_GetInt(ConfigKey key);

/// Get the value associated with the given key as a `string`
/// @return The value associated with `key` if `key` is among entries and the value's type is `string`, `NULL` otherwise
const char* Config_GetString(ConfigKey key);

#endif
