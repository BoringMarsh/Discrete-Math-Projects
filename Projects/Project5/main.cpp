#include<iostream>
#include<climits>
#include<stdlib.h>
#include<iomanip>
#include"HuffmanTree.h"
#include"String.h"
using namespace std;

/***************************************************************************
  �������ƣ�findCode
  ��    �ܣ��������������������ҵ���ʾÿ��Ҷ���Ĺ��������루�ݹ���̣�
  ���������HuffmanNode<_class>* ptr�����������ĸ�
			String& code���ݴ������ַ���
  �� �� ֵ����
  ˵    ������
***************************************************************************/
template<class _class>
void findCode(HuffmanNode<_class>* ptr, String& code)
{
	if (ptr == NULL)
		return;

	if (ptr->leftChild == NULL && ptr->rightChild == NULL)  /*�ҵ�Ҷ��㣬��ӡ��Ӧ����*/
		cout << setiosflags(ios::left) << setw(4) << ptr->data << "����" << code << endl;

	if (ptr->leftChild) {
		code += '0';  /*�������������������'0'*/
		findCode(ptr->leftChild, code);
		code--;  /*��һ��ݹ����������ȥ�����һλ*/
	}

	if (ptr->rightChild) {
		code += '1';  /*�������������������'1'*/
		findCode(ptr->rightChild, code);
		code--;  /*��һ��ݹ����������ȥ�����һλ*/
	}
}

/***************************************************************************
  �������ƣ�findCode
  ��    �ܣ��������������������ҵ���ʾÿ��Ҷ���Ĺ���������
  ���������const HuffmanTree<_class>& tree������������ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
template<class _class>
void findCode(const HuffmanTree<_class>& tree)
{
	if (tree.getRoot()->leftChild == NULL && tree.getRoot()->rightChild == NULL) {  /*��ֻ��һ���ڵ㣬�ý�������һ��0��ʾ*/
		cout << setiosflags(ios::left) << setw(4) << tree.getRoot()->data << "����0" << endl;
		return;
	}

	String code;
	findCode(tree.getRoot(), code);
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
	int num, weight;

	while (1) {
		cout << "����ڵ������";
		cin >> num;

		if (cin.good() && num > 0 && num <= INT_MAX)
			break;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	int* data = new int[num];  /*���ٴ洢�ڵ������*/
	if (data == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	cout << "����ڵ㣺";

	for (int i = 0; i < num; i++) {
		while (1) {
			cin >> weight;

			if (cin.good() && weight > 0 && weight <= INT_MAX)
				break;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "��" << i + 1 << "���ڵ����������Ӹý�㿪ʼ�������룺" << endl;
		}

		data[i] = weight;
	}

	HuffmanTree<int> tree(data, num);  /*����������Ľڵ����ݴ�����������*/
	findCode(tree);  /*���ݹ����������ɹ���������*/
	return 0;
}