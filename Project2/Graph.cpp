#include "Graph.h"
#include "MinHeap.h"
#include "Stack.h"
#include <set>
#include <algorithm>
#define DFS_FIRST_PATH

Graph::Graph()
{
	m_pVHead = NULL;
	m_vSize = 0;
    // TODO: implement
}
Graph::~Graph()
{
	Clear();
    // TODO: implement
}
void Graph::Set_size(int size)//setting graph size
{
	m_vSize = size;//setting graph size
}
void Graph::AddVertex(int vertexKey)//add vertex to graph
{
	Vertex* new_vertex = new Vertex(vertexKey);//make new vertex
	if (m_pVHead == NULL)//case for first time of add
	{
		m_pVHead = new_vertex;
	}
	else
	{
		Vertex* temp = m_pVHead;
		while (temp->GetNext() != NULL)//find vertex link tail
		{
			temp = temp->GetNext();
		}
		temp->SetNext(new_vertex);//linking vertex to tail 
	}
}
void Graph::AddEdge(int startVertexKey, int endVertexKey, int weight)//adding edge 
{
	if(weight != 0)
	{ 
		Vertex* temp = m_pVHead;
		while (temp->GetKey() !=  startVertexKey)//find from vertex
		{
			temp = temp->GetNext();
		}
		temp->AddEdge(endVertexKey, weight);//add edge
	}
}
int Graph::Size() const
{
	return m_vSize;
}
void Graph::Clear()
{
	if (m_pVHead != NULL)
	{
		Vertex* temp = m_pVHead;
		Vertex* temp2;
		while (temp != NULL)
		{
			temp2 = temp->GetNext();
			delete temp;
			temp = temp2;
		}
		m_pVHead = NULL;
	}
}
void Graph::Print(std::ofstream& fout)//for print graph
{
	int matrix_size = Size();

	Vertex* temp = m_pVHead;
	Edge* temp2 = NULL;
	for (int i = 0; i < matrix_size; i++)//print 
	{
		temp2 = temp->GetHeadOfEdge();//get head of edge
		for (int j = 0; j < matrix_size; j++)
		{
			if (temp2->GetKey() == j)//case for print destination vertex weight
			{
				fout << temp2->GetWeight() << " ";//print weight
				if(temp2->GetNext() != NULL)
				{ 
					temp2 = temp2->GetNext();//move pointer to next edge 
				}
			}
			else
			{
				fout << 0 << " ";
			}
		}
		fout << endl;
		if (temp->GetNext() != NULL)
		{
			temp = temp->GetNext();//move vertex pointer
		}
	}
}
bool Graph::IsNegativeEdge()//func for negative edge detect
{
	Vertex* temp = m_pVHead;
	bool flag = false;//flag for detec info
	while (temp != NULL)
	{
		Edge* edge = temp->GetHeadOfEdge();//get head of edge
		while (edge != NULL)//find nega edge
		{
			if (edge->GetWeight() < 0)//if detect
			{
				flag = true;//detec
				break;
			}
			edge = edge->GetNext();
		}
		if (flag == true) break;//return detec
		temp = temp->GetNext();
	}
	if (flag == true) return true;//return negative edge exist
	else return false;//no nega edge
}
Vertex* Graph:: FindVertex(int key)//func for find vertex
{
	Vertex* temp = m_pVHead;
	while (temp != NULL)
	{
		if (temp->GetKey() == key)
		{
			break;//if find vertex
		}
		temp = temp->GetNext();
	}
	return temp;//return pointer of finded vertex
}
std::vector<int> Graph::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)//func for DijstraUsingset
{
	int* dist = new int[m_vSize];
	int* prev = new int[m_vSize];
	for (int i = 0; i < m_vSize; i++)
	{
		dist[i] = IN_FINITY;
		prev[i] = IN_FINITY;
	}
	set<pair<int, int>> S;//dist, from vertex num
	S.insert({ 0,startVertexKey});//init
	dist[startVertexKey] = 0;//init
	while (!S.empty())//loop for find
	{
		int u = S.begin()->second;
		int ud = S.begin()->first;
		S.erase(S.begin());
		Vertex* temp = m_pVHead;
		while (temp->GetNext() != NULL)
		{
			if (temp->GetKey() == u) break;
			temp = temp->GetNext();
		}//find from vertex
		if (dist[u] < ud) continue;
		Edge* temp2 = temp->GetHeadOfEdge();
		for (int i = 0; i < temp->Size(); i++)//setting Dijstra
		{
			int v = temp2->GetKey();
			int vd = temp2->GetWeight() + ud;
			if (dist[v] > vd) {
				S.erase({ dist[v],v });
				dist[v] = vd;
				prev[v] = u;
				S.insert({ dist[v],v });
			}
			temp2 = temp2->GetNext();
		}
	}
	vector<int> save;//for return
	for (int i = endVertexKey; i != IN_FINITY;)//save to save 
	{
		save.push_back(i);
		i = prev[i];
	}
	path_length = dist[endVertexKey];//get path length
	return save;//return save
}
std::vector<int> Graph:: FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)//func for Dijstra Minheap
{
	int* dist = new int[m_vSize];
	int* prev = new int[m_vSize];
	for (int i = 0; i < m_vSize; i++)
	{
		dist[i] = IN_FINITY;
		prev[i] = IN_FINITY;
	}
	MinHeap<int, int> S;
	S.Push(0, startVertexKey);//initial the key
	dist[startVertexKey] = 0;//init
	while (!S.IsEmpty())//loop for find
	{
		int u = S.Top().second;
		int ud = S.Top().first;
		S.Pop();
		if (dist[u] < ud) continue;
		Vertex* temp = m_pVHead;
		while (temp->GetNext() != NULL)
		{
			if (temp->GetKey() == u) break;
			temp = temp->GetNext();
		}//find from vertex
		Edge* temp2 = temp->GetHeadOfEdge();
		for (int i = 0; i < temp->Size(); i++)//setting Dijstra
		{
			int v = temp2->GetKey();
			int vd = temp2->GetWeight() + ud;
			if (dist[v] > vd) {
				dist[v] = vd;
				prev[v] = u;
				S.Push( dist[v],v );
			}
			temp2 = temp2->GetNext();
		}
	}
	vector<int> save;//for return
	for (int i = endVertexKey; i != IN_FINITY;)//get info
	{
		save.push_back(i);
		i = prev[i];
	}
	path_length = dist[endVertexKey];//get dist
	return save;//return save
}
std::vector<int> Graph:: FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)//func for bellman
{
	int** d = new int*[m_vSize-1];
	int** p = new int*[m_vSize-1];
	for (int i = 0; i < m_vSize; i++)
	{
		d[i] = new int[m_vSize];
		p[i] = new int[m_vSize];
	}
	for (int i = 0; i < m_vSize-1; i++)
	{
		for (int j = 0; j < m_vSize; j++)
		{
			d[i][j] = IN_FINITY;
			p[i][j] = IN_FINITY;
		}
		d[i][startVertexKey] = 0;//setting edge constraint 0 case
	}
	/////////////Initial
	Vertex* start_vertex = m_pVHead;
	while (start_vertex->GetKey() != startVertexKey)
	{
		start_vertex = start_vertex->GetNext();
	}
	Edge* temp = start_vertex->GetHeadOfEdge();
	while(temp != NULL)
	{
		d[1][temp->GetKey()] = temp->GetWeight();
		p[1][temp->GetKey()] = startVertexKey;
		temp = temp->GetNext();
	}
	//////////////case for adjacent, temp_vertex = start_vertex
	for (int k = 2; k < m_vSize-1; k++)//setting Bellman edge constraint 2 to edge size 
	{
		for (int j = 0; j < m_vSize; j++)
		{
			if (d[k - 1][j] != IN_FINITY && d[k-1][j] != 0)//case for update
			{
				Vertex* temp_vertex = m_pVHead;
				while (temp_vertex->GetKey() != j)//find vertex
				{
					temp_vertex = temp_vertex->GetNext();
				}
				Edge* temp_edge = temp_vertex->GetHeadOfEdge();//get head of finded vertex
				while (temp_edge != NULL) //while for update 
				{
					int weight = d[k - 1][j] + temp_edge->GetWeight();//get weight
					/////d(v, k) = min{d(v, k-1), min{d(w, k-1) + length of edge (w, v)}}
					if (d[k - 1][temp_edge->GetKey()] > weight)
					{
						if (d[k][temp_edge->GetKey()] > weight)
						{
							d[k][temp_edge->GetKey()] = weight;
							p[k][temp_edge->GetKey()] = temp_vertex->GetKey();
						}
					}
					else
					{
						d[k][temp_edge->GetKey()] = d[k - 1][temp_edge->GetKey()];
						p[k][temp_edge->GetKey()] = p[k - 1][temp_edge->GetKey()];
					}
					temp_edge = temp_edge->GetNext();//move next linked edge address
				}
			}
		}
		for (int j = 0; j < m_vSize; j++)//loop for rearrange
		{
			if (d[k][j] == IN_FINITY)
			{
				if (d[k - 1][j] != IN_FINITY)
				{
					d[k][j] = d[k - 1][j];
					p[k][j] = p[k - 1][j];
				}
			}
		}
	}
	vector<int> save;//for save value
	vector<int> err;//for error
	int check = 0;
	for (int i = 0, j = endVertexKey; i < m_vSize;check++,i++)//loop for save
	{
		
		if (j == startVertexKey)
		{
			if (p[m_vSize - 2][j] != IN_FINITY)
			{
				err.push_back(IN_FINITY);
				break;
			}
			else
			{ 
				save.push_back(startVertexKey);//push to save
				break;
			}
		}
		save.push_back(j);
		j = p[m_vSize - 2][j];
	}
	if (check == m_vSize)//if there is cycle loop
	{
		err.push_back(IN_FINITY);
		return err;//return error
	}
	if (err.empty()== false)
	{
		return err;
	}
	path_length = d[m_vSize - 2][endVertexKey];//get path length
	return save;//return save
}
std::vector<vector<int>> Graph::FindShortestPathFloyd()//func for Folyd
{
	int** A = new int*[m_vSize];
	int** p = new int*[m_vSize];
	for (int i = 0; i < m_vSize; i++)
	{
		A[i] = new int[m_vSize];
		p[i] = new int[m_vSize];
	}
	for (int i = 0; i < m_vSize; i++)//loop for setting init
	{
		Vertex* temp = FindVertex(i);//find vertex
		if(temp!=NULL)
		{ 
			Edge* edge = temp->GetHeadOfEdge();
			for (int j = 0; j < m_vSize; j++)
			{
				if(edge!= NULL)
				{ 
					if (edge->GetKey() == j)//case for adjacent vertex
					{
						A[i][j] = edge->GetWeight();
						p[i][j] = temp->GetKey();
						edge = edge->GetNext();
						continue;
					}
				}
				if (i == j)//case for same vertex
				{
					A[i][j] = 0;
					p[i][j] = 0;
				}
				else
				{ 
					A[i][j] = IN_FINITY;
					p[i][j] = IN_FINITY;
				}
			}
		}
	}
	//////////////////////////Init
	for (int i = 0; i < m_vSize; i++) //loop for flyd
	{
		for (int j = 0; j < m_vSize; j++)
		{
			for (int k = 0; k < m_vSize; k++)
			{
				if (A[k][j] > A[k][i] + A[i][j])//Ak[i][j] = min{Ak-1[i][j], Ak-1[i][k] + Ak-1[k][j]}
				{
					A[k][j] = A[k][i] + A[i][j];
					p[k][j] = p[i][j];
				}
			}
		}
	}
	vector<int>* keep = new vector<int>[m_vSize];//keep for save result
	vector<vector<int>> save;
	for (int i = 0; i < m_vSize; i++)
	{
		for (int j = 0; j < m_vSize; j++)
		{
			keep[i].push_back(A[i][j]);
		}
		save.push_back(keep[i]);
	}
	return save;//return result
}