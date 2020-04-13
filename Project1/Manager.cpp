#include "Manager.h"
#include <stdlib.h>
#include <fstream>
using namespace std;
Manager::Manager()//constructor of Manage class
{
	flog.open("log.txt", ios::app);//open log file
	flog.setf(ios::fixed);

	avl = new AVLTree(&flog);//for avl
	gp = new Graph(&flog);//for graph
	iter = 0;
	cmd = NULL;
}

Manager::~Manager()
{
	flog.close();
}

void Manager::run(const char * command)
{
	fin.open(command);

	cmd = new char[40];


	while (!fin.eof())
	{
		iter = iter + 1;
		fin.getline(cmd, 40);//read line of file
		char * one = strtok(cmd, " ");//token by " "
		if (!strcmp(one, "LOAD")) {//command == load
			//call function()
			//example. ( you have to change )
			if (LOAD()) printSuccessCode("LOAD");
			else printErrorCode(100, "LOAD");//error
		}
		else if (!strcmp(one, "INSERT")) {//command == insert
			//call function());
			char *distance = strtok(NULL," ");//get distance info
			char *City = strtok(NULL," ");//get City name info
			char *Country = strtok(NULL, ")");//get Country name info
			/*
			flog << "==> command " << iter << ") " << "SEARCH_AVL" << endl;
			if (SEARCH_AVL(atoi(two)) == false) flog << "Error code: " << 500 << endl;
			*/
			flog << "==> command " << iter << ") " << "INSERT" << endl;
			if (INSERT(distance, City, Country) == false) flog << "Error code: " << 200 << endl;//error
		}
		else if (!strcmp(one, "PRINT_AVL")) {//command == PRIN_AVL
			//call function()
			flog << "==> command " << iter << ") " << "PRINT_AVL" << endl;
			if(PRINT_AVL()== false) flog << "Error code: " << 300 << endl;
		}
		else if (!strcmp(one, "SEARCH_AVL")) {//command == SEARCH_AVL
			char* two = strtok(NULL, "\0");//get info
			//call function()
			flog << "==> command " << iter << ") " << "SEARCH_AVL" << endl;
			if (SEARCH_AVL(atoi(two)) == false) flog << "Error code: " << 500 << endl;
		}
		else if (!strcmp(one, "DELETE_AVL")) {//command == DELETE_AVL
			char* two = strtok(NULL, "\0");//get info
			//call function()
			if (two != NULL && DELETE_AVL(atoi(two))) printSuccessCode("DELETE_AVL");
			else printErrorCode(400, "DELETE_AVL");//error
		}
		else if (!strcmp(one, "BUILD_GP")) {//command == BUILD_GP
			//call function()
			if (BUILD_GP()) printSuccessCode("BUILD_GP");
			else printErrorCode(600, "BUILD_GP");//error
		}
		else if (!strcmp(one, "PRINT_GP")) {//command == Print_gp
			//call function()
			flog << "==> command " << iter << ") " << "PRINT_GP" << endl;
			if (PRINT_GP() == false) flog << "Error code: " << 700 << endl;//error code
		}
		else if (!strcmp(one, "BUILD_MST")) {//command == BUILD_MST
			//call function()
			if (BUILD_MST()) printSuccessCode("BUILD_MST");
			else printErrorCode(800, "BUILD_MST");//error
		}
		else if (!strcmp(one, "PRINT_MST")) {//command == PRINT_MST
			//call function()
			flog << "==> command " << iter << ") " << "PRINT_MST" << endl;
			if (PRINT_MST() == false) flog << "Error code: " << 900 << endl;//error code
		}		
		else if (!strcmp(one, "EXIT")) {
			//call function()
			EXIT();	
		}
		else {
			printErrorCode(0,"Unknown");
		}
	}
	fin.close();
	return;
}

bool Manager::LOAD()
{
	ifstream l_fin;
	l_fin.open("city_list.txt");
	if (!l_fin.is_open()) return false;//no file case
	if (avl->Getroot() != NULL) return false;//already avl exist
	l_fin.seekg(0, ios::end);
	if (l_fin.tellg() == 0) return false;//there is file but no contents
	l_fin.seekg(0, ios::beg);
	char* city_name;
	char* city_country;
	char* city_location;
	while (!l_fin.eof())
	{
		char* city_info = new char[60];
		l_fin.getline(city_info, 60);//get city info
		city_location = strtok(city_info, "\t");//get location
		city_name = strtok(NULL,"\t");//get name
		city_country = strtok(NULL, "\0");//get coutry
		CityData* new_city_data = new CityData();
		new_city_data->SetLocationId(atoi(city_location));
		new_city_data->Setcountry(city_country);
		new_city_data->Setname(city_name);//set city data
		AVLNode* new_node = new AVLNode();
		new_node->SetCityData(new_city_data);//add new_city_data node
		if (avl->root == NULL)
		{
			avl->Setroot(new_node);//first time of avl setting
		}
		else
		{
			avl->Insert(new_node);//avl setting
		}
	}
	return true;
}

bool Manager::INSERT(char*dis, char*city, char* country)
{
	if (avl->Getroot() == NULL) return false;//if there is no avl 
	CityData* new_city_data = new CityData();
	char* city_dis = new char[strlen(dis)];//get distance info
	char* city_city = new char[strlen(city)];//get city info
	char* city_country = new char[strlen(country)];//get coutry info
	strcpy(city_dis, dis);
	strcpy(city_city, city);
	strcpy(city_country, country);

	new_city_data->SetLocationId(atoi(city_dis));
	new_city_data->Setcountry(city_country);
	new_city_data->Setname(city_city);//set city data
	AVLNode* new_node = new AVLNode();
	new_node->SetCityData(new_city_data);//set new node
	if (avl->Insert(new_node) == false)//insert  new node to avl
	{
		return false;
	}
	flog << '(' <<dis<< ", " <<city << ", " <<country << ')' << endl;
	return true;
}

bool Manager::PRINT_AVL()
{
	if (avl->Getroot() == NULL)//if there is no avl 
	{
		return false;
	}
	if (avl->Print() == false)//print
	{
		return false;
	}
	return true;
	
}

bool Manager::SEARCH_AVL(int num)
{
	if (num > 9999 || num < 1000) return false;//range 1000 to 9999
	AVLNode* result = avl->Search(num);//call avl search function
	if (result == NULL)//if there is no data
	{
		return false;
	}
	flog << '(' << result->GetCityData()->GetLocationId() << ", " << result->GetCityData()->Getname() << ", " << result->GetCityData()->Getcountry() << ')' << endl;
	return true;
}

bool Manager::DELETE_AVL(int num)
{
	if (avl->Getroot() == NULL) return false;//if there is no avl
	if (avl->Delete(num) == false)//delete
	{
		return false;
	}
	return true;
}

bool Manager::BUILD_GP()
{
	if (avl->Getroot() == NULL) return false;//if there is no avl
	if (gp->Build(avl)) return true;//Build gp
	return false;
}

bool Manager::PRINT_GP()
{
	if (gp->mList == NULL) return false;//if there is no gp
	gp->Print_GP();//Print gp
	return true;
}

bool Manager::BUILD_MST()
{
	if (gp->mList == NULL) return false;//if there is no gp
	if (gp->Kruskal() == false)//Build mst
	{
		return false;
	}
	return true;
}

bool Manager::PRINT_MST()
{
	if (gp->mstMatrix == NULL) return false;//if there is no gp
	gp->Print_MST();//print mst
	return true;
}

void Manager::EXIT()
{
	flog << "==> command " << iter << ") " << "EXIT" << endl;
	flog << "Success" << endl;
	exit(1);
}

void Manager::printErrorCode(int n, const char * cmdname) {//ERROR CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Error code: " << n << endl;
}

void Manager::printSuccessCode(const char * cmdname) {//SUCCESS CODE PRINNT FUNCTION
	flog << "==> command " << iter << ") " << cmdname << endl;
	flog << "Success" << endl;
}
