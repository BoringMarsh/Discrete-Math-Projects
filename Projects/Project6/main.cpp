#include<iostream>
#include<climits>
#include<conio.h>
#include<stdlib.h>
using namespace std;

/***************************************************************************
  �������ƣ�create
  ��    �ܣ�����һ����������Ϊnum�Ķ�ά����
  ���������bool**& matrix����άָ��
			const int num�������С��ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void create(bool**& matrix, const int num)
{
	matrix = (bool**) new bool*[num];  /*����һάָ�������*/

	if (matrix == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < num; i++) {
		matrix[i] = new bool[num];  /*Ϊÿһ��һάָ�뿪�ٿռ�*/

		if (matrix[i] == NULL) {
			cerr << "�洢�������" << endl;
			exit(1);
		}
	}
}

/***************************************************************************
  �������ƣ�clear
  ��    �ܣ�ɾ��һ����������Ϊnum�Ķ�ά����
  ���������bool**& matrix����άָ��
			const int num�������С��ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void clear(bool**& matrix, const int num)
{
	for (int i = 0; i < num; i++)
		delete[] matrix[i];
}

/***************************************************************************
  �������ƣ�show
  ��    �ܣ�չʾһ����������Ϊnum�Ķ�ά����
  ���������bool**& matrix����άָ��
			const int num�������С��ֻ����
  �� �� ֵ����
  ˵    ������
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
  �������ƣ�transitive_Warshall
  ��    �ܣ�����num��Ԫ�ع�ϵ�Ĵ��ݱհ���Warshall�㷨��
  ���������bool**& matrix����άָ��
			const int num�������С��ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void transitive_Warshall(bool** matrix, const int num)
{
	for (int k = 0; k < num; k++) {
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				if (i != k && j != k && !matrix[i][j]) {  /*��ʮ����Ϊ���Ԫ��M[i,j]*/
					matrix[i][j] = matrix[i][k] && matrix[k][j];  /*��M[i,k]=1 && M[k,j]=1����M[i,j]��Ϊ1*/
				}
			}
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
	int num = 0;
	bool if_on = true;

	while (if_on) {
		while (1) {  /*����Ԫ�ظ���*/
			cout << "������Ԫ�ظ�����";
			cin >> num;

			if (cin.good() && num > 0 && num <= INT_MAX)
				break;

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "�����������������" << endl;
		}

		bool** data;
		create(data, num);

		for (int i = 0; i < num; i++) {  /*����ÿ��Ԫ��*/
			cout << "���������ĵ�" << i << "��Ԫ��(Ԫ���Կո�ָ�):";

			for (int j = 0; j < num; j++) {
				while (1) {
					cin >> data[i][j];

					if (cin.good() && (data[i][j] == true || data[i][j] == false))
						break;

					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "����ĵ�" << i << "�У���" << j << "��Ԫ������������������:";
				}
			}
		}

		cout << "��ϵ�Ĵ��ݱհ���" << endl;
		transitive_Warshall(data, num);  /*Warshall�㷨���*/
		show(data, num);
		clear(data, num);
	}

	return 0;
}