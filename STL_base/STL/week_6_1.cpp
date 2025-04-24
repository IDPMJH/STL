#define Prac 3
// ★★★시험 == 8주 2일, 4월 24일(30점), 과제 == (30점) - 4월 10일 설명

// =================이전 주제=================
// STRING - std::string가 유사한 클래스, STL 표준 컨테이너가 되도록..
// C++ 언어
// 1. OOPL(Objected Oriented Programming Language)	: 특정 자료형만을 위한 Coding
// 2. Generic PL (Programming Language)				: 자료형과 무관한 자료구조와 알고리즘의 Coding (Template)
// 
// 별을 Modeling 하고자 한다.
// -> 
// Class Star {
// private:
// [메모리 요청소]
// };
// 이를 토대로 Compiler는 아래를 해석 가능함 (내가 만들지 않아도) (복사 생성자 등을)
// Star a; 
// Star aa[100];
// new Star[];
// Star b = a;
// 메모리를 만드는 동작은 Compiler의 주관, 만들 때 어떻게 만들 것인가는 생성자에서 코딩한다.
// Star() {}	소멸자도 special한 함수이기 때문에 기본 소멸자가 생성된다.
// 
// 하지만 Star에서 위성(메모리,Resource-자원)을 가지는 경우,
// 생성자에서 분명히 Star() {new ~~} 를 했을 것이다..
// Star = a
// Star b = a 를 하는 경우 대입 연산자 오버로딩이 필요하다. 이후 할당 연산자도 세트로 오버로딩한다.
// 
// =================이번 주제=================
// STRING - std::string가 유사한 클래스, STL 표준 컨테이너가 되도록..
//	내부 동작을 관찰할 수 있게 하자.
// 
//

using namespace std;
extern bool inspect;
#if Prac == 1
#include <iostream>
#include "STRING.h"



// =======================================================================
//[문제] 아래 코딩이 정상적으로 실행되도록 수정
//========================================================================

int main()
{
	STRING s{ "std::string과 유사한 클래스" };

	cout << s.size() << endl;
	cout << s << endl;

	// 이건 안 되는게 당연함 - 생성자를 우리가 만들었기에, default 생성자를 따로 만들어야 함.
	STRING t;

	//special한 동작이라 자동 생성되어야 함. 근데 왜 안 될까?
	//못 만들어주는 이유? - unique_ptr의 기본 대입 연산자가 삭제되어 있기 때문,
	t = s;

	// 마찬가지로, 삭제되어 있기 때문
	STRING u = s;

	cout << t << endl;
	cout << s << endl;
	cout << u << endl;
}
#elif Prac == 2

#include "STRING.h"
#include <iostream>

STRING s{ "이제 준비가 끝났다" };
// 관찰하려면 true로 설정

// =======================================================================
//[문제] 아래 코딩이 정상적으로 실행되도록 수정
//========================================================================

int main()
{
	inspect = true;
	cout << "메인 시작" << endl;
	// 복사 생성자
	STRING t = s;

	cout << "이제 소멸할게~ " << endl;
}


#elif Prac == 3
#include "STRING.h"
#include <iostream>
#include <array>
#include <algorithm>




// =======================================================================
//[문제]
//========================================================================

int main()
{
	array<STRING, 5> arr{ "1", "333", "22" , "55555", "4444" };

	// 길이 오름차순 정렬하고 출력하라
	inspect = true;

	sort(arr.begin(), arr.end(), [](const STRING& a, const STRING& b) {return a.size() < b.size(); });

	inspect = false;

	for (const STRING& str : arr)
	{
		cout << str << endl;
	}

	//inspect = true;
	for (const auto& str : arr)
	{
		cout << str << endl;
	}
	//inspect = false;

}


#elif Prac == 4

#include <iostream>

// =======================================================================
//[문제] 다음시간 STRING도 이렇게 동작하게 하자.
//========================================================================

int main()
{
	string s{ "표준 string" };
	string t = move(s);

	cout << s << endl;
	cout << t << endl;


}


#elif Prac == 5



// =======================================================================
//[문제]
//========================================================================

int main()
{


}


#endif