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
  �������ƣ�create
  ��    �ܣ�����һ����������Ϊnum�Ķ�ά���飬ͬʱ����һ����ά���������г�ʼ��
  ���������bool**& matrix����άָ��
			bool** data��������Դ����
			const int num�������С��ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void create(bool**& matrix, bool** data, const int num)
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

		for (int j = 0; j < num; j++)
			matrix[i][j] = data[i][j];
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
  �������ƣ�reflexive
  ��    �ܣ�����num��Ԫ�ع�ϵ���Է��հ�
  ���������bool** matrix��ԭ��Ԫ��ϵ�Ĺ�ϵ����
			const int num��Ԫ�ظ�����ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void reflexive(bool** matrix, const int num)
{
	//�Խ�����Ԫ�ض���Ϊ1
	for (int i = 0; i < num; i++)
		matrix[i][i] = true;
}

/***************************************************************************
  �������ƣ�symmetric
  ��    �ܣ�����num��Ԫ�ع�ϵ�ĶԳƱհ�
  ���������bool** matrix��ԭ��Ԫ��ϵ�Ĺ�ϵ����
			const int num��Ԫ�ظ�����ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void symmetric(bool** matrix, const int num)
{
	bool** rev;
	create(rev, num);

	//ȡԭ�����ת��
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			rev[i][j] = matrix[j][i];
		}
	}

	//ԭ������ת�����
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			matrix[i][j] = matrix[i][j] || rev[i][j];
		}
	}

	clear(rev, num);
}

/***************************************************************************
  �������ƣ�transitive
  ��    �ܣ�����num��Ԫ�ع�ϵ�Ĵ��ݱհ���һ���󷨣�
  ���������bool** matrix��ԭ��Ԫ��ϵ�Ĺ�ϵ����
			const int num��Ԫ�ظ�����ֻ����
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void transitive(bool** matrix, const int num)
{
	//ԭ����
	bool** Default;
	create(Default, num);

	//ԭ�����n�η�
	bool** Current;
	create(Current, num);

	//����ԭ����n�η�ʱ�������ʱ���
	bool** Result;
	create(Result, num);

	//��Default��Current��ֵ��ʹ��Default��ԭ����Current�ǵ�λ��
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
		//Current��Default��ˣ��õ�M��n�η�
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

		//����Current��ֵ
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				Current[i][j] = Result[i][j];
			}
		}

		//matrix��Current��ӣ��õ����
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

	while (if_on) {
		cout << "�����Ӧ���ѡ���㷨\n"
			<< "1.�Է��հ�\n"
			<< "2.�ԳƱհ�\n"
			<< "3.���ݱհ�\n"
			<< "4.�˳�\n";

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