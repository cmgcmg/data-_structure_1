#ifndef _LIST_CIRCULAR_H
#define  _LIST_CIRCULAR_H

#include "Employment.h"
#include <iostream>

class List_Circular
{
private:
	Employment* pHead;
public:
	List_Circular();
	~List_Circular();

	void SetHead(Employment* pNode);
	Employment* GetHead();	
	void Insert(Employment* pNode);		
	void Print();
	Employment* Search(Employment* pNode);
	Employment* Update(Employment* pNode);
	Employment* Delete(Employment* pNode);	
	Employment* Search(char* region_code, char* region_name, char* company, char* qualification, char* workingcondition, char* to);
	Employment* Search(char* region_code);
};
#endif