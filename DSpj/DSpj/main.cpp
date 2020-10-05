#define _CRTDBG_MAP_ALLOC

#include "Management.h"
#include<utility>
#include<cstring>

int main()
{	
	//_CrtSetBreakAlloc(268);
	Management m;

	m.ReadCommand();
	_CrtDumpMemoryLeaks();
	return 0;
}
