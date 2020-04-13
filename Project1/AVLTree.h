#include "AVLNode.h"
#include <iostream>
#include <fstream>// header file declare
using namespace std;
class AVLTree
{
public:
	AVLNode * root;	// AVLTree Root
	ofstream * flog;
	AVLNode* Searched_Node = NULL;//for searching
	AVLNode* pa = NULL;
public:
	AVLTree(ofstream * flog);
	~AVLTree();

	AVLNode  *  Getroot();//get root info
	void	 	Setroot(AVLNode * node);//set root
	bool		Insert(AVLNode* node);
	bool	Delete(int num);
	AVLNode *	Search(int num);
	int get_height(AVLNode* node);//get height each node
	void update_bf(AVLNode* node);//update bf 
	void Visit(AVLNode* node);
	void Inorder(AVLNode* node);
	void make_balance(AVLNode* node);//make balance
	AVLNode* Inorder_search(int num, AVLNode* node);//for searching
	bool Print();

};

