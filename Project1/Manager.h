#include "Graph.h"
#include<utility>
#include<iostream>
#include<fstream>
#include<string.h>

using namespace std;

class Manager
{
public:
	AVLTree * avl;//for avl
	Graph * gp;//for graph

	char * cmd;
	int iter;

public:
	Manager();
	~Manager();

	ofstream flog;
	ifstream fin;

	void run(const char * command);//run
	bool LOAD();
	bool INSERT(char* dis, char* city, char* country);
	bool PRINT_AVL();
	bool SEARCH_AVL(int num);
	bool DELETE_AVL(int num);
	bool BUILD_GP();
	bool PRINT_GP();
	bool BUILD_MST();
	bool PRINT_MST();
	void EXIT();
	//command function
	void printErrorCode(int n, const char * cmdname);
	void printSuccessCode(const char * cmdname);

};
