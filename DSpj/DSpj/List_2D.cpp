#include "List_2D.h"

List_2D::List_2D()
{
	this->pHead = NULL;
}


List_2D::~List_2D()
{
	/* You must fill in here */
	if (pHead != NULL) {

		Region* rTemp = pHead;
		Employment* eNode;

		while (1)
		{	
			eNode = rTemp->GetDown();

			while (1)
			{
				if (eNode->GetDown() == NULL) {
					delete eNode;
					break;
				}

				else {
					eNode = eNode->GetDown();
				}
			}
			if (rTemp->GetNext() == NULL) break;
			rTemp = rTemp->GetNext();
		}
	}
	
}

/* You must fill in the member function definitions of the List_2D class here */

Region* List_2D::GetRegion(Region* rNode)
{
	Region* rTemp = rNode->GetNext();
	return rTemp;
}
void List_2D::SetHead(Region* pNode)
{
	pHead = pNode;
}

Region* List_2D::GetHead()
{
	return pHead;
}

void List_2D::Insert(Region* pNode)
{	
	if (pHead == NULL) {
		SetHead(pNode);
	}

	Region* temp = pHead;

	while (1)
	{
		if (strcmp(pNode->GetRegionCode(), temp->GetRegionCode()) == 0) {
			pNode = NULL;
			delete pNode;
			return;
		}

		if (temp->GetNext() == NULL) break;
		temp = temp->GetNext();
	}
		temp->SetNext(pNode);
		return;
}

void List_2D::Insert(Employment* pNode)
{	
	
	Region* rNode = pHead;

	while (1)
	{
		if (strcmp(rNode->GetRegionCode(), pNode->GetRegionCode()) == 0) break;

		rNode = rNode->GetNext();
	}
	
	if (rNode->GetDown() == NULL) {
		rNode->SetDown(pNode);
		return;
	}
	
	else {
		Employment* eNode = rNode->GetDown();

		
		while (1)
		{
			if (eNode->GetDown() == NULL) break;
			eNode = eNode->GetDown();
		}

		eNode = rNode->GetDown();
		
		if (strcmp(eNode->GetCompany(), pNode->GetCompany()) > 0)
		{
			rNode->SetDown(pNode);
			pNode->SetDown(eNode);
			return;
		}
		else {
			while (1)
			{
				if (eNode->GetDown() == NULL) {
					eNode->SetDown(pNode);
					return;
				}

				if (strcmp(pNode->GetCompany(), eNode->GetDown()->GetCompany()) > 0)
				{
					eNode = eNode->GetDown();
				}

				else {
					pNode->SetDown(eNode->GetDown());
					eNode->SetDown(pNode);
					return;
				}
			}
		}
	}
	return;
}

bool List_2D::Delete(Employment* pNode)
{	
	Region* rTemp = NULL;
	Region* Prev = NULL;
	Employment* eTemp = NULL;

	rTemp = pHead;

	while (1)
	{
		if (strcmp(rTemp->GetRegionCode(), pNode->GetRegionCode()) == 0) {
			break;
		}
		
		Prev = rTemp;
		rTemp = rTemp->GetNext();
	}

	if(rTemp->GetDown() == NULL) return false;

	eTemp = rTemp->GetDown();

	while (1)
	{
		if (eTemp->GetDown() != NULL) {
			rTemp->SetDown(eTemp->GetDown());
			cout << eTemp->GetRegionCode() << "," << eTemp->GetRegionName() << "," << eTemp->GetCompany() << "," <<
				eTemp->GetQualification() << "," << eTemp->GetWorkingCondition() << "," << eTemp->GetTo() << endl;
			delete eTemp;
			return true;
		}
		
		if (eTemp->GetDown() == NULL) {
			rTemp->SetDown(NULL);
			cout << eTemp->GetRegionCode() << "," << eTemp->GetRegionName() << "," << eTemp->GetCompany() << "," <<
				eTemp->GetQualification() << "," << eTemp->GetWorkingCondition() << "," << eTemp->GetTo() << endl;
			delete eTemp;
			return true;
		}
	}
	
}

Employment* List_2D::Search(Employment* pNode)
{	
	int rOverLap = 0;
	int OverLap = 0;

	Region* rTemp = pHead;
	Employment* eTemp = NULL;

	while (1) {
		if (strcmp(rTemp->GetRegionCode(), pNode->GetRegionCode()) == 0) {
			rOverLap = 1;
			break;
		}
		if (rTemp->GetNext() == NULL) break;
		rTemp = rTemp->GetNext();
	}

	if (rOverLap == 1) {
		eTemp = rTemp->GetDown();
		while (1)
		{
			if (strcmp(eTemp->GetCompany(), pNode->GetCompany()) == 0) {
				OverLap = 1;
				break;
			}

			if (eTemp->GetDown() == NULL) break;
			eTemp = eTemp->GetDown();
		}
	}

	else return NULL;

	if (OverLap == 0) return NULL;

	else return eTemp;

}

Employment* List_2D::Update(Employment* pNode)
{

	Region* rTemp = pHead;
	Employment* eTemp = NULL;

	/*Update 하려는 Node가 Region Node 바로 밑에 있을 때*/
	/*Region Node를 Next()하면서 Region Node 밑에 부분만 비교한다.*/
	while (1) {
		if ((strcmp(rTemp->GetDown()->GetRegionCode(), pNode->GetRegionCode()) == 0) &&
			(strcmp(rTemp->GetDown()->GetRegionName(), pNode->GetRegionName()) == 0) &&
			(strcmp(rTemp->GetDown()->GetCompany(), pNode->GetCompany()) == 0)) {

			eTemp = rTemp->GetDown();

			if (eTemp->GetDown() != NULL) {
				rTemp->SetDown(eTemp->GetDown());
				return eTemp;
			}
			/*Region Node아래 Empoloyment Node가 한개만 존재할 때*/
			else {
				rTemp->SetDown(NULL);
				return eTemp;
			}
		}
		if (rTemp->GetNext() == NULL) break;
		rTemp = rTemp->GetNext();
	}

	rTemp = pHead;

	/*Update하려는 Node가 Region Node 바로 밑에 있지 않은 경우*/
	while (1)
	{
		eTemp = rTemp->GetDown();

		while (1)
		{
			if (eTemp->GetDown() == NULL) break;

			if ((strcmp(eTemp->GetDown()->GetRegionCode(), pNode->GetRegionCode()) == 0) &&
				(strcmp(eTemp->GetDown()->GetRegionName(), pNode->GetRegionName()) == 0) &&
				(strcmp(eTemp->GetDown()->GetCompany(), pNode->GetCompany()) == 0)) {

				if (eTemp->GetDown()->GetDown() == NULL) {
					Employment* cNode = eTemp->GetDown();
					eTemp->SetDown(NULL);
					return cNode;
				}

				else {
					Employment* cNode = eTemp->GetDown();
					eTemp->SetDown(eTemp->GetDown()->GetDown());
					return cNode;

				}

			}

			if (eTemp->GetDown() == NULL) break;
			eTemp = eTemp->GetDown();
		}

		rTemp = rTemp->GetNext();
	}
}

void List_2D::DelNext(Employment* pNode)
{
	Region* rTemp = NULL;
	Region* Prev = NULL;

	rTemp = pHead;

	while (1)
	{
		if (strcmp(rTemp->GetRegionCode(), pNode->GetRegionCode()) == 0) {
			break;
		}

		Prev = rTemp;
		rTemp = rTemp->GetNext();
	}

	if (rTemp == pHead && rTemp->GetNext() != NULL) {
		pHead = rTemp->GetNext();
		return;
	}

	if (rTemp->GetNext() == NULL) {
		Prev->SetNext(NULL);
		return;
	}

	else {
		Prev->SetNext(rTemp->GetNext());
		rTemp->SetNext(NULL);
	}

	return;
}

Employment* List_2D::Search(char* region_code, char* company)
{		
	if (pHead == NULL) return NULL;

	else {
		int rOverLap = 0;
		int eOverLap = 0;

		Region* rTemp = pHead;

		while (1)
		{
			if (strcmp(region_code, rTemp->GetRegionCode()) == 0) {
				rOverLap = 1;
				break;
			}

			if (rTemp->GetNext() == NULL) break;

			rTemp = rTemp->GetNext();
		}

		if (rOverLap == 0) return NULL;

		else {
			Employment* eTemp = rTemp->GetDown();

			while (1)
			{
				if (strcmp(eTemp->GetCompany(), company) == 0) {
					eOverLap = 1;
					break;
				}
				if (eTemp->GetDown() == NULL) break;

				eTemp = eTemp->GetDown();
			}

			if (eOverLap == 1) return eTemp;

			else return NULL;
		}
	}

}

Employment* List_2D::Search(char* region_code)
{
	if (pHead == NULL) return NULL;

	else {
		int rOverLap = 0;
		int eOverLap = 0;

		Region* rTemp = pHead;

		while (1)
		{
			if (strcmp(region_code, rTemp->GetRegionCode()) == 0) {
				rOverLap = 1;
				break;
			}

			if (rTemp->GetNext() == NULL) break;

			rTemp = rTemp->GetNext();
		}

		if (rOverLap == 0) return NULL;

		else {
			return rTemp->GetDown();
		}
	}
}

Region* List_2D::rSearch(char* region_code)
{
	if (pHead == NULL) return NULL;

	else {
		int rOverLap = 0;
		int eOverLap = 0;

		Region* rTemp = pHead;

		while (1)
		{
			if (strcmp(region_code, rTemp->GetRegionCode()) == 0) {
				rOverLap = 1;
				break;
			}

			if (rTemp->GetNext() == NULL) break;

			rTemp = rTemp->GetNext();
		}

		if (rOverLap == 0) return NULL;

		else return rTemp;
	}
}

void List_2D::DelNext(Region* pNode)
{
	Region* rTemp = NULL;
	Region* Prev = NULL;

	rTemp = pHead;

	while (1)
	{
		if (strcmp(rTemp->GetRegionCode(), pNode->GetRegionCode()) == 0) {
			break;
		}

		Prev = rTemp;
		rTemp = rTemp->GetNext();
	}

	if (rTemp == pHead && rTemp->GetNext() != NULL) {
		pHead = rTemp->GetNext();
		return;
	}

	if (rTemp->GetNext() == NULL) {
		Prev->SetNext(NULL);
		return;
	}

	else {
		Prev->SetNext(rTemp->GetNext());
		rTemp->SetNext(NULL);
	}

	return;
}

bool List_2D::ISearch(char* Region_Code, char* company)
{
	if (pHead == NULL) return false;

	else {
		int rOverLap = 0;
		int eOverLap = 0;

		Region* rTemp = pHead;

		while (1)
		{
			if (strcmp(Region_Code, rTemp->GetRegionCode()) == 0) {
				rOverLap = 1;
				break;
			}

			if (rTemp->GetNext() == NULL) break;

			rTemp = rTemp->GetNext();
		}

		if (rTemp->GetDown() == NULL) return true;

		else {
			Employment* eTemp = rTemp->GetDown();

			while (eTemp) {
				if (strcmp(eTemp->GetCompany(), company) == 0) return false;
				eTemp = eTemp->GetDown();
			}
			return true;
		}
	}

}