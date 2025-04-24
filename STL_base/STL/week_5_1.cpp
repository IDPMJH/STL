#define Prac 8
// 이전 주제			★★★시험 == 8주 2일 , 4월 24일(30점),	과제 == (30점) - 4월 10일 설명
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
	// 본래 호출 방식
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
		bool operator()(int a, int b) const	// 함수 내용에서 인자들에 변경사항이 없을 때는 확실히 const를 붙인다.☆☆☆☆
		{
			return a > b;
		}
	};
	sort(a.begin(), a.end(), Dog{}); // Dog{} == predicate : 조건자, {}이니셜라이저 기호를 쓰는 이유 - ()를 쓰면 operator()인지 생성인지 애매하기 때문 - 생성자를 받을 수 있는 이유? Callable Type을 인자로 받음 - 함수 객체, 함수 포인터 등등
	for (int num : a)
		cout << num << " ";
	cout << endl;	// 10 9 8 ... 3 2 1
}
#elif Prac == 4
#include <iostream>
#include <array>
#include <algorithm>

// =======================================================================
//[문제] 만약 Prac == 3에서와 달리, Callable Type - Predicate에 Dog만 있다면?
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
	// 실제 코드 - auto에 커서 대보기
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
	void (*a)();	// 함수 포인터 생성
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
#include <chrono>



// ★★★종합적 예제★★★
// =======================================================================
//[설명] Dog 10만마리를 다음과 같이 파일 "Dog 십만마리"에 저장하였다.
// 파일은 다음 코드로 열었다. 
// ofstream out("Dog 십만마리");
//
// Dog 객체는 class Dog의 friend함수인 operator<<를 사용하여 저장하였다.
// 
// [문제] 파일에"Dog 십만마리"에는 정확하게 10만개의 Dog 객체가 저장되어 있다.
// 파일에 저장된 Dog객체를 모두 읽어 메모리에 저장하라.		==> 저장할 객체의 '수'가 정해져 있음 = Array에 저장
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
		println("[{:12}] - {}", _id, _name);
	}

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		return os << dog._id << " " << dog._name << " ";
	}

	friend istream& operator>>(istream& is, Dog& dog) {
		return is >> dog._id >> dog._name;
	}

	size_t GetNameLength() const // 함수에 const붙이는 거 항상 생각하기
	{
		// == name.size(), length가 조금 더 자연스러움
		return _name.length();
	}

	bool operator<(const Dog& other) const // 함수에 const붙이는 거 항상 생각하라고
	{
		return GetNameLength() < other.GetNameLength();
	}
private:
	string	_name;
	int		_id;
};

array<Dog, 100'000> arr;

int main()
{
	// 저장한 방식과 동일한 방식으로 연다.
	/*ofstream out("Dog 십만마리");
	for (int i = 0; i < 100'000; ++i)
	{
		Dog dog;
		out << dog;
	}*/

	ifstream in("Dog 십만마리", ios::binary);

	// 반드시 체크할 것
	if (not in)
	{
		cout << "Dog 십만마리 - 파일을 열 수 없습니다." << endl;
		return 20250403;
	}

	// 이러한 방식이 가능하다. (좋은 건 아님)
	/*int num{};
	string name;
	int count{};
	while (in >> num >> name)
	{
		println("[{:7}] - {:12}{:}", ++count, num, name);
	}*/

	// 정상적인 코딩
	for (Dog& dog : arr)
	{
		in >> dog;
	}

	// 클래스의 Getter는 최대한 쉽게 코딩하지말자 - 캡슐화와 어긋남
	// -> Setter을 만드는 경우가 필요한 경우, 클래스를 다시 설계하는 편이 낫다
	// cout << "제일 마지막 객체의 정보 : "<< arr.back() << endl;
	arr.back().show();

	// 정렬의 경우 sort를 쓴다.
	cout << "Dog name 길이 기준 오름차순 (ascending oredr) 정렬합니다." << endl;
	//ranges::sort(arr); https://velog.io/@minsu_lighting--/C20-Range
	auto start = chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const Dog& a, const Dog& b) { return a.GetNameLength() < b.GetNameLength(); });
	auto end = chrono::high_resolution_clock::now();

	cout << "경과시간(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

	// ★★★sort에 대해
	// int data에 대해 람다로 오름차순 함수를 작성하지 않아도 되는 이유?
	// 이미 int는 < 연산자가 있기 때문에 람다 등을 작성하지 않아도 default로 ascendingorder로 정렬
	// [하지만] 사용자 정의 자료형(class 등)은 < 연산자가 없기 때문에 default 정렬되지 않음
	// 따라서 함수 객체를 설정해주어도 되지만, < 연산자를 구성(오버로딩)해도 됨.
	// 이에 따라 < 연산자를 오버로딩 하면, 아래같은 default sort도 가능하다

	// 이미 정렬되어 있기에 시간 측정에 주의할 것
	auto start2 = chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end());
	auto end2 = chrono::high_resolution_clock::now();
	cout << "경과시간(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end2 - start2).count() << "ms" << endl;

	// range-based for 문에서 const와 &는 항상 생각하기, 
	// auto는 필요한 경우가 아닌 이상 명시적인 타입 활용하기
	for (const Dog& dog : arr | views::take(1000)) // ranges::views::take(1000) - 원본
		dog.show();

	// [확인]===========filter의 강력함을 알아보자============
	//for (const Dog& dog : arr | views::reverse) // 역순 출력
	//	dog.show();

	cout << endl;

}





#endif