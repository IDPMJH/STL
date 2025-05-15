#define Prac 3

#include "STRING.h"

// Container <= [Iterator] => Alogrithm
// 반복자를 알아야 컨테이너와 알고리즘의 상호작용을 알 수 있다.
// Sequence  
//	- array		] => span<T> 로 레퍼런싱 가능
//	- vector	]
//	- deque
//	- list
//	- forward_list
//
// 
// Iterator - 반복자
// "Iterators are a generalization of pointers
// that allow a C++ program to work with different data structures
// in a uniform manner."
// 
// "반복자는 포인터를 일반화 해놓은 것이다.
// == 포인터가 할 수 있는 일을 더욱 일반화 해놓은 것
// C++ 프로그램이 서로 다른 자료구조들 사이에서 동작할 수 있도록
// 일관된 방식으로"
// 
// 이터레이터는 대부분의 포인터 문법 구조를 쓸수 있도록 
// 추상화 / 일반화 해놓은 것이다.
// 마치 포인터를 쓰듯이 동작한다.
// 이터레이터 카테고리



using namespace std;
extern bool inspect;

#if Prac == 1

#include <iostream>
#include <string>
// =======================================================================
//[문제] 
//========================================================================

int main()
{
	std::string s{ "2025 5 13" };
	for (const char c : s)
		cout << c;
	cout << endl;

	STRING S{ "2025 5 13 STRING Ver." };
	// Syntactic sugar 
	for (const char c : S)	// 범위(range)가 필요
	{
		cout << c << " ";
	}
	// 위와 아래는 똑같은 의미이다.
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
// 반복자는 포인터를 일반화한 것이다. 
// 모니터를 예시로 설명한다.
// cout == 모니터이다.
//========================================================================

int main()
{
	// 생성할 때 반드시 어떤 스트림을 가리킬 반복자인지 지정이 필요하다.
	// 디폴트 생성자가 삭제되어 있다. 생성자() = delete
	ostream_iterator<char> p{ cout };

	// 실제 포인터와 동일하게 동작한다.
	// 그리고 포인터와 동일하게 동작하는 것처럼 보이도록 적는 것이
	// uniform manner이다.

	*p = 'A';	// p.operator*() = 'A';
	++p;		// p.operator++(); (후위 연산자도 오버로딩 가능하다)
	*p = 'B';
	//++p;
	*p = 'C';
	//++p;
	*p = '\n';

	// 참고로 cout 은 
	// 1. 데이터가 들어올 때마다 커서가 자동으로 전진++을 하지 않아도 된다.
	// 2. 쓰기만 하는 스트림이기 때문에 *를 붙이지 않아도 된다.
	// 그러나 이는 포인터의 기본 동작과 다른 동작이기 때문에
	// 포인터처럼 쓰는 unform manner에 위배된다.

}

#elif Prac == 3
#include <iostream>
#include <span>

// =======================================================================
//[문제] 컨테이너 글자를 거꾸로 출력하시오
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


	
	// span을 이용
	/*span<char> a{ s2 };
	for (auto i = a.rbegin(); i != a.rend(); ++i)
	{
		cout << *i;
	}*/

	// 사용자 정의 rbegin(), rend(), *rebegin(), operator++ 등 구현하기
	// rend()와 rebegin()이 반환하는 객체의 타입을 구성한다. (특수하게)


	// ★ 반복자는 클래스로 코딩한다.
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
//[문제] 반복자는 종류(6 category)가 있다.
// 함수 f는 반복자를 인자로 받아 어떤 종류의 반복자인지 화면에 출력하는 함수이다.
// 다음 코드가 문제 없이 실행되도록 해본다.
//========================================================================


template<class Iterator>
void f(Iterator i)
{
	// 어떤 종류의 반복자인지 출력
	cout << "[" << typeid(i).name() << "의 반복자 category]  " << endl << typeid(Iterator::iterator_category).name() << endl;
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






