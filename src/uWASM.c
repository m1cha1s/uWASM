#include <stdint.h>

#include "uWASM.h"
#include "leb128.h"

wasmHeader wasmReadHeader(uint8_t** data) {
  wasmHeader header;

  uint8_t* headerPtr = (uint8_t*)&header;
  uint8_t* ptr = *data;

  for (int i = 0; i < sizeof(wasmHeader); i ++) {
    *(headerPtr++) = *(ptr++);
  }

  *data = ptr;
  return header;
}

wasmSection wasmReadSection(uint8_t** data) {
  wasmSection section;

  uint8_t* sectionPtr = (uint8_t*)&section;
  uint8_t* ptr = *data;

  for(int i = 0; i < sizeof(uint8_t); i++) {
    *(sectionPtr++) = *(ptr++);
  }

  *data = ptr;

  section.size = decodeUnsignedLEB128(data);

  return section;
}
