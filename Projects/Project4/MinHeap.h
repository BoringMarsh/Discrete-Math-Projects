#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include<iostream>
#include<stdlib.h>
using namespace std;

#define MINHEAP_DEFAULT_SIZE 20

template<class _class>
class MinHeap {
private:
	_class* data;
	int size;
	int maxSize;

	void siftDown(const int start, const int m);
	void siftUp(const int start);
	void siftAll();
public:
	MinHeap(const int sz = MINHEAP_DEFAULT_SIZE);
	MinHeap(_class arr[], const int n);
	~MinHeap();

	bool GetMin(_class& x)const;
	int GetSize()const;
	int GetCapacity()const;
	bool Insert(const _class x);
	bool RemoveMin(_class& x);
	bool IsEmpty()const;
	bool IsFull()const;
	void MakeEmpty();
	void Output()const;

	_class& operator[](const int pos)const;
};

//��ָ����С�Ĺ��캯��
template<class _class>
MinHeap<_class>::MinHeap(const int sz)
{
	maxSize = (MINHEAP_DEFAULT_SIZE < sz) ? sz : MINHEAP_DEFAULT_SIZE;

	data = new _class[maxSize];
	if (data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	size = 0;
}

//�������ݺʹ�С�Ĺ��캯��
template<class _class>
MinHeap<_class>::MinHeap(_class arr[], const int n)
{
	maxSize = (MINHEAP_DEFAULT_SIZE < n) ? n : MINHEAP_DEFAULT_SIZE;

	data = new _class[maxSize];
	if (data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < n; i++)
		data[i] = arr[i];

	size = n;

	int current = (size - 2) / 2;

	while (current >= 0) {
		siftDown(current, size - 1);
		current--;
	}
}

//��������
template<class _class>
MinHeap<_class>::~MinHeap()
{
	delete[] data;
}

//��start��m�»�������Ϊ��С��
template<class _class>
void MinHeap<_class>::siftDown(const int start, const int m)
{
	if (start < 0 || start > size || m < 0 || m > size)
		return;

	int i = start, j = 2 * i + 1;
	_class temp = data[i];

	while (j <= m) {
		if (j < m && data[j] > data[j + 1])
			j++;

		if (temp <= data[j])
			break;
		else {
			data[i] = data[j];
			i = j;
			j = 2 * j + 1;
		}
	}

	data[i] = temp;
}

//��start��0�ϻ�������Ϊ��С��
template<class _class>
void MinHeap<_class>::siftUp(const int start)
{
	int j = start, i = (j - 1) / 2;
	_class temp = data[j];

	while (j > 0) {
		if (data[i] <= temp)
			break;
		else {
			data[j] = data[i];
			j = i;
			i = (i - 1) / 2;
		}
	}

	data[j] = temp;
}

//ֱ�ӵ���Ϊ��С��
template<class _class>
void MinHeap<_class>::siftAll()
{
	if (IsEmpty())
		return;

	int current = (size - 2) / 2;

	while (current >= 0) {
		siftDown(current, size - 1);
		current--;
	}
}

//ȡ�Ѷ�Ԫ�أ�����СԪ��
template<class _class>
bool MinHeap<_class>::GetMin(_class& x)const
{
	if (IsEmpty()) {
		cout << "��Ϊ�գ�" << endl;
		return false;
	}

	x = data[0];
	return true;
}

//ȡ�ѵĵ�ǰ��С
template<class _class>
int MinHeap<_class>::GetSize()const
{
	return size;
}

//ȡ�ѵ��������
template<class _class>
int MinHeap<_class>::GetCapacity()const
{
	return maxSize;
}

//��x������С����
template<class _class>
bool MinHeap<_class>::Insert(const _class x)
{
	if (size == maxSize) {
		cout << "��������" << endl;
		return false;
	}

	data[size] = x;
	siftUp(size);

	size++;
	return true;
}

//ɾ���Ѷ��ϵ���СԪ��
template<class _class>
bool MinHeap<_class>::RemoveMin(_class& x)
{
	if (!size) {
		cout << "��Ϊ�գ�" << endl;
		return false;
	}

	x = data[0];
	data[0] = data[size - 1];

	size--;
	siftDown(0, size - 1);
	//siftAll();
	return true;
}

//�ж϶��Ƿ�Ϊ��
template<class _class>
bool MinHeap<_class>::IsEmpty()const
{
	return (size == 0);
}

//�ж϶��Ƿ�����
template<class _class>
bool MinHeap<_class>::IsFull()const
{
	return(size == maxSize);
}

//�ÿն�
template<class _class>
void MinHeap<_class>::MakeEmpty()
{
	size = 0;
}

//�������ڴ��˳��������ڵ�Ԫ��
template<class _class>
void MinHeap<_class>::Output()const
{
	for (int i = 0; i < size; i++)
		cout << data[i] << endl;
}

//���غ������±����
template<class _class>
_class& MinHeap<_class>::operator[](const int pos)const
{
	if (pos < 0 || pos >= size) {
		cout << "λ�ô���" << endl;
		return data[0];
	}

	return data[pos];
}

#endif
