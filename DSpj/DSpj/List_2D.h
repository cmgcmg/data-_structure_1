#ifndef _LIST_2D_H
#define _LIST_2D_H

#include "Employment.h"
#include "Region.h"
#include <cstring>
#include <iostream>
using namespace std;

class List_2D
{
private:
	Region* pHead;

public:
	List_2D();
	~List_2D();

	void SetHead(Region* pNode);
	Region* GetHead();

	void Insert(Region* pNode);
	void Insert(Employment* pNode);
	bool Delete(Employment* pNode);

	Employment* Search(Employment* pNode);
	Employment* Update(Employment* pNode);
	void DelNext(Employment* pNode);
	Employment* Search(char* region_code, char* company);
	Employment* Search(char* region_code);
	Region* rSearch(char* region_code);
	void DelNext(Region* pNode);
	Region* GetRegion(Region* rNode);
	bool ISearch(char* Region_Code, char* company);
};
#endif