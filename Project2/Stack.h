#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif
template <typename T>
class Stack
{
private:
	class StackNode
	{
	public:
		T Data;
		StackNode* pNext;//next pointer for pointing next
		StackNode* pPrev;//prev pointer for pointing prev
		StackNode(T data) : Data(data), pNext(NULL),pPrev(NULL) {}
	};

private:
	// the head pointer of the stack
	StackNode* m_pTop;
public:
	Stack() {
		m_pTop = 0;
	};
	~Stack() {//clear all of stack data
		if (m_pTop != NULL)
		{
			while (m_pTop != NULL)
			{
				Pop();//Poping
			}
		}
	}

	/// <summary>
	/// push the data into this stack
	/// </summary>
	///
	/// <param name="data">
	/// a data to push into this stack
	/// </param>
	void Push(T data) {//insert data
		StackNode* new_stack = new StackNode(data);//make node
		if (m_pTop == 0)
		{
			m_pTop = new_stack;//case for first time
		}
		else
		{//make stack structure
			new_stack->pPrev = m_pTop;
			m_pTop->pNext = new_stack;
			m_pTop = new_stack;
		}
	};
	/// <summary>
	/// pop(remove) the last-in data from this stack
	/// </summary>
	void Pop() {//Poping 
		if(m_pTop != NULL)//loop for pop
		{ 
			StackNode* temp = 0;
			temp = m_pTop->pPrev;
			delete m_pTop;
			if (temp != NULL)
			{
				temp->pNext = NULL;
			}
			m_pTop = temp;
		}
	};
	/// <summary>
	/// get the last-in data of this stack
	/// </summary>
	/// 
	/// <returns>
	/// the last-in data of this stack
	/// </returns>
	T Top() {
		return m_pTop->Data;
	};
	/// <summary>
	/// check whether this stack is empty or not.
	/// </summary>
	///
	/// <returns>
	/// true if this stack is empty.
	/// false otherwise.
	/// </returns>
	bool IsEmpty() {
		if (m_pTop == NULL) return true;
		else return false;
	};
};

#endif
