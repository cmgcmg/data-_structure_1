#include "List_Circular.h"
using namespace std;

List_Circular::List_Circular()
{
	this->pHead = NULL;
}


List_Circular::~List_Circular()
{
	/* You must fill in here */
	if (pHead != NULL) {

		
		if (pHead->GetNext() == pHead) {
			pHead->SetNext(NULL);
			delete pHead;
		}
		
		else {
				while (1)
				{	
					Employment* Prevprev = pHead;
					Employment* Prev = pHead->GetNext();

					if (Prevprev == Prev) {
						pHead->SetNext(NULL);
						delete pHead;
						break;
					}

					else  {
						while (1)
						{
							if (Prev->GetNext() == pHead) break;
							Prevprev = Prevprev->GetNext();
							Prev = Prev->GetNext();
						}

						Prev->SetNext(NULL);
						Prevprev->SetNext(pHead);
						delete Prev;
					}
				}
			}
		}
}

/* You must fill in the member function definitions of the List_Circular class here */
void List_Circular::SetHead(Employment* pNode)
{
	this->pHead = pNode;
	pHead->SetNext(pHead);
}

Employment* List_Circular::GetHead()
{
	return pHead;
}

void List_Circular::Insert(Employment* pNode)
{
	
	if (pHead == NULL) {
		pHead = pNode;
		pHead->SetNext(pHead);
		return;

	}
	if (pHead->GetNext() == pHead) {
		pHead->SetNext(pNode);
		pNode->SetNext(pHead);
		return;
	}

	
	else {
		Employment* temp;
		temp = pHead;

		while (1) {

			if (temp->GetNext() == pHead) break;
			
			temp = temp->GetNext();
		}
		
		temp->SetNext(NULL);
		temp->SetNext(pNode);
		pNode->SetNext(pHead);
	}
}

void List_Circular::Print()
{
	Employment* temp;
	temp = pHead;

	while (1)
	{
		cout << temp->GetRegionCode() << " - " << temp->GetRegionName() << " - " << temp->GetCompany() << " - "  << endl;
		if (temp->GetNext() == pHead) break;
		temp = temp->GetNext();
	}

	return;
}

Employment* List_Circular::Search(Employment* pNode)
{	
	if (pHead == NULL) return NULL;

	Employment* eTemp = pHead;
	int OverLap = 0;

	while (1)
	{
		if ((strcmp(eTemp->GetRegionCode(), pNode->GetRegionCode()) == 0) &&
			(strcmp(eTemp->GetRegionName(), pNode->GetRegionName()) == 0) &&
			(strcmp(eTemp->GetCompany(), pNode->GetCompany()) == 0) &&
			(strcmp(eTemp->GetQualification(), pNode->GetQualification()) == 0) &&
			(strcmp(eTemp->GetWorkingCondition(), pNode->GetWorkingCondition()) == 0)) {
			
			OverLap = 1;
			return eTemp;
		}

		if (eTemp->GetNext() == pHead) break;
		eTemp = eTemp->GetNext();
	}

	if (OverLap == 0) return NULL;

	return NULL;
}

Employment* List_Circular::Update(Employment* pNode)
{
	Employment* eTemp = pHead;
	Employment* PrevTemp = NULL;

	while (1)
	{
		if ((strcmp(eTemp->GetRegionCode(), pNode->GetRegionCode()) == 0) &&
			(strcmp(eTemp->GetRegionName(), pNode->GetRegionName()) == 0) &&
			(strcmp(eTemp->GetCompany(), pNode->GetCompany()) == 0) &&
			(strcmp(eTemp->GetQualification(), pNode->GetQualification()) == 0) &&
			(strcmp(eTemp->GetWorkingCondition(), pNode->GetWorkingCondition()) == 0)) {

			/*Head 정보를 Update하고 Head 다음 Node가 존재하지 않을 때*/
			if (eTemp == pHead && eTemp->GetNext() == pHead) {
				/*Delete해줘야함 아무런 Node가 존재하지 않기 떄문에*/
				eTemp->SetNext(NULL);
				pHead = NULL;
				return eTemp;
			}

			/*Head의 정보를 수정하는데 다음 Node가 존재할 경우*/
			else if (eTemp == pHead && eTemp->GetNext() != pHead)
			{
				Employment* cNode = NULL;

				while (1)
				{
					if (eTemp->GetNext() == pHead) break;
					eTemp = eTemp->GetNext();
				}
				
				eTemp->SetNext(pHead->GetNext());
				cNode = pHead;
				pHead = cNode->GetNext();
				cNode->SetNext(NULL);
				return cNode;
			}
			/*Head의 정보를 수정하지 않을 경우*/
			else if(eTemp != pHead)
			{		
				/*Circular List 맨 마지막 정보를 Update하는 경우*/
				if (eTemp->GetNext() == pHead) {
					PrevTemp->SetNext(pHead);
					return eTemp;
				}
				/*Circular List 중간의 Node 정보를 Update하는 경우*/
				else {
					PrevTemp->SetNext(eTemp->GetNext());
					eTemp->SetNext(NULL);
					return eTemp;
				}
			}
		}

		if (eTemp->GetNext() == pHead) break;
		
		else {
			PrevTemp = eTemp;
			eTemp = eTemp->GetNext();
		}
	}

	return NULL;
}

Employment* List_Circular::Delete(Employment* pNode)
{	
	Employment* eTemp = pHead;
	Employment* PrevTemp = NULL;

	while (1)
	{
		if (strcmp(eTemp->GetRegionCode(), pNode->GetRegionCode()) == 0)
		{
			/*Head 정보 수정*/
			if (eTemp == pHead && eTemp->GetNext() == pHead)
			{
				eTemp->SetNext(NULL);
				return eTemp;
			}

			else if (eTemp == pHead && eTemp->GetNext() != pHead)
			{
				Employment* tNode = eTemp;

				while (1)
				{
					if (tNode->GetNext() == pHead) break;
					tNode = tNode->GetNext();
				}

				tNode->SetNext(eTemp->GetNext());
				pHead = eTemp->GetNext();
				eTemp->SetNext(NULL);
				return eTemp;
			}

			else if (eTemp != pHead && eTemp->GetNext() == pHead)
			{
				eTemp->SetNext(NULL);
				PrevTemp->SetNext(pHead);
				return eTemp;
			}

			else if (eTemp != pHead && eTemp->GetNext() != pHead)
			{
				PrevTemp->SetNext(eTemp->GetNext());
				eTemp->SetNext(NULL);
				return eTemp;
			}
		}

		if (eTemp->GetNext() == pHead) break;

		PrevTemp = eTemp;
		eTemp = eTemp->GetNext();

	}

	return NULL;
}

Employment* List_Circular::Search(char* region_code, char* region_name, char* company, char* qualification, char* workingcondition, char* to)
{
	if (pHead == NULL) return NULL;

	Employment* eTemp = pHead;
	int OverLap = 0;

	while (1)
	{
		if ((strcmp(eTemp->GetRegionCode(), region_code) == 0) &&
			(strcmp(eTemp->GetRegionName(), region_name) == 0) &&
			(strcmp(eTemp->GetCompany(), company) == 0) &&
			(strcmp(eTemp->GetQualification(), qualification) == 0) &&
			(strcmp(eTemp->GetWorkingCondition(), workingcondition) == 0)) {

			OverLap = 1;
			return eTemp;
		}

		if (eTemp->GetNext() == pHead) break;
		eTemp = eTemp->GetNext();
	}

	if (OverLap == 0) return NULL;

	return NULL;
}

Employment* List_Circular::Search(char* region_code)
{
	if (pHead == NULL) return NULL;

	Employment* eTemp = pHead;

	int OverLap = 0;

	while (1)
	{
		if (strcmp(eTemp->GetRegionCode(), region_code) == 0) {

			OverLap = 1;
			return eTemp;
		}

		if (eTemp->GetNext() == pHead) break;
		eTemp = eTemp->GetNext();
	}

	if (OverLap == 0) return NULL;

	return NULL;
}

