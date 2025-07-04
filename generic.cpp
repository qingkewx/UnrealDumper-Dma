#include "generic.h"
#include "memory.h"

#include<codecvt>


DWORD64 GameBase = 0;
FNamePool* NamePoolData = NULL;
TUObjectArray* ObjObjects = NULL;

#define _WORD  uint16_t
#define WORD1(x)   (*((_WORD*)&(x)+1))

string FNamePool::GetName(uint32_t NameId)
{
	uint32_t Block = (WORD1(NameId) + 2);
	uint8_t* NameAddr = mem.Read<uint8_t*>(this + Block * 8) + 2 * (uint16_t)NameId;
	FNameEntry Info = mem.Read<FNameEntry>(NameAddr);

	char buf[1024]{0};
	mem.Read((uint64_t)(NameAddr + 2), &buf, Info.Header.Len);

	string Name;
	if (Info.Header.bIsWide){

		try
		{
			wstring_convert<codecvt<wchar_t, char, mbstate_t>> converter(new codecvt<wchar_t, char, mbstate_t>("CHS"));
			Name = converter.to_bytes((wchar_t*)buf);
		}
		catch (...)
		{
			Name = buf;
		}
	}
	else{
		Name = buf;
	}

	size_t Pos = Name.rfind('/');
	if (Pos != std::string::npos) {
		Name = Name.substr(Pos + 1);
	}

	return Name;
}

uint32_t TUObjectArray::GetNumChunks()
{
	return  mem.Read<uint32_t>(this + Offsets.TUObjectArray.NumChunks);
}

uint32_t TUObjectArray::GetNumElements()
{
	return  mem.Read<uint32_t>(this + Offsets.TUObjectArray.NumElements);
}
UE_UObject* TUObjectArray::GetObjectFormId(size_t Id) {
	//printf("id:%d\n", id);
	uint64_t chunkIndex = Id / 65536;
	uint64_t Objects_ptr = mem.Read<uint64_t>(this + Offsets.TUObjectArray.Objects);
	uint8_t* chunk = mem.Read<uint8_t*>(Objects_ptr + chunkIndex * 8);
	if (!chunk) return nullptr;
	uint32_t withinChunkIndex = Id % 65536 * Offsets.FUObjectItem.Size;
	return mem.Read<UE_UObject*>(chunk + withinChunkIndex);
}

UE_UObject* TUObjectArray::FindObject(string FullName)
{
	for (size_t i = 0; i < GetNumElements(); i++)
	{
		UE_UObject* Object = GetObjectFormId(i);
		if (Object && Object->GetFullName() == FullName)
			return Object;
	}

	return NULL;
}

