#pragma once

//����ͼ�Ĵ��� �洢��ʽ���ڽӱ�
#include <iostream>
using namespace std;


template<class V, class E> class CGraphLnk;
const int DEFAULT_VTX_SIZE = 10;

////////////////////////////////////////////////////////////////////////////////////
//the declaration of edge
template<class V, class E>
class Edge
{
	friend class CGraphLnk<V, E>;

public:
	Edge(int num, E wt): dest(num), weight(wt), pNext(NULL) {}

private:
	int dest;
	E weight;
	Edge<V, E> *pNext;
};

//////////////////////////////////////////////////////////////////////////
//the declaration of vertex
template<class V, class E>
class Vertex
{
	friend class CGraphLnk<V, E>;

public:
	Vertex() : data(V()), adj(NULL) {}
	Vertex(const V& d) : data(d), adj(NULL) {}

	Vertex& operator=(const Vertex& v)
	{
		if (this != &v)
		{
			this->data = v.data;
			this->adj = v.adj;
		}

		return *this;
	}

private:
	V data;
	Edge<V, E> *adj;  //�ö���ĵ�һ���ڽӶ���
};

/////////////////////////////////////////////////////////////////////////
//the declaration of CGraphLnk
template<class V, class E>
class CGraphLnk
{
public:
	CGraphLnk(int sz = DEFAULT_VTX_SIZE)
	{
		m_maxVtxSize = sz > DEFAULT_VTX_SIZE ? sz : DEFAULT_VTX_SIZE;
		m_edgeSize = m_vtxSize = 0;
		m_vtxTable = new Vertex<V, E>[m_maxVtxSize];
	}
	~CGraphLnk()
	{
		Edge<V, E> *e = NULL;
		for (int i = 0; i < m_vtxSize; ++i)
		{
			while((e = m_vtxTable[i].adj) != NULL)
			{
				m_vtxTable[i].adj = e->pNext;
				delete e;
			}
			e = NULL;
		}

		delete[]m_vtxTable;
	}

public:
	bool insertVtx(const V& v);
	bool insertEdge(const V& vfst, const V& vscd, const E& weight);
	bool removeVtx(const V& v);
	bool removeEdge(const V& vfst, const V& vscd);

	void showGraph();

public:
	int getIdx(const V& v) const;
	V getElement(const int index) const	{ return (index >= 0 && index < m_vtxSize) ? m_vtxTable[index].data : V(); }
	int	getFirstNeighbor(const V& v) const
	{
		int vIdx = getIdx(v);
		if (vIdx != -1)
		{
			Edge<V, E> *e = m_vtxTable[vIdx].adj;
			return e->dest;
		}

		return -1;
	}

	//����v���ڽӶ���w��ʼ����һ��v����Ӷ���
	int getNextNeighbor(const V& v, const V& w) const
	{
		int vIdx = getIdx(v);
		int wIdx = getIdx(w);
		if (vIdx != -1)
		{
			Edge<V, E> *e = m_vtxTable[vIdx].adj;
			while (e != NULL && e->dest != wIdx) //Ѱ���ڽӶ���w��λ��
				e = e->pNext;

			if (e != NULL && e->pNext != NULL)	//ͨ����λ���ж��Ƿ�����һ���ڽӶ���
				return e->pNext->dest;
		}

		return -1;
	}

	int numberOfVertex() const { return m_vtxSize; }
	int numberOfEdge() const { return m_edgeSize; }

private:
	Vertex<V, E> *m_vtxTable;
	int m_maxVtxSize;
	int m_edgeSize;
	int m_vtxSize;
};

////////////////////////////////////////////////////////////////////////////////////
//the definitions of functions declared in CGraphLnk
template<class V, class E>
bool CGraphLnk<V, E>::insertVtx(const V& v)
{
	if (m_vtxSize >= m_maxVtxSize) return false;

	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (m_vtxTable[i].data == v)
			return true;
	}

	m_vtxTable[m_vtxSize].data = v;
	m_vtxTable[m_vtxSize].adj = NULL;
	++m_vtxSize;
	return true;
}

template<class V, class E>
int CGraphLnk<V, E>::getIdx(const V& v) const
{
	Vertex<V, E> *p = m_vtxTable;
	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (m_vtxTable[i].data == v)
			return i;
	}
	return -1;
}

template<class V, class E>
bool CGraphLnk<V, E>::insertEdge(const V& vfst, const V& vscd, const E& weight)
{
	int vf = getIdx(vfst);
	int vs = getIdx(vscd);

	if (vf == -1 || vs == -1)
		return false;
	
	Edge<V, E> *tmp = m_vtxTable[vf].adj;
	while (tmp != NULL && tmp->dest != vs)
		tmp = tmp->pNext;

	if (tmp != NULL) return true;			//�Ѿ����ڷ���true�����Ǳߵ���������

	//�ڵ����ѡ��ǰ��ķ�ʽ
	Edge<V, E> *newEdge = new Edge<V, E>(vs, weight);
	newEdge->pNext = m_vtxTable[vf].adj;
	m_vtxTable[vf].adj = newEdge;

	tmp = new Edge<V, E>(vf, weight);
	tmp->pNext = m_vtxTable[vs].adj;
	m_vtxTable[vs].adj = tmp;

	++m_edgeSize;

	return true;
}

/*
ɾ��һ�����㣺
˼�룺
	��ɾ����ýڵ���ص����бߣ���ȥ���ýڵ㡣
ʵ��ϸ�ڣ�
	�����ڽӱ��ҵ��ýڵ㣬Ȼ����Ҹýڵ����������Ƿ�Ϊ�գ���Ϊ������������ҵ���ýڵ��Ӧ�ĵ�һ���ߣ�
Ȼ�󽫸ñ�ɾ����ͬʱ���ñ�����һ���ڵ�����ñ߶�Ӧ�ı�ɾ��������ظ�������ֱ������ɾ���Ľڵ��йص����б�ɾ��
Ϊֹ����ʱ�����һ���ڵ㼰����Ӧ�ı�������Ҫɾ���ڵ��λ�á�
*/
template<class V, class E>
bool CGraphLnk<V, E>::removeVtx(const V& v)
{
	int vIdx = getIdx(v);
	Edge<V, E> *q = NULL,*p = NULL, *tmp = NULL;

	if (vIdx == -1) return false;

	while ((p = m_vtxTable[vIdx].adj) != NULL)
	{	
		m_vtxTable[vIdx].adj = p->pNext;
		int eIdx = p->dest;

		tmp = q = m_vtxTable[eIdx].adj;
		delete p;
		p = NULL;

		//ɾ����ýڵ��ڽӽڵ��ж�Ӧ�ı�
		while (q != NULL )		
		{
			//�ҵ���Ӧ��
			if (q->dest == vIdx)
			{
				//ͬtmp��ֵ�жϸñ�����λ�ã���Ϊ����λ�ò�ͬ��ɾ��������ӷ�ʽ��ͬ
				if (tmp == q)
					m_vtxTable[eIdx].adj = q->pNext;
				else
					tmp->pNext = q->pNext;
				
				delete q;
				q = NULL;
				--m_edgeSize;
			}
			else  //δ�ҵ���Ӧ��
			{
				tmp = q;
				q = q->pNext;
			}
		}//while	
	}//while

	m_vtxTable[vIdx] = m_vtxTable[--m_vtxSize];
	//�໥����֮��������Ҫ����һ��ԭ�������һ���ڵ������ı�����һ���ڵ���±�
	m_vtxTable[m_vtxSize].data = V();
	m_vtxTable[m_vtxSize].adj = NULL;

	p = m_vtxTable[vIdx].adj;
	while (p != NULL)
	{
		tmp = m_vtxTable[p->dest].adj;
		while (tmp != NULL)
		{
			if (tmp->dest = m_vtxSize)
			{
				tmp->dest = vIdx;
				break;
			}
			tmp = tmp->pNext;
		}

		p = p->pNext;
	}

	return true;
}

template<class V, class E>
bool CGraphLnk<V, E>::removeEdge(const V& vfst, const V& vscd)
{
	int vf = getIdx(vfst); 
	int vs = getIdx(vscd);
	Edge<V, E> *e = NULL, *p = NULL;

	if (vf == -1 || vs == -1)	return false;
	
	//��vfst��Ӧ�����в��ұ�ɾ��
	e = p = m_vtxTable[vf].adj;
	while (e != NULL && e->dest != vs)
	{
		p = e;
		e = e->pNext;
	}

	//�ö������������ı�
	if (e != NULL)
	{
		if (e == p)	 //�ҵ��Ľڵ���������׽ڵ�
			m_vtxTable[vf].adj = e->pNext;
		else		 //�����׽ڵ�
			p->pNext = e->pNext;

		delete e;	e = NULL;
	}
	else
		return false;

	//��vscd��Ӧ�����в������������Ӧ�ı�
	p = e = m_vtxTable[vs].adj;
	while (e->dest != vf)
	{
		p = e;
		e = e->pNext;
	}

	if (e == p)
		m_vtxTable[vs].adj = e->pNext;
	else
		p->pNext = e->pNext;

	delete e;	e = NULL;
	--m_edgeSize;

	return true;
}

template<class V, class E>
void CGraphLnk<V, E>::showGraph()
{
	for (int i = 0; i < m_vtxSize; ++i)
	{
		cout << m_vtxTable[i].data << "-->";
		Edge<V, E> *e = m_vtxTable[i].adj;
		while (e != NULL)
		{
			cout << e->dest << "-->";
			e = e->pNext;
		}
		cout << "Nul." << endl;
	}
}