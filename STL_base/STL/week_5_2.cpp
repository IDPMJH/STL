#define Prac 2
// ★★★시험 == 8주 2일, 4월 24일(30점), 과제 == (30점) - 4월 10일 설명

// 이전 주제	
// generic - 자료형에 무관한	
// Callable type : 호출 가능한 타입 - C++에서 ()를 붙여서 호출할 수 있는 모든 것을 Callable이라고 한다, C++의 핵심
// 모든 것을 대표하는 ★★★funchtion★★★ (include <functional>)
// 1. 함수
// -> 함수 명은 함수의 주소(시작번지), 본래 호출 방식 => (*함수명)() == (*save)()
// 2. 함수를 받아온 함수 포인터
// 3. 람다(이름없는 함수), 실체가 있어야 한다.(VS - class로 코딩)
// 4. 함수객체(FunctionObject) - "함수호출연산자(operator())를 오버로딩한 클래스 객체"
// 5. 멤버함수
// C++ stack-unwinding을 보장하기
// 
// 이번 주제
// STRING - std::string가 유사한 클래스, STL 표준 컨테이너가 되도록...
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

#include <string>
#include <string_view>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
using namespace std;


class STRING {
	// 접근 제한자 (Access Modifier)
public:
	// []를 -> *로 collapsing 
	STRING(const char* str)
		:_len{ strlen(str) }
	{		
		_p.reset();		// lvalue : 등식의 왼쪽 값 -> location value (메모리)
		_p = make_unique<char[]>(_len);

		memcpy(_p.get(), str, _len);		// DMA (Direct / Dynamic Memory Accesse)
		// p.get() : 확보한 메모리 주소
		// p.reset() : 메모리 리셋
		// p.release() : 메모리 반환
	}

	size_t size() {
		return _len;
	}



private:
	size_t _len{};
	unique_ptr<char[]> _p;		// 생성은 이미 여기서 진행 됨
	//vector<char> _string;




	friend ostream& operator<<(ostream& os, const STRING& str) {
		// null캐릭터를 마지막에 넣지 않는 경우에는 for문을 사용..
		for (int i = 0; i < str._len; ++i)
			os << str._p[i];
		return os;
	}
	// 다양한 방법
	/*friend std::ostream& operator<<(std::ostream& os, const STRING& str) {
		for (char ch : std::string_view(str._p.get(), str._len))
			os << ch;
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const STRING& str) {
		std::copy(str._p.get(), str._p.get() + str._len, std::ostream_iterator<char>(os));
		return os;
	}
	friend std::ostream& operator<<(std::ostream& os, const STRING& str) {
		os << std::string(str._p.get(), str._len);
		return os;
	}*/
};

#if Prac == 1
#include <iostream>

class Star {
public:
	Star() { _child = nullptr; }
	~Star() {}
public:
	Star* _child;
};

int main()
{
	Star a;
	a._child = new Star();
}

#elif Prac == 2



// =======================================================================
//[문제] 아래 코딩이 정상적으로 실행되도록 수정
//========================================================================

int main()
{
	STRING s{ "std::string과 유사한 클래스" };

	cout << s.size() << endl; // s가 확보한 자원의 바이트 수

	cout << s << endl;
}


#elif Prac == 3



// =======================================================================
//[문제]
//========================================================================

int main()
{


}


#elif Prac == 4



// ========================================= ==============================
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