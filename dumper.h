#ifndef DUMPER_H
#define DUMPER_H

#include "base.h"


class Dumper
{
public:
	static Dumper& GetInstance() {
		static Dumper Instance;
		return Instance;
	}

	void Init(std::string& processname);

	void Dump();

private:
	Dumper() {};
	Dumper(Dumper&) {};
};

#endif // !DUMPER_H