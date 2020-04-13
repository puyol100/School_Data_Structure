#include "Vertex.h"

Vertex::Vertex()
{
	m_key = 0;
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}
Vertex::Vertex(int key)
{
	m_key = key;
	m_size = 0;
	m_pEHead = NULL;
	m_pNext = NULL;
}
Vertex::~Vertex()
{
	Clear();
}
void Vertex::SetNext(Vertex* pNext)//set next
{
	m_pNext = pNext;
}
int Vertex::GetKey() const//get key
{
	return m_key;
}
Vertex* Vertex::GetNext() const//get next
{
	return m_pNext;
}
int Vertex::Size() const
{
	return m_size;//return Vertex Size
}
void Vertex::AddEdge(int edgeKey, int weight)//func for adding edge
{
	Edge* new_edge = new Edge(edgeKey, weight);//make edge node
	if (m_pEHead == NULL)
	{
		m_pEHead = new_edge;//first add case
	}
	else
	{
		Edge* temp = m_pEHead;
		while (temp->GetNext() != NULL)//find edge link tail
		{
			temp = temp->GetNext();
		}
		temp->SetNext(new_edge);//linking new edge
	}
	m_size = m_size + 1;//edge size + 1
}
Edge* Vertex::GetHeadOfEdge() const
{
	return m_pEHead;//return head pointer of vertex
}
void Vertex::Clear()
{
	if (m_pEHead != NULL)
	{
		Edge* temp = m_pEHead;
		Edge* temp2;
		while (temp != NULL)
		{
			temp2 = temp->GetNext();
			delete temp;
			temp = temp2;
		}
		m_pEHead = NULL;
		m_pNext = NULL;
	}
}