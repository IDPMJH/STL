#define Prac 7
// ★★★시험 == 8주 2일, 4월 24일(30점) ★시험 장소★: E동320호
// 문제는 4~5문제, 1시간
// 강의하지 않은 내용을 내지 않음, 모든 자료 허용, 범위는 8주 1일까지
// 
// 과제 == (30점) - 4월 10일 설명
// 5월 6일(화) -> 6월 19일(예정)
// ======================================주제======================================
// STL : 자료형과 무관한 클래스와 함수를 마음대로 작성, 클래스를 통해 자료구조를 제공, 함수를 통해 알고리즘을 제공
// 반복자 디자인 패턴을 통해 시간복잡도를 단축..?(iterator design pattern) - (GOF 디자인 패턴 서적 참고)
// [단어 정리]
// Container : 규격화된(동일한) 원소를 담는 자료구조(Homogeneouse data type)
// Algorithm : 정렬, 탐색, 그래프 알고리즘 
// Adapter : Container adapter는 기존 컨테이너를 변경(modify, adapt)하여 특정 인터페이스(기능)만을 제공하도록 만든 컨테이너를 의미한다
//	컨테이너 어댑터는 vector, list, deque 등 기존 컨테이너(underlying container)의 인터페이스를 제한하여 특정 기능만을 수행하게끔 만들어진 컨테이너 구현체이다.
// Predicates: Callable Type, bool값을 return하는 Callable Type
// FunctionObject: Function call 오퍼레이터[()]를 오버로딩한 클래스 객체
// Concepts : 추후 소개 template을 만들며서 생기는 문제점을 해결하기 위한 것(C++ 20 제공 핵심 내용)
// 어떤 타입이 가져야하는 조건을 정의해 주기 위해 나온 것이 Concept라고 할 수 있다.
// Ranges: Concept와 함께 이용하여 라이브러리를 새로 제작함		
// //https://velog.io/@minsu_lighting--/C20-Range
// Span : contiguous 메모리를 쉽게, 가볍게 다루기 위한 도우미 클래스(views)(String view와 같이 메모리 관찰 가능)
//
// {STL Components}
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
// 	C++표준 N4917 워킹 드래프트에서의 의미:
// Containers are objects that store other objects.
// "다른 객체를 담을 수 있는 객체", 본인 또한 담을 수 있다는 점이 중요함
// 
// C++ Container library: 쉽게 구현할 수 있도록 일반적인 템플릿과 알고리즘을 모아놓은 것
//
// [이전 내용]
// 
// 
// [이번 내용]
// array<T, N>
// vector<T>
// deque<T> - vector보다 더 많은 원소를 담을 수 있다.
//
//	

#include "STRING.h"
using namespace std;
extern bool inspect;
#if Prac == 1
#include <vector>


// =======================================================================
// [문제]
//========================================================================

int main()
{
	// 벡터의 개념
	vector<STRING> v{};
	//v.reserve(1'000);
	// v에 최대 얼마만큼의 원소를 저장할 것인지 예측한다.
	// 그리고 예측한 만큼 공간을 확보한다 -> reserve
	// 24바이트 메모리 v의 안에는
	// size : 0
	// capacity : 1000
	// STRING(24b) 1000개 만큼의 메모리의 주소
	// 1. 원소 수가 늘어날 수 있는 상황에서 사용함
	// 2. capacity는 고정이지만 size가 변동될 수 있는 경우 -> inplace_vector





}

#elif Prac == 2
#include <iostream>
#include <fstream>
#include <array>



// =======================================================================
// [문제]"week_8_1"파일의 소문자 알파벳 빈도(freequency)를 다음과 같이 출력하라.
// ex)
// a -> 10
// b -> 3
// ...
// z -> 0 
// [해결]
// array를 쓴다. (알파벳은 그 수가 정해져 있기 때문)
//========================================================================


int main()
{
	// 항상 {}를 통해 default 초기화를 잊지 말자
	array<int, 26> a{};
	//for (int n : a)
	//	cout << n << " ";
	//cout << endl;

	ifstream in("week_8_1.cpp");

	char c;
	while (in >> c)
	{
		if (islower(c))
		{
			a[c - 'a']++;
		}
	}

	for (int i = 0; i < a.size(); ++i)
		cout << static_cast<char>(i + 'a') << " -> " << a[i] << endl;;
}



#elif Prac == 3
#include <iostream>
#include <vector>
#include <algorithm>

// =======================================================================
//[문제] v에서 3을 제거하라
//========================================================================

int main()
{
	// remove는 new end itrerator를 반환
	// 왜 이렇게 되어 있을까?
	// 알고리즘 자체는 자료구조가 가진 메모리에만 접근 가능하지,
	// 자료구조 자체(멤버 변수) 등에는 접근할 수 없다 
	// - 자료구조 내부 처리 동작이 존재하기 때문(vector의 가변 기능 등)
	// 그래서 new end 반복자만 반환하고 그건 알아서 처리하도록 맡긴다.

	vector<int> v{ 1, 2, 3, 3, 3,4, 5,6,7 };
	// idiom
	v.erase(remove(v.begin(), v.end(), 3), v.end());
	// ==auto new_end =  remove(v.begin(), v.end(), 3)
	// v.erase(new_end, v.end())

	// 위와 같은 방식을 간단하게 하여 vector전용 함수가 존재한다.
	// 근데 이런 건 명시적으로 원칙을 깨는 듯하게 표현된다.
	// erase(v, 3);

	// [문제] v에서 홀수를 제거하라
	// remove에서 조건을 판단(predicate를 사용)하는 경우, remove_if를 사용한다.

	// idiom
	v.erase(remove_if(v.begin(), v.end(), [](int a)
		{
			return a & 1;
		}), v.end());

	// == 
	/*erase_if(v, [](int a)
		{
			return a & 1;
		});*/

	for (int a : v)
	{
		cout << a << " ";
	}
}


#elif Prac == 4
#include <iostream>
#include <vector>


// =======================================================================
//[문제] v에서"3"을 제거하라
//========================================================================

int main()
{
	vector<STRING> v{ "11","22","33","3","44","55" };

	//v.erase(remove(v.begin(), v.end(), "3"));
	erase(v, "3");


	for (const STRING& str : v) {
		cout << str << endl;
	}
	cout << "size : " << v.size() << endl;
}


#elif Prac == 5
#include <iostream>
#include <vector>

extern bool inspect;
// =======================================================================
//[문제] v에서 "2" 와 "4"사이에 "3"을 삽입하라.
//========================================================================

int main()
{

	vector<STRING> v{ "1","2","4","5" };

	inspect = true;
	// 벡터의 insert가 사용되는 순간이 있다면, 그건 잘못된 짜임이다.
	v.insert(v.begin() + 2, "3");
	inspect = false;
	for (const STRING& s : v)
	{
		cout << s << endl;
	}

}

#elif Prac == 6
#include <iostream>
#include <list>

// =======================================================================
//[문제] l에서 "3"을 삽입하라 - list ver / 제거는 따로 공부하기
//========================================================================

int main()
{

	//list<STRING> l{ "1","2","3","4","5" };
	list<STRING> l{ "1","2","4","5" };

	STRING temp{ "333" };

	inspect = true;
	// 벡터의 insert가 사용되는 순간이 있다면, 그건 잘못된 짜임이다.
	//remove(l.begin(), l.end(), "3");
	//l.insert(++ ++l.begin(), "3");	// 임시 객체 생성, 이동 생성자 버전
	//l.insert(++++l.begin(), temp);	// 복사 생성자 버전
	l.emplace(++++l.begin(), "3");		// emplace, 그자리에 바로 생성자 버전
	inspect = false;


	for (const STRING& s : l)
	{
		cout << s << endl;
	}

}

#elif Prac == 7
#include <iostream>
#include <deque>

// =======================================================================
//[문제] 
//========================================================================

int main()
{
	inspect = true;
	deque<STRING> d{ "1","22","333","4444", "55555" };
	inspect = false;

	
	inspect = true;
	d.emplace_front("0");
	inspect = false;
	
	d.push_front("-1");
	// 덱의 크기
	//cout << "VS에서 x64기기일 때 deque의 크기 - " << sizeof(d) << endl;

	//for (int i = 0; i < d.size(); ++i)
	//{
	//	// [] random_access가 가능하다.
	//	cout << &d[i] << endl;
	//}

	
	for (const STRING& s : d)
	{
		cout << &s << endl;
	}
	

}



#endif