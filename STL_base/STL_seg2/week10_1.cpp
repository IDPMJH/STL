#define Prac 6

#include "STRING.h"
using namespace std;
extern bool inspect;

// 알고리즘 라이브러리에 대해 학습한다.
// 대부분의 알고리즘은 동작을 정의하기 때문에 동사로 한다. (대부분)
// 알고리즘에서 가장 중요한 것은 복잡도
// 1. Non-modifying sequence operations - find 등


// 06.19 (목) - 15주 2일 - 기말 시험
// STL Container
// 1. Sequence Containers
// array<T, N>
// vector<T>	- push_back() O(1) 복잡도
// list<T>		- node기반, 임의 위치에서 삽입과 삭제 O(1)
// deque<T>		- push_front() / push_back() O(1) , vector보다 더 많은 원소를 담을 수 있다.

// list만의 대표 동작 - sort(), unique(), merge(), splice();

// ★★
// forward_list<T>
// std::forward_list is a container 
// that supports fast insertion and removal of elements 
// from anywhere in the container.

// It is intended thar forward_list have zero space or time overhead
// 공간적으로, 시간적으로 손해보는 일이 없다.
// relative to a hand-written C-style singly linked list.
// 직접 손으로 짠 C Style의 간략한 단일 리스트 코드보다, (최적의 코드이다.)
// Features thar would confilic with that goal have been omitted
// 이 주장과 충돌이 나는 기능은 들어있지 않기 때문이다.


// C++ 20 에서 바뀐 알고리즘, Constrained algorithms
// https://en.cppreference.com/w/cpp/algorithm/ranges 
// 오류 발생시 도움이 되는 메시지 출력, 컴파일러 효율 증대

// 함수를 더욱 정교하게 - C++ 26 contract
// https://en.cppreference.com/w/cpp/contract 
#if Prac == 1

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
// =======================================================================
//[문제] 
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;

	// 오퍼레이터(>>)를 만들었기 때문에 가능한 초기화
	// {파일 시작 이터레이터} 부터, 파일 끝{}까지
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	while (true) {
		cout << "찾으실 단어는?";
		STRING str;
		cin >> str;
		// 리스트만의 특별한 방법으로 찾아줄 방법이 있는가? 없으면 표준 알고리즘 사용
		// cont.find()가 있는가? 없으면 전역 알고리즘 사용
		// cont.sort()는 지원하기 때문에 이런 유형을 주의, 표준 정렬 알고리즘보다 성능이 좋음
		auto pi = find(cont.begin(), cont.end(), str);
		// 찾은 위치를 전달, 못찾으면 end 이터레이터 반환
		if (pi != cont.end())
			cout << "찾았습니다. 위치: " << distance(cont.begin(), pi) + 1 << endl;
		else
			cout << str << " - 없는 단어 입니다." << endl;
	}
}

#elif Prac == 2
#include <iostream>
#include <algorithm>
#include <fstream>
#include <list>
#include <ranges>

// =======================================================================
//[문제] 단어 길이가 5인 단어만 화면에 출력하라
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	// for 문 해답
	// for loop 보단 STL을 사용하는 것을 권장함,
	// 특히 loop안에 함수 호출이 있다면 STL을 사용하는 걸 고려
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
//[문제] copy알고리즘을 사용하여 원하는 데이터를 목적지에 복사 가능
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	// 고급 출력 코드
	// 가능하려면 출력 오퍼레이터 (>>)가 코딩 되어있어야 함
	// 그러나 공백문자가 없음
	//copy(cont.begin(), cont.end(), ostream_iterator<STRING>{cout});

	// 딜리미터 지정
	// copy(cont.begin(), cont.end(), ostream_iterator<STRING>{cout, "\n"});

	// 조건 지정
	copy_if(cont.begin(), cont.end(), ostream_iterator<STRING>{cout, "\n"},
		[](const STRING& str) {
			return 5 == str.size();	// 항상 조건식에서 상수를 왼쪽에, 컴파일 단계에서 오류 발생시키기 위함
		});
}

#elif Prac == 4
#include <iostream>
#include <list>
#include <algorithm>
#include <string>

// =======================================================================
//[문제] sort(), unique() - 인접한 요소 유니크하게, merge(), splice();
//========================================================================

int main()
{ 
	//inspect = true;
	list<STRING> list1{ "1","55555","333" };
	list<STRING> list2{ "4444", "22" };
	//inspect = false;
	// O(1)시간에 합쳐짐
	// 이때 인자형식은 &&, rvalue 레퍼런스로, 인자로 들어간 밸류는 rvalue가 됨

	// merge할 때에는, 반드시 정렬 후 merge한다.
	// 하지 않으면 debug 모드에서 에러 발생
	inspect = true;
	list1.sort();	// less 연산자(<)가 코딩 되어 있어야 한다.
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
//[문제] forward_list의 특성 알아보기
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
//[문제] 컨테이너 정리
//========================================================================

// std::function<T> == 모든 callable타입(함수 포인터, 람다, 함수 객체)
// 을 대표하는 callable 타입
// 그렇다면 contiguous메모리 컨테이너를 대표하는 타입 => "span"
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


	// 거꾸로 출력하라
	f<int>(a);
}
#endif 



