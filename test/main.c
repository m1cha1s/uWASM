#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <uWASM.h>

int main()
{
    FILE *wasmFile = fopen("../test/test.wasm", "rb");

    if (!wasmFile)
    {
        printf("Unable to open file!\n");
        return 1;
    }

    fseek(wasmFile, 0L, SEEK_END);
    size_t sz = ftell(wasmFile);
    fseek(wasmFile, 0L, SEEK_SET);

    uint8_t *wasmBinaryBuffer = malloc(sz);
    uint8_t *wasmBBptr = wasmBinaryBuffer;

    fread(wasmBinaryBuffer, sz, 1, wasmFile);
    fclose(wasmFile);

    wasmHeader header;
    wasmSection section;
    wasmFuncSigSet sigs;

    header = wasmReadHeader(&wasmBBptr);
    section = wasmReadSection(&wasmBBptr);
    sigs = wasmParseTypeSection(section.size, &wasmBBptr);

    free(wasmBinaryBuffer);

    printf("WASM magic: %c%c%c WASM version: %d\n", header.magic[1], header.magic[2], header.magic[3], header.version);
    printf("--------------------------------------------------------\n");
    printf("Section ID: %d Section size: %d\n", section.id, section.size);
    printf("--------------------------------------------------------\n");
    for (int s = 0; s < sigs.sigCount; s++)
    {
        printf("Params: ");
        for (int p = 0; p < sigs.sigs[s].paramCount; p++)
        {
            printf("%x ", sigs.sigs[s].params[p]);
        }
        printf(" ");
        printf("Results: ");
        for (int r = 0; r < sigs.sigs[s].resultCount; r++)
        {
            printf("%x ", sigs.sigs[s].results[r]);
        }
        printf("\n");
    }

    return 0;
}
