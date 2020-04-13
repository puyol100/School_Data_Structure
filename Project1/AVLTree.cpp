#include "AVLTree.h"

AVLTree::AVLTree(ofstream * flog)
{
	this->flog = flog;
	root = NULL;
}

AVLTree::~AVLTree()
{
}

AVLNode * AVLTree::Getroot()
{
	return root;//get avl tree root
}

void AVLTree::Setroot(AVLNode * node)
{
	node->SetmBF(0);//set BF
	node->SetLeft(NULL);//set left
	node->SetRight(NULL);//set right
	root = node;//set node
}

bool AVLTree::Insert(AVLNode * node)
{
	char* cmp1;
	char* cmp2;
	if (root->GetLeft() == NULL && root->GetRight() == NULL)
	{//insert for only root case
		cmp1 = (root->GetCityData()->Getname());
		cmp2 = (node->GetCityData()->Getname());
		if (strcmp(cmp1,cmp2) > 0)
		{
			root->SetLeft(node);
			root->SetmBF(1);//if there is left node
		}
		else if (strcmp(cmp1,cmp2) < 0)
		{
			root->SetRight(node);
			root->SetmBF(-1);//if there is right node 
		}
	}
	else
	{
		pa = NULL;
		AVLNode* pp = root;
		AVLNode* p = root;
		cmp2 = (node->GetCityData()->Getname());//insert node
		while (p!=NULL)
		{
			cmp1 = (p->GetCityData()->Getname());//compare node
			pp = p;
			if (strcmp(cmp1,cmp2) > 0)//if insert node smaller than compare node
			{
				p = p->GetLeft();//go left
			}
			else if (strcmp(cmp1,cmp2)<0)//if insert node bigger than compare node
			{
				p = p->GetRight();//go right
			}
		}
		if (strcmp(cmp1,cmp2) > 0)
		{
			pp->SetLeft(node);//set left node of pp
		}
		else if (strcmp(cmp1,cmp2) < 0)
		{
			pp->SetRight(node);//set right node of pp
		}
		update_bf(root);//update BF
		make_balance(root);//make balance
	}
	return true;
}

int AVLTree::get_height(AVLNode* node)//get height
{
	int l_height = 0;
	int r_height = 0;
	int result = 0;
	if (node->GetLeft() != NULL)
	{
		l_height = get_height(node->GetLeft());//get each node height
	}
	if (node->GetRight() != NULL)
	{
		r_height = get_height(node->GetRight());//get each node height
	}
	if (node != NULL)//after recursive
	{
		if (l_height > r_height)//case for l_heght > r_height
		{
			result = l_height + 1;
		}
		else if (r_height > l_height)//case for l_heght < r_height
		{
			result = r_height + 1;
		}
		else//case for l_heght == r_height
		{
			result = l_height + 1;
		}
	}
	return result;
}
void AVLTree::update_bf(AVLNode* node)
{
	AVLNode* temp = node;
	int l_height = 0;
	int r_height = 0;
	//counting left height
	if (node->GetLeft() != NULL)
	{
		temp = node->GetLeft();
		l_height = get_height(temp);
	}
	//counting right height
	if (node->GetRight() != NULL)
	{
		temp = node->GetRight();
		r_height = get_height(temp);
	}
	node->SetmBF(l_height - r_height);//setting BF
	if (node->GetLeft() != NULL)
	{
		update_bf(node->GetLeft());//setting left node BF  recursively
	}
	if (node->GetRight() != NULL)
	{
		update_bf(node->GetRight());//setting right node BF recursively
	}
}
void AVLTree::make_balance(AVLNode* node)
{
	AVLNode* temp = node;
	if (node)//node != NULL
	{
		if (node->GetLeft() != NULL)
		{
			if (node->GetLeft()->GetmBF() < -1 || node->GetLeft()->GetmBF() > 1)
			{
				pa = node;
			}
		}
		if(node->GetRight() != NULL)
		{
			if (node->GetRight()->GetmBF() < -1 || node->GetRight()->GetmBF() > 1)
			{
				pa = node;
			}
		}
		make_balance(node->GetLeft());
		make_balance(node->GetRight());
		if (temp->GetmBF() < -1 || temp->GetmBF() > 1)
		{
			AVLNode* rootSub;
			int BF = temp->GetmBF();
			if (BF > 1)//case for LR ,LL
			{
				//LL case
				if (temp->GetLeft()->GetLeft() != NULL)//LL case
				{
					AVLNode* temp1 = temp->GetLeft();
					temp->SetLeft(temp1->GetRight());
					temp1->SetRight(temp);
					rootSub = temp1;
				}
				else if (temp->GetLeft()->GetRight() != NULL)//LR case
				{
					AVLNode* temp1 = temp->GetLeft();//b temp ==a
					AVLNode* temp2 = temp->GetLeft()->GetRight();//c
					temp1->SetRight(temp2->GetLeft());
					temp->SetLeft(temp2->GetRight());
					temp2->SetLeft(temp1);
					temp2->SetRight(temp);
					rootSub = temp2;
				}
			}
			else if (BF < -1)//case for RL, RR
			{
				if (temp->GetRight()->GetRight() != NULL)//RR
				{
					AVLNode* temp1 = temp->GetRight();
					temp->SetRight(temp1->GetLeft());
					temp1->SetLeft(temp);
					rootSub = temp1;
				}
				else if (temp->GetRight()->GetLeft() != NULL)//RL
				{

					AVLNode* temp1 = temp->GetRight();//b temp ==a
					AVLNode* temp2 = temp->GetRight()->GetLeft();//c
					temp1->SetLeft(temp2->GetRight());
					temp->SetRight(temp2->GetLeft());
					temp2->SetRight(temp1);
					temp2->SetLeft(temp);
					rootSub = temp2;
				}
			}
			if (pa == NULL) root = rootSub;
			else if (temp == pa->GetLeft()) pa->SetLeft(rootSub);
			else pa->SetRight(rootSub);
			update_bf(root);//update bf
		}
	}
}
bool AVLTree::Delete(int num)
{ 
	AVLNode* Del_node;
	CityData* temp;
	Del_node = Search(num);//search delete node
	if (Del_node == NULL) return false;//if delete node is not exist
	else
	{
		AVLNode* pp = NULL;
		AVLNode* p = root;
		temp = Del_node->GetCityData();//get det node's city data
		while (p!=NULL)//compare for searching node's position
		{
			if (strcmp(temp->Getname(),p->GetCityData()->Getname()) > 0)
			{
				pp = p;
				p = p->GetRight();
			}
			else if (strcmp(temp->Getname(),p->GetCityData()->Getname()) < 0)
			{
				pp = p;
				p = p->GetLeft();
			}
			else
			{
				break;//search! ,p has postion
			}
		}
		if (p->GetLeft() == NULL && p->GetRight() == NULL)//case for no child
		{
			if (pp != NULL)//if that is not root node
			{
				if (pp->GetLeft() == p)
				{
					pp->SetLeft(NULL);
				}
				else if (pp->GetRight() == p)
				{
					pp->SetRight(NULL);
				}
			}
			else//root node 
			{
				root = NULL;
			}
			delete p;
		}
		else if(p->GetLeft() == NULL || p->GetRight() == NULL)//case for single child
		{ 
			if (p->GetLeft() != NULL)
			{
				if (pp != NULL)
				{
					if (pp->GetLeft() == p)
					{
						pp->SetLeft(p->GetLeft());//setting left
					}
					else if (pp->GetRight() == p)
					{
						pp->SetRight(p->GetLeft());//setting right
					}
				}
				else
				{
					root = p->GetLeft();
				}
			}
			else
			{
				if (pp != NULL)
				{
					if (pp->GetLeft() == p)
					{
						pp->SetLeft(p->GetRight());//setting left
					}
					else if (pp->GetRight() == p)
					{
						pp->SetRight(p->GetRight());//setting right
					}
				}
				else
				{
					root = p->GetRight();
				}
			}
			delete p;
		}
		else//case for two children
		{ 
			AVLNode* temp_p = NULL;
			AVLNode* swap = p->GetLeft();
			while (swap->GetRight() != NULL)
			{
				temp_p = swap;
				swap = swap->GetRight();
			}
			if (temp_p != NULL) temp_p->SetRight(NULL);
			swap->SetLeft(p->GetLeft());
			if (swap == swap->GetLeft()) swap->SetLeft(NULL);//case for leaf node
			swap->SetRight(p->GetRight());			
			if (swap == swap->GetRight()) swap->SetRight(NULL);//case for leaf node
			if (pp != NULL)//if delete node is not root node
			{
				if (pp->GetLeft() == p)
				{
					pp->SetLeft(swap);
				}
				else if (pp->GetRight() == p)
				{
					pp->SetRight(swap);
				}
			}
			else//if delete node is root node
			{
				root = swap;
			}
			delete p;
		}
	}
	if (root != NULL)
	{
		update_bf(root);
		make_balance(root);
	}
	return true;
}
AVLNode * AVLTree::Search(int num)
{
	AVLNode* temp = root;
	AVLNode* result = NULL;
	Inorder_search(num, temp);//for searcing node
	result = Searched_Node;//get Searched node
	Searched_Node = NULL;
	return result;//return result
}
AVLNode* AVLTree::Inorder_search(int num, AVLNode* node)
{
	AVLNode* temp = node;
	if (node)
	{
		if (temp->GetCityData()->GetLocationId() == num)//compare search node 
		{
			Searched_Node = temp;//if find
			return temp;//return searched node 
		}
		else
		{
			Inorder_search(num, node->GetLeft());//iterate left recursively
			Inorder_search(num, node->GetRight());//iterate right recursively
		}
	}
	return NULL;
}
void AVLTree::Visit(AVLNode* node)
{
	CityData* temp = node->GetCityData();
	*flog << '(' << temp->GetLocationId() << ", " << temp->Getname() << ", " << temp->Getcountry() << ')' << endl;
	//print avl
}
void AVLTree::Inorder(AVLNode* node)
{
	if (node)
	{
		Inorder(node->GetLeft());
		Visit(node);//print
		Inorder(node->GetRight());
	}
}
bool AVLTree::Print()//print avl
{
	if (root != NULL)
	{
		Inorder(root);//print inorderry
		return true;
	}
	return false;
}
