#ifndef UWASM_H
#define UWASM_H

#include <stdint.h>

// WASM instructions
typedef enum
{
    Unreachable = 0x00,
    Nop = 0x01,
    Block_bt = 0x02,
    Loop_bt = 0x03,
    If_bt = 0x04,
    Else = 0x05,
    End = 0x0B,
    Br_l = 0x0C,
    Br_if_l = 0x0D,
    Br_table_Ll = 0x0E,
    Return = 0x0F,
    Call_x = 0x10,
    Call_indirect_xy = 0x11,
    Drop = 0x1A,
    Select = 0x1B,
    Select_t = 0x1C,
    LocalGet_x = 0x20,
    LocalSet_x = 0x21,
    LocalTee_x = 0x22,
    GlobalGet_x = 0x23,
    GlobalSet_x = 0x24,
    TableGet_x = 0x25,
    TableSet_x = 0x26,
    I32Load_memarg = 0x28,
    I64Load_memarg = 0x29,
    F32Load_memarg = 0x2A,
    F64Load_memarg = 0x2B,
    I32Load8_s_memarg = 0x2C,
    I32Load8_u_memarg = 0x2D,
    I32Load16_s_memarg = 0x2E,
    I32Load16_u_memarg = 0x2F,
    I64Load8_s_memarg = 0x30,
    I64Load8_u_memarg = 0x31,
    I64Load16_s_memarg = 0x32,
    I64Load16_u_memarg = 0x33,
    I64Load32_s_memarg = 0x34,
    I64Load32_u_memarg = 0x35,
    I32Store_memarg = 0x36,
    I64Store_memarg = 0x37,
    F32Store_memarg = 0x38,
    F64Store_memarg = 0x39,
} wasmInstType;

// WASM value types
typedef enum {
    i32 = 0x7F,
    i64 = 0x7E,
    f32 = 0x7D,
    f64 = 0x7C,
    v128 = 0x7B,
    funcref = 0x70,
    extrnref = 0x6F,
    functype = 0x60,
    result = 0x40,
} wasmValType;

// Header of WASM file
typedef struct
{
    char magic[4];
    uint32_t version;
} wasmHeader;

// WASM section
typedef struct
{
    uint8_t id;
    uint32_t size;
} wasmSection;

typedef struct
{
    uint8_t tag;

} wasmFuncType;

// WASM module
typedef struct
{
    wasmHeader header;
    wasmSection *sections;
} wasmModule;

wasmHeader wasmReadHeader(uint8_t** data);
wasmSection wasmReadSection(uint8_t** data);

#endif
