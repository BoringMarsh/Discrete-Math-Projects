#include<iostream>
#include<cmath>
using namespace std;

#define VAR_NUM 5

/***************************************************************************
  函数名称：trans
  功    能：将十进制数转换为二进制数，位数和命题数量对齐
  输入参数：const int number：待转换的二进制数（只读）
			bool vars[]：存储转换结果的布尔数组
  返 回 值：无
  说    明：二进制每一位是布尔类型，表示每个命题的真假
***************************************************************************/
void trans(const int number, bool vars[])
{
	int n = number;
	int count = 0;

	do {  /*由于除2取余法需要反转才能得到结果，故在此处直接反着存到vars数组内*/
		const int rem = n % 2;
		vars[VAR_NUM - count - 1] = bool(rem);
		n = (n - rem) / 2;
		count++;
	} while (n);

	for (int i = 0; i < VAR_NUM - count; i++)  /*多出来的空位用0（false）填补*/
		vars[i] = false;
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
	bool vars[VAR_NUM];

	for (int i = 0; i < pow(2, VAR_NUM); i++) {
		trans(i, vars);  /*将十进制数转换为二进制数，位数和命题数量对齐*/

		if (  /*若情况符合，输出结果*/
			(vars[0] || vars[1])
			&& (!vars[0] || !vars[2])
			&& (!vars[3] || !vars[4])
			&& (vars[3] || vars[2])
			&& vars[4]
			) {
			cout << "A=" << vars[0] << ' ' << "B=" << vars[1] << endl;
		}
			
	}
	//A="营业员A偷了手表"
	//B="营业员B偷了手表"
	//C="作案在营业时间"
	//D="B提供的证据正确"
	//E="柜子上锁"
	//表达式：(A || B) && (A -> !C) && (D -> !E) && (!D -> C) && E
	return 0;
}