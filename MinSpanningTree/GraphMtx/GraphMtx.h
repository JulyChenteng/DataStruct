
//����ͼ�Ĵ���, �����ڽӾ���ķ�ʽ�洢
#include<iostream>
using namespace std;
#include <assert.h>

#define MAX_COST 0x7FFF		//�ٶ�ȨֵΪ����

template<class V, class E>
class CGraphMtx
{
public:
	CGraphMtx(int sz = DEFAULT_VTX_SIZE)
	{
		m_maxVtxSize = sz > DEFAULT_VTX_SIZE ? sz : DEFAULT_VTX_SIZE;

		m_vertex = new V[m_maxVtxSize];
		for (int i = 0; i < m_maxVtxSize; ++i)
		{
			m_vertex[i] = V();
		}

		m_edge = new E*[m_maxVtxSize];
		for (int i = 0; i < m_maxVtxSize; ++i)
		{
			m_edge[i] = new E[m_maxVtxSize];
		}

		for (int i = 0; i < m_maxVtxSize; ++i)
		{
			for (int j = 0; j < m_maxVtxSize; ++j)
			{
				if (i != j)
					m_edge[i][j] = MAX_COST;//��ʼ��ʱ�����ֵ��ʼ������ʾ������֮��û�б�
				else
					m_edge[i][j] = E();
			}
		}

		m_edgeSize = m_vtxSize = 0;
	}

	~CGraphMtx()
	{
		delete m_vertex;
		delete[]m_edge;
	}

public:
	bool isFull() const { return m_vtxSize >= m_maxVtxSize; }
	int numberOfVtx() const { return m_vtxSize; }
	int numberOfEdge() const { return m_edgeSize; }

	int getIdx(const V& v) const
	{
		for (int i = 0; i < m_vtxSize; ++i)
		{
			if (m_vertex[i] == v)
				return i;
		}

		return -1;
	}

public:
	bool insertVtx(const V& v);
	bool insertEdge(const V& vfst, const V& vscd, const E& weight);

	bool removeVtx(const V& v);						//ɾ������V�����������ı�
	bool removeEdge(const V& vfst, const V& vscd);	//ɾ���ߣ�vfst, vscd��

	int getFirstNeighbor(const V& v) const;				//ȡ����v�ĵ�һ���ڽӶ���
	int getNextNeighbor(const V& v, const V& w) const;	//ȡ����v���ڽӶ���w����һ�ڽӶ���

	void showGraph();

public:
	//��С������������ķ�㷨ʵ�ֺ�������
	bool MST_Prime(const V& vBegin);
	E& getWeight(int v1, int v2) { return m_edge[v1][v2];}

	bool MST_Kruskal();
	static int compare(const void *a, const void *b);

private:
	static const int DEFAULT_VTX_SIZE = 10;
	V *m_vertex;
	E **m_edge;
	
	int m_maxVtxSize;
	int m_vtxSize;
	int m_edgeSize;
};

///////////////////////////////////////////////////////////////////////

template<class V, class E>
bool CGraphMtx<V, E>::insertVtx(const V& v)
{
	if (isFull()) return false;

	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (v == m_vertex[i])
			return true;
	}

	m_vertex[m_vtxSize++] = v;
	return true;
}

//����ߣ�weightΪȨֵ
template<class V, class E>
bool CGraphMtx<V, E>::insertEdge(const V& vfst, const V& vscd, const E& weight)
{
	int vf = getIdx(vfst);
	int vs = getIdx(vscd);

	if (vs == -1 || vf == -1 || weight == MAX_COST)
		return false;

	if (m_edge[vf][vs] == MAX_COST)
	{
		m_edge[vf][vs] = m_edge[vs][vf] = weight;
		m_edgeSize++;
	}

	return true;
}

template<class V, class E>
bool CGraphMtx<V, E>::removeVtx(const V &v)
{
	int vIdx = getIdx(v);
	int num = 0;   
	if (vIdx == -1) return false;

	//��¼�뵱ǰ������صıߵ���Ŀ
	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (m_edge[vIdx][i] != E())
		{
			++num;
			m_edge[vIdx][i] = m_edge[i][vIdx] = MAX_COST; //ɾ����ö�����ص����б�
		}
	}

	//���������һ�к����һ��ǰ�Ƹ���Ҫɾ�����к���
	if (v != m_vtxSize)
	{
		for (int i = 0; i < m_vtxSize; ++i)
		{
			m_edge[vIdx][i] = m_edge[m_vtxSize-1][i];
			m_edge[i][vIdx] = m_edge[i][m_vtxSize-1];
		}

		m_vertex[vIdx] = m_vertex[m_vtxSize-1];
	}
	--m_vtxSize;
	m_edgeSize -= num;

	return true;
}

//ɾ���ߣ�vfst, vscd��
template<class V, class E>
bool CGraphMtx<V, E>::removeEdge(const V& vfst, const V& vscd)
{
	int vf = getIdx(vfst);
	int vs = getIdx(vscd);

	if (vf == -1 || vs == -1) return false;

	if (m_edge[vf][vs] != MAX_COST)
	{
		m_edge[vf][vs] = m_edge[vs][vf] = MAX_COST;
		m_edgeSize--;
	}

	return true;
}

//��ȡv�ĵ�һ���ڽӶ���
template<class V, class E>
int CGraphMtx<V, E>::getFirstNeighbor(const V& v) const
{
	int vIdx = getIdx(v);
	if (vIdx != -1)
	{
		for (int i = 0; i < m_vtxSize; ++i)
		{
			if (m_edge[vIdx][i] != MAX_COST)
				return i;
		}
	}

	return -1;
}

//ȡ����v���ڽӶ���w����һ��v���ڽӶ���
template<class V, class E>
int CGraphMtx<V, E>::getNextNeighbor(const V& v, const V& w) const
{
	int vIdx = getIdx(v);
	int wIdx = getIdx(w);

	if (wIdx != -1 && vIdx != -1)
	{
		for (int i = wIdx + 1; i < m_vtxSize; ++i)
		{
			if (m_edge[vIdx][i] != E())
				return i;
		}
	}

	return -1;	
}

template<class V, class E>
void CGraphMtx<V, E>::showGraph()
{
	cout << " ";
	for (int i = 0; i < m_vtxSize; ++i)
	{
		cout << "  " << m_vertex[i];
	}
	cout << endl;

	for (int i = 0; i < m_vtxSize; ++i)
	{
		cout << m_vertex[i] << "  ";
		for (int j = 0; j < m_vtxSize; ++j)
		{
			if (m_edge[i][j] == MAX_COST)
				cout << '#' << "  ";
			else
			cout << m_edge[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
/*
Prime�㷨������
�������ݽṹ��
		��С��ͬ�ڵ����һ����
		lowCost[i]:��ʾ��iΪ�յ�ıߵ���СȨֵ,��lowCost[i]=0˵����iΪ�յ�ıߵ���СȨֵ=0,Ҳ���Ǳ�ʾi�������MST
		mst[i]:��ʾ��Ӧlowcost[i]����㣬��˵����<mst[i],i>��MST��һ���ߣ���mst[i]=0��ʾ�����±�Ϊ0���յ�
	���±�Ϊi��
		��������ѡ��һ����ʼ�ڵ㣬��ʼ��lowCost[i]Ϊ��ʼ�ڵ㵽���������ڵ�ıߵ�Ȩֵ����������ڱ����ʼ��Ϊ�����MAX_COST��,
	ͼ�������Ի����������ǽ��Ի���Ϊ0��
		Ȼ������a.��lowCost���ҵ��뵱ǰ��ʼ�ڵ��Ȩֵ��С�ıߣ�b.��ñ�����Ӧ����һ�ڵ���Ϊ��ʼ�ڵ㣬����lowCost��mst[i],
	���µ�ʱ������Ǳȵ�ǰȨֵС��ʱ��Ÿ���,�����ܱ�֤����С���ظ�ִ����������a��b����ִ��n-1��(nΪ�������)����Ϊ��n���ڵ㣬
	������С�������϶���n-1���ߡ�
*/
template<class V, class E>
bool CGraphMtx<V, E>::MST_Prime(const V &vBegin/*��ʼ�ڵ�*/)
{
	int n = numberOfVtx();
	E *lowCost = new E[n];
	int *mst = new int[n];												  

	if (lowCost == NULL || mst == NULL) return false;

	int vf = getIdx(vBegin);
	for (int i = 0; i < n; ++i)
	{
		if (i != vf)
		{
			lowCost[i] = getWeight(vf, i);
			mst[i] = vf;
		}
		else
			lowCost[i] = 0;
	}

	int low = MAX_COST;  //��vf��������ڽӽڵ����С���ѣ���Ȩֵ��
	int lowIdx = -1;	 //�����С���Ѷ�Ӧ�Ľڵ���±�
	for (int i = 0; i < n - 1; ++i)
	{
		low = MAX_COST;
		lowIdx = -1;
		for (int j = 0; j < n; ++j)
		{
			if (low > lowCost[j] && lowCost[j] != 0)
			{
				low = lowCost[j];
				lowIdx = j;
			}
		}  //for j

		int begin = mst[lowIdx];
		int end = lowIdx;
		cout << m_vertex[begin] << "--->" << m_vertex[end] << ":" << m_edge[begin][end] << endl;
		lowCost[end] = 0;

		for (int i = 0; i < n; ++i)
		{
			int weight = getWeight(end, i);
			if (weight < lowCost[i])
			{
				lowCost[i] = weight;
				mst[i] = end;
			}
		}
	} //for i

	return true;
}


/*
kruskal(��³˹����)�㷨��
	������Ӹ����ṹ��Edge����¼��ǰ�ߵ���㣬�յ��Ȩֵ��Ȼ�����߽ṹ�����¼��ǰͼ�����бߵ���Ϣ��
Ȼ������б߰�Ȩֵ���򣬷��㽨����С��������������С������ʱ�����Ǵ���С�ı߿�ʼȡ��ÿ��ȡ������ʱ����Ҫ�ж�
�ñߵ�ǰ��ڵ��Ƿ�����ͬһ�������������ͬһ���������Ӿͻ����ɻ�·�����ԣ����Ǿͺ��Ըøñߣ�ȡ��һ���ߣ����
����ͬһ��ͨ������������mark_Same������������������ʹ�䴦��ͬһ��ͨ������ע������������˵����ͨ��ͨ��
father����ʵ�ֵģ����޸�father[i]�ı�i�ڸ���ͨ�����еĵ���һ���ڽӶ��㣬������ֱ������ȡ�����һ�����һ��
�ߣ���ʱ�õ�����ͨ�������Ǹ�ͼ����С��������
*/

template<class E>
class Edge
{
	template<class V> friend  ostream& operator<<(ostream& os, Edge<V> &e);
public:
	static int compare(const void *a, const void *b);
	bool is_Same(int *ft);
	void mark_Same(int *ft);

public:
	int x;	//start
	int y;	//end
	E cost;
};

//�жϱ�Ȩֵ�Ĵ�С����������
template<class E>
int Edge<E>::compare(const void *a, const void *b)
{
	return (*(Edge<E>*)a).cost - (*(Edge<E>*)b).cost;
}

//�жϵ�ǰ�ڵ�ͼ������������Ľڵ��Ƿ�����ͬһ��ͨ����
template <class E>
bool Edge<E>::is_Same(int *ft)
{
	int i = this->x; 
	int j = this->y;

	while (ft[i] != i)
		i = ft[i];
	while (ft[j] != j)
		j = ft[j];

	return i == j;
}

//���ӵ�ǰ���㣬ʹ����������Ľڵ㴦��ͬһ��ͨ����
template <class E>
void Edge<E>::mark_Same(int *ft)
{
	int i = this->x;
	int j = this->y;				                                                   

	while (ft[i] != i)
		i = ft[i];
	while (ft[j] != j)
		j = ft[j];

 	ft[j] = i;
}

template<class V, class E>
bool CGraphMtx<V, E>::MST_Kruskal()
{
	int n = numberOfVtx();
	int size = n*(n - 1) / 2;

	Edge<E> *edge = (Edge<E> *)malloc(sizeof(Edge<E>)*size);
	if (edge == NULL)	return false;

	//��¼���бߵ���Ϣ
	int k = 0; 
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if (m_edge[i][j] != 0 && m_edge[i][j] != MAX_COST)
			{
				edge[k].x = i;
				edge[k].y = j;
				edge[k].cost = m_edge[i][j];
				k++;
			}
		}	 //for i
	} //for i

	//���մ�С��������
 	qsort(edge,k, sizeof(Edge<E>), Edge<E>::compare);

	int *father = new int[n];
	if (father == NULL) return false;

	for (int i = 0; i < n; ++i)
		father[i] = i;     //��ʼʱÿ�����㶼�Ƕ����ģ����ڵ㶼������

	int vbegin, vend;
	for (int i = 0; i < size; ++i)
	{
		if (!edge[i].is_Same(father))
		{
			vbegin = edge[i].x;
			vend = edge[i].y;
			cout << m_vertex[vbegin] << "-->" << m_vertex[vend] << " : " << edge[i] << endl;
			edge[i].mark_Same(father);
		}
	}

	return true;
}

template<class E>
ostream& operator<<(ostream& os, Edge<E> &e)
{
	cout << e.cost << " ";
	return os;
}
