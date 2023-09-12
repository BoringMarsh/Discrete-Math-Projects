#include <iostream>
#include <string>
#include <map>
#include <stack>
using namespace std;

typedef map<char, int> Map_ci;
typedef map<int, char> Map_ic;
typedef map<int, int> Map_ii;

Map_ci priority;

/***************************************************************************
  �������ƣ�findProposition
  ��    �ܣ��ж�һ����������Ƿ񱻱�����
  ���������Map_ic pSet�����⼯�ϣ��±�-�ַ���
			char p���������������
  �� �� ֵ��int��-1��ʾ�����������δ��������������˵������������ѱ�������������ָ�����������±�
  ˵    ������
***************************************************************************/
int findProposition(Map_ic pSet, char p)
{
	Map_ic::iterator it = pSet.begin();
	while (it != pSet.end()) 
	{
		if (it->second == p) 
		{
			return it->first;
		}
		it++;
	}
	return -1;
}

/***************************************************************************
  �������ƣ�getProposition
  ��    �ܣ�ͳ�ƹ�ʽ�е������������
  ���������string formula����ͳ�ƵĹ�ʽ
  �� �� ֵ��Map_ic�����⼯�ϣ��±�-�ַ���
  ˵    ������
***************************************************************************/
Map_ic getProposition(string formula)
{
	Map_ic proposition;
	int n_proposition = 0;
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
		{
			//���������������
			int r = findProposition(proposition, c);
            //cout << r << endl;
			if (r == -1) 
			{
				//˵�������������δ��������
				proposition[n_proposition] = c;
				n_proposition++;
			}
		}
		else if (!priority.count(c))  //���ַǷ��ַ���ֱ�ӱ����˳�
		{
			cout << c << " is undefined!" << endl;
			exit(2);
		}
	}
	return proposition;
}

/***************************************************************************
  �������ƣ�toBinary
  ��    �ܣ���һ����ת��Ϊnλ�Ķ�����
  ���������int n_proposition��λ��
			int index����ת������
  �� �� ֵ��Map_ii��ȡֵ���ϣ�λ��-ȡֵ��
  ˵    ������
***************************************************************************/
Map_ii toBinary(int n_proposition, int index)
{
	Map_ii result;
	for (int i = 0; i < n_proposition; i++) 
	{
		int r = index % 2;
		result[n_proposition - 1 - i] = r;
		index = index / 2;
	}
	return result;
}

/***************************************************************************
  �������ƣ�pow2
  ��    �ܣ�����2��n�η�
  ���������int n��ָ��
  �� �� ֵ��int��2��n�η�
  ˵    ������
***************************************************************************/
int pow2(int n)
{
	if (n == 0)
		return 1;
	else
		return 2 * pow2(n - 1);
}

/***************************************************************************
  �������ƣ�check
  ��    �ܣ����ݲ��������������ջ�����ݣ�������Ӧ������һ��
  ���������stack<int>& value�����������ջ
			stack<char>& opter�����������ջ
  �� �� ֵ����
  ˵    ������
***************************************************************************/
void check(stack<int> &value, stack<char> &opter)
{
	int p, q, result;
	char opt = opter.top();  //ȡջ���������������������Ҫȡ1��������������������ɺ����Ż�ջ�С�ջ���������ջ

	switch (opt) 
	{
	case '&':  //������
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p && q;
		value.push(result);
		opter.pop();
		break;

	case '|':  //������
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = p || q;
		value.push(result);
		opter.pop();
		break;

	case '!':  //������
		p = value.top();
		value.pop();
		result = !p;
		value.push(result);
		opter.pop();
		break;

	case '^':  //�̺�����
		q = value.top();
		value.pop();
		p = value.top();
		value.pop();
		result = !p || q;
		value.push(result);
		opter.pop();
		break;

	case '~':  //�ȼ�����
		p = value.top();
		value.pop();
		q = value.top();
		value.pop();
		result = (!p || q) && (p || !q);
		value.push(result);
		opter.pop();
		break;

	case '#':
		break;

	case '(':
		break;

	case ')':
		opter.pop();
		while (opter.top() != '(')  //��������ֱ����һ�������ų���
		{
			check(value, opter);
		}
		if (opter.top() == '(')  //����һ��������ѹ��ջ��
		{
			opter.pop();
		}
		break;

	default:
		break;
	}
}

/***************************************************************************
  �������ƣ�calculate
  ��    �ܣ����ݹ�ʽ�����⼯�ϣ��±�-�ַ�����ȡֵ���ϣ�λ��-ȡֵ���������ʽ����ֵ
  ���������string formula����ʽ
			Map_ic pSet�����⼯�ϣ��±�-�ַ���
			Map_ii value��ȡֵ���ϣ�λ��-ȡֵ��
  �� �� ֵ��������
  ˵    ������
***************************************************************************/
int calculate(string formula, Map_ic pSet, Map_ii value)
{
	stack<char> opter;  //���������ջ
	stack<int> pvalue;  //���������ջ
	opter.push('#');
	formula = formula + "#";
	for (unsigned int i = 0; i < formula.length(); i++)
	{
		char c = formula[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
		{
			pvalue.push(value[findProposition(pSet, c)]);  //��ĳ����������ȡֵ�ҵ�������ջ��
		}
		else 
		{
			//��ʱ�������������
			char tmp = opter.top();  //ȡջ�������
			if (priority[tmp] > priority[c])  //��ջ�����ȼ��ߣ������㵽ջ�����ȼ�����c���������ų���
			{
				while (priority[tmp] > priority[c] && tmp != '(')
				{
					check(pvalue, opter);
					tmp = opter.top();
					if (tmp == '#' && c == '#')  //������#����˵��������ɣ����ؽ��
					{
						return pvalue.top();
					}
				}
				opter.push(c);  //ջ�����ȼ�����c��c��ջ
			}
			else
				opter.push(c);  //ջ�����ȼ�����c��c��ջ
		}
	}
	return -1;
}

/***************************************************************************
  �������ƣ�isOp
  ��    �ܣ��ж�һ���ַ��Ƿ��������
  ���������const char ch����������������ֻ����
  �� �� ֵ��bool�����ַ��Ƿ��������
  ˵    ���������������ڼӼ��˳����ж�
***************************************************************************/
bool isOp(const char ch)
{
	switch (ch) {
	case '&':
	case '|':
	case '!':
	case '^':
	case '~':
		return true;
		break;
	default:
		return false;
	}
}

/***************************************************************************
  �������ƣ�formulaCheck
  ��    �ܣ��ж�һ�����ʽ�Ƿ�Ϸ�
  ���������const String& str��������ı��ʽ��ֻ����
  �� �� ֵ��bool���ñ��ʽ�Ƿ�Ϸ�
  ˵    �������������ڱ��ʽ��Ԥ���������жϣ�ȥ���ո���Ե�Ŀ������Ĵ���
***************************************************************************/
bool formulaCheck(const string& str)
{
	string::const_iterator it = str.begin();  /*�α����*/
	stack<char> brackets;  /*��¼���������ջ*/
	int op1Num = 0, op2Num = 0, numNum = 0;  /*����������Ŀ��˫Ŀ�����������ָ���*/

	while (it != str.end()) {
		/*1����ɨ�赽�ַ���ʾ���⣬����м���*/
		if (((*it) >= 'a' && (*it) <= 'z') || ((*it) >= 'A' && (*it) <= 'Z'))
			numNum++;  /*һ������ɨ����ɣ����м���*/

		if (*it == '(')  /*�����������ţ�ѹ��ջ��*/
			brackets.push(*it);
		else if (*it == ')') {  /*�����������ţ�ջ��Ϊ���򵯳�һ��Ԫ�أ�ջΪ����˵�������Ŷ��࣬�Ƿ�*/
			if (!brackets.empty())
				brackets.pop();
			
			else {
				cout << "���Ų�ƥ��" << endl;
				return false;
			}
		}
		else if (isOp(*it)) {  /*�����������������м���*/
			if (*it == '!')
				op1Num++;
			else
				op2Num++;
		}

		if (it != str.end())
			it++;
		else
			break;
	}

	if (!brackets.empty()) {  /*��ɨ�����ջ�Բ�Ϊ�գ��������Ŷ��࣬�Ƿ�*/
		cout << "���Ų�ƥ��" << endl;
		return false;
	}

	if (numNum != op2Num + 1) {  /*��˫Ŀ������������������ָ���+1����ƥ�䣬�Ƿ�*/
		cout << "�������������������ƥ��" << endl;
		return false;
	}
	
	return true;  /*���б�׼�����ϣ�����ʽ�Ϸ�*/
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
	priority['('] = 6;
	priority[')'] = 6;
	priority['!'] = 5;
	priority['&'] = 4;
	priority['|'] = 3;
	priority['^'] = 2;
	priority['~'] = 1;
	priority['#'] = 0;
	//��������ȼ�

	cout << "***************************************\n";
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "Please enter a legitimate proposition formula: " << endl;
	string formula;
	cin >> formula;  //���빫ʽ

	if (!formulaCheck(formula))  //��鹫ʽ�Ƿ�Ϸ�
		return 0;

	Map_ic proposition_set = getProposition(formula);  //ͳ���������
	cout << "��ʽ���еı�������Ϊ��" << proposition_set.size() << endl << "�����ֵ�����£�" << endl;
	for (unsigned int i = 0; i < proposition_set.size(); i++)
	{
		cout << proposition_set[i] << "\t";  //������е��������
	}
	cout << formula << endl;
	int *m;
	m = (int*)malloc(sizeof(int)*pow2(proposition_set.size()));   //���������δ�����⹫ʽ�ĸ���(0��1)����������ֵ
	for (int i = 0; i < pow2(proposition_set.size()); i++)  //��2^n��ȡֵ������һ��
	{
		Map_ii bina_set = toBinary(proposition_set.size(), i);  //��ȡֵת��Ϊ������
		for (unsigned int j = 0; j < bina_set.size(); j++)
		{
			cout << bina_set[j] << "\t";  //������������ֵ��ӡ����
		}
		int result = calculate(formula, proposition_set, bina_set);  //���㹫ʽ��ֵ
		*(m+i) = result;  //��¼��һ�˵���ֵ
		cout << result << endl;  //��ӡ��һ�˵ļ�����
	}
	int n_m = 0, n_M = 0;
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)  //ͳ�Ƴ��渳ֵ����ӡ����ȡ��ʽ
	{
		if (*(m + i) == 1)
		{
			if (n_m == 0) 
			{
				cout << "m<" << i << ">";
			}
			else 
			{
				cout << " \\/ m<" << i << "> ";
			}
			n_m++;
		}
	}
	if (n_m == 0)    //�޳��渳ֵ���
	{
		cout << "0";
	}
	cout << endl;
	cout << "�����⹫ʽ������ȡ��ʽ��" << endl;
	for (int i = 0; i < pow2(proposition_set.size()); i++)   //ͳ�Ƴɼٸ�ֵ����ӡ����ȡ��ʽ
	{
		if (*(m + i) == 0)
		{
			if (n_M == 0) 
			{
				cout << "M<" << i << ">";
			}
			else 
			{
				cout << " /\\ M<" << i << "> ";
			}
			n_M++;
		}
	}
	if (n_M == 0)  //�޳ɼٸ�ֵ���
	{
		cout << "0";
	}
	cout << endl;
	return 0;
}