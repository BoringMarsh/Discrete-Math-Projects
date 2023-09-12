#ifndef _STRING_H_
#define _STRING_H_

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

#define STRING_DEFAULT_SIZE 16
#define STRING_BUFFER_SIZE  65536

//���к��������ַ�������
int StrLen(const char* str)
{
	int length = 0;
	
	while (str[length] != '\0')
		length++;

	return length;
}

class String {
private:
	char* data;   //�������
	int size;     //�ַ�����ǰ����
	int maxSize;  //�ַ����������

	void expand(const int _timesOfExpandingDefaultSize);  //��������ռ��С
public:
	String();
	String(const String& str);
	String(const char* str);
	String(const char* str, const int length);
	~String();

	class iterator {
	private:
		char* data;
	public:
		iterator() :data(NULL) {}
		iterator(char* datas) :data(datas) {}

		//��ȡ����
		char& operator*()const
		{
			return *data;
		}
		//�Ƚ�����������
		inline bool operator==(const iterator& s)const
		{
			return (data == s.data);
		}
		//�Ƚ������������
		inline bool operator>(const iterator& s)const
		{
			return (data > s.data);
		}
		//�Ƚ��������С��
		inline bool operator<(const iterator& s)const
		{
			return (data < s.data);
		}
		//�Ƚ�����������ڵ���
		inline bool operator>=(const iterator& s)const
		{
			return (data >= s.data);
		}
		//�Ƚ��������С�ڵ���
		inline bool operator<=(const iterator& s)const
		{
			return (data <= s.data);
		}
		//�Ƚ��������������
		inline bool operator!=(const iterator& s)const
		{
			return (data != s.data);
		}
		//�����������ǰ��
		String::iterator& operator++()
		{
			data++;
			return *this;
		}
		//���������������
		String::iterator operator++(int)
		{
			String::iterator old = *this;
			++(*this);
			return old;
		}
		//�Լ��������ǰ��
		String::iterator& operator--()
		{
			data--;
			return *this;
		}
		//�Լ������������
		String::iterator operator--(int)
		{
			String::iterator old = *this;
			--(*this);
			return old;
		}
		//�ӷ���������+����
		String::iterator operator+(const int num)
		{
			String::iterator old = *this;

			for (int i = 0; i < num; i++)
				old++;

			return old;
		}
		//�ӷ�������+������
		friend typename String::iterator operator+(const int num, const typename String::iterator s)
		{
			typename String::iterator old = s;

			for (int i = 0; i < num; i++)
				++old;

			return old;
		}
		//������������-����
		String::iterator operator-(const int num)
		{
			String::iterator old = *this;

			for (int i = 0; i < num; i++)
				old--;

			return old;
		}
		//����������-������
		friend typename String::iterator operator-(const int num, const typename String::iterator s)
		{
			typename String::iterator old = s;

			for (int i = 0; i < num; i++)
				--old;

			return old;
		}
		//�Լ�
		String::iterator operator+=(const int num)
		{
			for (int i = 0; i < num; i++)
				++(*this);

			return *this;
		}
		//�Լ�
		String::iterator operator-=(const int num)
		{
			for (int i = 0; i < num; i++)
				--(*this);

			return *this;
		}
		//���������
		friend int operator-(const String::iterator s1, const String::iterator s2)
		{
			return (s1.data - s2.data);
		}
	};

	inline String::iterator begin();
	inline const String::iterator begin()const;
	inline String::iterator end();
	inline const String::iterator end()const;
	inline String::iterator last();
	inline const String::iterator last()const;

	char& operator[](const int pos)const;
	String& operator=(const String& str);
	String& operator=(const char* str);
	friend istream& operator>>(istream& istr, String& str);
	friend ostream& operator<<(ostream& ostr, const String& str);
	friend bool operator==(const String& Left, const String& Right);
	friend bool operator==(const String& Left, const char* Right);
	friend bool operator==(const char* Left, const String& Right);
	friend bool operator!=(const String& Left, const String& Right);
	friend bool operator!=(const String& Left, const char* Right);
	friend bool operator!=(const char* Left, const String& Right);
	friend String operator+(const String& Left, const String& Right);
	friend String operator+(const String& Left, const char* Right);
	friend String operator+(const char* Left, const String& Right);
	friend String operator+(const String& Left, const char Right);
	friend String operator+(const char Left, const String& Right);
	friend String operator*(const String& Left, const int Right);
	friend String operator*(const int Left, const String& Right);
	friend String& operator+=(String& Left, const String& Right);
	friend String& operator+=(String& Left, const char* Right);
	friend String& operator+=(String& Left, const char Right);
	friend String& operator*=(String& Left, const int Right);
	String operator--();
	String operator--(int);

	void gets();
	void clear();
	const char* c_str()const;
	int length()const;
	int capacity()const;
	bool isEmpty()const;
	bool isFull()const;
	bool isDigit()const;
	bool isOnlyDigit()const;
	bool stringToDouble(double& d)const;
	bool stringToInt(int& i)const;
	char* reverse();
};

//Ĭ�Ϲ��캯��
String::String()
{
	maxSize = STRING_DEFAULT_SIZE;
	size = 0;

	data = new char[maxSize];
	data[0] = '\0';

	if (data == NULL) {
		cout << "�洢�������" << endl;
		exit(1);
	}
}

//���ƹ��캯������String������
String::String(const String& str)
{
	maxSize = str.maxSize;
	size = str.size;

	data = new char[maxSize];
	if (data == NULL) {
		cout << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
		data[i] = str.data[i];

	data[size] = '\0';
}

//���ƹ��캯������const char*��������
String::String(const char* str)
{
	int length = StrLen(str);

	size = length;
	maxSize = (length / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	data = new char[maxSize];
	if (data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
		data[i] = str[i];
	data[size] = '\0';
}

//��const char*�������ƣ�ͬʱָ�����ȵĹ��캯��������ȡ������Сֵ��
String::String(const char* str, const int length)
{
	int strLength = StrLen(str);
	maxSize = (strLength / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;

	if (strLength >= length)
		size = length;
	else
		size = strLength;

	data = new char[maxSize];
	if (data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
		data[i] = str[i];
	data[size] = '\0';
}

//��������
String::~String()
{
	delete[] data;
}

//�����ַ�������ʼλ��
inline typename String::iterator String::begin()
{
	return size > 0 ? typename String::iterator(&data[0]) : typename String::iterator();
}

//�����ַ�������ʼλ��
inline const typename String::iterator String::begin()const
{
	return size > 0 ? typename String::iterator(&data[0]) : typename String::iterator();
}

//�����ַ���ĩβ�ĺ�һ��λ��
inline typename String::iterator String::end()
{
	return size > 0 ? ++(typename String::iterator(&data[size - 1])) : typename String::iterator();
}

//�����ַ���ĩβ�ĺ�һ��λ��
inline const typename String::iterator String::end()const
{
	return size > 0 ? ++(typename String::iterator(&data[size - 1])) : typename String::iterator();
}

//�����ַ�����ĩβλ��
inline typename String::iterator String::last()
{
	return size > 0 ? typename String::iterator(&data[size - 1]) : typename String::iterator();
}

//�����ַ�����ĩβλ��
inline const typename String::iterator String::last()const
{
	return size > 0 ? typename String::iterator(&data[size - 1]) : typename String::iterator();
}

//���غ������±����
char& String::operator[](const int pos)const
{
	if (pos < 0 || pos >= size) {
		cout << "λ�÷Ƿ����ѷ����׸���ĸ" << endl;
		return data[0];
	}

	return data[pos];
}

//���غ��������ƣ���String�����ƣ�
String& String::operator=(const String& str)
{
	if (*this == str)
		return *this;

	delete[] data;

	maxSize = str.maxSize;
	size = str.size;

	data = new char[maxSize];
	if (data == NULL) {
		cout << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i <= size; i++)
		data[i] = str.data[i];

	return *this;
}

//���غ��������ƣ���const char*�������ƣ�
String& String::operator=(const char* str)
{
	delete[] data;

	int length = StrLen(str);

	size = length;
	maxSize = (length / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;

	data = new char[maxSize];
	if (data == NULL) {
		cout << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i <= size; i++)
		data[i] = str[i];

	return *this;
}

//�����ַ�����֧�ֿո����룩
void String::gets()
{
	char* buffer = new char[STRING_BUFFER_SIZE];
	if (buffer == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	fgets(buffer, STRING_BUFFER_SIZE, stdin);

	const int buffer_len = StrLen(buffer);
	
	if (buffer_len >= maxSize) {
		maxSize = (buffer_len / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
		char* newData = new char[maxSize];
		if (newData == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}

		for (int i = 0; i <= buffer_len; i++)
			newData[i] = buffer[i];

		char* oldData = data;
		data = newData;
		delete[] oldData;
	}

	else {
		for (int i = 0; i < buffer_len; i++)
			data[i] = buffer[i];

		data[buffer_len] = '\0';
	}

	size = buffer_len;
	delete[] buffer;
}

//���ַ�����Ϊ��
void String::clear()
{
	delete[] data;

	maxSize = STRING_DEFAULT_SIZE;
	size = 0;

	data = new char[maxSize];
	if (data == NULL) {
		cout << "�洢�������" << endl;
		exit(1);
	}

	data[size] = '\0';
}

//���غ���������
istream& operator>>(istream& istr, String& str)
{
	char* buffer = new char[STRING_BUFFER_SIZE];
	if (buffer == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	istr >> buffer;

	const int buffer_len = StrLen(buffer);
	
	if (buffer_len >= str.maxSize) {
		str.maxSize = (buffer_len / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
		char* newData = new char[str.maxSize];
		if (newData == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}

		for (int i = 0; i <= buffer_len; i++)
			newData[i] = buffer[i];

		char* oldData = str.data;
		str.data = newData;
		delete[] oldData;
	}

	else {
		for (int i = 0; i < buffer_len; i++)
			str.data[i] = buffer[i];

		str.data[buffer_len] = '\0';
	}

	str.size = buffer_len;
	delete[] buffer;
	return istr;
}

//���غ��������
ostream& operator<<(ostream& ostr, const String& str)
{
	ostr << str.c_str();
	return ostr;
}

//���غ��������ڣ���һ��String������ȣ�
bool operator==(const String& Left, const String& Right)
{
	if (Left.size != Right.size)
		return false;

	for (int i = 0; i < Left.size; i++) {
		if (Left.data[i] != Right.data[i])
			return false;
	}

	return true;
}

//���غ��������ڣ���һ��const char*������ȣ�
bool operator==(const String&Left,const char* Right)
{
	if (Left.size != StrLen(Right))
		return false;

	for (int i = 0; i < Left.size; i++) {
		if (Left.data[i] != Right[i])
			return false;
	}

	return true;
}

//���غ���������
bool operator==(const char* Left, const String& Right)
{
	if (StrLen(Left) != Right.size)
		return false;

	for (int i = 0; i < Right.size; i++) {
		if (Left[i] != Right.data[i])
			return false;
	}

	return true;
}

//���غ����������ڣ���һ��String������ȣ�
bool operator!=(const String& Left, const String& Right)
{
	if (Left.size != Right.size)
		return true;

	for (int i = 0; i < Left.size; i++) {
		if (Left.data[i] != Right.data[i])
			return true;
	}

	return false;
}

//���غ����������ڣ���һ��const char*������ȣ�
bool operator!=(const String& Left, const char* Right)
{
	if (Left.size != StrLen(Right))
		return true;

	for (int i = 0; i < Left.size; i++) {
		if (Left.data[i] != Right[i])
			return true;
	}

	return false;
}

//���غ�����������
bool operator!=(const char* Left, const String& Right)
{
	if (StrLen(Left) != Right.size)
		return true;

	for (int i = 0; i < Right.size; i++) {
		if (Left[i] != Right.data[i])
			return true;
	}

	return false;
}

//���غ������Ҽ���һ��String����
String operator+(const String&Left,const String& Right)
{
	String Str;

	Str.maxSize = ((Left.size + Right.size) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Str.data;
	Str.data = new char[Str.maxSize];
	if (Str.data == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < Left.size; i++)
		Str.data[i] = Left.data[i];

	delete[] oldStr;

	Str.size = Left.size + Right.size;  //���캯�����ַ������Ⱥ�ָ�����ȼ�����ȡ��Сֵ�����ڴ���������sizeֵ
	for (int i = Left.size; i < Str.size; i++)
		Str.data[i] = Right.data[i - Left.size];
	Str.data[Str.size] = '\0';

	return Str;
}

//���غ������Ҽ���һ��const char* str����
String operator+(const String& Left, const char* Right)
{
	const int length = StrLen(Right);
	String Str;

	Str.maxSize = ((Left.size + length) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Str.data;
	Str.data = new char[Str.maxSize];
	if (Str.data == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < Left.size; i++)
		Str.data[i] = Left.data[i];

	delete[] oldStr;

	Str.size = Left.size + length;  //���캯�����ַ������Ⱥ�ָ�����ȼ�����ȡ��Сֵ�����ڴ���������sizeֵ
	for (int i = Left.size; i < Str.size; i++)
		Str.data[i] = Right[i - Left.size];
	Str.data[Str.size] = '\0';

	return Str;
}

//��Ԫ������const char*����+String����
String operator+(const char* Left, const String& Right)
{
	const int length = StrLen(Left);
	String Str;

	Str.maxSize = ((length + Right.size) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Str.data;

	Str.data = new char[Str.maxSize];
	if (Str.data == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < length; i++)
		Str.data[i] = Left[i];

	delete[] oldStr;

	Str.size = length + Right.size;  //���캯�����ַ������Ⱥ�ָ�����ȼ�����ȡ��Сֵ�����ڴ���������sizeֵ
	for (int i = length; i < Str.size; i++)
		Str.data[i] = Right[i - length];
	Str.data[Str.size] = '\0';

	return Str;
}

//���غ������Ҽ���һ���ַ�
String operator+(const String& Left, const char Right)
{
	String Str;

	if (Left.size + 1 >= Str.maxSize) {
		Str.maxSize = ((Left.size + 1) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
		char* oldStr = Str.data;
		Str.data = new char[Str.maxSize];
		if (Str.data == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}

		delete[] oldStr;
	}

	for (int i = 0; i < Left.size; i++)
		Str.data[i] = Left.data[i];

	Str.data[Left.size] = Right;
	Str.data[Left.size + 1] = '\0';
	Str.size = Left.size + 1;

	return Str;
}

//��Ԫ�������ַ�+String����
String operator+(const char Left, const String& Right)
{
	String Str;

	if (Right.size + 1 >= Str.maxSize) {
		Str.maxSize = ((Right.size + 1) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
		char* oldStr = Str.data;
		Str.data = new char[Str.maxSize];
		if (Str.data == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}

		Str.data[0] = Left;

		for (int i = 0; i <= Right.size; i++)
			Str.data[i + 1] = Right.data[i];

		delete[] oldStr;
	}

	else {
		Str.data[0] = Left;
		for (int i = 1; i < Right.size + 1; i++)
			Str.data[i] = Right.data[i - 1];

		Str.data[Right.size + 1] = '\0';
	}

	Str.size = Right.size + 1;
	return Str;
}

//���غ������˷�
String operator*(const String& Left, const int Right)
{
	String Str;

	if (Right <= 0)
		return Str;

	Str.maxSize = (Left.size * Right / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Str.data;
	Str.data = new char[Str.maxSize];
	if (Str.data == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	delete[] oldStr;

	for (int i = 0; i < Right; i++) {
		for (int j = 0; j < Left.size; j++) {
			Str.data[i * Left.size + j] = Left[j];
		}
	}

	Str.size = Left.size * Right;
	Str.data[Right * Left.size] = '\0';

	return Str;
}

//���غ������˷�
String operator*(const int Left, const String& Right)
{
	String Str;

	if (Left <= 0)
		return Str;

	Str.maxSize = (Right.size * Left / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Str.data;
	Str.data = new char[Str.maxSize];
	if (Str.data == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	delete[] oldStr;

	for (int i = 0; i < Left; i++) {
		for (int j = 0; j < Right.size; j++) {
			Str.data[i * Right.size + j] = Right[j];
		}
	}

	Str.size = Right.size * Left;
	Str.data[Left * Right.size] = '\0';

	return Str;
}

//���غ���������һ��String����
String& operator+=(String& Left, const String& Right)
{
	Left.maxSize = ((Left.size + Right.size) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Left.data;
	Left.data = new char[Left.maxSize];
	if (Left.data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < Left.size; i++)
		Left.data[i] = oldStr[i];

	Left.size = Left.size + Right.size;

	for (int i = Left.size - Right.size; i < Left.size; i++)
		Left.data[i] = Right.data[i - Left.size + Right.size];

	Left.data[Left.size] = '\0';
	delete[] oldStr;

	return Left;
}

//���غ���������һ��const char*����
String& operator+=(String& Left, const char* Right)
{
	int length = StrLen(Right);
	Left.maxSize = ((Left.size + length) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Left.data;
	Left.data = new char[Left.maxSize];
	if (Left.data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < Left.size; i++)
		Left.data[i] = oldStr[i];

	Left.size = Left.size + length;

	for (int i = Left.size - length; i < Left.size; i++)
		Left.data[i] = Right[i - Left.size + length];

	Left.data[Left.size] = '\0';
	delete[] oldStr;

	return Left;
}

//���غ���������һ���ַ�
String& operator+=(String& Left, const char Right)
{
	if (Left.size + 1 >= Left.maxSize) {
		Left.maxSize = ((Left.size + 1) / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
		char* oldStr = Left.data;

		Left.data = new char[Left.maxSize];
		if (Left.data == NULL) {
			cerr << "�洢����ʧ�ܣ�" << endl;
			exit(1);
		}

		for (int i = 0; i < Left.size; i++)
			Left.data[i] = oldStr[i];

		delete[] oldStr;
	}
	
	Left.data[Left.size] = Right;
	Left.data[Left.size + 1] = '\0';
	Left.size++;

	return Left;
}

//���غ������������ɱ�
String& operator*=(String& Left, const int Right)
{
	if (Right <= 0)
		return Left;

	Left.maxSize = (Left.size * Right / STRING_DEFAULT_SIZE + 1) * STRING_DEFAULT_SIZE;
	char* oldStr = Left.data;
	Left.data = new char[Left.maxSize];
	if (Left.data == NULL) {
		cerr << "�洢�������" << endl;
		exit(1);
	}

	for (int i = 0; i < Right; i++) {
		for (int j = 0; j < Left.size; j++) {
			Left.data[i * Left.size + j] = oldStr[j];
		}
	}

	delete[] oldStr;
	Left.data[Right * Left.size] = '\0';
	Left.size = Left.size * Right;

	return Left;
}

//����һ���ַ���ǰ׺��
String String::operator--()
{
	if (size == 0)
		return *this;

	String old = *this;
	data[size - 1] = '\0';
	size--;
	return old;
}

//����һ���ַ�����׺��
String String::operator--(int)
{
	if (size == 0)
		return *this;

	data[size - 1] = '\0';
	size--;
	return *this;
}

//�����ַ����׵�ַ����const char*��ʽ���أ�
const char* String::c_str()const
{
	return data;
}

//�����ַ�������
int String::length()const
{
	return StrLen(data);
}

//�����ַ����������
int String::capacity()const
{
	return maxSize;
}

//�ж��ַ����Ƿ�Ϊ��
bool String::isEmpty()const
{
	return (size == 0);
}

//�ж��ַ����Ƿ�����
bool String::isFull()const
{
	return (size == maxSize - 1);
}

//���ַ�����ת
char* String::reverse()
{
	String::iterator front = begin();
	String::iterator back = last();
	char temp;

	while (front < back) {
		temp = *front;
		*front = *back;
		*back = temp;

		front++;
		back--;
	}

	return data;
}

//�ж��ַ����Ƿ��ʾһ����ֵ
bool String::isDigit()const
{
	String::iterator iter = begin();
	bool if_point = false;

	if (*iter == '\0')
		return false;
	else if (*iter == '-') {
		if (*(iter + 1) < '0' || *(iter + 1) > '9')
			return false;

		else
			iter++;
	}

	while (iter != end()) {
		if (*iter == '.') {
			if (!if_point) {
				if (*(iter - 1) < '0' || *(iter - 1) > '9' || *(iter + 1) < '0' || *(iter + 1) > '9')
					return false;

				else
					if_point = true;
			}

			else
				return false;
		}

		else if (*iter < '0' || *iter > '9')
			return false;

		iter++;
	}

	return true;
}

//�ж��ַ����Ƿ��������
bool String::isOnlyDigit()const
{
	String::iterator iter = begin();

	while (iter != end()) {
		if (*iter < '0' || *iter>'9')
			return false;

		iter++;
	}

	return true;
}

//���ַ���ת��˫������
bool String::stringToDouble(double& d)const
{
	if (!isDigit())
		return false;

	String::iterator iter = begin();
	bool if_minus = false, if_point = false;
	double result = 0.0;
	int count = 1;

	if (*iter == '-') {
		if_minus = true;
		iter++;
	}

	while (iter != end()) {
		if (*iter == '.') {
			if_point = true;
			iter++;
		}

		if (if_point) {
			double item = double(*iter) - '0';

			for (int i = 0; i < count; i++)
				item = item / 10;

			result += item;
			count++;
		}

		else
			result = result * 10 + *iter - '0';

		iter++;
	}

	if (if_minus)
		d = -1.0 * result;
	else
		d = result;

	return true;
}

//���ַ���ת��������
bool String::stringToInt(int& i)const
{
	if (!isDigit())
		return false;

	String::iterator iter = begin();
	bool if_minus = false;
	int result = 0;

	if (*iter == '-') {
		if_minus = true;
		iter++;
	}

	while (iter != end()) {
		if (*iter == '.')
			break;

		result = result * 10 + *iter - '0';
		iter++;
	}

	if (if_minus)
		i = -1 * result;
	else
		i = result;
	return true;
}

//��������ռ��С
void String::expand(const int _timesOfExpandingDefaultSize)
{
	if (_timesOfExpandingDefaultSize <= 0)
		return;

	maxSize += _timesOfExpandingDefaultSize * STRING_DEFAULT_SIZE;
	char* oldData = data;
	data = new char[maxSize];
	if (data == NULL) {
		cerr << "�洢����ʧ�ܣ�" << endl;
		exit(1);
	}

	for (int i = 0; i < size; i++)
		data[i] = oldData[i];
	data[size] = '\0';

	delete[] oldData;
}

#endif