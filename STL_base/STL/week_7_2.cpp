#define Prac 5
// ★★★시험 == 8주 2일, 4월 24일(30점) ★시험 장소★: E동320호
// 문제는 4~5문제
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
//	- inplace_vector:  런타임에원소 개수가 결정되는 vector
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
// 1. Sequence Containers
//		array<T,N>
//		vector<T> - dynamic(run - time) array
// 
// [이번 내용]
// 
//
//	

#include "STRING.h"
using namespace std;

#if Prac == 1
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


// =======================================================================
//[문제] 키보드에서 입력한 단어를 오름차순을 정렬한 후 출력하라.
// - > 용량이 컴파일 시간에 결정되지 않기 때문에 dynamic메모리를 활용하여 해결한다.
//========================================================================

int main()
{
	// 고급입력작업을 통해 키보드에서 읽어오는 의미
	vector<std::string> v{ istream_iterator<string>{cin},{} };			// 키보드 입력 시작/끝
	

	// [문제] 이게 왜 정렬되는가?
	// 1. v.begin()으로부터 정보(타입, 시작주소 등)을 얻어옴
	// 2. std::string은 비교연산자 operator<를 기본적으로 지원함 (사전 순)
	// 이에 의해 <를 사용하는 sort함수에 의해 기본 정렬이 가능하게 된다.
	
	sort(v.begin(), v.end());

	for (const std::string& str : v)
	{
		cout << str << endl;
	}

}

#elif Prac == 2
#include <iostream>
#include <vector>


// =======================================================================
// [문제] vector는 어떻게 메모리를 관리하는가?
//========================================================================


int main()
{
	// 웬만하면 STL에서 for루프는 옆에 붙이기
	vector<int> v;
	v.reserve(10);

	for(int i = 0; i < 10; ++i) {

		cout << "--------------------------------" << endl;
		cout << "원소 개수 - " << v.size() << endl;
		cout << "용량	  - " << v.capacity() << endl;
		cout << "메모리	  - " << v.data() << endl;

		// 현재 오브젝트 v 는 스택에 존재
		// v의 안, 멤버에는
		// 1. size		(8byte)				== 0
		// 2. capacity	(8byte)				== 0
		// 3. data		(8byte - pointer)	== nullptr (절대 NULL이 아님)

		//https://en.cppreference.com/w/cpp/container/vector/push_back
		v.push_back(i);
		// push_back시 변화된 size()가 old capacity보다 크다면, 메모리 재할당 실시
		// 이에 의해 모든 이터레이터와(end()포함) 참조는 무효화 됨

		// v의 상태
		// size			0 -> 1
		// capacity		0 -> 1
		// data			free-store의 어딘가를 가리키는 8byte ptr이 할당
		// - *data = 1 (이동 할당 연산자에 의해)

		//cout << "원소를 한 개 추가한 이후 " << endl;
		cout << endl;
	}
}



#elif Prac == 3
#include <iostream>
#include <vector>

// =======================================================================
//[문제]vector의 메모리를 재할당 하는 순간만 출력
//========================================================================

int main()
{
	// visual studio에서는 vector capacity를 50%씩 늘림
	// 보통은 2배씩 늘림
	// 효율적으로는 처음에 많이 늘렸다가, 늘리는 용량을 줄일 수도 있음
	vector<int> v;
	size_t old = v.capacity();
	for (int i = 0; i < 1000000; ++i) {
		if (v.capacity() != old)
		{
			/*cout << "원소 수 - " << v.size() << endl;*/
			cout << "용량	 -" << v.capacity() << endl;
			old = v.capacity();
		}
		v.push_back(i);
	}


}


#elif Prac == 4
#include <vector>
#include <iostream>


// =======================================================================
//[문제]
//========================================================================
bool extern inspect;
int main()
{
	inspect = true;
	vector<STRING> v;
	v.reserve(100);	// 원소 수 예측해서 reserve하는게 지당하다.
	// STACK - v의 내부구조
	// v [0] [0] [nullptr]

	//v.push_back(STRING{ "12345" });
	//v.push_back("12345");	// 이름없는 객체가 생성됨
	// 인자를 넘길 때 컴파일러가 이렇게 판단
	// v.push_back(move(STRING{ "12345" }));
	// v.push_back(static_cast<STRING&&>(STRING{ "12345" }));
	
	//const STRING& s = v.back();
	// 이름없는 STRING 객체 생성 [size:5] [ptr] [id:1] 이후 free-store에 5글자 들어갈 메모리를 만들고 그걸 pointing
	// []에 "1,2,3,4,5" 채움
	// push_back 실시
	// capacity가 맞지 않음, 24바이트 들어갈 새로운 저장공간 생성
	// copy(copy constructor)해서 v의 내부는
	// v가 가리키는 곳은 [size:5] [ptr:"1,2,3,4,5"] [id:2]
	// 이름없는 객체는 xvalue, 이걸 임시객체rvalue로 컴파일이 인식함, copy가 아닌 move construction을 실행
	
	// 메모리가 이사가는 동작이 vector에서 가장 기피되는 동작
	// push_back은 armortized O(1), 무조건 O(1)은 아님
	// vector의 원소수를 예측해서 v.reserve(); 시키자
	// 
	// dynamic 이지만 run-time에 숫자가 결정되는 경우
	// => inplace_vector - 실행시에 크기에 변경점이 일어나지 않을 벡터

	// 집가서 그림그리기
	// stack 주소는 프로그래머가 정할 요소가 아님 컴파일 시 고정되는 객체 - 그래서 이름으로 접근 가능한 것임
	// baseoffset이 정해져있음, code입장에서는 결정되어 있음
	// 
	// 
	// freestore의 경우에는 주소가 정해질 수 없으니까 이름을 정하지 못함 = ptr로 접근
	// freestore에 있는 객체는 항상 접근 가능해야 함 - xvalue가 되어선 안 됨
	// 왜? delete동작을 반드시 해주어야 하기 때문
	// vector보다 deque이 더욱 큰 최대 용량을 가질 수 있는 이유
	// vector는 contiguous 메모리기 때문에 반드시 이어져있어야 함
	// deque는 linkedlist로 관리하기 때문에 메모리가 이어져 있을 필요 x
	// deque : vector와 list의 중간
	// vector처럼 v[i]와 같이 "랜덤 액세스"를 지원하지만, 그 속도는 현저히 느림
	

	
	// [emplace_back]
	// 잘못된 방식 :
	//v.emplace_back(STRING{"12345" }); // STRING{"12345"}도 Stack에 생성됨
	// 
	// 이름없는 객체 : [size:5] [id:1] [ptr] -> "12345"
	// 시스템에 요청하는 작업을 게임에선 사용해선 안 된다.(new 등)
	// -> 시간이 얼마나 걸릴 지 모름, 
	// 따라서 메모리를 여유롭게, inplace vector사용, 혹은 operator new()를 재코딩하여 memory pool을 지정함..?

	// v : [size:0] [1] [ptr] -> 이동생성자에 의해 채워지는 free-store 메모리 :
	//		 [size:5] [id:2] [ptr] -> "12345"
	// 지금까지가 기존의 push_back의 구조

	// emplace_back,
	// 이동생성자로부터 바로 free-store의 메모리에 직접 채움
	// 이름없는 객체 메모리가 스택에 생성돼서  이동생성자가 실행되냐,
	// vector가 가질 메모리가 free-store에 생성돼서 생성자가 실행되냐의 차이?
	// 메모리 위치는 컴파일러가 결정하는 것이다. 이를 조정하는 것이 emplace_back?
	// STRING("12345")에서 넘겨주는 생성자this를 통해 free-store의 장소를 안다
	// 위치에 직접 생성
	
	// emplace_back을 쓸 때는, 객체가 만들어지는 코드를 적어선 안 된다.
	// 재료(인자)만 쓴다.

	cout << "push_back_copy" << endl;
	STRING d = "12345";
	v.push_back(d);

	cout << "push_back_move" << endl;
	v.push_back(std::move(d));	// d는 이동됨, d는 더 이상 사용 불가

	cout << "push_back_move_xvalue" << endl;
	v.push_back("12345");	// d는 이동됨, d는 더 이상 사용 불가

	cout << "emplace_back" << endl;
	v.emplace_back("12345");
	
	cout << "main end" << endl;
	
	
	

	int a = 0;
}


#elif Prac == 5
#include <iostream>
#include <utility>

// =======================================================================
//[문제] perfect forwarding
// 
//lvalue(Left Value)
//이름과 주소를 가진 객체
//
//대입 연산자의 왼쪽에 올 수 있는 표현식
//
//함수 호출 후에도 계속 존재하는 객체*/
//
//
//rvalue(Right Value)
//	임시 객체
//
//	이름 없는 객체
//
//	주소가 없는 객체*/
//========================================================================




void process(int& lval) {
	std::cout << "L-value reference" << std::endl;
}

void process(int&& rval) {
	std::cout << "R-value reference" << std::endl;
}

template<typename T>
void forwarder(T&& arg) {
	// std::forward를 사용하여 arg의 원래 value category 보존
	process(std::forward<T>(arg));
}

int main() {
	int x = 10;
	forwarder(x);    // x는 lvalue, "L-value reference" 출력
	forwarder(10);   // 10은 rvalue, "R-value reference" 출력
	return 0;
}



#endif