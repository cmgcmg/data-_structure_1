#include "BST.h"
#include <utility>
#include <stack>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable:4996)
#pragma warning (disable:4101)

BST::BST()
{
	this->root = NULL;
}

BST::~BST()
{
	/* You must fill in here */
	if (root != NULL)
	{
		Region* rNode = root;
		Remove(rNode);
	}
}

/* You must fill in the member function definitions of the BST class here */
void BST::SetRoot(Region* pNode)
{
	this->root = pNode;
}

Region* BST::GetRoot()
{
	return root;
}

bool BST::Insert(Region* rNode)
{
	if (root == NULL) {
		SetRoot(rNode);
	}

	else {
	
		Region* rTemp = root;

		while (1)
		{	
			if (strcmp(rTemp->GetRegionCode(), rNode->GetRegionCode()) == 0) {
				rNode = NULL;
				delete rNode;
				return false;
			}
			
			if (strcmp(rTemp->GetRegionCode(), rNode->GetRegionCode()) < 0)
			{
				if (rTemp->GetRight() == NULL) {
					rTemp->SetRight(rNode);
					return true;
				}

				else {
					rTemp = rTemp->GetRight();
					continue;
				}
			}

			else if (strcmp(rTemp->GetRegionCode(), rNode->GetRegionCode()) > 0) 
			{
				if (rTemp->GetLeft() == NULL) {
					rTemp->SetLeft(rNode);
					return true;
				}

				else {
					rTemp = rTemp->GetLeft();
					continue;
				}
			}
		}

	}

	return true;
}

bool BST::Delete(Region* eNode)
{
	Region* p = root;
	Region* q = NULL;

	while (p && strcmp(p->GetRegionCode(), eNode->GetRegionCode()) != 0)
	{
		if (strcmp(p->GetRegionCode(), eNode->GetRegionCode()) > 0) p = p->GetLeft();

		else p = p->GetRight();

	}

	/*Leaf Node*/
	if (p->GetLeft() == NULL && p->GetRight() == NULL)
	{
		if (q == NULL) {
			delete root;
			root = NULL;
				return true;
		}

		else if (q->GetLeft() == p) q->SetLeft(NULL);

		else q->SetRight(NULL);

		delete p;

		return true;
	}
	/*오른쪽 자식만 존재할 때*/
	else if (p->GetLeft() == NULL)
	{
		if (q == NULL) {
			root = p->GetRight();
			p->SetRight(NULL);
			delete p;
			return true;
		}
		else if (q->GetLeft() == p) q->SetLeft(p->GetRight);

		else q->SetRight(p->GetRight());

		delete p;

		return true;
	}

	else if (p->GetRight() == NULL)
	{
		if (q == NULL) {
			root = p->GetLeft();
			p->SetLeft(NULL);
			delete p;
			return true;
		}

		else if (q->GetLeft() == p) q->SetLeft(p->GetLeft());

		else q->SetRight(p->GetLeft());

		delete p;

		return true;
	}
	/*Degree 2 Node Delete*/
	Region* prevprev = p;
	Region* prev = p->GetLeft();
	Region* cur = p->GetLeft()->GetRight();

	while (cur)
	{
		prevprev = prev;
		prev = cur;
		cur = cur->GetRight();
	}
	/*Root를 삭제할 때*/
	if (cNode == NULL) {

		if (Prevprev == dNode)
		{
			Prev->SetRight(dNode->GetRight());
			root = Prev;
			delete dNode;
			return true;
		}

		else
		{
			Prevprev->SetRight(Prev->GetLeft());
			Prev->SetLeft(dNode->GetLeft());
			Prev->SetRight(dNode->GetRight());
			root = Prev;

			delete dNode;
			return true;
		}
	}
	/*Node 탐색을 하지 않은 경우, 편향되있을 때*/
	if (Prevprev == dNode)
	{
		if (cNode->GetLeft() == dNode) cNode->SetLeft(Prev);

		else cNode->SetRight(Prev);

		Prev->SetRight(dNode->GetRight());
		delete dNode;
		return true;
	}

	else
	{
		if (cNode->GetLeft() == dNode) cNode->SetLeft(Prev);

		else cNode->SetRight(Prev);

		Prevprev->SetRight(Prev->GetLeft());
		Prev->SetLeft(dNode->GetLeft());
		Prev->SetRight(dNode->GetRight());

		delete dNode;
		return true;
	}

}

Employment* BST::Search(char* region_code)
{
	Region* rNode = root;

	char cpy_arg[60] = { 0 };
	strcpy(cpy_arg, strtok(region_code, " "));

	if (root == NULL) return NULL;
	
	else {
		int OverLap = 0;

		while (rNode)
		{
			if (strcmp(cpy_arg, rNode->GetRegionCode()) > 0)
			{
				rNode = rNode->GetRight();
			}

			else if (strcmp(cpy_arg, rNode->GetRegionCode()) < 0)
			{
				rNode = rNode->GetLeft();
			}

			else if (strcmp(cpy_arg, rNode->GetRegionCode()) == 0)
			{
				OverLap = 1;
				break;
			}
		}
		/*지역코드를 찾지 못한 경우*/
		if (OverLap == 0) return NULL;
		/*지역 코드를 찾은 경우*/
		else {
			Employment* eNode = rNode->GetDown();
			return eNode;
		}
	}
}

void BST::Remove(Region* rNode)
{
	if (rNode == NULL)        //destructing by using recursive 
	{
		return;
	}
	if (rNode->GetRight() != NULL)
	{
		Remove(rNode->GetRight());
	}
	if (rNode->GetLeft() != NULL)
	{
		Remove(rNode->GetLeft());
	}
	rNode->SetLeft(NULL);
	rNode->SetRight(NULL);

	if (rNode != NULL)
	{
		delete rNode;
	}
}