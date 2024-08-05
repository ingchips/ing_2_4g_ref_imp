#ifndef ING_RAM_CODE__H
#define ING_RAM_CODE__H
#include "stdint.h"

#ifndef OPT_RAM_CODE
#define OPT_RAM_CODE
#endif

#ifdef OPT_RAM_CODE
    #define ADDITIONAL_ATTRIBUTE    __attribute__((section(".ram_code")))
#else
    #define ADDITIONAL_ATTRIBUTE
#endif

#endif
