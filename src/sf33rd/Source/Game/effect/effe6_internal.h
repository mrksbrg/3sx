#ifndef EFFE6_INTERNAL_H
#define EFFE6_INTERNAL_H

#include "structs.h"

void effe6_init_common(WORK_Other* ewk);
void mark_effe6_for_cleanup_if_stale(WORK_Other* ewk);

#endif
