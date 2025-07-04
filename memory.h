#ifndef MEMORY_H
#define MEMORY_H

#include "base.h"
#include <map>
#include"Memory/Memory.h"
#include <codecvt>


inline bool ReaderInit(std::string& processname) {

	if (!mem.Init(processname, true, false))
	{
		printf("[db] Failed to init memory reader\n");
		return false;
	}
	return true;
}
//add your Decryption
#endif // !MEMORY_H
