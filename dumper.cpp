#include "dumper.h"
#include "generic.h"
#include "memory.h"
#include "file.h"
#include "engine.h"

void Dumper::Init(std::string& processname)
{

	ReaderInit(processname);
	GameBase = mem.BaseAddr;
	NamePoolData = (FNamePool*)(mem.BaseAddr+ offset_NamePool);
	ObjObjects = (TUObjectArray*)(mem.BaseAddr + offset_Gobject);
	if(NamePoolData->GetName(0) != "None")
		throw "GetName Error\n";
	printf("%s\n", NamePoolData->GetName(0).c_str());
	if (ObjObjects->GetNumChunks() == 0)
		throw "GObject chunks is 0";
	printf("GetNumChunks:%d\n", ObjObjects->GetNumChunks());
	setlocale(LC_ALL, "");
	CreateDirectoryA("SDK",NULL);

	return;
}

void Dumper::Dump()
{
	File ObjectDump(SaveFileName.ObjectsName);
	int maxsize = ObjObjects->GetNumElements();
	for (size_t i = 0; i < ObjObjects->GetNumElements(); i++)
	{
		UE_UObject* Object = ObjObjects->GetObjectFormId(i);
		if (!Object)
			continue;
		if (Object->IsA<UE_UEnum>())
		{
			Object->Cast<UE_UEnum*>()->Generate();
		}
		else if (Object->IsA<UE_UClass>())
		{
			Object->Cast<UE_UClass*>()->Generate();
		}
		else if (Object->IsA<UE_UFunction>())
		{
			Object->Cast<UE_UFunction*>()->Generate();
		}
		else if (Object->IsA<UE_UScriptStruct>())
		{
			Object->Cast<UE_UScriptStruct*>()->Generate();
		}

		fprintf(ObjectDump.GetFile(), "[0x%p]\t%s\n", Object, Object->GetFullName().c_str());
	}

	printf("\nOK!\n");
}
