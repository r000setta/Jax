#include "JaxMath.h"

namespace Jax
{
#define POLYNOMIAL 0x04c11db7L
    unsigned int CRCTable[256];

    bool JAXMATH_API JaxInitMath()
    {
        return false;
    }

    void JAXMATH_API JaxInitCRCTable()
    {
        register int i, j;
        register unsigned long crc_accum;
        for (i = 0; i < 256; ++i)
        {
            crc_accum = ((unsigned long)i << 24);
            for (j = 0; j < 8; ++j)
            {
                if (crc_accum & 0x80000000L) crc_accum = (crc_accum << 1) ^ POLYNOMIAL;
                else crc_accum = (crc_accum << 1);
            }
            CRCTable[i] = crc_accum;
        }
    }

    unsigned int JAXMATH_API CRC32Compute(const void* data, size_t size)
    {
        unsigned int res;
        if (size == 0) return 0;
        const unsigned char* tmp = (const unsigned char*)data;
        res = *tmp++ << 24;
        if (size > 1)
        {
            res |= *tmp++ << 16;
            if (size > 2)
            {
                res |= *tmp++ << 8;
                if (size > 3) {
                    res |= *tmp++;
                }
            }
        }
        res = ~res;
        for (size_t i = 4; i < size; ++i)
        {
            res = (res << 8 | *tmp++) ^ CRCTable[res >> 24];
        }
        return ~res;
    }
}