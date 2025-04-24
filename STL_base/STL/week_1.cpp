// ---------------------------------------------------------------------
//			2025-1 STL 월910목910 3월 13일 목요일 (2주 1일)
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Generic Programming의 핵심키워드 - template 
// ---------------------------------------------------------------------


// C++ PL
// 1. Procedural P/L
// 2. Object Oriented P/L -> virtual 
// 3. Generic P/L -> template
// 4. Meta P/L
// 5. Functional P/L

#include <iostream>
#include "save.h"

using namespace std;
// [문제] main을 변경하지 않고 의도대로 실행되게 코딩하라.
// Dog를 Class로 코딩하시오.

// 컴파일러의 동작

class Dog {
public:
	Dog() = default;
	explicit Dog(const int _n) :num(_n) {}
	Dog(const Dog& other) :num(other.num) {}
	
	friend ostream& operator << (ostream& out, const Dog& dog) { return out << dog.num; }
	// operator int() { return num; }
	// friend istream& operator >> (istream& in, Dog& dog) { return in >> dog; }

private:
	int num;	// 4 + 4
	double d;	// 8

};
// void change(int& a, int& b);

// Ambiguous
// void change(Dog, Dog);
// void change(Dog& a, Dog& b); // ->함수는 Code segment에 기록., 메모리 시작 번지 == 함수이름(실행 - jmp)

// [질문] 도대체 몇 개의 change를 만들면 되겠니?
// -> C++언어는 도대체 자료형이 몇 개일까? : 몰라
// -> 코드생성을 자동화하자
// -> template

// Stack
// Free Store
// Code
// template-> 소스코드를 생성하는 코드 



// cpp, header 분리 이유 
// template코드는 반드시 cpp공개되어야 함
// cpp코드가 있어야됨

// 템플릿은 선언과 정의를 동시에 해야함.
// 알고리즘
// Generic 프로그래밍 - 자료형에 구애받지않는,
template<class T> - 3순위
void change(T& a, T& b)
{
	T temp{ a };
	a = b;
	b = temp;
}
// 알고리즘함수는 전부 템플릿
// 자료구조도 마찬가지.

// 템플릿 특수화 - 2순위
template<class Dog>
void change(Dog& a, Dog& b)
{

	Dog temp{ a };
	a = b;
	b = temp;
}

// 일반 함수 - 1순위
void change(Dog& a, Dog& b)
{
	Dog temp{ a };
	a = b;
	b = temp;
}

// ------------
int main()
// ------------
{
	{
		Dog a{ 1 }, b{ 2 };
		change(a, b);	// 도대체 어떤 함수를 호출하는 것인가? 

		// 우선순위 탐색
		// 1. 일반 함수 Dog 타입
		// 2. 템플릿 특수화 Dog타입
		// 3. 일반 템플릿
		// // 아래는 좀 더 찾아봐야 할듯
		// 1. change(Dog, Dog);
		// 2. change(Dog& Dog&);
		// 3. 컴파일러인 내가 만들 순 없을까? -> template
		
		std::cout << a << "," << b << std::endl; // [출력] 2, 1
	}

	//{
	//	int a{ 1 }, b{ 2 };
	//	change(a, b);
	//	std::cout << a << "," << b << std::endl; // [출력] 2, 1
	//}

	// name mangling - 함수 이름이 같지만 인자가 다를 때 어떻게 구분하나요? 컴파일러가 따로 이름을 구분함
	//-> change1, change2

	//save("main.cpp");
}

//
//void change(int& a, int& b)
//{
//	int temp{ a };
//	a = b;
//	b = temp;
//	// swap(a, b);
//}
//
//void change(Dog& a, Dog& b)
//{
//	Dog temp{ a };
//	a = b;
//	b = temp;
//}

