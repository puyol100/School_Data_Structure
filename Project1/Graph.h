#include "AVLTree.h"
#include <iostream>
#include <fstream>// header file declare
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
struct edge {
	int  weight, src, dest;//for edge set
};
class Graph
{
public:
	multimap<int,CityData *> * mList;	// mList[from vetex] = map<to vertex, weigth>
	CityData * * vertex;			// vetex[index] = CityData * 
	int size;					// AVLTree size
	int * mstMatrix;			// MST
	int count = 0;
	int sum_mst = 0;
	int start_index = 0;
	vector<edge> v;	//for alll of edge set
	vector<edge> mst_set;//for mst edge set
	ofstream * flog;
public:
	Graph(ofstream * flog);
	~Graph();

	bool	Build(AVLTree * root);
	void 	Print_GP();
	void	Make_mList();
	void	Print_MST();
	void	Make_vertex(AVLNode* node);//make vertex 
	void    Counting_size(AVLNode* node);//counting the avl tree
	/*for Kruskal union_set*/
	bool	Kruskal();
	void 	make_set();
	bool 	union_set(int x, int y);
	int		find(int x);
	void	print_mst_info(int index,int flag);
	
};


