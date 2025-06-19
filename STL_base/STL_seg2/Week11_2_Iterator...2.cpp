#define Prac 7



#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <list>
#include <deque>
#include <forward_list>
#include <vector>
#include <array>
#include <print>
// =======================================================================
//[문제] 반복자는 종류(6 category)가 있다.
// 함수 f는 반복자를 인자로 받아 어떤 종류의 반복자인지 화면에 출력하는 함수이다.
// 다음 코드가 문제 없이 실행되도록 해본다.
//========================================================================

template<class Iterator>
void f(Iterator i)
{
	// 어떤 종류의 반복자인지 출력
	print("[{}] 의 반복자 catergory \n {:20}", typeid(i).name(), typeid(Iterator::iterator_category).name());
	//cout << "[" << typeid(i).name() << "의 반복자 category]  " << endl << typeid(Iterator::iterator_category).name() << endl;
	cout << endl;
}
int main()
{

	// 반복자들의 생성 방식
	f(istream_iterator<char>{cin});
	f(ostream_iterator<char>{cout});

	f(forward_list<int>{}.begin());
	f(list<STRING>::iterator{});

	f(deque<int>::reverse_iterator{});

}

#elif Prac == 2
#include <iostream>

template<class Iterator>
void f(Iterator i)
{




	// 어떤 종류의 반복자인지 출력
	print("[{}] 의 반복자 catergory \n {:20}", typeid(i).name(), typeid(Iterator::iterator_category).name());
	//cout << "[" << typeid(i).name() << "의 반복자 category]  " << endl << typeid(Iterator::iterator_category).name() << endl;
	cout << endl;
}

// =======================================================================
//[문제] f에게 포인터를 넘기면? int*::iterator_category는 존재하지 않는다. => 오류
// "Iterator 는 Pointer를 일반화 한 것이다."
// 
// [포인터 에 대해]
// 포인터를 일반화 했다. 포인터가 반복자의 특수한 경우이다.
// 즉 포인터는 반복자에 포함된다.
// 
// [템플릿을 추론, Concept] - 반복자인지 판단하는 기관(클래스를)만들어서 질의
// std::iterator_traits
// 
// 
// [Metaprogramming]
// 프로그램을 만들어 내는 프로그래밍
// 메타 - 프로그램을 만들 수 있는 기능, 고수준의 기능?
// 
// [Type traits]자료형의 특성
// Type traits define compile-time template-based interfaces to query the properties of types.
// 템플릿 기반으로 만든 기능이 전달된 타입이 어떤 특성을 가지고 있는지 확인하는 것
// => run시간이 아니라 compile 시간에 확인되는 거임
//========================================================================

int main()
{
	int* p{};
	f(p);
	f(1111);
}

#elif Prac == 3
#include <iostream>

// =======================================================================
//[문제] Type_tratis확인하기
//========================================================================



template<class Iterator>
void f(Iterator i)
{
	cout << typeid(iterator_traits<Iterator>::iterator_category).name();
}
int main()
{
	int* a;
	f(a);
}

#elif Prac == 4
#include <iostream>
#include <vector>
#include <deque>

// =======================================================================
//[문제]  
// vector는 진짜 메모리가 contiguous
// deque는  contiguous 가 아니다.
// 그런데, 왜 같은 랜덤액세스?
//========================================================================

template<class Iterator>
void f(Iterator i)
{
	cout << typeid(iterator_traits<Iterator>::iterator_category).name() << endl;;

}

int main()
{
	f(vector<int>{}.begin());

	f(deque<int>{}.begin());
}


#elif Prac == 5
#include <iostream>
#include <vector>
#include <deque>

// =======================================================================
//[문제] C++ standard의 종류
// 1. input
// 2. output
// 3. forward
// 4. bidirectional
// 5. randomaccess
// 
// 근데 randomaccess의 동작방식이 vector와 deque에서 다름
// => 6가지로 나누고자 했으나, 하위 호환성의 고려가 필요함
// 
// 
//========================================================================

template<class Iterator>
void f(Iterator i)
{
	// 옛날 C++ standard의 존재
	cout << typeid(iterator_traits<Iterator>::iterator_category).name() << endl;;

	// ★★vector는 C++20의 concept을 이용하여 contiguous임을 판정할 수 있다.★★
	// list의 경우에는 ::iterator_concept시 오류가 난다. 이때 사용하는게 cexpr
	cout << "벡터의 반복자 - " << typeid(Iterator::iterator_concept).name() << endl;

	// =============벡터의 경우 출력되는 것=============
	// struct std::random_access_iterator_tag - iterator_category
	// 벡터의 반복자 - struct std::contiguous_iterator_tag - iterator_concept
}

template<class 반복자, class 호출가능타입>
void sort(반복자 a, 반복자 e, 호출가능타입 f)
{

}
int main()
{
	f(vector<int>{}.begin());

	//f(deque<int>{}.begin());
}


#elif Prac == 6
#include <iostream>
#include <vector>
#include <concepts>
#include <deque>

// =======================================================================
//[문제] 
//========================================================================


int main()
{
	//contiguous_iterator 콘셉
	cout << boolalpha << contiguous_iterator<vector<int>::iterator> << endl;
	cout << boolalpha << contiguous_iterator<deque<int>::iterator> << endl;
}

#elif Prac == 7
#include <iostream>
#include <vector>
#include <concepts>
#include <deque>
#include <algorithm>

// =======================================================================
//[문제] sort가 문제없이 실행되도록 하라.
//========================================================================




int main()
{
	STRING s{ "2025 5 20" };

	sort(s.begin(), s.end(), greater<>());

	// 람다도 가능
	/*sort(s.begin(), s.end(), [](char a, char b) {
		return a > b;
		});*/

	cout << s << endl;	// "  0122555"

	// 이걸로 Random Access Iterator인지 걸러내지는 못함
	//template< class RandomIt >
	//void sort(RandomIt first, RandomIt last);


	// 대신 ranges::sort사용
	// RandomAcccessIterator가 필요로 하는 조건들은 연산자 오버로딩 등 많은 조건이 있음
	// 이터레이터의 대소비교가 가능
	// => 항상 이전 이터레이터보다 다음 이터레이터의 메모리 주소가 크기 때문?

	char* a{};
	char* b{};
	auto d = a <=> b;
	cout << typeid(d).name();

	
}
#endif 



