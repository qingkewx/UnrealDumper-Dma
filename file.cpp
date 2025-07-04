#include "file.h"


File::File(const char* FileName)
{
	fopen_s(&file,FileName, "w+");

	if (file)
	{
		fwprintf(file, L"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t/* https://github.com/qingkewx/UnrealDumper-Dma */\n");
	}
}

File::~File()
{
	if (file)
		fclose(file);
}

int File::fprintf(string str)
{
	return std::fprintf(file, str.c_str());
}

int File::fprintf(const char* str)
{
	return std::fprintf(file, str);
}

FILE* File::GetFile()
{
	return file;
}