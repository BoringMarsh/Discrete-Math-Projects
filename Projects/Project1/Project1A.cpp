#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

int main()
{
	bool results[4];
	bool p, q;

	while (1) {
		cout << "***************************************\n"
			<< "**                                   **\n"
			<< "**        ��ӭ�����߼��������       **\n"
			<< "**                                   **\n"
			<< "***************************************\n\n";

		while (1) {  //��ȷ����p��ֵ
			cout << "\n  ������P��ֵ��0��1��,�Իس�����:";
			int num;
			cin >> num;

			if (cin.good() && (num == 0 || num == 1)) {
				p = bool(num);
				break;
			}

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "  P��ֵ������������������" << endl;
		}

		while (1) {  //��ȷ����q��ֵ
			cout << "\n  ������Q��ֵ��0��1��,�Իس�����:";
			int num;
			cin >> num;

			if (cin.good() && (num == 0 || num == 1)) {
				q = bool(num);
				break;
			}

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "  Q��ֵ������������������" << endl;
		}

		results[0] = p && q;  //������
		results[1] = p || q;  //������
		results[2] = (!p) || q;  //�̺����㣬����ת��Ϊ������ʽ
		results[3] = ((!p) || q) && ((!q) || p);  //��ֵ���㣬����ת��Ϊ������ʽ

		cout << "\n\n  ��ȡ:\n       P/\\Q = " << results[0] << endl  //������
			<< "  ��ȡ:\n       P\\/Q = " << results[1] << endl
			<< "  ����:\n       P->Q = " << results[2] << endl
			<< "  ˫����:\n       P<->Q = " << results[3] << endl
			<< "\n�Ƿ��������?��y/n��";

		char selection;
		while (1) {
			selection = _getch();

			if (selection == 'y' || selection == 'n') {
				cout << selection << endl;
				break;
			}
		}

		if (selection == 'y')
			system("cls");
		else {
			cout << "��ӭ�´�ʹ�ã�" << endl;
			break;
		}
	}

	return 0;
}