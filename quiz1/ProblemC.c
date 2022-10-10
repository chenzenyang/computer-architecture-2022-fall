/*
Let’s try to determine endianness at compile time.
If someone needs to know the endianess at compile time, there are 2 different use cases:

in some rare cases one needs to know the endianess to lay out structs and the like, for example an RGB union; or directly in the code.
in most cases, just a conversion from one endian to the other is needed,
    e.g. when a protocol defines that a value is stored in a specific endianness.
In the majority of use cases, one wants just to convert from little to big endian, and vice versa (or actually to and from host endianness!).

Assume that we are going to provide endian conversion functions/macros start with the end_ prefix.
*/

/*
You shall provide the functioned implementations.
Both C01 and C02 are hexadecimal integer literals, meaning that they should start with 0x. C03, C04, C05, and C06 are C expressions.

You might consider to call end_bswap32 function when it is necessary. You must obey the following rules when filling them:
- Write shorter code as possible as you can.
- Do necessary casting to eliminate compilation warnings.
- Follow the consistent coding style. That is, we prefer end_bswap32(n) to end_bswap32( n ).
    Be aware of the spaces! Details determine success or failure.
*/

/* Return a value in which the order of the bytes in 4-byte arguments is reversed. */
#include <stdlib.h>
static inline uint32_t end_bswap32(uint32_t __x)
{
    return (__x >> 24) | (__x >> 8 & 0x0000FF00) | (__x << 8 & 0x00FF0000) |
           (__x << 24);
}

/* Host to Big Endian 32-bit */
static inline uint32_t end_htobe32(uint32_t n)
{
    union {
        int i;
        char c;
    } u = {1};
    return u.c ? end_bswap32(n) : n;
}

/* Host to Little Endian 32-bit */
static inline uint32_t end_htole32(uint32_t n)
{
    union {
        int i;
        char c;
    } u = {1};
    return u.c ? n : end_bswap32(n);
}