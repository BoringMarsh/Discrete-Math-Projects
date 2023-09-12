#ifndef _UFSETS_H_
#define _UFSETS_H_

#include<iostream>
#include<stdlib.h>
#include<climits>
using namespace std;

#define UFSETS_DEFAULT_SIZE 10

class UFSets {
private:
	int* parents;
	int size;
public:
	UFSets(const int sz = UFSETS_DEFAULT_SIZE);
	UFSets(const UFSets& UFSet);
	~UFSets();

	UFSets& operator=(const UFSets& UFSet);

	void Union(const int Root1, const int Root2);
	int Find(const int x);
	void Show()const;
};

//构造函数
UFSets::UFSets(const int sz)
{
	size = sz;
	parents = NULL;
	
	parents = new int[size];
	if (parents == NULL) {
		cerr << "存储分配失败！" << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
		parents[i] = -1;
}

//复制构造函数
UFSets::UFSets(const UFSets& UFSet)
{
	size = UFSet.size;
	parents = NULL;

	parents = new int[size];
	if (parents == NULL) {
		cerr << "存储分配失败！" << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
		parents[i] = UFSet.parents[i];
}

//析构函数
UFSets::~UFSets()
{
	delete[] parents;
}

//重载函数：赋值
UFSets& UFSets::operator=(const UFSets& UFSet)
{
	size = UFSet.size;
	delete[] parents;
	parents = NULL;

	parents = new int[size];
	if (parents == NULL) {
		cerr << "存储分配失败！" << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
		parents[i] = UFSet.parents[i];

	return *this;
}

//搜寻集合x的根
int UFSets::Find(const int x)
{
	if (x < 0 || x >= size)
		return INT_MIN;

	int current = x;

	while (parents[current] >= 0)
		current = parents[current];

	return current;
}

//两个子集合合并
void UFSets::Union(const int Root1, const int Root2)
{
	if (Root1 < 0 || Root1 >= size || Root2 < 0 || Root2 >= size)
		return;

	const int r1 = Find(Root1), r2 = Find(Root2);
	int temp;

	if (r1 != r2) {
		temp = parents[r1] + parents[r2];

		if (parents[r2] < parents[r1]) {
			parents[r1] = r2;
			parents[r2] = temp;
		}

		else {
			parents[r2] = r1;
			parents[r1] = temp;
		}
	}
}

//显示并查集中的元素状况
void UFSets::Show()const
{
	for (int i = 0; i < size; i++)
		cout << parents[i] << ' ';
}

#endif