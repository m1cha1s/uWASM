#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <uWASM.h>

int main()
{
    FILE *wasmFile = fopen("./test/test.wasm", "rb");

    if (!wasmFile)
    {
        printf("Unable to open file!\n");
        return 1;
    }

    fseek(wasmFile, 0L, SEEK_END);
    size_t sz = ftell(wasmFile);
    fseek(wasmFile, 0L, SEEK_SET);

    uint8_t* wasmBinaryBuffer = malloc(sz);
    uint8_t* wasmBBptr = wasmBinaryBuffer;

    fread(wasmBinaryBuffer, sz, 1, wasmFile);
    fclose(wasmFile);


    wasmHeader header;
    wasmSection section;

    header = wasmReadHeader(&wasmBBptr);
    section = wasmReadSection(&wasmBBptr);

    free(wasmBinaryBuffer);

//    fread(&header, sizeof(wasmHeader), 1, wasmFile);
//    fread(&section, sizeof(wasmSection), 1, wasmFile);

    printf("%c%c%c %d\n", header.magic[1], header.magic[2], header.magic[3], header.version);
    printf("%d %d\n", section.id, section.size);

//    fclose(wasmFile);
    return 0;
}
