#define Prac 1
// 주제
// smart pointer와 동적할당, RAII
// 왜 RAII가 중요한가? - 예외 안전성을 보장하기 위해
// RAII - 자원의 생명주기와 객체의 생명주기를 일치시키는 것
// C++ stack-unwinding을 보장하기
// 
// 이때 Dog 객체는 메모리 영역
// 1. 스택
// 2. 데이터 (초기화된 데이터 영역 + 초기화 되지 않은 데이터 영역)
// 3. free-store (HEAP) 힙으로 부르기는 지양할 것
// 4. CODE 영역 - 코드가 저장되는 영역

// 1,2번과 3번의 차이 - 메모리 크기를 언제 결정할 수 있는가. 
// 1,2번은 컴파일 타임에 결정된다. 3번은 런타임에 결정된다.
// 
// 1번과 2번의 차이	  - 메모리 크기가 얼마나 큰가.


using namespace std;

#if Prac == 1

#include <iostream>
#include <array>
#include <memory>
#include <numeric>


// =======================================================================
//[문제] (int의 최댓값 까지로 제한)양의 정수 num을 입력받는다.
// 1부터 num까지의 정수를 저장할 수 있는 메모리를 확보하고,
// 메모리의 값을 1부터 num까지 채운다.
// 메모리에 저장된 값의 합계를 화면에 출력한다.
// 화면에 출력된 합계는 답안지에도 작성한다.
// 이 문제가 아무런 문제 없이 영원히 반복실행될 수 있게 코딩하라.
//========================================================================

int main()
{
	while (true)
	{
		size_t num;
		cout << "양의 정수를 입력하세요: ";
		cin >> num;

		{
			// 바로 밑에서 채울 텐데, 초기화 할 이유는 딱히 없음.
			// 스마트 ver. shared_ptr<size_t[]> arr;
			size_t* arr2;
			try
			{
				//스마트 ver. arr = make_shared<size_t[]>(num);
				arr2 = new size_t[num];	// free-store의 차이: heap은 void *로 반환한다.
			}
			catch (exception& e)
			{
				cout << e.what() << endl; // bad allocation - delete를 안 할시

				return 20250325;
			}


			// 1부터 채우기
			//스마트 ver. iota(arr.get(), arr.get() + num, 1);
			iota(arr2, arr2 + num, 1);

			long long sum{};

			// 병렬 버전 함수도 찾아보기? -> reduce
			sum = accumulate(arr2, arr2 + num, 0LL); // 3번째 인자로 타입을 결정
			// 직접적인 for 루프를 사용할 때는, 항상 기존 알고리즘을 생각해보자
			//for (size_t i = 0; i < num; i++)
			//{
			//	//arr.get()[i] = i + 1;
			//	 arr2[i] = i + 1;
			//	 //sum += arr.get()[i];
			//	 sum += arr2[i];
			//	
			//}
			cout << "1부터" << num << "까지의  합계: " << sum << endl;
			delete[](arr2);	// 중요
		}
	}

	return 0;

}

#elif Prac == 2

#include <iostream>
#include <numeric>
// =======================================================================
//[문제]
//=======================================================================

void f() // 예외를 발생시키지 않을 경우에 사용 키워드 : noexcept 
{
	shared_ptr<int> sp(new int[10], [](int* p) { delete[] p; });
	int* p = new int[10] {}; // 0으로 초기화

	// 값을 측정하기
	cout << "free-store의 메모리 주소 - " << p << ", ";
	cout << "합계 : " << accumulate(p, p + 10, 0) << endl;

	// 예외
	throw 20250325;

	// 1. 예외로 인한 실행 불가 - 메모리 누수
	delete[] p;


	// 2. 만약 예외가 발생하지 않고, 시간 경과 후... 이중해제 하는 경우 - 즉시 프로그램 사망(댕글링포인터 해제)
	delete[] p;
}

int main()
{
	// 예외를 감싸기 
	// but 예외 체크 코드는 속도에 지장을 주기 때문에 가능하면 사용하지 않음
	try {
		f();
	}
	catch (int& e)
	{
		cout << "예외 발생 : " << e << endl;
		 
	}
}


#elif Prac == 3

#include <iostream>
#include <numeric>
#include <memory>
// =======================================================================
//[문제]
//=======================================================================

class Dog {
public:
	Dog() { cout << "Dog 생성" << endl; }
	~Dog() { cout << "Dog 소멸" << endl; }
};

class mysmartptr {
public:
	mysmartptr(Dog* p) : _p(p) {}
	~mysmartptr() { delete _p; }

private:
	Dog* _p;

};
void f()
{
	// 지역에 만들어진 객체는 지역이 끝날 때 반드시 소멸하기
	// stack unwinding

	//mysmartptr p{ new Dog }; // RAII 초기화

	// RAII를 보장하기
	unique_ptr<Dog[]> up = make_unique<Dog[]>(10);	// 배열 선언 시 ()안에
	shared_ptr<Dog[]> sp = make_shared<Dog[]>(10);	// 배열 크기 삽입

	// RAII 가 아님
	//Dog* p;	
	//p = new Dog;

	throw 1;
	//cout << "절대 출력되지 않음" << endl;
}

int main()
{

	try {
		f();
	}
	catch (int& e)
	{
		cout << "예외 발생 : " << e << endl;

	}
}

#elif Prac == 4

#include <iostream>
#include <fstream>
#include <algorithm>
#include "save.h"

// =======================================================================
//[문제] "main.cpp"의 내용 중에 소문자를 모두 대문자로 바꾸어 
// "main_upper.cpp"로 저장하라.
// 
//=======================================================================

int main()
{
	ifstream in{ "main.cpp" };
	ofstream out{ "main_upper.cpp" };
	in >> noskipws;
	// 기존 방식
	/*char c;

	while (in >> c)
	{
		if (islower(c)) <- 굳이 체크 안해도
		{
			c = toupper(c); <- 여기서 체크함
		}
		out << c;
	}*/

	// STL -> while과 for를 대신하기 위한 라이브러리이자, Generic Programming
	//  이 함수 및 copy() 반드시 살펴볼 것
	transform(istreambuf_iterator<char>{in}, {},
		ostreambuf_iterator<char>{out},
		[](char c) {return toupper(c); });

	//save("main.cpp");

}

#endif