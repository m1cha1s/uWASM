#include <stdlib.h>
#include <stdint.h>

#include "uWASM.h"
#include "leb128.h"

wasmHeader wasmReadHeader(uint8_t **data)
{
    wasmHeader header;

    uint8_t *headerPtr = (uint8_t *)&header;
    uint8_t *ptr = *data;

    for (int i = 0; i < sizeof(wasmHeader); i++)
    {
        *(headerPtr++) = *(ptr++);
    }

    *data = ptr;
    return header;
}

wasmSection wasmReadSection(uint8_t **data)
{
    wasmSection section;

    uint8_t *sectionPtr = (uint8_t *)&section;
    uint8_t *ptr = *data;

    for (int i = 0; i < sizeof(uint8_t); i++)
    {
        *(sectionPtr++) = *(ptr++);
    }

    *data = ptr;

    section.size = decodeUnsignedLEB128(data);

    return section;
}

bool wasmCheckHeader(wasmHeader header)
{
    return (header.magic == (char[4]){'\n', 'a', 's', 'm'} && header.version == 1);
}

wasmFuncSigSet wasmParseTypeSection(uint32_t sectionSize, uint8_t **data)
{
    uint8_t *ptr = *data;

    wasmFuncSigSet result;

    result.sigCount = *(ptr++);

    result.sigs = malloc(sizeof(wasmFuncSigType) * result.sigCount);

    for (uint8_t s = 0; s < result.sigCount; s++)
    {
        // Skip the first byte since it defines the function type and there is only one type
        ptr++;

        result.sigs[s].paramCount = *(ptr++);

        result.sigs[s].params = malloc(sizeof(wasmValType) * result.sigs[s].paramCount);

        for (uint8_t p = 0; p < result.sigs[s].paramCount; p++)
        {
            result.sigs[s].params[p] = *(ptr++);
        }

        result.sigs[s].resultCount = *(ptr++);

        result.sigs[s].results = malloc(sizeof(wasmValType) * result.sigs[s].resultCount);

        for (uint8_t p = 0; p < result.sigs[s].resultCount; p++)
        {
            result.sigs[s].results[p] = *(ptr++);
        }
    }

    *data = ptr;
    return result;
}