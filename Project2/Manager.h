#define _CRT_SECURE_NO_WARNINGS
#ifndef SOLUTION_H
#define SOLUTION_H

#include "Result.h"
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string.h>

class Manager
{
private:
    // the filepath for the result log
    const char* RESULT_LOG_PATH = "log.txt";
    // the filepath for the error log
	//const char* ERROR_LOG_PATH = "error.txt";

    // the file stream for the result log
    std::ofstream fout;
    // the file stream for the error log
//	std::ofstream ferr;
    // graph instance to manage the vertics.
	Graph m_graph;

public:
    ~Manager();
	char * cmd;
    void Run(const char* filepath);//for run
    void PrintError(Result result);//for print error
private:
    Result Load(const char* filepath);//for load
    Result Print();//for print
    Result FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey);
    Result FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey);
    Result FindShortestPathBellmanFord(int startVertexKey, int endVertexKey);
    Result FindShortestPathFloyd();
};

#endif
