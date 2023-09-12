#include<iostream>
#include<climits>
#include<stdlib.h>
#include<iomanip>
#include"HuffmanTree.h"
#include"String.h"
using namespace std;

/***************************************************************************
  函数名称：findCode
  功    能：遍历整个哈夫曼树，找到表示每个叶结点的哈夫曼编码（递归过程）
  输入参数：HuffmanNode<_class>* ptr：哈夫曼树的根
			String& code：暂存编码的字符串
  返 回 值：无
  说    明：无
***************************************************************************/
template<class _class>
void findCode(HuffmanNode<_class>* ptr, String& code)
{
	if (ptr == NULL)
		return;

	if (ptr->leftChild == NULL && ptr->rightChild == NULL)  /*找到叶结点，打印对应编码*/
		cout << setiosflags(ios::left) << setw(4) << ptr->data << "——" << code << endl;

	if (ptr->leftChild) {
		code += '0';  /*往左子树遍历，编码加'0'*/
		findCode(ptr->leftChild, code);
		code--;  /*上一层递归结束，编码去掉最后一位*/
	}

	if (ptr->rightChild) {
		code += '1';  /*往右子树遍历，编码加'1'*/
		findCode(ptr->rightChild, code);
		code--;  /*上一层递归结束，编码去掉最后一位*/
	}
}

/***************************************************************************
  函数名称：findCode
  功    能：遍历整个哈夫曼树，找到表示每个叶结点的哈夫曼编码
  输入参数：const HuffmanTree<_class>& tree：哈夫曼树（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
template<class _class>
void findCode(const HuffmanTree<_class>& tree)
{
	if (tree.getRoot()->leftChild == NULL && tree.getRoot()->rightChild == NULL) {  /*若只有一个节点，该结点编码用一个0表示*/
		cout << setiosflags(ios::left) << setw(4) << tree.getRoot()->data << "——0" << endl;
		return;
	}

	String code;
	findCode(tree.getRoot(), code);
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
	int num, weight;

	while (1) {
		cout << "输入节点个数：";
		cin >> num;

		if (cin.good() && num > 0 && num <= INT_MAX)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	int* data = new int[num];  /*开辟存储节点的数组*/
	if (data == NULL) {
		cerr << "存储分配错误！" << endl;
		exit(1);
	}

	cout << "输入节点：";

	for (int i = 0; i < num; i++) {
		while (1) {
			cin >> weight;

			if (cin.good() && weight > 0 && weight <= INT_MAX)
				break;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "第" << i + 1 << "个节点输入错误，请从该结点开始继续输入：" << endl;
		}

		data[i] = weight;
	}

	HuffmanTree<int> tree(data, num);  /*根据所输入的节点内容创建哈夫曼树*/
	findCode(tree);  /*根据哈夫曼树生成哈夫曼编码*/
	return 0;
}