#ifndef _LIBVIB_H_
#define _LIBVIB_H_

#define SCE_VIB_PROFILE_SIZE (1)
#define SCE_VIB_DATA_SIZE (2)

int sceVibGetProfile(int, unsigned char*);

/* The five values sceVibSetActParam takes, in its own parameter order. */
typedef struct {
    int socket_number;
    int profile_size;
    unsigned char* profile;
    int data_size;
    unsigned char* data;
} VibActParam;

int sceVibSetActParam(const VibActParam*);
void* sceVibGetErxEntries(void);

#endif
