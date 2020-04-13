#include "AVLNode.h"

AVLNode::AVLNode()
{
	pCityData = NULL;//for city data node
	pLeft = NULL;//for left pointer
	pRight = NULL;//for right pointer
	mBF = 0;//for balance factor
}

AVLNode::~AVLNode()
{
}

CityData * AVLNode::GetCityData()
{
	return pCityData;
}

AVLNode * AVLNode::GetLeft()
{
	return pLeft;
}

AVLNode * AVLNode::GetRight()
{
	return pRight;
}

int AVLNode::GetmBF()
{
	return mBF;
}

void AVLNode::SetCityData(CityData * node)
{
	pCityData = node;//setting City data
}

void AVLNode::SetLeft(AVLNode * node)
{
	pLeft = node;//setting left pointer
}

void AVLNode::SetRight(AVLNode * node)
{
	pRight = node;//setting right pointer
}

void AVLNode::SetmBF(int n)
{
	mBF = n;//setting Balance Factor
}