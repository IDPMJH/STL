#define Prac 3

#include "STRING.h"

// Container <= [Iterator] => Alogrithm
// �ݺ��ڸ� �˾ƾ� �����̳ʿ� �˰����� ��ȣ�ۿ��� �� �� �ִ�.
// Sequence  
//	- array		] => span<T> �� ���۷��� ����
//	- vector	]
//	- deque
//	- list
//	- forward_list
//
// 
// Iterator - �ݺ���
// "Iterators are a generalization of pointers
// that allow a C++ program to work with different data structures
// in a uniform manner."
// 
// "�ݺ��ڴ� �����͸� �Ϲ�ȭ �س��� ���̴�.
// == �����Ͱ� �� �� �ִ� ���� ���� �Ϲ�ȭ �س��� ��
// C++ ���α׷��� ���� �ٸ� �ڷᱸ���� ���̿��� ������ �� �ֵ���
// �ϰ��� �������"
// 
// ���ͷ����ʹ� ��κ��� ������ ���� ������ ���� �ֵ��� 
// �߻�ȭ / �Ϲ�ȭ �س��� ���̴�.
// ��ġ �����͸� ������ �����Ѵ�.
// ���ͷ����� ī�װ�



using namespace std;
extern bool inspect;

#if Prac == 1

#include <iostream>
#include <string>
// =======================================================================
//[����] 
//========================================================================

int main()
{
	std::string s{ "2025 5 13" };
	for (const char c : s)
		cout << c;
	cout << endl;

	STRING S{ "2025 5 13 STRING Ver." };
	// Syntactic sugar 
	for (const char c : S)	// ����(range)�� �ʿ�
	{
		cout << c << " ";
	}
	// ���� �Ʒ��� �Ȱ��� �ǹ��̴�.
	/*for (auto c = S.begin(); c != S.end(); ++c)
	{
		cout << *c;
	}*/
	cout << endl;


}

#elif Prac == 2
#include <iostream>
#include <iterator>

// =======================================================================
// �ݺ��ڴ� �����͸� �Ϲ�ȭ�� ���̴�. 
// ����͸� ���÷� �����Ѵ�.
// cout == ������̴�.
//========================================================================

int main()
{
	// ������ �� �ݵ�� � ��Ʈ���� ����ų �ݺ������� ������ �ʿ��ϴ�.
	// ����Ʈ �����ڰ� �����Ǿ� �ִ�. ������() = delete
	ostream_iterator<char> p{ cout };

	// ���� �����Ϳ� �����ϰ� �����Ѵ�.
	// �׸��� �����Ϳ� �����ϰ� �����ϴ� ��ó�� ���̵��� ���� ����
	// uniform manner�̴�.

	*p = 'A';	// p.operator*() = 'A';
	++p;		// p.operator++(); (���� �����ڵ� �����ε� �����ϴ�)
	*p = 'B';
	//++p;
	*p = 'C';
	//++p;
	*p = '\n';

	// ����� cout �� 
	// 1. �����Ͱ� ���� ������ Ŀ���� �ڵ����� ����++�� ���� �ʾƵ� �ȴ�.
	// 2. ���⸸ �ϴ� ��Ʈ���̱� ������ *�� ������ �ʾƵ� �ȴ�.
	// �׷��� �̴� �������� �⺻ ���۰� �ٸ� �����̱� ������
	// ������ó�� ���� unform manner�� ����ȴ�.

}

#elif Prac == 3
#include <iostream>
#include <span>

// =======================================================================
//[����] �����̳� ���ڸ� �Ųٷ� ����Ͻÿ�
//========================================================================

int main()
{
	//std::string s1{ "2025 05 13" };
	//
	//for (auto a = s1.rbegin(); a != s1.rend(); ++a)
	//	cout << *a;

	char s2[]{ "2025 05 13" };
	unique_ptr<char[]> p{ s2 };
	/*for (int i = sizeof(s2); i != 0; --i)
	{
		cout << s2[i - 1];
	}*/


	
	// span�� �̿�
	/*span<char> a{ s2 };
	for (auto i = a.rbegin(); i != a.rend(); ++i)
	{
		cout << *i;
	}*/

	// ����� ���� rbegin(), rend(), *rebegin(), operator++ �� �����ϱ�
	// rend()�� rebegin()�� ��ȯ�ϴ� ��ü�� Ÿ���� �����Ѵ�. (Ư���ϰ�)


	// �� �ݺ��ڴ� Ŭ������ �ڵ��Ѵ�.
	STRING s3{ "2025 05 13" };

	for (auto i = s3.rbegin(); i != s3.rend(); ++i)
	{
		cout << *i;
	}



}
#elif Prac == 4
#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

// =======================================================================
//[����] �ݺ��ڴ� ����(6 category)�� �ִ�.
// �Լ� f�� �ݺ��ڸ� ���ڷ� �޾� � ������ �ݺ������� ȭ�鿡 ����ϴ� �Լ��̴�.
// ���� �ڵ尡 ���� ���� ����ǵ��� �غ���.
//========================================================================


template<class Iterator>
void f(Iterator i)
{
	// � ������ �ݺ������� ���
	cout << "[" << typeid(i).name() << "�� �ݺ��� category]  " << endl << typeid(Iterator::iterator_category).name() << endl;
	cout << endl;
}
int main()
{
	// 1. 
	//f(array<int, 0>::iterator{});
	array<int, 2> a;
	f(a.begin());

	// 2. 
	vector<int> v;
	f(v.begin());

	// 3.
	f(deque<STRING>::iterator{});

	// 4.
	f(list<int>{}.rbegin());

	// 5.
	f(forward_list<int>::const_iterator{});
}
#endif 






