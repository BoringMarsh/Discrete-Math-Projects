#ifndef _HUFFMANTREE_H_
#define _HUFFMANTREE_H_

#include<iostream>
#include<stdlib.h>
#include"MinHeap.h"
using namespace std;

template<class _class>
struct HuffmanNode {
	_class data;
	HuffmanNode* leftChild, * rightChild, * parent;

	HuffmanNode() :leftChild(NULL), rightChild(NULL), parent(NULL) {}
	HuffmanNode(_class d, HuffmanNode* l = NULL, HuffmanNode* r = NULL, HuffmanNode* p = NULL)
		:data(d), leftChild(l), rightChild(r), parent(p) {}
};

template<class _class>
struct InfoNode {
	HuffmanNode<_class>* pos;
	_class key;

	InfoNode() :pos(NULL) {}
	InfoNode(const _class k, HuffmanNode<_class>* ptr) :key(k), pos(ptr) {}

	inline bool operator>(const InfoNode<_class> node) {
		return (key > node.key);
	}
	inline bool operator<(const InfoNode<_class> node) {
		return (key < node.key);
	}
	inline bool operator>=(const InfoNode<_class> node) {
		return (key >= node.key);
	}
	inline bool operator<=(const InfoNode<_class> node) {
		return (key <= node.key);
	}
	inline bool operator==(const InfoNode<_class> node) {
		return (key == node.key);
	}
	inline bool operator!=(const InfoNode<_class> node) {
		return (key != node.key);
	}
};

template<class _class>
class HuffmanTree {
private:
	HuffmanNode<_class>* root;
	int size;

	void mergeNode(HuffmanNode<_class>* node1, HuffmanNode<_class>* node2, HuffmanNode<_class>*& parent);
	bool ifLeaf(HuffmanNode<_class>* node)const;
	void makeEmpty(HuffmanNode<_class>* ptr);
	void Traversal(HuffmanNode<_class>* ptr)const;
public:
	HuffmanTree(_class weight[], const int num);
	~HuffmanTree();

	void makeEmpty();
	HuffmanNode<_class>* getRoot()const;
	int getSize()const;
	bool IsEmpty()const;
	void Traversal()const;
};

//ָ��Ҷ������ݵĹ��캯��
template<class _class>
HuffmanTree<_class>::HuffmanTree(_class weight[], const int num)
{
	size = num;

	if (num == 1) {
		root = new HuffmanNode<_class>(weight[0]);
		if (root == NULL) {
			cerr << "�洢�������" << endl;
			exit(1);
		}

		return;
	}

	MinHeap<InfoNode<_class> > heap;
	HuffmanNode<_class>* parent = NULL;

	for (int i = 0; i < num; i++) {
		HuffmanNode<_class>* ptr = new HuffmanNode<_class>(weight[i]);
		if (ptr == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}

		heap.Insert(InfoNode<_class>(ptr->data, ptr));
	}

	for (int i = 0; i < num - 1; i++) {
		InfoNode<_class> info1, info2;

		heap.RemoveMin(info1);
		heap.RemoveMin(info2);
		
		mergeNode(info1.pos, info2.pos, parent);
		heap.Insert(InfoNode<_class>(parent->data, parent));
	}

	root = parent;
}

//��������
template<class _class>
HuffmanTree<_class>::~HuffmanTree()
{
	makeEmpty();
}

//�����������Ϊ��Ů���ӵ�ͬһ�����ڵ���
template<class _class>
void HuffmanTree<_class>::mergeNode(HuffmanNode<_class>* node1, HuffmanNode<_class>* node2, HuffmanNode<_class>*& parent)
{
	parent = new HuffmanNode<_class>(node1->data + node2->data, node1, node2);
	if (parent == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	node1->parent = parent;
	node2->parent = parent;
}

//�ж�һ������Ƿ�ΪҶ���
template<class _class>
bool HuffmanTree<_class>::ifLeaf(HuffmanNode<_class>* node)const
{
	if (node == NULL)
		return false;

	if (node->leftChild != NULL || node->rightChild != NULL)
		return false;

	return true;
}

//�����������������ݹ����
template<class _class>
void HuffmanTree<_class>::Traversal(HuffmanNode<_class>* ptr)const
{
	if (ptr == NULL)
		return;

	if (ptr->leftChild != NULL)
		Traversal(ptr->leftChild);

	if (ptr->leftChild == NULL && ptr->rightChild == NULL)
		cout << ptr->data << endl;

	if (ptr->rightChild != NULL)
		Traversal(ptr->rightChild);
}

//����������������
template<class _class>
void HuffmanTree<_class>::Traversal()const
{
	Traversal(root);
}

//����������������ݹ����
template<class _class>
void HuffmanTree<_class>::makeEmpty(HuffmanNode<_class>* ptr)
{
	if (ptr == NULL)
		return;

	makeEmpty(ptr->leftChild);
	makeEmpty(ptr->rightChild);
	delete ptr;
}

//���������������
template<class _class>
void HuffmanTree<_class>::makeEmpty()
{
	makeEmpty(root);
	size = 0;
}

//ȡ���������ĸ����
template<class _class>
HuffmanNode<_class>* HuffmanTree<_class>::getRoot()const
{
	return root;
}

//ȡ���������Ľ����
template<class _class>
int HuffmanTree<_class>::getSize()const
{
	return size;
}

//�жϹ��������Ƿ�Ϊ��
template<class _class>
bool HuffmanTree<_class>::IsEmpty()const
{
	return (root == NULL);
}

#endif
