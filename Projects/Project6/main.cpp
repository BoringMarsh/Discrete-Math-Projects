#include<iostream>
#include<climits>
#include<conio.h>
#include<stdlib.h>
using namespace std;

/***************************************************************************
  函数名称：create
  功    能：生成一个行列数都为num的二维数组
  输入参数：bool**& matrix：二维指针
			const int num：数组大小（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void create(bool**& matrix, const int num)
{
	matrix = (bool**) new bool*[num];  /*开辟一维指针的数组*/

	if (matrix == NULL) {
		cerr << "存储分配错误！" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++) {
		matrix[i] = new bool[num];  /*为每一个一维指针开辟空间*/

		if (matrix[i] == NULL) {
			cerr << "存储分配错误！" << endl;
			exit(1);
		}
	}
}

/***************************************************************************
  函数名称：clear
  功    能：删除一个行列数都为num的二维数组
  输入参数：bool**& matrix：二维指针
			const int num：数组大小（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void clear(bool**& matrix, const int num)
{
	for (int i = 0; i < num; i++)
		delete[] matrix[i];
}

/***************************************************************************
  函数名称：show
  功    能：展示一个行列数都为num的二维数组
  输入参数：bool**& matrix：二维指针
			const int num：数组大小（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void show(bool** matrix, const int num)
{
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (j == num - 1)
				cout << matrix[i][j] << endl;
			else
				cout << matrix[i][j] << ' ';
		}
	}
}

/***************************************************************************
  函数名称：transitive_Warshall
  功    能：求有num个元素关系的传递闭包（Warshall算法）
  输入参数：bool**& matrix：二维指针
			const int num：数组大小（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void transitive_Warshall(bool** matrix, const int num)
{
	for (int k = 0; k < num; k++) {
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				if (i != k && j != k && !matrix[i][j]) {  /*非十字且为零的元素M[i,j]*/
					matrix[i][j] = matrix[i][k] && matrix[k][j];  /*若M[i,k]=1 && M[k,j]=1，则M[i,j]置为1*/
				}
			}
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
	int num = 0;
	bool if_on = true;

	while (if_on) {
		while (1) {  /*输入元素个数*/
			cout << "请输入元素个数：";
			cin >> num;

			if (cin.good() && num > 0 && num <= INT_MAX)
				break;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "输入错误！请重新输入" << endl;
		}

		bool** data;
		create(data, num);

		for (int i = 0; i < num; i++) {  /*输入每个元素*/
			cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";

			for (int j = 0; j < num; j++) {
				while (1) {
					cin >> data[i][j];

					if (cin.good() && (data[i][j] == true || data[i][j] == false))
						break;

					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "矩阵的第" << i << "行，第" << j << "列元素输入错误，请继续输入:";
				}
			}
		}

		cout << "关系的传递闭包：" << endl;
		transitive_Warshall(data, num);  /*Warshall算法求解*/
		show(data, num);
		clear(data, num);
	}

	return 0;
}