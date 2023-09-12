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
  函数名称：create
  功    能：生成一个行列数都为num的二维数组，同时用另一个二维数组对其进行初始化
  输入参数：bool**& matrix：二维指针
			bool** data：数据来源数组
			const int num：数组大小（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void create(bool**& matrix, bool** data, const int num)
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

		for (int j = 0; j < num; j++)
			matrix[i][j] = data[i][j];
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
  函数名称：reflexive
  功    能：求有num个元素关系的自反闭包
  输入参数：bool** matrix：原二元关系的关系矩阵
			const int num：元素个数（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void reflexive(bool** matrix, const int num)
{
	//对角线上元素都置为1
	for (int i = 0; i < num; i++)
		matrix[i][i] = true;
}

/***************************************************************************
  函数名称：symmetric
  功    能：求有num个元素关系的对称闭包
  输入参数：bool** matrix：原二元关系的关系矩阵
			const int num：元素个数（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void symmetric(bool** matrix, const int num)
{
	bool** rev;
	create(rev, num);

	//取原矩阵的转置
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			rev[i][j] = matrix[j][i];
		}
	}

	//原矩阵与转置相加
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			matrix[i][j] = matrix[i][j] || rev[i][j];
		}
	}

	clear(rev, num);
}

/***************************************************************************
  函数名称：transitive
  功    能：求有num个元素关系的传递闭包（一般求法）
  输入参数：bool** matrix：原二元关系的关系矩阵
			const int num：元素个数（只读）
  返 回 值：无
  说    明：无
***************************************************************************/
void transitive(bool** matrix, const int num)
{
	//原矩阵
	bool** Default;
	create(Default, num);

	//原矩阵的n次方
	bool** Current;
	create(Current, num);

	//运算原矩阵n次方时，存放临时结果
	bool** Result;
	create(Result, num);

	//给Default和Current赋值，使得Default是原矩阵，Current是单位阵
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			Default[i][j] = matrix[i][j];

			if (i == j)
				Current[i][j] = true;
			else
				Current[i][j] = false;
		}
	}

	for (int times = 0; times < num; times++) {
		//Current和Default相乘，得到M的n次方
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				bool* primes = new bool[num];

				for (int k = 0; k < num; k++)
					primes[k] = Current[i][k] && Default[k][j];

				Result[i][j] = false;

				for (int k = 0; k < num; k++)
					Result[i][j] = Result[i][j] || primes[k];

				delete[] primes;
			}
		}

		//更新Current的值
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				Current[i][j] = Result[i][j];
			}
		}

		//matrix和Current相加，得到结果
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				matrix[i][j] = matrix[i][j] || Current[i][j];
			}
		}
	}

	clear(Default, num);
	clear(Current, num);
	clear(Result, num);
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

	while (if_on) {
		cout << "输入对应序号选择算法\n"
			<< "1.自反闭包\n"
			<< "2.对称闭包\n"
			<< "3.传递闭包\n"
			<< "4.退出\n";

		char selection = '\0';

		while (1) {
			selection = _getch();

			if (selection >= '1' && selection <= '4') {
				cout << selection << endl;
				break;
			}
		}

		bool** matrix;
		create(matrix, data, num);

		switch (selection) {
		case '1':
			reflexive(matrix, num);
			show(matrix, num);
			clear(matrix, num);
			break;
		case '2':
			symmetric(matrix, num);
			show(matrix, num);
			clear(matrix, num);
			break;
		case '3':
			transitive(matrix, num);
			show(matrix, num);
			clear(matrix, num);
			break;
		case '4':
			if_on = false;
			clear(matrix, num);
			break;
		}
	}

	return 0;
}