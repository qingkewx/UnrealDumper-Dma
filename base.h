#ifndef BASE_H
#define BASE_H

#include <Windows.h>
#include <iostream>
#include <string>

using namespace std;
inline uint64_t offset_uworld = 0x10249dd8;
inline uint64_t offset_NamePool = 0x12f54500;
inline uint64_t offset_Gobject = 0x12F6DB50 - 0x18;
struct _Offsets {
    struct {
        uint16_t Objects = 24;
        uint16_t NumChunks = 0x10;
        uint16_t NumElements = 0x0;
    }TUObjectArray;
    struct {
        uint16_t Size = 24;
        uint16_t Object = 0x0;
    } FUObjectItem;
    struct {
        uint16_t Index = 0x34;
        uint16_t Class = 0x18;
        uint16_t Name = 0x2C;
        uint16_t Outer = 0x20;
    } UObject;
    struct {
        uint16_t SuperStruct = 0x58;
        uint16_t Children = 0x68;
        uint16_t ChildProperties = 0x80;
        uint16_t PropertiesSize = 0x50;
    } UStruct;
    struct {
        uint16_t Name = 0x0;
        uint16_t Value = 0x8;
        uint16_t Size = 0x10;
        uint16_t Names = 0x50;
    } UEnum;
    struct {
        uint16_t Func = 0xf0;
    } UFunction;
    struct {
        uint16_t Class = 0x20;
        uint16_t Next = 0x18;
        uint16_t Name = 0x28;
    } FField;
    struct {
        uint16_t ElementSize = 0x40;
        uint16_t Offset = 0x54;
        uint16_t Size = 0x88;
    } FProperty;
};

struct _SaveFileName
{
    const char* EnumName = "SDK\\Enum.cpp";
    const char* ClassName = "SDK\\Class.cpp";
    const char* StructName = "SDK\\Struct.cpp";
    const char* ObjectsName = "SDK\\Object.cpp";
    const char* FunctionName = "SDK\\Function.cpp";
};

static _Offsets Offsets;
static _SaveFileName SaveFileName;
#endif // !BASE_H
