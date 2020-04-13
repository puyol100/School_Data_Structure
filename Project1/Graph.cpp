#include "Graph.h"
#include <map>
#include <vector>
#include <algorithm>
Graph::Graph(ofstream * flog)
{
	this->flog = flog;//get file pointer
	mList = NULL;
	size = 0;
	mstMatrix = NULL;
}

Graph::~Graph()
{

}

bool Graph::Build(AVLTree * root)
{
	if (mList != NULL)//case for second call of Build command 
	{//Initiallize
		delete[] mList;
		mList = NULL;
		delete[] vertex;
		vertex = NULL;
		if (mstMatrix != NULL)
		{
			delete[] mstMatrix;
			mstMatrix = NULL;
		}
		count = 0;
		size = 0;
	}
	Counting_size(root->Getroot());//get tree size
	vertex = new CityData*[size];
	Make_vertex(root->Getroot());//make **vertex
	count = 0;
	Make_mList();//make mList
	return true;
}
void Graph:: Counting_size(AVLNode* node)
{
	if (node)
	{
		size = size + 1;//counting avl tree
		Counting_size(node->GetLeft());
		Counting_size(node->GetRight());
	}
}
void Graph::Make_vertex(AVLNode* node)
{
	if (node)
	{
		Make_vertex(node->GetLeft());
		vertex[count++] = node->GetCityData();//get city data inorderry
		Make_vertex(node->GetRight());
	}
}
void Graph::Make_mList()
{
	mList = new multimap<int, CityData *>[size];
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int weight = vertex[i]->GetLocationId() - vertex[j]->GetLocationId();//get weight
			if (weight < 0) weight = weight * (-1);//for absolute value
			mList[i].insert(pair<int, CityData*>(weight,vertex[j]));//make mList
		}
	}
}
void Graph::Print_GP()
{//itertartor_mlist
	map<int,CityData*>::iterator iterator_mlist;
	int val = 0;
	int j = 0;
	for (int i = 0; i < size; i++)
	{
		for (j=0; j<size;j++)
		{
		
			for (iterator_mlist = mList[i].begin(); iterator_mlist != mList[i].end();)//iterate mList[i] tree
			{

				if (iterator_mlist->second->Getname() == vertex[j]->Getname())//if iterator->name == vertex oreder name
				{
					val = iterator_mlist->first;
					*flog << val << " ";//print value
					break;
				}
				iterator_mlist++;
			}
		}
		*flog << endl;
	}
}

void Graph::print_mst_info(int index,int flag)
{
	int temp_index = 0, temp_flag = 0;
	count = count + 1;//counting edge 
	if (flag == 0)//case for src -> dest
	{
		*flog << "( " << vertex[mst_set[index].src]->Getname() << ", " << vertex[mst_set[index].dest]->Getname() << "), " << mst_set[index].weight << endl;
	}
	else if (flag == 1)//case for dest -> src
	{
		*flog << "( " << vertex[mst_set[index].dest]->Getname() << ", " << vertex[mst_set[index].src]->Getname() << "), " << mst_set[index].weight << endl;
	}
	mstMatrix[index] = -1;//vertex printed check 
	sum_mst = mst_set[index].weight + sum_mst;//sum weight
	for (int i = 0; i < mst_set.size(); i++)//loop for setting next index
	{
		if (mstMatrix[i] != -1)//case: not printed edge
		{
			if(flag ==0)//src -> dest case
			{ 
				if (mst_set[index].src == mst_set[i].src)//if there is link more than twice
				{
					temp_index = i;
					temp_flag = 0;
				}
				else if (mst_set[index].src == mst_set[i].dest)//if there is link more than twice
				{
					temp_index = i;
					temp_flag = 1;
				}
				else if (mst_set[index].dest == mst_set[i].src)
				{
					temp_index = i;
					temp_flag = 0;
				}
				else if (mst_set[index].dest == mst_set[i].dest)
				{
					temp_index = i;
					temp_flag = 1;
				}
			}
			else if (flag == 1)//case for dest -> src
			{
				if (mst_set[index].dest == mst_set[i].src)//if there is link more than twice
				{
					temp_index = i;
					temp_flag = 0;
				}
				else if (mst_set[index].dest == mst_set[i].dest)//if there is link more than twice
				{
					temp_index = i;
					temp_flag = 1;
				}
				else if (mst_set[index].src == mst_set[i].src)
				{
					temp_index = i;
					temp_flag = 0;
				}
				else if (mst_set[index].src == mst_set[i].dest)
				{
					temp_index = i;
					temp_flag = 1;
				}
			}
		}
	}
	if (count == size-1) return;//n-1 exit
	print_mst_info(temp_index,temp_flag);//call funtion recursively
}
void Graph::Print_MST()
{
	int v_num = start_index;//mst start index
	for (int i = 0; i < size; i++)
	{
		mstMatrix[i] = 0;//reset mstMatrix
	}
	for (int i = 0; i < mst_set.size(); i++)
	{
		if (mst_set[i].src == v_num)
		{
			v_num = i;//get mst_set index
			break;
		}
	}
	count = 0;
	sum_mst = 0;//for total weight
	print_mst_info(v_num,0);//call print function
	*flog << "total: " << sum_mst << endl;//print total weight
}

bool Graph::Kruskal()
{
	if (mList == NULL)
	{
		return false;
	}
	else
	{
		if (mstMatrix != NULL)//case for second call of build_mst
		{
			delete[] mstMatrix;
			mstMatrix = NULL;
		}
		if (!v.empty())//case for second call of build_mst
		{
			v.clear();
			vector<edge>().swap(v);//clear the v vector container
		}
		if (!mst_set.empty())//case for second call of build_mst
		{
			mst_set.clear();
			vector<edge>().swap(mst_set);//clear the mst_set vector container
		}
		mstMatrix = new int[size];
		for (int i = 0; i < size; i++)
		{
			mstMatrix[i] = i;//make mst parent info
		}
		count = 0;
		make_set();//make set.
		edge edge_info;
		for (int i = 0; i < v.size(); i++)//loop for making mst_set
		{
			if (union_set(v[i].src, v[i].dest))
			{
				edge_info.src = v[i].src;
				edge_info.dest = v[i].dest;
				edge_info.weight = v[i].weight;
				mst_set.push_back(edge_info);//make mst_set
			}
		}
		start_index = mstMatrix[0];
		return true;
	}
}
bool compare_make_set(const edge&a, const edge&b)//for sort function
{
	return a.weight < b.weight;//sort weight acending order
}
void Graph::make_set()
{
	multimap<int, CityData*>::iterator iterator_mlist;
	edge edge_info;
	for (int i = 0; i < size; i++)
	{
		edge_info.src = i;//get source vertex index
		for (int j = 0; j < size; j++)
		{
			for (iterator_mlist = mList[i].begin(); iterator_mlist != mList[i].end();)
			{
				if (iterator_mlist->second->Getname() == vertex[j]->Getname())
				{
					edge_info.dest = j;//get destination vertex index
					edge_info.weight = iterator_mlist->first;//get weight 
					v.push_back(edge_info);//push to vector v
					break;
				}
				iterator_mlist++;
			}
		}
	}
	sort(v.begin(), v.end(),compare_make_set);//sorting vector v
}
bool Graph::union_set(int x, int y)//x = source, y = dest
{
	x = find(x);//check x's parent
	y = find(y);//checl y's parent
	if (x == y) return false;//case for cycle 
	mstMatrix[y] = x;//case for no cycle
	return true;
}
int Graph::find(int x)
{	
	if (x == mstMatrix[x]) return x;
	return mstMatrix[x] = find(mstMatrix[x]);
}
