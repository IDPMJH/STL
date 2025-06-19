#define Prac 5

#include "STRING.h"

// �⸻ ������ E320ȣ����


using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <thread>
#include <chrono>
#include <print>

// =======================================================================
//[����] rotate, shift_left
// undefined behavior
//========================================================================

int main()
{
	// sorting ���� �˰��� ����
	string s{ "C++ Standard Template Library - 2025.06.12" };

	for (int i = 0; i < 12; ++i)
		cout << endl;

	//while (true)
	//{
	//	print("{:^80}'\r'", s);
	//	
	//	//cout << s << endl;
	//	// 100ms����
	//	this_thread::sleep_for(100ms);

	//	rotate(s.begin(),s.end() - 2, s.end());
	//}

	//while (true)
	//{
	//	print("{:^80}'\r'", s);

	//	//cout << s << endl;
	//	// 100ms����
	//	this_thread::sleep_for(100ms);

	//	shift_left(s.begin(), s.end(), 1);
	//}

	while (true)
	{
		print("{:^80}'\r'", s);

		//cout << s << endl;
		// 100ms����
		this_thread::sleep_for(100ms);

		shuffle(s.begin(), s.end(), less<string>());
	}
}

#elif Prac == 2
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <print>
#include <numeric>
// =======================================================================
//[����] ���� Algorithm�� �˾ƺ��� - ���⵵ ������
// 
// 1. partition - O(N)
// 2. nth_element
// 3. partial_sort
// 4. sort			- O(N logN)
// 5. stable_sort
//========================================================================

default_random_engine dre{ random_device{}() };
int main()
{
	vector<int> v(100);
	iota(v.begin(), v.end(), 1);
	// partition
	{
		cout << "Ȧ���� ¦���� �и�" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "partition ��" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		auto p = partition(v.begin(), v.end(), [](int num) {
			return num & 1; });

		cout << "Ȧ��" << endl;
		for (auto i = v.begin(); i < p; ++i)
			print("{:8}", *i);
		cout << endl;


		cout << "¦��" << endl;
		for (auto i = p; i < v.end(); ++i)
			print("{:8}", *i);
		cout << endl;

		// 1 2 3 .. 9 0
		// 6 8 9 0�� ������ ���ڸ� ���� �� ���?
	}

	// nth_element
	{
		// ex Ȧ�� 30���� �������� �и� ��
		cout << "40��° ������ �������� �и�" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "nth_element ���� ��" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		nth_element(v.begin(), v.begin() + 40, v.end());

		cout << "�տ������� 40��" << endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i)
			print("{:8}", *i);
		cout << endl;


		cout << "������" << endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i)
			print("{:8}", *i);
		cout << endl;
	}

	// partial sort
	{
		cout << "40��° ������ ����" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "partial sort ���� ��" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		partial_sort(v.begin(), v.begin() + 40, v.end(), greater<int>{});

		cout << "�տ������� 40���� ����" << endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i)
			print("{:8}", *i);
		cout << endl;


		cout << "������" << endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i)
			print("{:8}", *i);
		cout << endl;
	}

	// sort
	{
		cout << "����" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "sort ���� ��" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		sort(v.begin(), v.end());

		cout << "���� ��" << endl;
		for (auto i = v.begin(); i < v.end(); ++i)
			print("{:8}", *i);
		cout << endl;
	}
}

#elif Prac == 3
#include <iostream>
#include <random>
#include <ranges>


default_random_engine dre{ random_device{}() };
uniform_int_distribution<int> uidChar{ 'A','Z' };
uniform_int_distribution<int> uid{ 1,100 };



struct Dog {
	char c{ static_cast<char>(uidChar(dre)) };
	int n{ uid(dre) };


	friend ostream& operator<<(ostream& os, const Dog& dog) {
		print(os, "{} - {:3}", dog.c, dog.n);
		return os;
	}
};

// =======================================================================
//[����] stable sort - �ڰ��� ������(equivalent)������ ��ġ�� �ٲ��� �ʴ� ����
//========================================================================

int main()
{
	vector<Dog> dogs(100);

	cout << "���� �� " << endl;
	for (const Dog& dog : dogs)
	{
		cout << dog << endl;
	}

	//// c ������������ ����
	//sort(dogs.begin(), dogs.end(), [](const Dog& a, const Dog& b) {
	//	return a.c < b.c;
	//	});

	cout << "Dog::c ���� ������������ ����" << endl;
	ranges::sort(dogs, {}, &Dog::c);
	for (const Dog& dog : dogs)
	{
		cout << dog << endl;
	}

	cout << "Dog::n ���� ������������ ����" << endl;
	//ranges::sort(dogs, {}, &Dog::n);
	ranges::stable_sort(dogs, less<int>{}, & Dog::n);
	for (const Dog& dog : dogs)
	{
		cout << dog << endl;
	}
}

#elif Prac == 4
#include <iostream>

// =======================================================================
//[����] 
// ���� �˰����
// �����Ͱ� ���ĵǾ��ִٸ�, ������ ���� Ž�� ���
// set �Լ��� - include, intersection, union ��
// merge�� ������ �Ǿ��־�� ��
// heap �Լ���
// min/max/clamp�Լ�
// permutation ���� next_permutation ��
// Numeric �˰���
// iota, accumulate - reduce
//========================================================================

int main()
{

}



#elif Prac == 5
#include <iostream>
#include <vector>
#include <list>
#include <concepts>
// =======================================================================
//[����] iterator ���̺귯�� ������
// �ݺ��ڰ��� �Ÿ��� ��� distance�Լ��� �����غ���.
// - �ݺ��� Ÿ�Կ� ���� �ٸ� ������ �� �� �ִ�.
// - ������ �Լ��� ȣ�� => function dispatch
// - �Լ� ȣ���ϴ� ���� ����ǥ�� �޾� ���� => tag dispatch
// ::�� ��� ���� C++ 17���� ���, 
// C++17���Ĵ� �����Ϸ��� ���ǿ� ���� �ʴ� �ڵ带 �����ϴ� if constexpr�� ���
// ::C++ 20���ʹ�
// - concept�� ����Ͽ� ������ ���� �Ǵ��� �� �ִ�.
// ���� ������ ������ ����
//========================================================================


// C++ 17 ���Ŀ��� if- constexpr
template<class Iter>
iterator_traits<Iter>::difference_type my_distance(Iter b, Iter e)
{
	// ���� Iter�� random_access_iterator_tag���
	// C++ 20�� concept�� �̿��ϸ� �Ǻ��� ����.

						// concept
	if constexpr  (random_access_iterator<Iter>)
	{
		return e - b;
	}
	else
	{
		// �ڷ����� ���� ���ظ���
		typename iterator_traits<Iter>::difference_type d{};
		while (b != e)
		{
			++b;
			++d;
		}
		return d;
	}
}
//https://en.cppreference.com/w/cpp/iterator/distance.html 
//template<>
//iterator_traits<list<int>::iterator>::difference_type my_distance<list<int>::iterator>(list<int>::iterator b, list<int>::iterator e)
//{
//	
//
//	// �ڷ����� ���� ���ظ���
//	typename iterator_traits<list<int>::iterator>::difference_type d{};
//	while (b != e)
//	{
//		++b;
//		++d;
//	}
//	return d;
//
//}
//
//
//// C++ 17 �������� tag-dispatch
//template<>
//iterator_traits<list<int>::iterator>::difference_type my_distance<list<int>::iterator>(list<int>::iterator b, list<int>::iterator e)
//{
//	// ���� Iter�� random_access_iterator_tag���
//	// C++ 20�� concept�� �̿��ϸ� �Ǻ��� ����.
//
//
//
//	// �ڷ����� ���� ���ظ���
//	typename iterator_traits<list<int>::iterator>::difference_type d{};
//	while (b != e)
//	{
//		++b;
//		++d;
//	}
//	return d;
//
//}

int main()
{
	vector<int> v{ 1,2,3,4,5 };
	list<int> c{ 1,2,3,4,5 };

	//cout << "vector�� distance - " << my_distance(v.begin(), v.end()) << endl;
	cout << "list�� distance - " << my_distance(c.end(), c.begin())<< endl;
}
#endif 



