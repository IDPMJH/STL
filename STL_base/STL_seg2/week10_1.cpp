#define Prac 6

#include "STRING.h"
using namespace std;
extern bool inspect;

// �˰��� ���̺귯���� ���� �н��Ѵ�.
// ��κ��� �˰����� ������ �����ϱ� ������ ����� �Ѵ�. (��κ�)
// �˰��򿡼� ���� �߿��� ���� ���⵵
// 1. Non-modifying sequence operations - find ��


// 06.19 (��) - 15�� 2�� - �⸻ ����
// STL Container
// 1. Sequence Containers
// array<T, N>
// vector<T>	- push_back() O(1) ���⵵
// list<T>		- node���, ���� ��ġ���� ���԰� ���� O(1)
// deque<T>		- push_front() / push_back() O(1) , vector���� �� ���� ���Ҹ� ���� �� �ִ�.

// list���� ��ǥ ���� - sort(), unique(), merge(), splice();

// �ڡ�
// forward_list<T>
// std::forward_list is a container 
// that supports fast insertion and removal of elements 
// from anywhere in the container.

// It is intended thar forward_list have zero space or time overhead
// ����������, �ð������� ���غ��� ���� ����.
// relative to a hand-written C-style singly linked list.
// ���� ������ § C Style�� ������ ���� ����Ʈ �ڵ庸��, (������ �ڵ��̴�.)
// Features thar would confilic with that goal have been omitted
// �� ����� �浹�� ���� ����� ������� �ʱ� �����̴�.


// C++ 20 ���� �ٲ� �˰���, Constrained algorithms
// https://en.cppreference.com/w/cpp/algorithm/ranges 
// ���� �߻��� ������ �Ǵ� �޽��� ���, �����Ϸ� ȿ�� ����

// �Լ��� ���� �����ϰ� - C++ 26 contract
// https://en.cppreference.com/w/cpp/contract 
#if Prac == 1

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
// =======================================================================
//[����] 
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;

	// ���۷�����(>>)�� ������� ������ ������ �ʱ�ȭ
	// {���� ���� ���ͷ�����} ����, ���� ��{}����
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	while (true) {
		cout << "ã���� �ܾ��?";
		STRING str;
		cin >> str;
		// ����Ʈ���� Ư���� ������� ã���� ����� �ִ°�? ������ ǥ�� �˰��� ���
		// cont.find()�� �ִ°�? ������ ���� �˰��� ���
		// cont.sort()�� �����ϱ� ������ �̷� ������ ����, ǥ�� ���� �˰��򺸴� ������ ����
		auto pi = find(cont.begin(), cont.end(), str);
		// ã�� ��ġ�� ����, ��ã���� end ���ͷ����� ��ȯ
		if (pi != cont.end())
			cout << "ã�ҽ��ϴ�. ��ġ: " << distance(cont.begin(), pi) + 1 << endl;
		else
			cout << str << " - ���� �ܾ� �Դϴ�." << endl;
	}
}

#elif Prac == 2
#include <iostream>
#include <algorithm>
#include <fstream>
#include <list>
#include <ranges>

// =======================================================================
//[����] �ܾ� ���̰� 5�� �ܾ ȭ�鿡 ����϶�
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	// for �� �ش�
	// for loop ���� STL�� ����ϴ� ���� ������,
	// Ư�� loop�ȿ� �Լ� ȣ���� �ִٸ� STL�� ����ϴ� �� ���
	/*for (const STRING& str : cont)
	{
		if (5 == str.size())
			cout << str << endl;
	}*/

	auto p = cont.begin();
	while(true)
	{
		p = find_if(p++, cont.end(), [](const STRING& e) {
			return 5 == e.size();
			});
		if (p != cont.end())
			cout << *p << endl;
		else
			break;
	}

	
	// 

}

#elif Prac == 3
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

// =======================================================================
//[����] copy�˰����� ����Ͽ� ���ϴ� �����͸� �������� ���� ����
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	// ��� ��� �ڵ�
	// �����Ϸ��� ��� ���۷����� (>>)�� �ڵ� �Ǿ��־�� ��
	// �׷��� ���鹮�ڰ� ����
	//copy(cont.begin(), cont.end(), ostream_iterator<STRING>{cout});

	// �������� ����
	// copy(cont.begin(), cont.end(), ostream_iterator<STRING>{cout, "\n"});

	// ���� ����
	copy_if(cont.begin(), cont.end(), ostream_iterator<STRING>{cout, "\n"},
		[](const STRING& str) {
			return 5 == str.size();	// �׻� ���ǽĿ��� ����� ���ʿ�, ������ �ܰ迡�� ���� �߻���Ű�� ����
		});
}

#elif Prac == 4
#include <iostream>
#include <list>
#include <algorithm>
#include <string>

// =======================================================================
//[����] sort(), unique() - ������ ��� ����ũ�ϰ�, merge(), splice();
//========================================================================

int main()
{ 
	//inspect = true;
	list<STRING> list1{ "1","55555","333" };
	list<STRING> list2{ "4444", "22" };
	//inspect = false;
	// O(1)�ð��� ������
	// �̶� ���������� &&, rvalue ���۷�����, ���ڷ� �� ����� rvalue�� ��

	// merge�� ������, �ݵ�� ���� �� merge�Ѵ�.
	// ���� ������ debug ��忡�� ���� �߻�
	inspect = true;
	list1.sort();	// less ������(<)�� �ڵ� �Ǿ� �־�� �Ѵ�.
	list2.sort();
	inspect = false;

	inspect = true;
	list1.merge(list2);
	inspect = false;
	for (const STRING& str : list1)
		cout << str << " ";
}


#elif Prac == 5
#include <iostream>
#include <forward_list>
// =======================================================================
//[����] forward_list�� Ư�� �˾ƺ���
//========================================================================

int main()
{
	forward_list<STRING> cont;

	cout << sizeof cont << endl;
}

#elif Prac == 6
#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <span>
// =======================================================================
//[����] �����̳� ����
//========================================================================

// std::function<T> == ��� callableŸ��(�Լ� ������, ����, �Լ� ��ü)
// �� ��ǥ�ϴ� callable Ÿ��
// �׷��ٸ� contiguous�޸� �����̳ʸ� ��ǥ�ϴ� Ÿ�� => "span"
template <class T>
void f(span<int> s)
{
	for (auto i = s.rbegin(); i != s.rend(); ++i)
		cout << *i << " ";
	cout << endl;
}

int main()
{
	// contiguous memory
	int a[]{ 1,2,3,4,5,6,7 };
	string s;
	vector<int> v{ begin(a),end(a) };  // {& a[0],&a[7]};

	// continous memory
	deque<int> d;


	// �Ųٷ� ����϶�
	f<int>(a);
}
#endif 



