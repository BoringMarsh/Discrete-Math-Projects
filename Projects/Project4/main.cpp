#include<iostream>
#include<climits>
#include<conio.h>
#include"MinSpanTree.h"
#include"GraphList.h"
#include"UFSets.h"
#include"MinHeap.h"
using namespace std;

/***************************************************************************
  函数名称：Kruskal
  功    能：用Kruskal算法生成最小生成树
  输入参数：const GraphList<_vertex, _edge>& graph：图（只读）
			MinSpanTree<_vertex, _edge>& tree：最小生成树
  返 回 值：无
  说    明：无
***************************************************************************/
template<class _vertex, class _edge>
void Kruskal(const GraphList<_vertex, _edge>& graph, MinSpanTree<_vertex, _edge>& tree)
{
	if (!graph.IsConnected()) {
		cout << "图不连通！" << endl;
		return;
	}

	const int ver_num = graph.NumOfVertices();  /*取点数*/
	const int edge_num = graph.NumOfEdges();    /*取边数*/
	MSTEdgeNode<_vertex, _edge> edge;
	MinHeap<MSTEdgeNode<_vertex, _edge>> heap(edge_num);  /*边的最小堆*/
	UFSets set(ver_num);  /*并查集*/

	for (int i = 0; i < ver_num; i++) {
		for (int j = i + 1; j < ver_num; j++) {  /*无向图，从i+1开始*/
			_edge ed;

			if (graph.getEdge(ed, i, j)) {  /*逐个扫描，取边*/
				graph.getVertex(edge.tail, i);
				graph.getVertex(edge.head, j);
				graph.getEdge(edge.key, i, j);
				heap.Insert(edge);  /*插入最小堆*/
			}
		}
	}

	int count = 1;

	while (count < ver_num) {
		heap.RemoveMin(edge);  /*取出最短边*/
		const int i = graph.getVertexPos(edge.tail);
		const int j = graph.getVertexPos(edge.head);
		const int k = set.Find(i);
		const int l = set.Find(j);

		if (k != l) {  /*若两个顶点不在同一连通分量，将该边放入最小生成树*/
			set.Union(k, l);
			tree.Insert(edge);
			count++;
		}
	}
}

/***************************************************************************
  函数名称：main
  功    能：主函数
  输入参数：无
  返 回 值：0
  说    明：无
***************************************************************************/
int main()
{
	int ver_num, edge_num;

	while (1) {
		cout << "请输入所求图的顶点数目和边的数目（以空格分隔各个数，输入两个0结束）:";
		cin >> ver_num >> edge_num;

		if (cin.good() && ver_num == 0 && edge_num == 0) /*退出*/
			return 0;
		else if (cin.good() && ver_num == 1 && edge_num == 0) {
			cout << "只有一个顶点，无需生成最小生成树！" << endl;
			return 0;
		}

		if (cin.good() && ver_num >= 1 && ver_num <= INT_MAX && edge_num >= 1 && edge_num <= INT_MAX)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "输入错误，请重新输入！" << endl;
	}

	GraphList<int, int> graph(false, ver_num);  /*存储图的邻接表*/
	for (int i = 0; i < ver_num; i++)  /*插入顶点*/
		graph.insertVertex(i + 1);

	cout << "请输入两条边的节点序号以及它们的权值（以空格分隔各个数）:" << endl;

	for (int i = 0; i < edge_num; i++) {
		int v1, v2, edge;
		int e;

		while (1) {
			cin >> v1 >> v2 >> edge;

			if (!cin.good())
				cout << "输入发生错误" << endl;

			else if (v1 <= 0 || v1 > ver_num)
				cout << "第" << i + 1 << "条边的第一个顶点序号输入错误" << endl;

			else if (v2 <= 0 || v2 > ver_num)
				cout << "第" << i + 1 << "条边的第二个顶点序号输入错误" << endl;

			else if (v1 == v2)
				cout << "第" << i + 1 << "条边是环" << endl;

			else if (graph.getEdge(e, v1 - 1, v2 - 1))
				cout << "第" << i + 1 << "条边已存在" << endl;

			else if (edge < 0)
				cout << "第" << i + 1 << "条边的权值输入错误" << endl;

			else
				break;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		graph.insertEdge(v1 - 1, v2 - 1, edge);
	}

	MinSpanTree<int, int> tree(edge_num);  /*最小生成树*/
	Kruskal(graph, tree);  /*用Kruskal算法生成最小生成树*/
	cout << "\n最小花费方案如下：" << endl;
	tree.Show();
	return 0;
}