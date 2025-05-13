#define Prac 4

// STL Container
// 1. Sequence Containers
// array<T, N>
// vector<T>	- push_back() O(1) ���⵵
// list<T>		- node, ��� ���� ��ġ���� ���԰� ���� O(1)
// deque<T>		- push_front() / push_back() O(1) , vector���� �� ���� ���Ҹ� ���� �� �ִ�.

#include "STRING.h"

using namespace std;
extern bool inspect;

#if Prac == 1

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <ranges>
#include <deque>

// =======================================================================
// �����̳ʰ� ���� �� �ִ� �뷮�� ���Ѵ�.
//========================================================================

class Test {
	char x[1'000'000];
};
int main()
{
	// vector<Test> v; �� ���� �Ʒ� ���� �������� �ƴ϶� ���� �ִٸ�?
	{
		//vector<Test> v;	// �ִ� ���� �� - 27310
		//
		//// try-catch ����
		//try {
		//	while (true) {
		//		v.emplace_back();
		//	}
		//}
		//catch (...) {
		//	cout << "�ִ� ���� �� - " << v.size() << endl;
		//}

	}

	//{
	//	deque<Test> d;		// �ִ� ���� �� - 57361

	//	// try-catch ����
	//	try {
	//		while (true) {
	//			d.emplace_back();
	//		}
	//	}
	//	catch (...) {
	//		cout << "�ִ� ���� �� - " << d.size() << endl;
	//	}

	//}

	// list�� Test�� �� �� ���� �� ������?? - �߿�
	{
		list<Test> l;		// �ִ� ���� �� - 57029

		// try-catch ����
		try {
			while (true) {
				l.emplace_back();
			}
		}
		catch (...) {
			cout << "�ִ� ���� �� - " << l.size() << endl;
		}

	}

}

#elif Prac == 2
#include <iostream>
#include <list>
#include <string.h>
#include <ranges>
// =======================================================================
//[����] container�� ��� ���Ҹ� ����϶�
// => container �� �ι�° ���Һ��� �������� ����϶�
//========================================================================

int main()
{
	list<int> cont{ 1,2,3,4,5,6,7,8,9,10 };

	for (int num : cont)
	{
		cout << num << " ";
	}
	cout << endl;

	auto beg = cont.begin();
	beg.operator++();	// �� ��� ������ list���� ó���Ѵ�.

	// cont�� vector,array,deque,string���ٸ� ����
	//for (int i = 1; i < cont.size(); ++i)
	//	cout << cont[i] << " ";


	// �ذ� ��� - �ݺ��� ����
	// list<int>::iterator begin = cont.begin();	// �� ��Ȳ���� auto�� ����Ѵ�.

	// i < end()�� �ƴ϶� != end()���� �������, �ּҸ� ���ϰ� �ǹǷ� ��� �񱳰� �Ұ����ϴ�.
	// cont.begin() == l-value���� �������.
	for (auto i = ++cont.begin(); i != cont.end(); ++i) {
		cout << *i << " ";
	}


	//for (int num : views::drop(cont, 1))
	//{
	//	cout << num << " ";
	//}
	cout << endl;


}

#elif Prac == 3
#include <iostream>
#include <list>
#include <unordered_set>
#include <ranges>

// =======================================================================
//[����] container�� ���Ҹ� "�Ųٷ�" ����Ͻÿ�
// container�� set, unordered_set,vector���� �Ǿ �˰����� �ݺ��ڸ� ����Ͽ� ����ϴ� ����� �ٲ��� �ʴ´�.
//========================================================================

int main()
{
	//list<int> cont{ 1,3,5,7,9,2,4,6,8,10 };

	unordered_set<int> cont{ 1,3,5,7,9,2,4,6,8,10 };

	/*for (auto i = cont.begin(); i != cont.end(); ++i)
	{
		cout << *i << " ";
	}*/

	// rbegin() == end()�ڸ��� �ٵ� �� ����� �ǳ�? �ڡڡڡڡ�
	// https://en.cppreference.com/w/cpp/iterator/reverse_iterator 
	// rebegin().operator*�� ����� ����, ���� ������ ���Ҹ� ����Ͽ��ֱ� �����̴�.
	/*for (auto i = cont.rbegin(); i != cont.rend(); ++i)
	{
		cout << *i << " ";
	}*/

	for (int a : ranges::reverse_view(cont))
	{
		cout << a << " ";

	}
	cout << endl;

}

#elif Prac == 4
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>

// =======================================================================
//[����] "main.cpp"�� �ܾ list�� ��������.
// ã�� �ܾ �������, ������ ����, ������ list�� ���° �ܾ����� �������.
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;

	// ���۷����͸� ������� ������ (>>) ������ �ʱ�ȭ
	// {���� ���� ���ͷ�����} ����, ���� ��{}����
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	while (true) {
		cout << "ã���� �ܾ��?";
		STRING str;
		cin >> str;
		// ����Ʈ���� Ư���� ������� ã���� ����� �ִ°�? ������ ǥ�� �˰��� ���
		// cont.find()�� �ִ°�? ������ ���� �˰��� ���
		// cont.sort()�� �����ϱ� ������ �̷� ������ ����,  ǥ�� ���� �˰��򺸴� ������ ����
		auto i = find(cont.begin(), cont.end(), str);
		if (i != cont.end())
			cout << "ã�ҽ��ϴ�." << endl;
		else
			cout << str << " - ���� �ܾ� �Դϴ�." << endl;
	}
	
	

	

}
#endif 



