#include "Management.h"
#include <iostream>
using namespace std;
#pragma warning (disable:4996)
#pragma warning (disable:4101)
#define _CRT_SECURE_NO_WARNINGS


Management::Management()
{
	this->m_2DLL = new List_2D();
	this->m_Circular = new List_Circular();
	this->m_BST = new BST();

	//Clear existing out file contents
	ofstream fout1, fout2, fout3;
	fout1.open("OUT_FIND.txt", ios::trunc);
	fout2.open("OUT_DELETE.txt", ios::trunc);
	fout3.open("OUT_PRINT.txt", ios::trunc);
	fout1.close();
	fout2.close();
	fout3.close();
}

Management::~Management()
{
	/* You must fill in here */
	delete m_Circular;
	delete m_2DLL;
	delete m_BST;

}

/* You must fill in the member function definitions of the Management class here */

bool Management::ReadCommand()
{
	ifstream fin;
	fin.open("IN_Command.txt");

	if (!fin) {
		cout << "[OPEN]" << endl << "error" << endl;
		return false;
	}

	char command[64] = { 0 };
	char arg[64] = { 0 };

	bool isWork = true;

	while (!fin.eof())
	{
		fin >> command;
		fin.getline(arg, 64);

		if (!strcmp(command, "LOAD")) { isWork = LOAD(arg); }
		else if (!strcmp(command, "UPDATE")) { isWork = UPDATE(arg); }
		else if (!strcmp(command, "FIND")) { isWork = FIND(arg); }
		else if (!strcmp(command, "DELETE")) { isWork = DELETE(arg); }
		else if (!strcmp(command, "PRINT")) { isWork = PRINT(); }
		else if (!strcmp(command, "EXIT")) { isWork = EXIT(); }
		else { isWork = false; }

		if (isWork == false) {
			cout << "Command Error" << endl << endl;
		}
	}

	fin.close();

	return true;
}

bool Management::LOAD(char* filename)
{
	if (strcmp(filename, " IN_LOAD.txt") != 0) {

		cout << "======== ERROR ========" << endl;
		cout << "100-1" << endl;
		cout << "=======================" << endl;

		return true;
	}

	else {

		char LoadData[128] = { 0 };

		ifstream fin;
		fin.open("IN_LOAD.txt");
	
		fin.getline(LoadData, 128);
		fin.getline(LoadData, 128);
		fin.getline(LoadData, 128);

		while (!fin.eof())
		{
			fin.getline(LoadData, 128);

			char RegionCode[64] = { 0 };
			char RegionName[64] = { 0 };
			char Company[64] = { 0 };
			char Qualification[64] = { 0 };
			char WorkingCondition[64] = { 0 };
			char To[64] = { 0 };

			strcpy(RegionCode, strtok(LoadData, ","));
			strcpy(RegionName, strtok(NULL, ","));
			strcpy(Company, strtok(NULL, ","));
			strcpy(Qualification, strtok(NULL, ","));
			strcpy(WorkingCondition, strtok(NULL, ","));
			strcpy(To, strtok(NULL, ","));

			if (strcmp(To, "E") == 0) {

				if (m_2DLL->rSearch(RegionCode) == NULL) {
					Region* rNode = new Region;
					rNode->SetRegionCode(RegionCode);
					rNode->SetRegionName(RegionName);
					m_2DLL->Insert(rNode);
				}

				if (m_2DLL->ISearch(RegionCode, Company) == true) {

					Employment* mNode = new Employment;

					mNode->SetRegionCode(RegionCode);
					mNode->SetRegionName(RegionName);
					mNode->SetCompany(Company);
					mNode->SetQualification(Qualification);
					mNode->SetWorkingCondition(WorkingCondition);
					mNode->SetTo(To);
					m_2DLL->Insert(mNode);

				}

				else {
					cout << "======== ERROR ========" << endl;
					cout << "100-2" << endl;
					cout << "=======================" << endl;
				}
			}

			else {
				Employment* mNode = new Employment;
				
				mNode->SetRegionCode(RegionCode);
				mNode->SetRegionName(RegionName);
				mNode->SetCompany(Company);
				mNode->SetQualification(Qualification);
				mNode->SetWorkingCondition(WorkingCondition);
				mNode->SetTo(To);
				m_Circular->Insert(mNode);

			}
		}

		Region* rNode = m_2DLL->GetHead();
		m_BST->Insert(rNode);
		rNode = rNode->GetNext();

		if (rNode != NULL) {
			while (rNode)
			{
				m_BST->Insert(rNode);
				rNode = rNode->GetNext();
			}
		}

		cout << "============ LOAD ============" << endl;
		cout << filename << " LOAD Successful" << endl;
		cout << "==============================" << endl;
		cout << endl;
		fin.close();
	}

	
	return true;
}

bool Management::UPDATE(char* filename)
{	
	if (strcmp(filename, " IN_UPDATE.txt") != 0) {

		cout << "======== ERROR ========" << endl;
		cout << "200-1" << endl;
		cout << "=======================" << endl;

		return true;
	}

	else {

		int OverLap = 0;
		ifstream fin;
		fin.open("IN_UPDATE.txt");

		char LoadData[128] = { 0 };
		char region_code[60] = { 0 };
		char region_name[60] = { 0 };
		char company[60] = { 0 };
		char qualification[60] = { 0 };
		char workingcondition[60] = { 0 };
		char to[60] = { 0 };

		fin.getline(LoadData, 128);
		fin.getline(LoadData, 128);
		fin.getline(LoadData, 128);

		while (!fin.eof())
		{
			fin.getline(LoadData, 128);


			strcpy(region_code, strtok(LoadData, ","));
			strcpy(region_name, strtok(NULL, ","));
			strcpy(company, strtok(NULL, ","));
			strcpy(qualification, strtok(NULL, ","));
			strcpy(workingcondition, strtok(NULL, ","));
			strcpy(to, strtok(NULL, ","));

			Employment* eNode = m_2DLL->Search(region_code, company);

			/*2D_List에서 Circular_List로 이동하는 경우*/
			if (strcmp(to, "NE") == 0) {

				if (eNode == NULL) {
					cout << "======== ERROR ========" << endl;
					cout << "200-2" << endl;
					cout << "=======================" << endl;
					cout << endl;
				}

				else OverLap = OverLap + 1;
			}
			/*Circular List에서 2D_List로 Update 하는 경우*/
			else {
				if (m_Circular->Search(region_code, region_name, company, qualification, workingcondition, to) == NULL) {
					cout << "======== ERROR ========" << endl;
					cout << "200-2" << endl;
					cout << "=======================" << endl;
					cout << endl;
				}

				else OverLap = OverLap + 1;
			}
		}

		fin.close();

		if (OverLap == 0) return true;

		/*Update한 정보가 존재한다면*/
		if (OverLap > 0) {

			cout << "======UPDATE - 변경된 채용정보======" << endl;
			cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
			cout << "====================================" << endl;

			fin.open("IN_UPDATE.txt", ios::app);

			char LoadData[128] = { 0 };
			char region_code[60] = { 0 };
			char region_name[60] = { 0 };
			char company[60] = { 0 };
			char qualification[60] = { 0 };
			char workingcondition[60] = { 0 };
			char to[60] = { 0 };

			fin.getline(LoadData, 128);
			fin.getline(LoadData, 128);
			fin.getline(LoadData, 128);

			while (!fin.eof())
			{
				fin.getline(LoadData, 128);

				strcpy(region_code, strtok(LoadData, ","));
				strcpy(region_name, strtok(NULL, ","));
				strcpy(company, strtok(NULL, ","));
				strcpy(qualification, strtok(NULL, ","));
				strcpy(workingcondition, strtok(NULL, ","));
				strcpy(to, strtok(NULL, ","));

				Employment* eNode = m_2DLL->Search(region_code, company);
				Employment* cNode = m_Circular->Search(region_code, region_name, company, qualification, workingcondition, to);

				if (eNode == NULL && cNode == NULL) continue;
				

				/*2D_List에서 Circular_List로 이동하는 경우*/
				if (strcmp(to, "NE") == 0) {

					if (m_2DLL->Search(eNode) != NULL) {

						/*Node가 한개밖에 없을 경우*/
						if (m_BST->Search(eNode->GetRegionCode())->GetDown() == NULL) {

							cout << eNode->GetRegionCode() << "," << eNode->GetRegionName() << "," << eNode->GetCompany() << "," <<
								eNode->GetQualification() << "," << eNode->GetWorkingCondition() << "," << eNode->GetTo() << endl;

							Region* rNode = m_2DLL->rSearch(region_code);
							eNode = m_2DLL->Update(eNode);
							eNode->SetTo("NE");
							m_Circular->Insert(eNode);
							m_2DLL->DelNext(eNode);
							m_BST->Delete(rNode);
							if (m_BST->GetRoot() == NULL) m_2DLL->SetHead(NULL);
						}

						else {
							cout << eNode->GetRegionCode() << "," << eNode->GetRegionName() << "," << eNode->GetCompany() << "," <<
								eNode->GetQualification() << "," << eNode->GetWorkingCondition() << "," << eNode->GetTo() << endl;
				
							eNode = m_2DLL->Update(eNode);
							eNode->SetTo("NE");
							m_Circular->Insert(eNode);
						}

					}
				}
				/*Circular List에서 2D_List로 Update 하는 경우*/
				else {
					if (m_Circular->Search(cNode) != NULL) {

						cout << cNode->GetRegionCode() << "," << cNode->GetRegionName() << "," << cNode->GetCompany() << "," <<
							cNode->GetQualification() << "," << cNode->GetWorkingCondition() << "," << cNode->GetTo() << endl;
						
						eNode = m_Circular->Update(cNode);
						eNode->SetTo("E");

						if (m_2DLL->GetHead() == NULL) {
							Region* rNode = new Region;
							rNode->SetRegionCode(eNode->GetRegionCode());
							rNode->SetRegionName(eNode->GetRegionName());
							m_2DLL->SetHead(rNode);
							m_2DLL->Insert(cNode);
							m_BST->Insert(rNode);

							rNode = NULL;
							delete rNode;
						}
						else {
							Region* rNode = new Region;
							rNode->SetRegionCode(cNode->GetRegionCode());
							rNode->SetRegionName(cNode->GetRegionName());
							m_2DLL->Insert(rNode);
							m_2DLL->Insert(cNode);
							m_BST->Insert(rNode);

							rNode = NULL;
							delete rNode;
						}
					}
				}
			}
			fin.close();
		}
		cout << endl;

	}
	return true;
}

bool Management::FIND(char* region_code)
{	
	if (m_BST->Search(region_code) == NULL) {
		cout << "======== ERROR ========" << endl;
		cout << "300-1" << endl;
		cout << "=======================" << endl;
	}
	
	else {
		
		cout << "====FIND - " << region_code << " 지역의 채용중인 기업====" << endl;
		cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
		cout << "=========================================================" << endl;

		Employment* eNode = m_BST->Search(region_code);

		while (1)
		{
			cout << eNode->GetRegionCode() << " " << eNode->GetRegionName() << " " << eNode->GetCompany() << " " << 
				eNode->GetQualification() << " " << eNode->GetWorkingCondition() << " " << eNode->GetTo() << endl;

			if (eNode->GetDown() == NULL) break;

			eNode = eNode->GetDown();
		}
	}

	cout << endl;

	return true;
}

bool Management::DELETE(char* region_code)
{	
	int EOverLap = 0;
	int NEOverLap = 0;
	int len = strlen(region_code);

	Employment* eNode = m_Circular->GetHead();
	Region* rNode = m_BST->GetRoot();

	for (int i = 0; i < len; i++) {
		region_code[i] = region_code[i + 1];
	}

	
	while (1)
	{	
		if (eNode->GetRegionCode() == NULL) break;

		if (strcmp(eNode->GetRegionCode(), region_code) == 0) {
			NEOverLap = NEOverLap + 1;
			break;
		}

		if (eNode->GetNext() == m_Circular->GetHead()) break;

		eNode = eNode->GetNext();
	}

	while (1)
	{	
		if (rNode->GetRegionCode() == NULL) break;

		if (strcmp(rNode->GetRegionCode(), region_code) == 0) {
			EOverLap = EOverLap + 1;
			break;
		}

		if (rNode->GetNext() == NULL) break;

		rNode = rNode->GetNext();
	}
	/*삭제하려는 정보가 존재하지 않을 때*/
	if ((EOverLap == 0) && (NEOverLap == 0)) {
			cout << "======== ERROR ========" << endl;
			cout << "400-1" << endl;
			cout << "=======================" << endl;
			cout << endl;
	}
	else {
		/*삭제하려는 정보가 채용중이지 않은 곳에만 존재할 때*/
		if ((EOverLap == 0) && (NEOverLap == 1))
		{	
			cout << "====DELETE -" << region_code << "  지역의 삭제된 채용마감 기업====" << endl;
			cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
			cout << "================================================" << endl;
			

			Employment* eNode = m_Circular->Search(region_code);
			Employment* Temp = NULL;

			while (1) {
				Temp = m_Circular->Delete(eNode);
				if (Temp == NULL) break;
				cout << Temp->GetRegionCode() << "," << Temp->GetRegionName() << "," << Temp->GetCompany() << "," <<
					Temp->GetQualification() << "," << Temp->GetWorkingCondition() << "," << Temp->GetTo() << endl;
				delete Temp;
			}
			cout << endl;
		}

		else if ((EOverLap == 1) && (NEOverLap == 0))
		{	
			cout << "====DELETE -" << region_code << "  지역의 삭제된 채용중인 기업====" << endl;
			cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
			cout << "================================================" << endl;

			Employment* eNode = m_2DLL->Search(region_code);
			Region* rNode = m_2DLL->rSearch(region_code);

			while (1) {
				m_2DLL->Delete(eNode);
				if (m_2DLL->Delete(eNode) == NULL) break;
			}
			m_2DLL->DelNext(eNode);
			m_BST->Delete(rNode);
			cout << endl;
		}

		else if ((EOverLap == 1) && (NEOverLap == 1))
		{	
			cout << "====DELETE -" << region_code << "  지역의 삭제된 채용중인 기업====" << endl;
			cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
			cout << "================================================" << endl;

			Region* rNode = m_2DLL->rSearch(region_code);

			while (1) {
				eNode = m_2DLL->Search(region_code);
				if (eNode == NULL) break;
				if (m_2DLL->Delete(eNode) == false) break;
			}
			Region* rTemp = m_2DLL->rSearch(region_code);
			m_2DLL->DelNext(rTemp);
			m_BST->Delete(rNode);
			cout << endl;

			cout << "====DELETE -" << region_code << "  지역의 삭제된 채용마감 기업====" << endl;
			cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
			cout << "================================================" << endl;

			Employment* eNode = m_Circular->Search(region_code);
			Employment* Temp = NULL;

			while (1) {
				eNode = m_Circular->Search(region_code);
				if (eNode == NULL) break;
				Temp = m_Circular->Delete(eNode);
				if (Temp == NULL) break;
				cout << Temp->GetRegionCode() << "," << Temp->GetRegionName() << "," << Temp->GetCompany() << "," <<
					Temp->GetQualification() << "," << Temp->GetWorkingCondition() << "," << Temp->GetTo() << endl;
				delete Temp;
			}

			cout << endl;
		}
	}
	return true;
}

bool Management::PRINT()
{	
	if (m_BST->GetRoot() == NULL) {

		ofstream fout;
		fout.open("OUT_PRINT.txt");

		fout << "======== ERROR ========" << endl;
		fout << "500-1" << endl;
		fout << "=======================";

		cout << "======== ERROR ========" << endl;
		cout << "500-1" << endl;
		cout << "=======================" << endl;

		fout.close();

		return true;
	}

	else {

		ofstream fout;
		fout.open("OUT_PRINT.txt", ios::app);

		fout << "=====OUT_PRINT - 모든 지역의 채용중인 기업=====" << endl;
		fout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
		fout << "===============================================" << endl;

		cout << "=====OUT_PRINT - 모든 지역의 채용중인 기업=====" << endl;
		cout << "지역코드,지역명,기업명,지원자격,근무조건,TO" << endl;
		cout << "===============================================" << endl;

		stack<Region *>stack;
		Region* rNode = m_BST->GetRoot();

		while (1)
		{
			while (rNode != NULL)
			{
				stack.push(rNode);
				rNode = rNode->GetLeft();
			}

			if (stack.size() != 0)
			{
				rNode = stack.top();
				stack.pop();
			}

			if (rNode == NULL) break;

			else {

				Employment* eNode = rNode->GetDown();

				while (eNode) {

					fout << eNode->GetRegionCode() << "," << eNode->GetRegionName() << "," <<
						eNode->GetCompany() << "," << eNode->GetQualification() << "," <<
						eNode->GetWorkingCondition() << "," << eNode->GetTo() << endl;

					cout << eNode->GetRegionCode() << "," << eNode->GetRegionName() << "," <<
						eNode->GetCompany() << "," << eNode->GetQualification() << "," <<
						eNode->GetWorkingCondition() << "," << eNode->GetTo() << endl;

					eNode = eNode->GetDown();

				}
				rNode = rNode->GetRight();
			}
		}

		fout.close();
	}
	cout << endl;

	return true;
}

bool Management::EXIT()
{
	return true;
}