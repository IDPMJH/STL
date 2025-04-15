#define Prac 3
// ★★★시험 == 8주 2일, 4월 24일(30점), 과제 == (30점) - 4월 10일 설명
// 5월 6일(화) -> 6월 19일(예정)
// =================이전 주제=================
// 이동 생성과 이동할당연산자 로딩
// 
// =================이번 주제=================
// STL : 자료형과 무관한 클래스와 함수를 마음대로 작성, 클래스를 통해 자료구조를 제공, 함수를 통해 알고리즘을 제공
// 반복자 디자인 패턴을 통해 시간복잡도를 단축..?(iterator design pattern) - (GOF 디자인 패턴 서적 참고)
// [단어 정리]
// Container : 규격화된(동일한) 원소를 담는 자료구조(Homogeneouse data type)
// Algorithm : 정렬, 탐색, 그래프 알고리즘 
// Adaptor : 기존의 컨테이너 변형 -> 새로운 자료구조를 만들어 낸 것(자료구조나 반복자, 알고리즘에 모두 적용 가능)
// Predicates: Callable Type, bool값을 return하는 Callable Type
// FunctionObject: Function call 오퍼레이터[()]를 오버로딩한 클래스 객체
// Concepts : 추후 소개 template을 만들며서 생기는 문제점을 해결하기 위한 것(C++ 20 제공 핵심 내용)
// Ranges: Concept와 함께 이용하여 라이브러리를 새로 제작함//ranges::sort() 파악해보기
// Span : Contiguous 메모리를 쉽게, 가볍게 다루기 위한 도우미 클래스(views)(String view와 같이 메모리 관찰 가능)
//
// {STL Components
// STL은 컴포넌트(컨테이너[자료구조], 반복자, 알고리즘)의 관계로 구성됨
// 
// [컨테이너(자료구조)]
// 1. Sequence Containers : Contiguous : [array, vector], deque, forward_list, list
// 원하는 위치에 직접 Access해서 read/write 해도 문제 없는 Container
//	- array : 원소 개수가 절대 변동되지 않음 - 원소 제거 불가능
//  - vector : data를 동적으로 늘려갈 수 있는 자료구조
//	- inplace_vector:
//	- hive : 
//  - deque : front/back에서 원소를 추출하기 매우 용이한 구조
// 2. Associative Containers : Key - Value가 assosiation됨 (set, map)
//	키 값을 통해 정렬할 수 있어야 함
//	- set : key 와 value가 동일
//	- map : key 에 따른 value가 있음
// 3. Unordered Associative Containers: Hash table을 통해 순서와 관계 없는 Associative Containers
//	원소를 가장 빨리 찾는 Container임, 메모리를 희생해서 속도를 얻음.
// 
// Container란?
// C++ Container library: 쉽게 구현할 수 있도록 일반적인 템플릿과 알고리즘을 모아놓은 것
//	C++표준 N4917 워킹 드래프트에서의 의미:
// Containers are objects that store other objects.
// "다른 객체를 담을 수 있는 객체", 본인 또한 담을 수 있다는 점이 중요함
// 1. Sequence Containers
//		array<T,N>
//		vector<T>
//
//	
#include "STRING.h"
using namespace std;

#if Prac == 1
#include <iostream>
#include <ranges>	// 최신 버전
#include <algorithm>
#include <array>

// =======================================================================
//[Array<T,N>] C++  reference 참조
// std::array is a container that encapsulates fixed size arrays.
// There is a special case for a zero-length array (N == 0).
//  - In that case, array.begin() == array.end()
// 
// Iterator invalidation(반복자 무효화)
// 정해진 공간을 쓰기 때문에, 반복자가 무효화될 수 없음.(제거 등)
// 
// 여러 멤버 타입이 있음
// begin(), cbegin() - constant
// 
//========================================================================
int main()
{
	/*array<int, 0> a1;
	cout << "is empty? - " << boolalpha << a1.empty() << endl;
	cout << typeid(array<int, 0>::value_type).name();*/

	array<int, 5> a2{ 1,2,3,4,5 };	// int a[5]를 struct로 포장함
	// 왜 포장했는가? 메모리 해킹이 너무 쉽기 때문에
	for (int i = -10; i < 10; ++i)
		cout << a2[i] << endl;	// 가능한 이유는, C++특성상 메모리를 접근할 수 있도록 해놨기 때문

	START:
	cout << "메모리 몇번? ";
	int num;
	cin >> num;

	// STL은 밑의 코드를 쓰지 않는 것을 목표로 한다, 속도 우선.
	try
	{
		cout << a2.at(num);	//★★★★안전 배열로 검색하는 기능★★★★
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
		cout << "다시 입력하십시오" << endl;
		goto START;
	}
}

#elif Prac == 2
#include <iostream>
#include <vector>

// =======================================================================
//[vector<T>] dynamic(run-time) array , 가변 배열
//========================================================================

vector<int>v2(6, 2);
int main()
{
	vector<int>* p = new vector<int>(6, 2);

	vector<int>v(6, 2);
	// v의 정체를 알아보기
	cout << "v의 크기 : " << sizeof(v) << endl;		// int* p, size, capacity = 24bytes, 실제로는 이렇지 않지만, 이렇게 알고 있어도 된다.
	cout << "v의 주소 : " << addressof(v) << endl;
	cout << "v의 타입 : " << typeid(v).name() << endl;
	
	// v2의 정체를 알아보기
	cout << "v2의 크기 : " << sizeof(v2) << endl;
	cout << "v2의 주소 : " << addressof(v2) << endl;
	cout << "v2의 타입 : " << typeid(v2).name() << endl;

	// p ..
	cout << "p의 크기 : " << sizeof(*p) << endl;
	cout << "p의 주소 : " << addressof(*p) << endl;
	cout << "p의 타입 : " << typeid(*p).name() << endl;
	// {} : initiallizer-list
	/*for (int num : {1, 2, 3, 4, 5})
		cout << num << endl;*/


	// 알고리즘은 generic하기 때문에,
	// 자료구조에서 사용하는 일반적인 반복자를 사용하여 access
	// 반복자는 != end(), ++, *등의 오퍼레이터를 지원하기 때문에 generic하게 알고리즘이 사용할 수 있다.
	/*for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << endl;
	}*/
	// 오토를 사용하는 것을 권장함, &를 붙일 필요는 없음, 애초에 메모리가 작음
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << endl;
	}

	// c를 붙여서 읽기모드로 얻어오는 것을 표기하는 것은 권장함
	for (auto i = v.cbegin(); i != v.cend(); ++i)
	{
		cout << *i << endl;
		// *i = 5; error, 읽기만 허용됨
	}

	// r키워드로 반복자 거꾸로 가져오기
	for (auto i = v.crbegin(); i != v.crend(); ++i)
	{
		cout << *i << endl;
	}
}



#elif Prac == 3
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// =======================================================================
//[문제]키보드에서 입력한 정수 값의 합계와 평균을 출력하시오
// - 개수가 지정되어 있지 않음 (vector를 사용)
//========================================================================

int main()
{
	
	cout << "정수를 입력하시오. " << endl;

	// vector에 키보드 입력부터 마지막까지
	vector<int> v(istream_iterator<int>{cin}, {});

	long long sum = accumulate(v.begin(), v.end(), 0LL);
	sum = reduce(v.begin(), v.end(), 0LL);
	cout << "합계 - " << sum;
	//cout << 
	cout << "평균 - " << static_cast<double>(sum / v.size());


}


#elif Prac == 4



// =======================================================================
//[문제]
//========================================================================

int main()
{



}


#elif Prac == 5



// =======================================================================
//[문제]
//========================================================================

int main()
{


}


#endif