// 이전 주제												시험 8주 2일 , 4월 24일
// smart pointer와 동적할당, RAII
// 왜 RAII가 중요한가? - 예외 안전성을 보장하기 위해
// RAII - 자원(메모리 등)의 생명주기와 객체의 생명주기를 일치시키는 것(객체의 생명주기에 동기화)
// 
// 이번 주제
// generic - 자료형에 무관한	
// Callable type : 호출 가능한 타입 - C++에서 ()를 붙여서 호출할 수 있는 모든 것을 Callable이라고 한다, C++의 핵심
// 1. 함수 (포인터)
// -> 함수 명은 함수의 주소(시작번지) 본래 호출 방식 => (*함수명)()
// 2. 
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

#define Prac 2
using namespace std;

#if Prac == 1

#include <iostream>
#include <array>
#include <random>
#include <print>
#include <ranges>
#include <functional>

// =======================================================================
//[문제] 랜덤 int 1000만개를 메모리에 저장하자. 
// => 스택오버플로우 - 전역으로, 1000만개 지정 - array사용
// 랜덤 int값은 7자리 [0,1'000'0000) 사이의 값으로 한다. == 1'000'0000 은 포함하지 않음
// "qsort"를 사용하여 오름차순으로 정렬하라
// 정렬한 결과를 앞에서부터 1000개만 화면에 출력하라.
//========================================================================


int sortstandard(const void* a, const void* b)
{
	int p = *const_cast<int*>(reinterpret_cast<const int*>(a));
	int q = *const_cast<int*>(reinterpret_cast<const int*>(b));

	// 오름차순(Ascending Order)
	//return p - q;

	// 내림차순(Descending Order)
	return q - p;

	// ★★★특정 조건의 정렬
}

class mystandard
{
public:
	int operator()(const void* a, const void* b)
	{
		int p = *const_cast<int*>(reinterpret_cast<const int*>(a));
		int q = *const_cast<int*>(reinterpret_cast<const int*>(b));

		return p - q;
	}
};

const int maxCount = 1'000'0000;
array<int, maxCount> arr;
default_random_engine dre{ random_device{}() };
uniform_int_distribution<int> uid{ 0, maxCount - 1 };
int main()
{
	mystandard ms;

	// 변수 명은 항상 맨 오른쪽, 그렇다면 함수포인터는?
	int (*sortingMethod)(const void*, const void*) = sortstandard;
	std::function<int(const void*, const void*)> f = sortstandard;


	for (int& element : arr)
		element = uid(dre);

	// C언어의 generic function
	// 조건:contiquous container만 가능 - O(1)의 동일한 접근 시간
	// sizeof(array<int,maxCount>::value_type) - int의 크기, 정식 호출 방법
	// 밑의 인자는 매직 넘버를 사용해선 안된다.
	qsort(arr.data(), maxCount, sizeof(array<int, maxCount>::value_type), sortingMethod);
	// 람다 버전
	// [](const void* a, const void* b)
	//{
	//	
	//	return *(const_cast<int*>(reinterpret_cast<const int*>(a))) - 
	//		*const_cast<int*>(reinterpret_cast<const int*>(b));
	//	// 정렬의 기준을 명시한다. (전역 함수로도 가능)
	//	// 둘의 자리를 바꿔야 하면 1을 return, 그렇지 않으면 0을 return
	//	// 둘이 정렬 기준 상 동일한 값이라면 0을 return
	//	// 그렇다면 인자로 들어오는 둘, a와 b는	무엇인가?
	//	// const void* - void*로 받아들이면, 모든 포인터를 받아들일 수 있다.
	//	// generic인 qsort는 알 수 없기 때문.
	//	// 따라서 a와 b의 타입을 우리가 변환해야 함.
	//});

// 이전 방식의 for loop
//const int printCount = 1000;
//for (int i = 0; i < printCount; ++i)
//{
//	//cout << arr[i] << " ";
//	print("{0:8}", arr[i]);
//}
//===========================================
// range-based for loop, filter - include <ranges> ranges::views::take
// 소수만 출력, 뒤에서  n개 출력, 특정 조건 만족시에만 출력 etc..
// 
	for (int e : arr | views::take(1000)) //| views::take(1))
	{
		print("{0:8}", e);
	}
	cout << endl;


}

#elif Prac == 2
#include <iostream>
#include <print>
#include <array>
#include <algorithm>
#include <random>
#include <ranges>
#include <chrono>
// =======================================================================
//[문제]랜덤 int 1000만개를 메모리에 저장하자. 
// => 스택오버플로우 - 전역으로, 1000만개 지정 - array사용
// 랜덤 int값은 7자리 [0,1'000'0000) 사이의 값으로 한다. == 1'000'0000 은 포함하지 않음
// C++의"sort"를 사용하여 오름차순으로 정렬하라
// 정렬한 결과를 앞에서부터 1000개만 화면에 출력하라.
//=======================================================================

const int maxCount = 1'000'0000;
array<int, maxCount> arr;

default_random_engine dre{ random_device{}() };
uniform_int_distribution<int> uid{ 0, maxCount - 1 };

// C++ 버전
inline bool compare(int a, int b)
{
	return a < b;
}

int main()
{
	{
		for (int& element : arr)
			element = uid(dre);

		// 정렬
		// 전제 : Contiguous 메모리여야 한다.
		// C++20 이후에는 컨셉? 을 이용해 contiquous container인지 판단한다.
		// 두 인자를 통해 전체 크기, 원소의 크기, 시작 주소를 다 알 수 있다.
		// 기본 정렬 인자가 존재한다. ( 오름차순 )
		// default sort : operator< (less operator) 사용
		// sort(arr.begin(), arr.end());

		// 정렬에 걸리는 시간 측정, 스톱워치
		auto start = chrono::high_resolution_clock::now();
		sort<array<int, maxCount>::iterator>(arr.begin(), arr.end(), compare);
		auto end = chrono::high_resolution_clock::now();

		// 기본은 나노
		cout << "경과시간(duration) - " << end - start << endl;
		cout << "경과시간(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
	}

	// 내림차순 버전 - ★왜 내림차순 정렬이 더 빠를까?★
	{
		//for (int& element : arr)
		//	element = uid(dre);
		shuffle(arr.begin(), arr.end(), dre);

		// 정렬에 걸리는 시간 측정, 스톱워치
		auto start = chrono::high_resolution_clock::now();
		sort(arr.begin(), arr.end(), [](const int a, const int b) {return a > b; });
		auto end = chrono::high_resolution_clock::now();

		// 기본은 나노
		cout << "경과시간(duration) - " << end - start << endl;
		cout << "경과시간(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
	}

	//int takeCount = 1000;
	//for (int num : arr | views::take(takeCount))
	//	print("{0:8}", num);
	//cout << endl;

}


#elif Prac == 3

#include <iostream>
#include <numeric>
#include <memory>
// =======================================================================
//[문제]
//=======================================================================


int main()
{


}

#elif Prac == 4

#include <iostream>
#include <fstream>
#include <algorithm>

// =======================================================================
//[문제] 
// 
//=======================================================================

int main()
{

}

#endif