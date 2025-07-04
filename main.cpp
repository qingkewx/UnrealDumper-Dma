#include "Base.h"
#include "dumper.h"


int main()
{

	Dumper& Dump = Dumper::GetInstance();
	std::string processname = "DeltaForceClient-Win64-Shipping.exe";


	try
	{
		Dump.Init(processname);
	}
	catch (const char* error)
	{
		printf("%s\n", error);
		system("pause");
		return -1;
	}

	Dump.Dump();

	system("pause");
	return 0;
}