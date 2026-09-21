#ifndef PSP_TEXTURES_H
#define PSP_TEXTURES_H

#include "sf33rd/AcrSDK/common/plcommon.h"

/// The texture PSPRenderer_SetTexture last selected, which the renderer draws with.
const FLTexture* PSPTextures_Current(void);

/// Forget the selected texture and palette, so the next PSPRenderer_SetTexture loads them again.
void PSPTextures_Reset(unsigned int texture_code);

#endif
