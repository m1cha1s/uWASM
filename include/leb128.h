#ifndef LEB128_H_
#define LEB128_H_

#include <stdint.h>

static uint32_t decodeUnsignedLEB128(uint8_t **data)
{
    uint8_t *ptr = *data;
    int result = *(ptr++);
    if (result > 0x7F)
    {
        int cur = *(ptr++);
        result = (result & 0x7F) | ((cur & 0x7F) << 7);
        if (cur > 0x7F)
        {
            cur = *(ptr++);
            result |= (cur & 0x7F) << 14;
            if (cur > 0x7F)
            {
                cur = *(ptr++);
                result |= (cur & 0x7F) << 21;
                if (cur > 0x7F)
                {
                    cur = *(ptr++);
                    result |= (cur & 0x7F) << 28;
                }
            }
        }
    }

    *data = ptr;
    return (uint32_t)result;
}

#endif // LEB128_H_
