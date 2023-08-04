/**
 * @brief LwIP arch support file
 */
#ifndef LWIP_CC_H
#define LWIP_CC_H

#include <stdlib.h>
#include <stdint.h>

#include <printf/printf.h>

#define LWIP_PROVIDE_ERRNO

// compiler specific stuff
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_STRUCT __attribute__ ((__packed__))
#define PACK_STRUCT_END
#define PACK_STRUCT_FIELD(x) x

void log_panic(const char *, ...);

#define LWIP_PLATFORM_ASSERT(x) do {log_panic("Assertion \"%s\" failed at line %d in %s\n", \
                                     x, __LINE__, __FILE__); } while(0)

/*
#define LWIP_RAND() ((u32_t)rand())
*/

#endif
