#define Prac 4

// STL Container
// 1. Sequence Containers
// array<T, N>
// vector<T>	- push_back() O(1) 복잡도
// list<T>		- node, 기반 임의 위치에서 삽입과 삭제 O(1)
// deque<T>		- push_front() / push_back() O(1) , vector보다 더 많은 원소를 담을 수 있다.

#include "STRING.h"

using namespace std;
extern bool inspect;

#if Prac == 1

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <ranges>
#include <deque>

// =======================================================================
// 컨테이너가 담을 수 있는 용량을 비교한다.
//========================================================================

class Test {
	char x[1'000'000];
};
int main()
{
	// vector<Test> v; 가 만약 아래 로컬 스코프가 아니라 여기 있다면?
	{
		//vector<Test> v;	// 최대 원소 수 - 27310
		//
		//// try-catch 사용법
		//try {
		//	while (true) {
		//		v.emplace_back();
		//	}
		//}
		//catch (...) {
		//	cout << "최대 원소 수 - " << v.size() << endl;
		//}

	}

	//{
	//	deque<Test> d;		// 최대 원소 수 - 57361

	//	// try-catch 사용법
	//	try {
	//		while (true) {
	//			d.emplace_back();
	//		}
	//	}
	//	catch (...) {
	//		cout << "최대 원소 수 - " << d.size() << endl;
	//	}

	//}

	// list는 Test를 몇 개 담을 수 있을까?? - 중요
	{
		list<Test> l;		// 최대 원소 수 - 57029

		// try-catch 사용법
		try {
			while (true) {
				l.emplace_back();
			}
		}
		catch (...) {
			cout << "최대 원소 수 - " << l.size() << endl;
		}

	}

}

#elif Prac == 2
#include <iostream>
#include <list>
#include <string.h>
#include <ranges>
// =======================================================================
//[문제] container의 모든 원소를 출력하라
// => container 의 두번째 원소부터 끝까지를 출력하라
//========================================================================

int main()
{
	list<int> cont{ 1,2,3,4,5,6,7,8,9,10 };

	for (int num : cont)
	{
		cout << num << " ";
	}
	cout << endl;

	auto beg = cont.begin();
	beg.operator++();	// 의 운용 원리는 list에서 처리한다.

	// cont가 vector,array,deque,string였다면 가능
	//for (int i = 1; i < cont.size(); ++i)
	//	cout << cont[i] << " ";


	// 해결 방안 - 반복자 패턴
	// list<int>::iterator begin = cont.begin();	// 이 상황에서 auto를 사용한다.

	// i < end()가 아니라 != end()임을 명심하자, 주소를 비교하게 되므로 대소 비교가 불가능하다.
	// cont.begin() == l-value임을 명심하자.
	for (auto i = ++cont.begin(); i != cont.end(); ++i) {
		cout << *i << " ";
	}


	//for (int num : views::drop(cont, 1))
	//{
	//	cout << num << " ";
	//}
	cout << endl;


}

#elif Prac == 3
#include <iostream>
#include <list>
#include <unordered_set>
#include <ranges>

// =======================================================================
//[문제] container의 원소를 "거꾸로" 출력하시오
// container는 set, unordered_set,vector등이 되어도 알고리즘의 반복자를 사용하여 출력하는 방법이 바뀌지 않는다.
//========================================================================

int main()
{
	//list<int> cont{ 1,3,5,7,9,2,4,6,8,10 };

	unordered_set<int> cont{ 1,3,5,7,9,2,4,6,8,10 };

	/*for (auto i = cont.begin(); i != cont.end(); ++i)
	{
		cout << *i << " ";
	}*/

	// rbegin() == end()자리임 근데 왜 출력이 되냐? ★★★★★
	// https://en.cppreference.com/w/cpp/iterator/reverse_iterator 
	// rebegin().operator*를 사용할 때는, 옆의 마지막 원소를 출력하여주기 때문이다.
	/*for (auto i = cont.rbegin(); i != cont.rend(); ++i)
	{
		cout << *i << " ";
	}*/

	for (int a : ranges::reverse_view(cont))
	{
		cout << a << " ";

	}
	cout << endl;

}

#elif Prac == 4
#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>

// =======================================================================
//[문제] "main.cpp"의 단어를 list에 저장하자.
// 찾을 단어를 물어봐서, 없으면 없다, 있으면 list의 몇번째 단어인지 출력하자.
//========================================================================

int main()
{
	ifstream in{ "Template.cpp" };
	if (not in)
		return 20250501;

	// 오퍼레이터를 만들었기 때문에 (>>) 가능한 초기화
	// {파일 시작 이터레이터} 부터, 파일 끝{}까지
	list<STRING> cont{ istream_iterator<STRING>{in}, {} };

	while (true) {
		cout << "찾으실 단어는?";
		STRING str;
		cin >> str;
		// 리스트만의 특별한 방법으로 찾아줄 방법이 있는가? 없으면 표준 알고리즘 사용
		// cont.find()가 있는가? 없으면 전역 알고리즘 사용
		// cont.sort()는 지원하기 때문에 이런 유형을 주의,  표준 정렬 알고리즘보다 성능이 좋음
		auto i = find(cont.begin(), cont.end(), str);
		if (i != cont.end())
			cout << "찾았습니다." << endl;
		else
			cout << str << " - 없는 단어 입니다." << endl;
	}
	
	

	

}
#endif 



