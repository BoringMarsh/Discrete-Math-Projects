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
			<< "**        欢迎进入逻辑运算程序       **\n"
			<< "**                                   **\n"
			<< "***************************************\n\n";

		while (1) {  //正确输入p的值
			cout << "\n  请输入P的值（0或1）,以回车结束:";
			int num;
			cin >> num;

			if (cin.good() && (num == 0 || num == 1)) {
				p = bool(num);
				break;
			}

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "  P的值输入有误，请重新输入" << endl;
		}

		while (1) {  //正确输入q的值
			cout << "\n  请输入Q的值（0或1）,以回车结束:";
			int num;
			cin >> num;

			if (cin.good() && (num == 0 || num == 1)) {
				q = bool(num);
				break;
			}

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "  Q的值输入有误，请重新输入" << endl;
		}

		results[0] = p && q;  //与运算
		results[1] = p || q;  //或运算
		results[2] = (!p) || q;  //蕴含运算，将其转化为与或非形式
		results[3] = ((!p) || q) && ((!q) || p);  //等值运算，将其转化为与或非形式

		cout << "\n\n  合取:\n       P/\\Q = " << results[0] << endl  //输出结果
			<< "  析取:\n       P\\/Q = " << results[1] << endl
			<< "  条件:\n       P->Q = " << results[2] << endl
			<< "  双条件:\n       P<->Q = " << results[3] << endl
			<< "\n是否继续运算?（y/n）";

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
			cout << "欢迎下次使用！" << endl;
			break;
		}
	}

	return 0;
}