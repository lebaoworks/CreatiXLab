#ifndef __LARGEINT_CONFIG__
#define __LARGEINT_CONFIG__

#include <stdint.h>
#include <stdlib.h>

#define LI_Size 128
#define LI_Bits 8
#define LI_Base 256

typedef uint8_t li[LI_Size];
typedef int16_t ii;
typedef uint8_t u8;
typedef uint16_t u16;
typedef size_t uin;

#endif //__LI_CONFIG__