#include<iostream>
#include<climits>
#include<conio.h>
#include"MinSpanTree.h"
#include"GraphList.h"
#include"UFSets.h"
#include"MinHeap.h"
using namespace std;

/***************************************************************************
  �������ƣ�Kruskal
  ��    �ܣ���Kruskal�㷨������С������
  ���������const GraphList<_vertex, _edge>& graph��ͼ��ֻ����
			MinSpanTree<_vertex, _edge>& tree����С������
  �� �� ֵ����
  ˵    ������
***************************************************************************/
template<class _vertex, class _edge>
void Kruskal(const GraphList<_vertex, _edge>& graph, MinSpanTree<_vertex, _edge>& tree)
{
	if (!graph.IsConnected()) {
		cout << "ͼ����ͨ��" << endl;
		return;
	}

	const int ver_num = graph.NumOfVertices();  /*ȡ����*/
	const int edge_num = graph.NumOfEdges();    /*ȡ����*/
	MSTEdgeNode<_vertex, _edge> edge;
	MinHeap<MSTEdgeNode<_vertex, _edge>> heap(edge_num);  /*�ߵ���С��*/
	UFSets set(ver_num);  /*���鼯*/

	for (int i = 0; i < ver_num; i++) {
		for (int j = i + 1; j < ver_num; j++) {  /*����ͼ����i+1��ʼ*/
			_edge ed;

			if (graph.getEdge(ed, i, j)) {  /*���ɨ�裬ȡ��*/
				graph.getVertex(edge.tail, i);
				graph.getVertex(edge.head, j);
				graph.getEdge(edge.key, i, j);
				heap.Insert(edge);  /*������С��*/
			}
		}
	}

	int count = 1;

	while (count < ver_num) {
		heap.RemoveMin(edge);  /*ȡ����̱�*/
		const int i = graph.getVertexPos(edge.tail);
		const int j = graph.getVertexPos(edge.head);
		const int k = set.Find(i);
		const int l = set.Find(j);

		if (k != l) {  /*���������㲻��ͬһ��ͨ���������ñ߷�����С������*/
			set.Union(k, l);
			tree.Insert(edge);
			count++;
		}
	}
}

/***************************************************************************
  �������ƣ�main
  ��    �ܣ�������
  �����������
  �� �� ֵ��0
  ˵    ������
***************************************************************************/
int main()
{
	int ver_num, edge_num;

	while (1) {
		cout << "����������ͼ�Ķ�����Ŀ�ͱߵ���Ŀ���Կո�ָ�����������������0������:";
		cin >> ver_num >> edge_num;

		if (cin.good() && ver_num == 0 && edge_num == 0) /*�˳�*/
			return 0;
		else if (cin.good() && ver_num == 1 && edge_num == 0) {
			cout << "ֻ��һ�����㣬����������С��������" << endl;
			return 0;
		}

		if (cin.good() && ver_num >= 1 && ver_num <= INT_MAX && edge_num >= 1 && edge_num <= INT_MAX)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "����������������룡" << endl;
	}

	GraphList<int, int> graph(false, ver_num);  /*�洢ͼ���ڽӱ�*/
	for (int i = 0; i < ver_num; i++)  /*���붥��*/
		graph.insertVertex(i + 1);

	cout << "�����������ߵĽڵ�����Լ����ǵ�Ȩֵ���Կո�ָ���������:" << endl;

	for (int i = 0; i < edge_num; i++) {
		int v1, v2, edge;
		int e;

		while (1) {
			cin >> v1 >> v2 >> edge;

			if (!cin.good())
				cout << "���뷢������" << endl;

			else if (v1 <= 0 || v1 > ver_num)
				cout << "��" << i + 1 << "���ߵĵ�һ����������������" << endl;

			else if (v2 <= 0 || v2 > ver_num)
				cout << "��" << i + 1 << "���ߵĵڶ�����������������" << endl;

			else if (v1 == v2)
				cout << "��" << i + 1 << "�����ǻ�" << endl;

			else if (graph.getEdge(e, v1 - 1, v2 - 1))
				cout << "��" << i + 1 << "�����Ѵ���" << endl;

			else if (edge < 0)
				cout << "��" << i + 1 << "���ߵ�Ȩֵ�������" << endl;

			else
				break;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		graph.insertEdge(v1 - 1, v2 - 1, edge);
	}

	MinSpanTree<int, int> tree(edge_num);  /*��С������*/
	Kruskal(graph, tree);  /*��Kruskal�㷨������С������*/
	cout << "\n��С���ѷ������£�" << endl;
	tree.Show();
	return 0;
}