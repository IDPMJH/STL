#define Prac 5

#include "STRING.h"

// 기말 시험은 E320호에서


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
//[문제] rotate, shift_left
// undefined behavior
//========================================================================

int main()
{
	// sorting 관련 알고리즘 이해
	string s{ "C++ Standard Template Library - 2025.06.12" };

	for (int i = 0; i < 12; ++i)
		cout << endl;

	//while (true)
	//{
	//	print("{:^80}'\r'", s);
	//	
	//	//cout << s << endl;
	//	// 100ms쉬고
	//	this_thread::sleep_for(100ms);

	//	rotate(s.begin(),s.end() - 2, s.end());
	//}

	//while (true)
	//{
	//	print("{:^80}'\r'", s);

	//	//cout << s << endl;
	//	// 100ms쉬고
	//	this_thread::sleep_for(100ms);

	//	shift_left(s.begin(), s.end(), 1);
	//}

	while (true)
	{
		print("{:^80}'\r'", s);

		//cout << s << endl;
		// 100ms쉬고
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
//[문제] 정렬 Algorithm을 알아본다 - 복잡도 순으로
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
		cout << "홀수와 짝수로 분리" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "partition 전" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		auto p = partition(v.begin(), v.end(), [](int num) {
			return num & 1; });

		cout << "홀수" << endl;
		for (auto i = v.begin(); i < p; ++i)
			print("{:8}", *i);
		cout << endl;


		cout << "짝수" << endl;
		for (auto i = p; i < v.end(); ++i)
			print("{:8}", *i);
		cout << endl;

		// 1 2 3 .. 9 0
		// 6 8 9 0을 제외한 숫자를 가진 값 출력?
	}

	// nth_element
	{
		// ex 홀수 30개와 나머지로 분리 등
		cout << "40번째 까지와 나머지로 분리" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "nth_element 실행 전" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		nth_element(v.begin(), v.begin() + 40, v.end());

		cout << "앞에서부터 40개" << endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i)
			print("{:8}", *i);
		cout << endl;


		cout << "나머지" << endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i)
			print("{:8}", *i);
		cout << endl;
	}

	// partial sort
	{
		cout << "40번째 까지만 정렬" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "partial sort 실행 전" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		partial_sort(v.begin(), v.begin() + 40, v.end(), greater<int>{});

		cout << "앞에서부터 40개만 정렬" << endl;
		for (auto i = v.begin(); i < v.begin() + 40; ++i)
			print("{:8}", *i);
		cout << endl;


		cout << "나머지" << endl;
		for (auto i = v.begin() + 40; i < v.end(); ++i)
			print("{:8}", *i);
		cout << endl;
	}

	// sort
	{
		cout << "정렬" << endl;
		shuffle(v.begin(), v.end(), dre);
		cout << "sort 실행 전" << endl;
		for (int num : v)
			print("{:8}", num);
		cout << endl;

		cout << endl;
		sort(v.begin(), v.end());

		cout << "정렬 후" << endl;
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
//[문제] stable sort - 자격이 동등한(equivalent)원소의 위치를 바꾸지 않는 정렬
//========================================================================

int main()
{
	vector<Dog> dogs(100);

	cout << "정렬 전 " << endl;
	for (const Dog& dog : dogs)
	{
		cout << dog << endl;
	}

	//// c 오름차순으로 정렬
	//sort(dogs.begin(), dogs.end(), [](const Dog& a, const Dog& b) {
	//	return a.c < b.c;
	//	});

	cout << "Dog::c 기준 오름차순으로 정렬" << endl;
	ranges::sort(dogs, {}, &Dog::c);
	for (const Dog& dog : dogs)
	{
		cout << dog << endl;
	}

	cout << "Dog::n 기준 오름차순으로 정렬" << endl;
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
//[문제] 
// 여러 알고리즘들
// 데이터가 정렬되어있다면, 무조건 이진 탐색 사용
// set 함수들 - include, intersection, union 등
// merge도 정렬이 되어있어야 함
// heap 함수들
// min/max/clamp함수
// permutation 순열 next_permutation 등
// Numeric 알고리즘
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
//[문제] iterator 라이브러리 내부의
// 반복자간의 거리를 재는 distance함수를 구현해본다.
// - 반복자 타입에 따라 다른 연산을 할 수 있다.
// - 적절한 함수를 호출 => function dispatch
// - 함수 호출하는 데에 꼬리표를 달아 구분 => tag dispatch
// ::위 방법 들은 C++ 17이전 방식, 
// C++17이후는 컴파일러가 조건에 맞지 않는 코드를 제거하는 if constexpr을 사용
// ::C++ 20부터는
// - concept을 사용하여 조건을 쉽게 판단할 수 있다.
// 관련 내용은 교과서 참조
//========================================================================


// C++ 17 이후에는 if- constexpr
template<class Iter>
iterator_traits<Iter>::difference_type my_distance(Iter b, Iter e)
{
	// 만일 Iter가 random_access_iterator_tag라면
	// C++ 20의 concept을 이용하면 판별이 쉽다.

						// concept
	if constexpr  (random_access_iterator<Iter>)
	{
		return e - b;
	}
	else
	{
		// 자료형이 뭔지 이해못함
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
//	// 자료형이 뭔지 이해못함
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
//// C++ 17 이전엔는 tag-dispatch
//template<>
//iterator_traits<list<int>::iterator>::difference_type my_distance<list<int>::iterator>(list<int>::iterator b, list<int>::iterator e)
//{
//	// 만일 Iter가 random_access_iterator_tag라면
//	// C++ 20의 concept을 이용하면 판별이 쉽다.
//
//
//
//	// 자료형이 뭔지 이해못함
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

	//cout << "vector의 distance - " << my_distance(v.begin(), v.end()) << endl;
	cout << "list의 distance - " << my_distance(c.end(), c.begin())<< endl;
}
#endif 



