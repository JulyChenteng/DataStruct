//��С�ѵĶ���
//��С����ʵ������һ�����ȼ����У��������룬ɾ�Ӷ���ɾ������ɾ��������СԪ��,������������ԽС���ȼ�Խ��
#pragma once

#include <iostream>
using namespace std;

template<class Type>
class MinHeap
{
public:
	MinHeap(int sz = DEFAULT_HEAP_SIZE)
	{
		m_capacity = sz > DEFAULT_HEAP_SIZE ? sz : DEFAULT_HEAP_SIZE;
		m_heap = new Type[m_capacity];
		if (NULL == m_heap)
		{
			cout << "Allot memory failed!" << endl;
			exit(1);
		}

		m_size = 0;
	}
	MinHeap(Type arr[], int len)
	{
		m_capacity = len > DEFAULT_HEAP_SIZE ? len : DEFAULT_HEAP_SIZE;
		m_heap = new Type[m_capacity];
		if (NULL == m_heap)
		{
			cout << "Allot memory failed!" << endl;
			exit(1);
		}

		for (int i = 0; i < len; ++i)	m_heap[i] = arr[i];
		m_size = len;

		//����������Ϊ��С��
		int pos = m_size / 2 - 1;     //�����һ����֧��ʼ��������¼���һ����֧�ĸ��ڵ���±�
		while (pos >= 0)
		{
			siftDown(pos, m_size - 1);//�ֲ��������µ���
			--pos;  
		}
	}

public:
	bool IsEmpty() const { return m_size == 0; }
	bool IsFull()  const { return m_size >= m_capacity; }
	int  GetSize() const { return m_size; }

	bool Insert(const Type &x);
	bool RemoveMin(Type &x);
	void ShowHeap();

private:
	void siftDown(int curIdx, int maxIdx/*���һ���ڵ���±�*/);
	void siftUp(int curIdx);

private:
	enum{DEFAULT_HEAP_SIZE = 10};
	Type *m_heap;
	int m_size;
	int m_capacity;
};


/////////////////////////////////////////////////////////////////////////
//��С�����µ����㷨��ʵ��
/*�����ҽڵ�����С���Ǹ��͸��ڵ㽻��*/
template<class Type>
void MinHeap<Type>::siftDown(int curIdx, int maxIdx)
{
	int curPos = curIdx, leftIdx = 2 * curPos + 1;
	
	while (leftIdx <= maxIdx)
	{
		if (leftIdx < maxIdx && m_heap[leftIdx] > m_heap[leftIdx + 1])
			++leftIdx;

		if (m_heap[leftIdx] < m_heap[curPos])
		{
			Type tmp = m_heap[leftIdx];
			m_heap[leftIdx] = m_heap[curPos];
			m_heap[curPos] = tmp;

			curPos = leftIdx;
			leftIdx = 2 * curPos + 1;
		}
		else
			break;
	}
}

//��С�����ϵ����㷨
/*�븸�ڵ���Ƚϣ����С�򽻻�������ֵ�����򲻱�*/
template<class Type>
void MinHeap<Type>::siftUp(int curIdx)
{
	int curPos = curIdx, pIdx = (curPos-1)/2;
	while (pIdx > 0)
	{
		if (m_heap[curPos] > m_heap[pIdx]) break;
		else
		{
			Type tmp = m_heap[pIdx];
			m_heap[pIdx] = m_heap[curPos];
			m_heap[curPos] = tmp;

			curPos = pIdx;
			pIdx = (curPos - 1) / 2;
		}
	}
}

//�����㷨��ÿ�ν�Ԫ�ز������ѵ����Ȼ�����ϵ�����
template<class Type>
bool MinHeap<Type>::Insert(const Type &x)
{
	if (IsFull()) { cout << "This is a full heap!" << endl; return false; }

	m_heap[m_size] = x;
	siftUp(m_size);
	++m_size;

	return true;
}

//ɾ���㷨��
/*ÿ��ɾ���Ķ��ǶѶ�Ԫ�أ�������С��Ԫ�أ�Ȼ�������һ��Ԫ��ȡ���Ѷ�Ԫ�أ������µ�����*/
template<class Type>
bool MinHeap<Type>::RemoveMin(Type &x)
{
	if (IsEmpty()){ cout << "This is an empty heap!" << endl;  return false; }
	
	x = m_heap[0];
	m_heap[0] = m_heap[m_size-1];
	--m_size;
	siftDown(0, m_size-1);
	return true;
}

//
template<class Type>
void MinHeap<Type>::ShowHeap()
{
	for (int i = 0; i < m_size; i++)
		cout << m_heap[i] << " ";
	cout << endl;
}
