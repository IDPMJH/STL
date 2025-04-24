//-----------------------------------------------------------------------------
// 2024 STL 중간시험
// 
// Visual Studio 버전 17.9.0 이상 
// Release / x64
// 프로젝트 속성 - C++ 언어 표준 - 최신 C++ 초안의 기능(/std:c++latest)
//-----------------------------------------------------------------------------
// 답지 작성 방법
// - 각 문제를 해결하는 데 필요한 코드만 적는다.
// - 화면 출력을 요구하는 문제는 출력된 내용을 답지에 적는다.
// - 헤더 파일을 적을 필요는 없다.
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <print>
#include <random>
#include <string>
#include <vector>
using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid{ 1, 111 };
uniform_int_distribution<int> uidNum{ 1, 999 };


//---------------------------------------------------------------------------
// class Bird는 num개의 int값을 free store에 저장한다.
//--------------------------------------------------------------------------- 
// file "새들"에는 몇 개인지 모르는 Bird 객체가 기록되어 있다.
// file은 binary mode로 열어 write 멤버함수를 사용하여 기록하였다.
//---------------------------------------------------------------------------

//-----------
// class Bird
//-----------

class Bird {
private:
	int num{};							// [1, 1000] random 값
	int* p{};							// 문제의 난이도를 낮추려고 raw pointer를 사용하였다

public:
	Bird( ) = default;
	
	Bird( int n ) : num{ n } {			// [문제 1]을 풀지 못한 경우 사용할 생성자
		p = new int[num];
		for (int i = 0; i < num; ++i)
			p[i] = uidNum( dre );
	}

	Bird( const Bird& other ) : num{ other.num } {
		p = new int[num];
		memcpy( p, other.p, sizeof( int ) * num );
	}

	Bird& operator=(const Bird& rhs) {		// 예외발생 가능이기 때문에 noexcept를 사용해야 함
		if (this == &rhs)
			return *this;
		delete[] p;
		num = rhs.num;
		p = new int[num];
		memcpy( p, rhs.p, sizeof( int ) * num );

		return *this;
	}
	
	int getNum( ) const {
		return num;
	}

	int* getData( ) const {
		return p;
	}

	void show( ) const {
		cout << "저장하고 있는 int 개수 - " << num << endl;
		for (int i = 0; i < num; ++i)
			print( "{:8}", p[i]  );
		cout << endl;
	}

	void write( ostream& os ) {
		os.write( (const char*)(this), sizeof( *this ) );
		os.write( (const char*)p, sizeof( int ) * num );
	}

};

//---------
int main( )
//---------
{
	string inFileName{ "새들" };
	ifstream in{ inFileName, ios::binary };

	if (not in) {
		cout << "파일 \"" << inFileName << "\"을 열 수 없습니다" << endl;
		return 0;
	}

	{
		// 실행 확인용 코드
		Bird bird{ 24 };
		bird.show( );

		// 화면 출력(예)
		// 저장하고 있는 int 개수 - 24
		//		814     136     905     835     127     968     913     221     632     308
		//		 98     547     279     189     547     992     957     996     964     967
		//		158     726     970     981
	}

	/*
		* 문제 1
	Bird(int arr, int n) 생성자를 구현하라.*
	
	int 배열 arr과 int n(배열 크기)을 받아, 해당 값을 free store에 복사하여 저장한다.
	
	cpp
	Bird(int* arr, int n) : num{ n } {
	    p = new int[num];
	    std::copy(arr, arr + num, p);
	}
	문제 2
	Bird 객체를 binary 파일에서 읽어오는 함수를 작성하라.
	
	파일 스트림에서 Bird 객체 하나를 읽어오는 함수
	
	반환형: Bird
	
	함수명: readBird
	
	힌트: 객체의 num 값을 먼저 읽고, 그 크기만큼 int 배열을 읽어 동적 할당한다.
	
	cpp
	Bird readBird(std::istream& is) {
	    Bird tmp;
	    is.read(reinterpret_cast<char*>(&tmp), sizeof(Bird));
	    if (!is) return tmp; // 읽기 실패 시 그대로 반환
	
	    tmp.p = new int[tmp.num];
	    is.read(reinterpret_cast<char*>(tmp.p), sizeof(int) * tmp.num);
	    return tmp;
	}
	문제 3
	파일 "새들"에 저장된 모든 Bird 객체의 int 값 합계를 구하여 출력하라.
	
	main 함수에 추가
	
	파일에서 끝까지 Bird 객체를 읽어가며 합산
	
	cpp
	int sum = 0;
	while (true) {
	    Bird b = readBird(in);
	    if (!in) break;
	    sum += std::accumulate(b.getData(), b.getData() + b.getNum(), 0);
	}
	cout << sum << endl;
	문제 4
	Bird 클래스에 move 생성자와 move 대입 연산자를 구현하라.
	
	cpp
	Bird(Bird&& other) noexcept : num{other.num}, p{other.p} {
	    other.num = 0;
	    other.p = nullptr;
	}
	
	Bird& operator=(Bird&& rhs) noexcept {
	    if (this != &rhs) {
	        delete[] p;
	        num = rhs.num;
	        p = rhs.p;
	        rhs.num = 0;
	        rhs.p = nullptr;
	    }
	    return *this;
	}
	문제 5
	Bird 클래스의 소멸자를 구현하라.
	
	cpp
	~Bird() {
	    delete[] p;
	}
		*/



	//--------------------------------------------------------------------------
	// [문제 1] 파일에 있는 Bird 객체를 컨테이너에 저장하라.                  
	// 모두 몇 객체인가를 화면에 출력하라.                          		(40) 
	//--------------------------------------------------------------------------
	// 컨테이너에 저장하기 위한 코드와 관련 코드를 답지에 적는다.
	// class Bird에 read 멤버를 추가하여 문제를 해결할 수 있다.
	// (물론 다른 방식으로 읽을 수도 있다)
	// 화면에 출력된 읽은 객체 수를 답지에 쓴다.
	//--------------------------------------------------------------------------


	/* =========1===========
	//--- class Bird에 read 멤버 함수 추가 ---
	void read(std::istream& is) {
	    is.read(reinterpret_cast<char*>(&num), sizeof(num));
	    delete[] p;
	    p = new int[num];
	    is.read(reinterpret_cast<char*>(p), sizeof(int) * num);
	}
	
	//--- main 함수에 컨테이너에 저장 및 개수 출력 ---
	std::vector<Bird> birds;
	while (in.peek() != EOF) {
	    Bird b;
	    b.read(in);
	    if (!in) break;
	    birds.push_back(std::move(b));
	}
	std::cout << birds.size() << std::endl;   // 화면 출력 예시: 40
	
	*/


	
	// ******************************************************
	// * 파일을 읽지 못한 학생은 아래 주석을 풀자.          *
	// * 답지에 파일을 읽지 못했다고 적고,                  *	
	// * 코드를 실행 한 후 [문제 2]부터 해결해 나가면 된다. *
	// ******************************************************
	
	// [문제 1]을 해결하지 못한 경우 주석을 제거하자
	
	vector<Bird> birds;
	birds.reserve( 1'000 );
	for ( int i = 0; i < 1'000; ++i )
		birds.emplace_back( uid( dre ) );
	


	//--------------------------------------------------------------------------
	// [문제 2] 컨테이너에 있는 Bird 객체 중에서 num 값이 100이하인 객체는 
	// 모두 몇 개인지 화면에 출력하라.										(20)
	//--------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력한 개수를 답지에 적어라.
	//--------------------------------------------------------------------------

	
	// [문제 2] 컨테이너에 있는 Bird 객체 중에서 num 값이 100이하인 객체는 모두 몇 개인지 화면에 출력하라.

	int cnt = std::count_if(birds.begin(), birds.end(),
	    [](const Bird& b) { return b.getNum() <= 100; });
	std::cout << cnt << std::endl;

// (예시 출력) 
// 7

	



	//--------------------------------------------------------------------------
	// [문제 3] 컨테이너에 있는 Bird 객체를 num 기준 오름차순으로 정렬하라.
	// 제일 마지막 객체의 정보를 출력하라.									(10)
	//--------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력한 마지막 객체의 num을 답지에 적어라.
	//--------------------------------------------------------------------------

	/*
	// [문제 3] 컨테이너에 있는 Bird 객체를 num 기준 오름차순으로 정렬하라.
	// 제일 마지막 객체의 정보를 출력하라.
	
	std::sort(birds.begin(), birds.end(),
	    [](const Bird& a, const Bird& b) { return a.getNum() < b.getNum(); });
	
	birds.back().show();
	
	// (예시 출력)
	// 저장하고 있는 int 개수 - 999
	//    ... (999개의 int 값 출력)
	// 마지막 객체의 num: 999

	*/




	//--------------------------------------------------------------------------
	// [문제 4] [문제 3]의 정렬을 더 효율적으로 실행하고 싶다. 
	// 해결방안을 간단하게 적어라.										   (10)	
	//--------------------------------------------------------------------------

	/* =========================1111111=======================
	정렬을 더 효율적으로 실행하려면 C++17 이상에서는 병렬 정렬 정책을 적용할 수 있습니다.
	예를 들어,
	
	cpp
	#include <execution>
	std::sort(std::execution::par, birds.begin(), birds.end(),
    [](const Bird& a, const Bird& b) { return a.getNum() < b.getNum(); });
	*/
	//
	// 
	// ==========================222222=======================
	//	C++20부터 도입된 std::ranges::sort(range::sort)는 반복자 대신 컨테이너 전체를 직접 넘길 수 있어 코드가 더 간결해지고, 실수(예: 잘못된 반복자 범위)도 줄일 수 있습니다.사용법은 다음과 같습니다 :
	//
	//	cpp
	//#include <ranges>
	//#include <algorithm>
	//
	//		// 오름차순 정렬
	//		std::ranges::sort(birds, [](const Bird& a, const Bird& b) { return a.getNum() < b.getNum(); });
	//	반복자를 명시하지 않고 컨테이너만 넘기면 되므로, 코드가 더 읽기 쉽고 안전합니다.
	//
	//		C++20 이상에서 지원되며, 기존 std::sort와 성능 차이는 거의 없습니다.
	//
	//		결론:
	//	range::sort(즉, std::ranges::sort)를 사용하는 것은 최신 C++ 표준에서 권장되는 방식이며, 코드의 가독성과 안전성을 높여줍니다.C++20 이상을 사용한다면 적극적으로 활용할 만한 방법입니다.



	//--------------------------------------------------------------------------
	// [문제 5] class Bird에서 잘못된 부분을 지적하고 해결방법을 적어라.   (10)	
	//--------------------------------------------------------------------------

	/*Rule of Five 미준수 :
	Bird 클래스는 동적 메모리(p)를 직접 관리하면서, 복사 생성자, 복사 대입 연산자만 정의되어 있고, move 생성자, move 대입 연산자, 소멸자 중 일부가 누락되어 있거나 불완전할 수 있습니다.
		Rule of Five를 지키지 않으면, 예기치 않은 메모리 누수, 이중 해제, 잘못된 소유권 문제가 발생할 수 있습니다.

		raw pointer 직접 관리 :
	동적 메모리 해제를 소멸자에서 명확히 하지 않으면 메모리 누수가 발생합니다.
		또한, 예외 안전성 측면에서 문제가 발생할 수 있습니다.*/

	/*
	Bird 클래스는 동적 메모리 관리와 관련된 Rule of Five(복사/이동 생성자, 복사/이동 대입, 소멸자)를 모두 구현해야 하며, 그렇지 않으면 메모리 누수, 이중 해제, 예외 안전성 문제 등이 발생할 수 있습니다.
	스마트 포인터 사용도 좋은 대안입니다.
	*/



	//--------------------------------------------------------------------------
	// [문제 6] 다음 블럭의 코드는 반복자 p를 사용하여 v의 모든 원소를 출력한다.
	// 원소 한개를 추가 후 다시 v의 모든 원소를 출력하면 제대로 출력되지 않는다.
	// 왜 그런지 설명하라.												   (20)
	//--------------------------------------------------------------------------
	// (주의) 이 문제는 앞의 문제들과 관련이 없다.
	// 앞의 문제를 모두 해결한 후 주석을 풀고, 단독으로 실행한 후 답하라.
	//--------------------------------------------------------------------------

	/*
	{ // 블럭 코드 시작
		vector<int> v( 100 );
		iota( v.begin( ), v.end( ), 1 );

		auto p = v.begin( );

		cout << endl;
		cout << "v의 원소를 모두 출력" << endl;

		for (auto i = p; i != v.end( ); ++i)
			print( "{:8}", *i );


		cout << endl;
		cout << "원소를 하나 추가한 후 다시 v를 출력" << endl;

		v.push_back( 101 );

		for (auto i = p; i != v.end( ); ++i)
			print( "{:8}", *i );
	}
	*/




	/*
	* 벡터에 원소를 추가하면서 메모리 재할당이 일어나면, 기존 반복자가 가리키는 주소가 더 이상 벡터의 실제 데이터와 일치하지 않으므로, 반복자가 무효화되어 잘못된 결과가 출력된다.
	이것이 "제대로 출력되지 않는" 근본 원인이다.
	*/
}
