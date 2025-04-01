#define Prac 8
// 이전 주제												시험 == 8주 2일 , 4월 24일(30점),				과제 == (30점) - 4월 10일 설명
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
// 
// 
using namespace std;

#if Prac == 1
#include <iostream>

void save()
{

}


int main()
{
	int n{};
	typeid(int);

	int* saveaddr = (int*)save;
	cout << "save함수가 저장된 메모리 번지: " << saveaddr << endl;

	// 람다는 도대체 무엇인가? -> typeid 활용 
	// class `int __cdecl main(void)'::`2'::<lambda_1> : main안에서 만들어진 클래스
	// '컴파일러'(VisualStudio)의 자동화 => class lambda 생성, lambda형 객체 생성을 위해서
	// 
	[]() {
		cout << "안녕 난 이름이 없어 ~" << endl;
		}();
}

#elif Prac == 2
#include <iostream>
#include <fstream>
#include <algorithm>



// =======================================================================
//[확인] 함수 객체를 통해 람다의 작동방식 확인하기
//=======================================================================

int main()
{

	// 함수 객체
	class Dog
	{
	public:
		// 함수 호출 연산자 FunctionCallOperator
		void operator()()
		{
			cout << "함수 객체 입니다." << endl;
		}
	};
	Dog dog;
	dog();
	cout << typeid(dog).name() << endl; // class `int __cdecl main(void)'::`2'::Dog -> 메인 함수에서 클래스를 생성한 경우, 람다의 방식과 동일하다.
	//dog.operator()();

}
#elif Prac == 3
#include <iostream>
#include <array>
#include <algorithm>


// =======================================================================
//[문제] 다음 코드가 의도대로 실행될 수 있게 필요한 코딩을 추가하라.
//=======================================================================

int main()
{
	array<int, 10> a{ 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	class Dog {
	public:
		bool operator()(int a, int b) const	// 함수 내용에서 인자들에 변경사항이 없을 때는 확실히 const를 붙인다.
		{
			return a > b;
		}
	};
	sort(a.begin(), a.end(), Dog{}); // Dog{} == predicate : 조건자, {}이니셜라이저 기호를 쓰는 이유 - ()를 쓰면 operator()인지 생성인지 애매하기 때문
	for (int num : a)
		cout << num << " ";
	cout << endl;	// 10 9 8 ... 3 2 1
}
#elif Prac == 4
#include <iostream>
#include <array>
#include <algorithm>

// =======================================================================
//[문제] 만약 Prac == 3에서와 달리, Predicate에 Dog만 있다면?
// 람다를 통해 Dog을 제작할 수 있다.
//=======================================================================

int main()
{
	array<int, 10> a{ 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

	// 컴파일러가 생성하는 코드
	//class 람다 {
	//public:
	//	bool operator()(int a, int b) { return a > b; }
	//};
	// 실제 코드
	auto Dog = [](int a, int b) {
		return a > b;	// 반환 형식은 추론을 통해 bool로 결정
		};

	sort(a.begin(), a.end(), Dog); // Dog == predicate : 조건자

	//sort(a.begin(), a.end(), Dog)
	//{
	//	? ? ? (3, 4); // 이 동작 방식이 성립((3,4)를 Callabe할 수 있으면)한다면 상관없는 sort함수
	//};


	for (int num : a)
		cout << num << " ";
	cout << endl;	// 10 9 8 ... 3 2 1
}

#elif Prac == 5
#include <iostream>
#include <algorithm>

// =======================================================================
//[문제] 
//=======================================================================

int main()
{
	// 함수는 인자 하나만 달라도 타입이 달라지기 때문에 호환될 수 없다. a = b 등
	void b();
	//void b( int );
	void (*a)();
	// b의 타입과 a의 타입 일치
	a = b;
}

#elif Prac == 6
#include <iostream>
#include <array>
#include <functional>
#include <algorithm>

// =======================================================================
//[문제] 
//=======================================================================

int main()
{
	int num;
	int a[10];
	array<int, 10> a_new;

	void(*aFunc) ();
	function<int> a_newFunc;	// generic
}

#elif Prac == 7
#include <iostream>
#include <array>
#include <functional>
#include <algorithm>

// =======================================================================
//[문제] 
//=======================================================================

int main()
{
	auto ptr = [](int a, int b) {return a > b; };
	// true - false 출력시 boolalpha
	cout << boolalpha << ptr(3, 4) << endl;


	// funchtion 활용 - 자료형은 왼편에, 이름은 오른편에 적는 것의 표준
	function<bool(int, int)> ptr2 = ptr;

}


#elif Prac == 8
#include <iostream>
#include <string>
#include <random>
#include <array>
#include <print>
#include <fstream>
#include <algorithm>
#include <ranges>

// =======================================================================
//[설명] Dog 10만마리를 다음과 같이 파일 "Dog 십만마리"에 저장하였다.
// 파일은 다음 코드로 열었다. 
// ofstream out("Dog 십만마리");
//
// Dog 객체는 class Dog의 friend함수인 operator<<를 사용하여 저장하였다.
// 
// [문제] 이 파일에는 정학하게 10만개의 Dog 객체가 저장되어 있다.
// 파일에 저장된 Dog객체를 모두 읽어 메모리에 저장하라.
// 제일 마지막 객체의 정보를 화면에 출력하고 답지에도 출력 내용을 적어라.
// 모두 몇 개의 객체가 저장되어 있는지 출력하라.
// 메모리에 저장된 Dog 객체를 멤버 name 길이 기준 오름차순으로 정렬하라.
// 정렬된 Dog 객체를 앞에서부터 1000개를 화면에 출력하라.
//========================================================================

default_random_engine dre;
uniform_int_distribution<int> uidName{ 'a', 'z' };
uniform_int_distribution uidNameLen{ 3,30 };
uniform_int_distribution uidId{  };


class Dog {

public:
	Dog() {
		int len = uidNameLen(dre);
		for (int i = 0; i < len; ++i)
		{
			_name += uidName(dre);
		}
		_id = uidId(dre);
	}

	void show() const {
		println("{:12} - {}", _id, _name);
	}

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		return os << dog._id << " " << dog._name << " ";
	}

	friend istream& operator>>(istream& is, Dog& dog) {
		return is >> dog._id >> dog._name;
	}

	int GetNameLength()
	{
		return _name.length();
	}

private:
	string	_name;
	int		_id;
};

array<Dog, 100'000> arr;

int main()
{
	/*ofstream out("Dog 십만마리");
	for (int i = 0; i < 100'000; ++i)
	{
		Dog dog;
		out << dog;
	}*/

	ifstream in("Dog 십만마리",ios::binary);
	if (not in)
		exit(2);
	
	for (Dog& dog : arr)
	{
		in >> dog;
	}

	cout << arr.back() << endl;

	sort(arr.begin(), arr.end(), [](Dog& a, Dog& b) { return a.GetNameLength() < b.GetNameLength(); });

	for (const Dog& dog : arr | views::take(1000))
		dog.show();


	cout << endl;

}





#endif