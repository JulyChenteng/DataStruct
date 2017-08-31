#pragma once 

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include <list>
using namespace std;

typedef int KeyType;
typedef struct
{
	KeyType key;
} DataType;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
void insertSort(DataType data[], int len)
{
	DataType temp;
	int j = 0;

	for (int i = 1; i < len; i++)		//���ν�data[1]~data[len-1]���뵽ǰ�������������
	{
		temp = data[i];			   
		for (j = i - 1; temp.key < data[j].key; --j) //�Ӻ���ǰ���Ҵ�����λ��
			data[j + 1] = data[j];							      //�����λ
		data[j + 1] = temp;								  //���Ƶ�����λ��			
	}
}

void shellInsert(DataType data[], int len, int dk)
{
	int j;
	DataType temp;
	for (int i = dk; i < len; ++i)
	{
		if (data[i].key < data[i - dk].key)
		{
			temp = data[i];
			for (j = i - dk; j>=0 && temp.key<data[j].key; j -= dk)
			{
				data[j + dk] = data[j];
			}
			data[j + dk] = temp;
		}
	}
}

void shellSort(DataType data[], int len, int dlta[], int t)
{
	for (int k = 0; k<t; ++k)
	{
		shellInsert(data, len, dlta[k]);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////

void bubbleSort(DataType data[], int len)
{
	int flag = 1;
	DataType temp;

	for (int i = 0; i < len - 1 && flag == 1; ++i)
	{
		flag = 0;
		for (int j = len - 1; j > i; --j)
		{
			if (data[j - 1].key > data[j].key)	
			{
				flag = 1;
				temp = data[j-1];
				data[j - 1] = data[j];
				data[j] = temp;
			}
		}
	}
}

int partition(DataType data[], int low, int high)
{
	DataType temp = data[low];
	while (low < high)
	{
		while (low < high && temp.key <= data[high].key)
			--high;
		data[low] = data[high];
	
		while (low < high && temp.key >= data[low].key)
			++low;
		data[high] = data[low];
	}

	data[low] = temp;
	return low;
}
  

/*
int partition(DataType data[], int low, int high)
{
	DataType privot = data[high];	    //ȡ���һλ��Ϊ��׼
	DataType tmp;
	int pos = low - 1;
	for (int j = low; j < high; ++j)
	{
		if (privot.key >= data[j].key)
		{
			++pos;
			tmp = data[pos];
			data[pos] = data[j];
			data[j] = tmp;
		}
	}
	tmp = data[pos + 1];
	data[pos + 1] = data[high];
	data[high] = tmp;
	return pos + 1;
}
*/
void quickSort(DataType data[], int low, int high)
{
	if (low < high)
	{
		int pos = partition(data, low, high);

		if (pos-1 > low)
			quickSort(data, low, pos-1);
		if (pos+1 < high)
			quickSort(data, pos + 1, high);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void selectSort(DataType data[], int len)
{
	DataType temp;
	int min;

	for (int i = 0; i < len - 1; ++i)
	{
		min = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (data[j].key < data[min].key)
				min = j;
		}

		if (min != i)
		{
			temp = data[i];
			data[i] = data[min];
			data[min] = temp;
		}
	}
}		  

void siftDown(DataType data[], int curIdx, int maxIdx)
{
	int curPos = curIdx, leftIdx = 2 * curPos + 1;
	DataType tmp;

	while (leftIdx <= maxIdx)
	{
		if (leftIdx < maxIdx && data[leftIdx].key < data[leftIdx + 1].key)
			++leftIdx;

		if (data[leftIdx].key > data[curPos].key)
		{
			tmp = data[leftIdx];
			data[leftIdx] = data[curPos];
			data[curPos] = tmp;

			curPos = leftIdx;
			leftIdx = 2 * curPos + 1;
		}
		else
			break;
	}
}

void createHeap(DataType data[], int len)
{
	for (int i = (len/2 - 1); i >= 0; --i)
		siftDown(data, i, len - 1);
}

void heapSort(DataType data[], int len)
{
	DataType temp;
	int lastIndex = len - 1;

	createHeap(data, len);
	while (lastIndex > 0)
	{
		temp = data[0];
		data[0] = data[lastIndex];
		data[lastIndex] = temp;

		--lastIndex;
		siftDown(data, 0, lastIndex);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

//�����������ϲ�
void merge(DataType data[], int len, DataType result[], int grpLen)
{
	int leftStart = 0, leftEnd = leftStart+grpLen-1, rightStart, rightEnd;
	int index = 0;
	int i = 0, j = 0;

	while (leftEnd < len - 1)
	{
		rightStart = leftStart + grpLen;
		rightEnd = (rightStart + grpLen - 1 >= len - 1) ? len - 1 : rightStart + grpLen - 1;

		for (i = leftStart, j = rightStart; i <= leftEnd && j <= rightEnd;)
		{
			if (data[i].key < data[j].key)
				result[index++] = data[i++];
			else
				result[index++] = data[j++];
		}
		while (i <= leftEnd)
			result[index++] = data[i++];
		while (j <= rightEnd)
			result[index++] = data[j++];	

		leftStart = rightEnd + 1;
		leftEnd = leftStart + grpLen - 1;
	}
	//����ʣ���Ԫ��
	for (i = leftStart; i < len; ++i)
		result[index++] = data[i];
}

void mergeSort(DataType data[], int len)
{
	DataType *result = (DataType *)malloc(sizeof(DataType)* len);
	memset(result, 0, sizeof(DataType)*len);

	//grplen��1��ʼ
	for (int grplen = 1; grplen <= len; grplen *= 2)
	{
		merge(data, len, result, grplen);
		for (int i = 0; i < len; ++i)
			data[i] = result[i];
	}

	free(result);
	result = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
int getKey(KeyType value, int k)
{
	int key = -1;
	while (k >= 0)
	{
		key = value % 10;
		value /= 10;
		--k;
	}
	return key;
}

void radixSort(DataType data[], int left, int right, int d) //d����λ��
{
	int count[10] = { 0 };
	int i, j;
	int p1, p2;
	DataType *result = (DataType *)malloc(sizeof(DataType)* (right-left+1));

	if (d <= 0)						   //λ��������ݹ����
		return;

	for (i = left; i <= right; i++)					   //ͳ��Ͱ��Ԫ�ظ���
		count[getKey(data[i].key, d)]++;
	for (j = 1; j < 10; j++)							 //�ҳ�����Ͱ��Ԫ�ذ���λ�õı߽�
		count[j] = count[j] + count[j - 1];

	//���������������������Ͱ�У����ڸ�������result��
	for (int i = left; i <= right; i++)
	{
		j = getKey(data[i].key, d);			  //ȡԪ��data[i].key�ĵ�dλ
		result[count[j]-1] = data[i];		  //������õ�λ�ô��
		count[j]--;									  //��������1
	}

	for (i = left, j = 0; i <= right; i++, j++)
		data[i] = result[j];						 //�Ӹ�������д��ԭ����

	free(result);
	result = NULL;
	for (j = 0; j < 10; j++)				   //��Ͱ�ݹ��d-1λ����
	{
		p1 = count[j];						   //ȡͰʼ��
		p2 = count[j + 1] - 1;			   //ȡͰβ��
		radixSort(data, p1, p2, d-1);
	}
}		 

/*
int getKey(KeyType value, int k)
{
	int key = -1;
	while (k >= 0)
	{
		key = value % 10;
		value /= 10;
		--k;
	}
	return key;
}

void distribute(DataType data[], int len, list<DataType>(&lst)[10], int k)
{
	for (int i = 0; i < 10; ++i)
		lst[i].clear();

	int key;
	for (int j = 0; j < len; ++j)
	{
		key = getKey(data[j].key, k);
		lst[key].push_back(data[j]);
	}
}

void collect(DataType data[], list<DataType>(&lst)[10])
{
	int k = 0;
	for (int i = 0; i < 10; ++i)
	{
		while (!lst[i].empty())
		{
			data[k++] = lst[i].front();
			lst[i].pop_front();
		}
	}
}

void radixSort(DataType data[], int len, int d) //d����λ��
{
	list<DataType> lst[10];
	for (int i = 0; i < d; ++i)
	{
		distribute(data, len, lst, i);
		collect(data, lst);
	}
}
*/