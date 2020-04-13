#include "Manager.h"
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <algorithm>
Manager::~Manager()//destructor 
{
    if (fout.is_open())
        fout.close();

   // if (ferr.is_open())
   //     ferr.close();
}

void Manager::Run(const char* filepath)//Run func
{
    fout.open(RESULT_LOG_PATH);//open result file
   // ferr.open(ERROR_LOG_PATH);
	std::ifstream fin;//stream for command
	cmd = new char[40];
	Result result;//for keep result state
	fin.open(filepath);//open command
	if (!fin.is_open())//file is not exist
	{
		fout << "====== SYSTEM ======" << std::endl;
		fout << "CommandFileNotExist" << std::endl;
		fout << "===================" << std::endl;
		result = CommandFileNotExist;
		PrintError(result);//print error
	}
	else//case for file exist
	{ 
		while (!fin.eof())
		{
			fin.getline(cmd, 40);//get command
			if(cmd[0] == '\0') break;		
			char* one = strtok(cmd, " ");
			if (!strcmp(one, "LOAD")) {//case for Load
			fout << "====== LOAD ======" << std::endl;
			char* two = strtok(NULL, "\0");
			if (two == NULL)
			{
				fout << "LoadFileNotExist" << std::endl;
				fout << "===================" << std::endl;
				result = LoadFileNotExist;
			}
			else
			{ 
				result = Load(two);//Load func
			}
		}
			else if (!strcmp(one, "PRINT")) {//case for Print
			fout << "====== PRINT ======" << std::endl;
			result = Print();//call Print func
		}
			else if (!strcmp(one, "DIJKSTRA")) {//case for DIjkstra using set
			fout << "====== DIJKSTRA ======" << std::endl;
			char* start = strtok(NULL, " ");
			char* end = strtok(NULL, "\0");
			if (start == NULL || end == NULL)//if Vertex key is not exist
			{
				fout << "VertexKeyNotExist"<<std::endl;
				fout << "===================" << std::endl;
				result = VertexKeyNotExist;
			}
			else
			{
				result = FindShortestPathDijkstraUsingSet(atoi(start), atoi(end));//call Distra
			}
		}
			else if (!strcmp(one, "DIJKSTARMIN")) {//case for Dijstra using minheap
			fout << "====== DIJKSTARMIN ======" << std::endl;
			char* start = strtok(NULL, " ");
			char* end = strtok(NULL, "\0");
			if (start == NULL || end == NULL)//case for vertex key is not exist
			{
				fout << "VertexKeyNotExist" << std::endl;
				fout << "===================" << std::endl;
				result = VertexKeyNotExist;
			}
			else
			{
				result = FindShortestPathDijkstraUsingMinHeap(atoi(start), atoi(end));//call Dijstra
			}
		}
			else if (!strcmp(one, "BELLMANFORD")) {//case for Bellmanford
				fout << "====== BELLMANFORD ======" << std::endl;
				char* start = strtok(NULL, " ");
				char* end = strtok(NULL, "\0");
				if (start == NULL || end == NULL)//case for vertex not exist
				{
					fout << "VertexKeyNotExist" << std::endl;
					fout << "===================" << std::endl;
					result = VertexKeyNotExist;
				}
				else
				{
					result = FindShortestPathBellmanFord(atoi(start), atoi(end));//func BellmanFord

				}
			}
			else if (!strcmp(one, "FLOYD")) {//case for Floyd
				fout << "====== FLOYD ======" << std::endl;
				result = FindShortestPathFloyd();//call func
			}
			else
			{//case for else error
				fout << "====== "<<one<<" ======" << std::endl;
				fout << "NonDefinedCommand" << std::endl;
				fout << "===================" << std::endl;
				result = NonDefinedCommand;
			}
			PrintError(result);//call error func
		}
	}
    // TODO: implement
}
void Manager::PrintError(Result result)//func for Print error
{
	fout << std::endl;
	fout<< "===================" << std::endl;
    fout << "Error code: " << result << std::endl;//print error
	fout << "===================" << std::endl<<std::endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)//func Load
{
	ifstream l_fin;
	l_fin.open(filepath);//open map data
	if (!l_fin.is_open())//if file is not exist
	{
		fout << "LoadFileNotExist" << std::endl;
		fout << "===================" << std::endl;
		return  LoadFileNotExist;
	}
	int iter = -1;
	int temp = 0;
	while (!l_fin.eof())//loop for read file
	{
		char* info = new char[60];
		l_fin.getline(info, 60);//get map data
		if (l_fin.eof()) break;
		if (iter == -1)
		{
			m_graph.Set_size(atoi(info));//get map size
		}
		else
		{
			m_graph.AddVertex(iter);//add vertex
			for (int i = 0; i < m_graph.Size(); i++)
			{
				if (i == 0) 
				{
					temp = atoi(strtok(info, " "));
				}
				else
				{
					temp = atoi(strtok(NULL, " "));
				}
				m_graph.AddEdge(iter, i, temp);//add edge
			}
		}
		iter++;
	}
	fout << "Success" << std::endl;
	fout << "==================" << std::endl;//print success code
    // TODO: implement
	return Success;
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()//func for print graph
{
	if (m_graph.Size() == 0)//if graph is not exist
	{
		fout << "GraphNotExist" << std::endl;
		fout << "===================" << std::endl;
		return GraphNotExist;
	}
	m_graph.Print(fout);//print graph
	fout << "===================" << std::endl;
    // TODO: implement
	return Success;
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with DFS (stack)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>


/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)//func for Dijstra using set
{
	if (m_graph.Size() == 0)//if graph is not exist
	{
		fout << "GraphNotExist" << std::endl;
		fout << "===================" << std::endl;
		return GraphNotExist;
	}
	if (m_graph.FindVertex(startVertexKey) == NULL && m_graph.FindVertex(endVertexKey) == NULL)//if key is invalid
	{
		fout << "InvalidVertexKey" << std::endl;
		fout << "===================" << std::endl;
		return InvalidVertexKey;
	}
	if (m_graph.IsNegativeEdge() == true)
	{
		fout << "InvalidAlgorithm" << std::endl;
		fout << "===================" << std::endl;
		return InvalidAlgorithm;
	}
	vector<int> Dij_usingset;
	Dij_usingset = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);//call Dijstra
	fout<<"shortest path: ";
	for (int i = Dij_usingset.size()-1; i > -1; i--)//print shortest path
	{
		fout <<Dij_usingset[i]<<" ";
	}
	fout <<endl<< "sorted nodes: ";
	sort(Dij_usingset.begin(), Dij_usingset.end());//sort vertex acseding 
	for (int i = 0; i < Dij_usingset.size(); i++)//print vertex
	{
		fout << Dij_usingset[i] << " ";
	}
	fout <<endl<< "path length: "<<m_graph.path_length<<endl;//print path length
	// TODO: implement
	fout << "===================" << std::endl;
	return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)//func for Dijstra min heap
{
	if (m_graph.Size() == 0)//case for grpah is not exist
	{
		fout << "GraphNotExist" << std::endl;
		fout << "===================" << std::endl;
		return GraphNotExist;
	}
	if (m_graph.FindVertex(startVertexKey) == NULL && m_graph.FindVertex(endVertexKey) == NULL)//case for invalid key
	{
		fout << "InvalidVertexKey" << std::endl;
		fout << "===================" << std::endl;
		return InvalidVertexKey;
	}
	if (m_graph.IsNegativeEdge() == true)
	{
		fout << "InvalidAlgorithm" << std::endl;
		fout << "===================" << std::endl;
		return InvalidAlgorithm;
	}
	vector<int> Dij_usingset;
	Dij_usingset = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);//call dijstrar minHeap
	fout << "shortest path: ";
	for (int i = Dij_usingset.size() - 1; i > -1; i--)//print shortest path
	{
		fout << Dij_usingset[i] << " ";
	}
	fout << endl << "sorted nodes: ";
	sort(Dij_usingset.begin(), Dij_usingset.end());//sort vertex ascending
	for (int i = 0; i < Dij_usingset.size(); i++)//print sorted node
	{
		fout << Dij_usingset[i] << " ";
	}
	fout << endl << "path length: " << m_graph.path_length << endl;//print length
    // TODO: implement
	fout << "===================" << std::endl;
	return Success;
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
	if (m_graph.Size() == 0)//case for graph not exist
	{
		fout << "GraphNotExist" << std::endl;
		fout << "===================" << std::endl;
		return GraphNotExist;
	}
	if (m_graph.FindVertex(startVertexKey) == NULL && m_graph.FindVertex(endVertexKey) == NULL)//case for invalid key
	{
		fout << "InvalidVertexKey" << std::endl;
		fout << "===================" << std::endl;
		return InvalidVertexKey;
	}
	vector<int> BellFord = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);//call bellman
	if (BellFord[0] == IN_FINITY)//case for negative cycle detected
	{
		fout << "NegativeCycleDetected" << std::endl;
		fout << "===================" << std::endl;
		return NegativeCycleDetected;
	}
	fout << "shortest path: ";
	for (int i = BellFord.size() - 1; i > -1; i--)//print shortest path
	{
		fout << BellFord[i] << " ";
	}
	fout << endl << "sorted nodes: ";
	sort(BellFord.begin(), BellFord.end());
	for (int i = 0; i < BellFord.size(); i++)//print sorted node
	{
		fout << BellFord[i] << " ";
	}
	fout << endl << "path length: " << m_graph.path_length << endl;//print path length

    // TODO: implement
	fout << "===================" << std::endl;
	return Success;
}
Result Manager::FindShortestPathFloyd()//func for floyd
{
	if (m_graph.Size() == 0)//case for grpah not exist
	{
		fout << "GraphNotExist" << std::endl;
		fout << "===================" << std::endl;
		return GraphNotExist;
	}
	vector<vector<int>> Floyd = m_graph.FindShortestPathFloyd();//call floyd
	vector<int> ::iterator iter;
	for (int i = 0; i < Floyd.size(); i++)//print floyd
	{
		for (iter = Floyd[i].begin(); iter != Floyd[i].end(); iter++)
		{
			fout << *iter << " ";
		}
		fout << endl;
	}
	fout << "===================" << std::endl;
	return Success;
}
