#define Prac 2
#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <ranges>

// =======================================================================
//[문제] ranges - 기존 (C++20 이전)의 [begin, end) 반복자 쌍을 이용한
// 범위를 확장, 확장된 범위의 개념은 다음과 같음
// 1. [begin, end)
// 2. [begin, count)
// 3. [begin, predicate)
// 4. [begin, ....) - 무한
// cppref -  Range 라이브러리
// Range primitives요소는 신경쓸 필요는 아마 없다.
// Range factories - range 생성
//========================================================================

int main()
{
	// range
	/*for (int num : {1, 2, 3, 4, 5})
		cout << num << " ";*/

	// range factory, 조합
	// lazy-evaluation, 지연 평가
	for (int num : views::iota(1)	// 4. 무한 범위
				| views::take(1000)	// 2. 개수를 갖는 범위
				| views::filter([](int n) {return n & 1; })	//3. 조건자를 갖는 범위
				| views::reverse
		)
		cout << num << " ";
}

#elif Prac == 2
#include <iostream>
#include <concepts>

// =======================================================================
// concepts :
// 템플릿 함수의 인자는 자료형(아닌 경우도 있음 - non-type template paramete)인데,
// 이 자료형이 문법적, 의미에서도 작성자가 의도한 것인지를 'compile-time'에
// 판단하기 위한 C++언어의 기능이다.
// 즉, template 자료형에 의미를 부여한다.
// 
// [문제]
// add를 작성하여 main함수가 정상적으로 작동하도록 하라.
//========================================================================


// 기존 템플릿 함수, no concepts
//template<class T>
//T add(T a, T b)
//{
//	return a + b;
//}

// 소스코드 확장, 템플릿으로 함수 제작
//template<>
//STRING add<STRING>(STRING a, STRING b)
//{
//	return a + b; <= 오류
//}

// concepts사용, type traits를 이용한다. 
// is_???형식을 띈다.
// 1. concept 제작
template <class T>
concept Addable = is_integral_v<T> or is_floating_point_v<T>;

// 2. 제작한 concept를 이용하여 템플릿 제작
template <Addable T>
T add(T a, T b)
{
	return a + b;
}





int main()
{
	cout << add<int>(1, 2) << endl;
	cout << add<float>(1.2, 3.4) << endl;

	// [문제] +연산자를 오버로딩하지 않음, compile시 오류가 출력됨
	// => 소스코드 확장, 템플릿을 이용해 함수 제작 시 오류 발생
	// cout << add<STRING>(STRING{"2025"}, STRING{"0617"}) << endl;
	// concept 이용 템플릿 이용시 컴파일 전에도 오류 메시지 출력 (빨간 줄)

}

#elif Prac == 3
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <concepts>
#include <ranges>

// =======================================================================
//[문제] concept를 이해한다.
// 표준 concept는 문법적인 요구사항(빨간줄)을 만족
// 동시에 의미가 가지는 요구사항을 만족할 때 모델링 되었다고 함
//========================================================================

int main()
{
	vector<int> v{ 1,2,3 };
	list<int> c{ 1,2,3 };

	
	sort(v.begin(), v.end());
	// 1. 컨테이너  2. 정렬방식 3. projection
	ranges::sort(v);// {}, );
	

	// 오류가 나지 않음
	sort(c.begin(), c.end());
	// 오류 발생
	// ranges::sort(c);
	
}

#elif Prac == 4
#include <iostream>

// =======================================================================
//[문제] ranges와 concepts를 사용하여 STL의 라이브러리를 재작성한 것이
// constrained algorithm이다.
// 이 알고리즘들은 ranges::algorithm에 들어가 있다.
//========================================================================

int main()
{

}
#endif 



// 정리
// STL은 Container , Iteator, Algorithm으로 구성된다.
// 1. 절차형 프로그래밍 언어
// 2. 객체지향 프로그래밍 언어
// 3. 제네릭 .. 
// 4. 함수형 ..


// ★class 핵심 6가지 구성요소
// 1. 디폴트 생성자
// 2. 소멸자
// 3. 복사 생성자
// 4. 복사 할당 연산자
// 5. 이동 생성자
// 6. 이동 할당 연산자
// => operator - overloading
// 
// 역할 / 책임 / 관계
// -> SOLID
// -> Inheritance , virtual
// 
// STL의 컨테이너를 구현해보았음
// class STRING{
// unique_ptr; => RAII
// };
// 

// ★Container - 찾기 실력에 따른 분류
// 1. Sequence Container				- O(n)
// - array <T,N>
// - vector<T>
// - deque<T>
// - list<T>
// - forward_list<T>
// 2. Associative Container				- O(log n)
// - set<T>, multiset<T>, flatset<T>
// - map<key,value>, mulitmap<key,value>
// 3. Unordered Associative Container	- O(1), 메모리/공간복잡도가 상당함에 주의
// - unorderd_set<T>, unordered_multiset<T>
// - unorderd_map<key,value>, unordered_multimap<key,value>

// STRING과의 연결
// STRING을 T와 Key로 대입
// 2. Associative Container에 들어가기 위해선 less<STRING> 필요
// 3. Unordered Associative Container에 들어가기 위해선 Hash필요


// ★Iterator - Week_11~12
// 6 Category가 존재 - hierarchy
// 1. input_iterator_tag
// 2. output_iterator_tag
// 3. forward_iterator_tag : 1번과 2번 상속, 앞으로 움직임
// 4. bidirectional_iterator_tag : 리스트의 반복자
// 5. random_access_iterator_tag : 최강 성능의 반복자
// 6. contiguouse_iterator_tag : 5번 중에서도 연속적으로 구성된 반복자

// for (char c : STRING a)
// 위를 위해선 반복자를 구성해야한다. (범위)
// class STRING_Iterator{
// iterator_traits; => 반복자의 특성
// using iterator_category = random_access_iterator_tag;
//};
// 
// class STRING_Reverse_Iterator{
// Iterator Adaptor;  => 구조를 변경 (++, *, == 등)
// };

// STRING과의 연결
// begin() -> return STRING_Iterator
// rbegin() -> return STRING_Reverse_Iterator

// ★Algorithm - Range를 인자로 받는다.
// 1. Non-Modifying Sequence - 대부분 O(n)
// 2. Modifying Sequence
// 3. Sort and Related
//
// distance를 구현해봄으로써
// iterator category를 구분
// => concept으로 조건에 맞는 T인지를 compile-time에 validity판정 (C++20)
// if constexpr으로 코드에서 제거
// concept를 사용하여 dispatch한다.
// 
// ranges::algorithm
// ->기존 STL algorithm을 재작성
// concept를 이용해 인자의 validity를 판단
// constrained algorithm으로 부름
// ranges::views와 결합 시 functional programming paradigm