#ifndef _GRAPHLIST_H_
#define _GRAPHLIST_H_

/***************************************************************************
  
  ��ͷ�ļ�������Ǳ�ʾ  ��Ȩ  ��ͼ��  �ڽӱ�ʹ��ʱ��ע�⣡��

***************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<climits>
#include"LinkedQueue.h"
using namespace std;

#define LIST_VERTICES_DEFAULT_SIZE 20

//IsConnected�����еĽڵ���ʷ�ʽ��Ϊ�գ�
template<class _vertex>
void IsConnected_visit(_vertex vertex)
{

}

template<class _vertex,class _edge>
struct Edge {
	int dest;
	_edge cost;
	Edge<_vertex, _edge>* link;

	Edge() :dest(-1), link(NULL) {}
	Edge(const int num, const _edge weight, Edge<_vertex, _edge>* first = NULL) :dest(num), cost(weight), link(first) {}

	inline bool operator!=(const Edge<_vertex, _edge>& edge)const
	{
		return (dest != edge.dest);
	}
};

template<class _vertex,class _edge>
struct Vertex {
	_vertex data;
	Edge<_vertex, _edge>* adj;
};

template<class _vertex,class _edge>
class GraphList {
private:
	int maxVertices;
	int numEdges;
	int numVertices;
	Vertex<_vertex, _edge>* NodeTable;
	const bool if_directed;

	typedef void(*_GraphListVisitFunction)(_vertex vertex);

	void DFS_Recursion(const int v, bool visited[], _GraphListVisitFunction visit)const;
	bool IsNonDirectedConnected()const;
public:
	GraphList(const bool ifDirected, const int sz = LIST_VERTICES_DEFAULT_SIZE);
	GraphList(const bool ifDirected, const GraphList<_vertex, _edge>& graph);
	~GraphList();

	int NumOfVertices()const;
	int NumOfEdges()const;
	void ShowList()const;
	bool IsVerticesEmpty()const;
	bool IsEdgesEmpty()const;
	bool IsVerticesFull()const;
	bool IsEdgesFull()const;
	bool IsConnected()const;
	int getVertexPos(_vertex vertex)const;
	bool getVertex(_vertex& vertex, const int pos)const;
	bool getEdge(_edge& edge, const int v1, const int v2)const;
	int getFirstNeighbor(const int v)const;
	int getNextNeighbor(const int v, const int w)const;
	bool insertVertex(const _vertex vertex);
	bool insertEdge(const int v1, const int v2, _edge cost);
	bool removeVertex(const int v);
	bool removeEdge(const int v1, const int v2);

	void DFS_Single(const _vertex v, _GraphListVisitFunction visit)const;
	void DFS_All(_GraphListVisitFunction visit)const;
	void BFS_Single(const _vertex v, _GraphListVisitFunction visit, bool Visited[] = NULL)const;
	void BFS_All(_GraphListVisitFunction visit)const;

	GraphList<_vertex, _edge>& operator=(const GraphList<_vertex, _edge>& graph);

	template<class V, class E>  //���ǳ�Ա��������Ҫ���Լ���ģ��
	friend istream& operator>>(istream& in, GraphList<V, E>& Graph);

	template<class V, class E>  //���ǳ�Ա��������Ҫ���Լ���ģ��
	friend ostream& operator<<(ostream& out, const GraphList<V, E>& Graph);
};

//���غ���������
template<class _vertex, class _edge>
istream& operator>>(istream& in, GraphList<_vertex, _edge>& Graph)
{
	int ver_num, edge_num;
	_vertex v1, v2;
	_edge edge;

	in >> ver_num >> edge_num;

	for (int i = 0; i < ver_num; i++) {
		in >> v1;
		Graph.insertVertex(v1);
	}

	int count = 0;
	while (count < edge_num) {
		in >> v1 >> v2 >> edge;

		int e1 = Graph.getVertexPos(v1);
		int e2 = Graph.getVertexPos(v2);

		if (e1 == -1 || e2 == -1) {
			cout << "�����˵���Ϣ����������������룡" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
			
		else {
			Graph.insertEdge(e1, e2, edge);
			count++;
		}
	}

	return in;
}

//���غ��������
template<class _vertex, class _edge>
ostream& operator<<(ostream& out, const GraphList<_vertex, _edge>& Graph)
{
	const int ver_num = Graph.NumOfVertices();
	const int edge_num = Graph.NumOfEdges();
	out << "vertices:" << ver_num << endl;
	out << "edges:" << edge_num << endl;

	for (int i = 0; i < ver_num; i++) {
		for (int j = 0; j < ver_num; j++) {  //����ͼ��i+1��ʼ
			_edge e;
			bool if_get = Graph.getEdge(e, i, j);

			if (if_get) {
				_vertex v1, v2;
				Graph.getVertex(v1, i);
				Graph.getVertex(v2, j);
				out << '<' << v1 << ',' << v2 << '>' << "-->" << e << endl;
			}
		}
	}

	return out;
}

//ָ����С�Ĺ��캯��
template<class _vertex, class _edge>
GraphList<_vertex, _edge>::GraphList(const bool ifDirected, const int sz) : if_directed(ifDirected)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;

	NodeTable = new Vertex<_vertex, _edge>[maxVertices];
	if (NodeTable == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < maxVertices; i++)
		NodeTable[i].adj = NULL;
}

//���ƹ��캯��
template<class _vertex, class _edge>
GraphList<_vertex, _edge>::GraphList(const bool ifDirected, const GraphList<_vertex, _edge>& Graph) : if_directed(ifDirected)
{
	maxVertices = Graph.maxVertices;
	numVertices = Graph.numVertices;
	numEdges = Graph.numEdges;

	NodeTable = new Vertex<_vertex, _edge>[maxVertices];
	if (NodeTable == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < numVertices; i++) {
		NodeTable[i].data = Graph.NodeTable[i].data;

		Edge<_vertex, _edge>* src = Graph.NodeTable[i].adj, * newNode, * current = NULL;

		if (src == NULL)
			NodeTable[i].adj = NULL;

		while (src != NULL) {
			newNode = new Edge<_vertex, _edge>(src->dest, src->cost);
			if (newNode == NULL) {
				cerr << "�洢����ʧ�ܣ�" << endl;
				exit(1);
			}

			if (src == Graph.NodeTable[i].adj)
				NodeTable[i].adj = newNode;
			else
				current->link = newNode;
			current = newNode;

			src = src->link;
		}
	}
}

//��������
template<class _vertex,class _edge>
GraphList<_vertex, _edge>::~GraphList()
{
	for (int i = 0; i < numVertices; i++) {
		Edge<_vertex, _edge>* p = NodeTable[i].adj;

		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}

	delete[] NodeTable;
}

//���ض���vertex�ڶ�����е�λ��
template<class _vertex, class _edge>
int GraphList<_vertex, _edge>::getVertexPos(_vertex vertex)const
{
	for (int i = 0; i < numVertices; i++) {
		if (NodeTable[i].data == vertex)
			return i;
	}

	return -1;
}

//DFS�ݹ鲿��
template<class _vertex, class _edge>
void GraphList<_vertex, _edge>::DFS_Recursion(const int v, bool visited[], _GraphListVisitFunction visit)const
{
	_vertex ver;
	getVertex(ver, v);
	visit(ver);

	visited[v] = true;
	int w = getFirstNeighbor(v);

	while (w != -1) {
		if (visited[w] == false)
			DFS_Recursion(w, visited, visit);

		w = getNextNeighbor(v, w);
	}
}

//���ص�ǰ������
template<class _vertex, class _edge>
int GraphList<_vertex, _edge>::NumOfVertices()const
{
	return numVertices;
}

//���ص�ǰ����
template<class _vertex, class _edge>
int GraphList<_vertex, _edge>::NumOfEdges()const
{
	return numEdges;
}

//չʾ�ڽӱ�
template<class _vertex, class _edge>
void GraphList<_vertex, _edge>::ShowList()const
{
	for (int i = 0; i < numVertices; i++) {
		cout << NodeTable[i].data << "->";
		Edge<_vertex, _edge>* p = NodeTable[i].adj;

		while (p != NULL) {
			if (p->link != NULL)
				cout << p->dest << "->";
			else
			 	cout << p->dest << endl;

			p = p->link;
		}
	}
}

//�ж�ͼ�Ķ������Ƿ�Ϊ��
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::IsVerticesEmpty()const
{
	return (numVertices == 0);
}

//�ж�ͼ�ı����Ƿ�Ϊ��
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::IsEdgesEmpty()const
{
	return (numEdges == 0);
}

//�ж�ͼ�Ķ������Ƿ�����
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::IsVerticesFull()const
{
	if (numVertices == maxVertices)
		return true;
	else
		return false;
}

//�ж�ͼ�ı����Ƿ�����
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::IsEdgesFull()const
{
	const int limit = if_directed ? numVertices * (numVertices - 1) : numVertices * (numVertices - 1) / 2;

	if (numEdges == limit)
		return true;
	else
		return false;
}

//�ж�һ������ͼ�Ƿ���ͨ
template<class _vertex,class _edge>
bool GraphList<_vertex, _edge>::IsNonDirectedConnected()const
{
	if (numVertices != 1 && IsEdgesEmpty())
		return false;

	bool* visited = new bool[numVertices];
	if (visited == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < numVertices; i++)
		visited[i] = false;

	BFS_Single(NodeTable[0].data, IsConnected_visit<_vertex>, visited);

	for (int i = 0; i < numVertices; i++) {
		if (!visited[i])
			return false;
	}

	delete[] visited;
	return true;
}

//�ж�һ��ͼ�Ƿ���ͨ����Ϊ����ͼ���ж��Ƿ�Ϊ����ͨ��
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::IsConnected()const
{
	if (!if_directed)
		return IsNonDirectedConnected();

	GraphList<_vertex, _edge> graph(false, numVertices);
	for (int i = 0; i < numVertices; i++)
		graph.insertVertex(NodeTable[i].data);

	for (int i = 0; i < numVertices; i++) {
		Edge<_vertex, _edge>* p = NodeTable[i].adj;

		while (p != NULL) {
			graph.insertEdge(i, p->dest, p->cost);
			p = p->link;
		}
	}

	return graph.IsNonDirectedConnected();
}

//ȡ����pos��pos��������false
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::getVertex(_vertex& vertex, const int pos)const
{
	if (pos < 0 || pos >= numVertices)
		return false;

	vertex = NodeTable[pos].data;
	return true;
}

//ȡ��<v1,v2>��(v1,v2)�ϵ�Ȩֵ
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::getEdge(_edge& edge, const int v1, const int v2)const
{
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
		return false;

	Edge<_vertex, _edge>* p = NodeTable[v1].adj;
	
	while (p != NULL && p->dest != v2)
		p = p->link;

	if (p != NULL) {
		edge = p->cost;
		return true;
	}

	return false;
}

//ȡ����v�ĵ�һ���ڽӶ���
template<class _vertex, class _edge>
int GraphList<_vertex, _edge>::getFirstNeighbor(const int v)const
{
	if (v >= 0 && v < numVertices) {
		Edge<_vertex, _edge>* p = NodeTable[v].adj;

		if (p != NULL)
			return p->dest;
	}

	return -1;
}

//ȡv�ڽӶ���w����һ�ڽӶ���
template<class _vertex, class _edge>
int GraphList<_vertex, _edge>::getNextNeighbor(const int v, const int w)const
{
	if (v >= 0 && v < numVertices && w >= 0 && w < numVertices) {
		Edge<_vertex, _edge>* p = NodeTable[v].adj;

		while (p != NULL && p->dest != w)
			p = p->link;

		if (p != NULL && p->link != NULL)
			return p->link->dest;
	}

	return -1;
}

//���붥��vertex
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::insertVertex(const _vertex vertex)
{
	if (numVertices == maxVertices)
		return false;

	NodeTable[numVertices++].data = vertex;
	return true;
}

//�����<v1,v2>��ȨֵΪcost
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::insertEdge(const int v1, const int v2, _edge cost)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
		Edge<_vertex, _edge>* p = NodeTable[v1].adj;

		while (p != NULL && p->dest != v2)
			p = p->link;

		if(p != NULL)
			return false;

		p = new Edge<_vertex, _edge>(v2, cost, NodeTable[v1].adj);
		if (p == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}
		NodeTable[v1].adj = p;

		numEdges++;

		if (if_directed)
			return true;
	}

	if (!if_directed && v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
		Edge<_vertex, _edge>* p = NodeTable[v2].adj;

		p = new Edge<_vertex, _edge>(v1, cost, NodeTable[v2].adj);
		if (p == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}
		NodeTable[v2].adj = p;

		return true;
	}

	return false;
}

//ɾȥ����v����������������ı�
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::removeVertex(const int v)
{
	if (v < 0 || v >= numVertices)
		return false;

	if (numVertices == 1)
		return false;

	Edge<_vertex, _edge>* p, * s;

	/*1��ɾ���ö���ĳ��߱�*/
	while (NodeTable[v].adj != NULL) {
		p = NodeTable[v].adj;
		NodeTable[v].adj = p->link;
		delete p;
		numEdges--;
	}

	/*2��ɾ���ö�������*/
	for (int i = 0; i < numVertices; i++) {
		if (i == v)
			continue;

		p = NodeTable[i].adj;
		s = NULL;

		while (p != NULL && p->dest != v) {
			s = p;
			p = p->link;
		}

		if (p != NULL) {
			if (s == NULL)
				NodeTable[i].adj = p->link;
			else
			 	s->link = p->link;

			if (if_directed)
				numEdges--;
			
			delete p;
			continue;
		}
	}

	/*3�����һ�����㶥��ɾ�������λ�ã�����������*/
	NodeTable[v] = NodeTable[numVertices - 1];
	for (int i = 0; i < numVertices; i++) {
		if (i == v)
			continue;

		else if (i == numVertices - 1) {
			NodeTable[i].adj = NULL;
			continue;
		}

		p = NodeTable[i].adj;

		while (p != NULL && p->dest != numVertices - 1)
			p = p->link;

		if (p != NULL) {
			p->dest = v;
			continue;
		}
	}

	numVertices--;
	return true;
}

//��ͼ��ɾȥ��(v1,v2)��<v1,v2>
template<class _vertex, class _edge>
bool GraphList<_vertex, _edge>::removeEdge(const int v1, const int v2)
{
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
		Edge<_vertex, _edge>* p = NodeTable[v1].adj, * q = NULL, * s = p;

		while (p != NULL && p->dest != v2) {
			q = p;
			p = p->link;
		}

		if (p != NULL) {
			if (p == s)
				NodeTable[v1].adj = p->link;
			else
				q->link = p->link;

			numEdges--;
			delete p;
		}

		else
			return false;

		if (if_directed)
			return true;
			
		p = NodeTable[v2].adj;
		q = NULL;
		s = p;

		while (p->dest != v1) {
			q = p;
			p = p->link;
		}

		if (p == s)
			NodeTable[v2].adj = p->link;
		else
			q->link = p->link;

		delete p;
		return true;
	}

	return false;
}

//������ȱ���ͼ����Ϊ����ͨͼ��������������������ͨ������
template<class _vertex, class _edge>
void GraphList<_vertex, _edge>::DFS_Single(const _vertex v, _GraphListVisitFunction visit)const
{
	const int ver_num = numVertices;
	int loc = getVertexPos(v);

	if (loc == -1) {
		cout << "���㲻���ڣ�" << endl;
		return;
	}

	bool* visited = new bool[ver_num];
	if (visited == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < ver_num; i++)
		visited[i] = false;

	DFS_Recursion(loc, visited, visit);
	delete[] visited;
}

//������ȱ���ͼ����Ϊ����ͨͼ��������������������ͨ��ͼ��
template<class _vertex, class _edge>
void GraphList<_vertex, _edge>::BFS_Single(const _vertex v, _GraphListVisitFunction visit, bool Visited[])const
{
	const int ver_num = numVertices;
	int w;
	int loc = getVertexPos(v);

	if (loc == -1) {
		cout << "���㲻���ڣ�" << endl;
		return;
	}

	bool* visited = NULL;

	if (Visited) {
		visited = Visited;
	}

	else {
		visited = new bool[ver_num];
		if (visited == NULL) {
			cerr << "�洢�������" << endl;
			exit(1);
		}

		for (int i = 0; i < ver_num; i++)
			visited[i] = false;
	}

	visit(v);
	visited[loc] = true;

	LinkedQueue<int> queue;
	queue.EnQueue(loc);

	while (!queue.IsEmpty()) {
		queue.DeQueue(loc);
		w = getFirstNeighbor(loc);

		while (w != -1) {
			if (!visited[w]) {
				_vertex vertex;
				getVertex(vertex, w);

				visit(vertex);
				visited[w] = true;
				queue.EnQueue(w);
			}

			w = getNextNeighbor(loc, w);
		}
	}

	if (Visited == NULL)
		delete[] visited;
}

//������ȱ���ͼ����Ϊ����ͨͼ�������������ͨ������
template<class _vertex,class _edge>
void GraphList<_vertex, _edge>::DFS_All(_GraphListVisitFunction visit)const
{
	const int ver_num = numVertices;

	bool* visited = new bool[ver_num];
	if (visited == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < ver_num; i++)
		visited[i] = false;

	for (int i = 0; i < ver_num; i++) {
		if (!visited[i]) {
			DFS_Recursion(i, visited, visit);
			cout << endl;
		}
	}

	delete[] visited;
}

//������ȱ���ͼ����Ϊ����ͨͼ�������������ͨ������
template<class _vertex, class _edge>
void GraphList<_vertex, _edge>::BFS_All(_GraphListVisitFunction visit)const
{
	const int ver_num = numVertices;

	bool* visited = new bool[ver_num];
	if (visited == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < ver_num; i++)
		visited[i] = false;

	for (int i = 0; i < ver_num; i++) {
		if (!visited[i]) {
			_vertex vertex;
			getVertex(vertex, i);

			BFS_Single(vertex, visit, visited);
			cout << endl;
		}
	}

	delete[] visited;
}

//���غ�������ֵ
template<class _vertex,class _edge>
GraphList<_vertex, _edge>& GraphList<_vertex, _edge>::operator=(const GraphList<_vertex, _edge>& graph)
{
	for (int i = 0; i < numVertices; i++) {
		Edge<_vertex, _edge>* p = NodeTable[i].adj;

		while (p != NULL) {
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}

	delete[] NodeTable;

	maxVertices = graph.maxVertices;
	numVertices = graph.numVertices;
	numEdges = graph.numEdges;

	NodeTable = new Vertex<_vertex, _edge>[maxVertices];
	if (NodeTable == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < numVertices; i++) {
		NodeTable[i].data = graph.NodeTable[i].data;

		Edge<_vertex, _edge>* src = graph.NodeTable[i].adj, * newNode, * current = NULL;

		if (src == NULL)
			NodeTable[i].adj = NULL;

		while (src != NULL) {
			newNode = new Edge<_vertex, _edge>(src->dest, src->cost);
			if (newNode == NULL) {
				cerr << "�洢����ʧ�ܣ�" << endl;
				exit(1);
			}

			if (src == graph.NodeTable[i].adj)
				NodeTable[i].adj = newNode;
			else
				current->link = newNode;
			current = newNode;

			src = src->link;
		}
	}

	return *this;
}

#endif
