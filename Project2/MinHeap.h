#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <utility>
#include <vector>
template<typename TKey, typename TValue>
class MinHeap
{
private:
    // array for the elements which should be heap-sorted
    std::vector<std::pair<TKey, TValue>> m_vec;
	//key is weight, value is key 
public:
    MinHeap() {}

    /// <summary>
    /// insert key-value pair
    /// </summary>
    ///
    /// <param name="key">
    /// the key that is used for sorting
    /// </param>
    ///
    /// <param name="value">
    /// the value that is managed in this heap
    /// </param>
	void Push(TKey key, TValue value) {//for minheap insert
		if (m_vec.empty() == true) {//if first time
			m_vec.push_back({ key, value });//push to root
		}
		else
		{ 
			m_vec.push_back({ key,value });
			int i = m_vec.size();
			while ((i != 1) && key < m_vec[(i-1) / 2].first)//setting for minheap
			{
				m_vec[i-1].swap(m_vec[(i-1) / 2]);
				i = i / 2;
			}
		}
	};
    /// <summary>
    /// remove the minimum element
    /// </summary>
	void Pop(){//case for Pop 
		Heapify(0);
	};
    /// <summary>
    /// get the minimum element
    /// </summary>
    ///
    /// <returns>
    /// the minimum element
    /// </returns>
	std::pair<TKey, TValue> Top() {
		return m_vec[0];//return Top of minheap
	};//key is weight, value is key
    /// <summary>
    /// get the key-value pair which the value is the same as the target
    /// </summary>
    ///
    /// <returns>
    /// the key-value pair which the value is the same as the target
    /// </returns>
	std::pair<TKey, TValue> Get(TValue target) {//find targe node
		int i = 0;
		for (i = 0; i < m_vec.size(); i++)
		{
			if (m_vec[i].second == target) break;
		}
		return m_vec[i];
	};
    /// <summary>
    /// check whether this heap is empty or not
    /// </summary>
    ///
    /// <returns>
    /// true if this heap is empty
    /// </returns>
	bool IsEmpty() {
		if (m_vec.empty() == true) return true;
		else return false;
	};
    /// <summary>
    /// change the key of the node which the value is the target.<para/>
    /// In general, the newKey should be smaller than the old key.<para/>
    /// </summary>
    ///
    /// <parma name="target">
    /// the target to change the key
    /// </param>
    ///
    /// <param name="newKey">
    /// new key for the target
    /// </param>
	void DecKey(TValue target, TKey newKey);

private:
    /// <summary>
    /// heap-sort, heapify.<para/>
    /// this function can be called recursively
    /// </summary>
	void Heapify(int index) {
		m_vec[index] = m_vec.back();
		m_vec.pop_back();//pop tail
		int current = 0;
		while (1)//loop for pop and re arrange
		{
			int left = current * 2 + 1;
			int right = current * 2 + 2;
			if (left >= m_vec.size())break;
			int next = current;
			if (m_vec[next].first > m_vec[left].first)
				next = left;
			if (right < m_vec.size() && m_vec[next].first > m_vec[right].first)
				next = right;
			if (next == current) break;
			m_vec[current].swap(m_vec[next]);
			current = next;
		}
	};
};

#endif
