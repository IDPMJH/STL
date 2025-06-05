#define Prac 3

#include "STRING.h"


// 1. Map에 대해 탐구한다.


// [Prac 3 부터]
// 2. STL, Unoredred Associative Containers - Hash 구조
// 
// Containers - 시간과 공간 사이의 trade off
// 찾기 실력에 따른 분류를 가진다고 이해해도 된다. N 개의 데이터를 갖는다고 가정한다.
// 1. Sequence				찾기 : O(N)
// - 메모리를 최소로 사용 (N 칸 사용)
// 
// 2. Associative			찾기 : O(log N)
// - 트리를 이용하여 N개 데이터를 담을 때 빨리 찾기위한 포인터들의 공간까지 포함되어 메모리를 차지한다.
// 
// 3. Unordered Associative	찾기 : O(1) 
// - 시간 상의 최고 이점을 가짐
// - 공간을 희생하고 있음
// - hash를 통해 자리 위치를 파악하기 때문에 미리 여러 공간이 필요하다.
// - vector + list
// - 각 원소가 버킷에 들어가 연결되어있음
// - Hash값을 통해 원소의 위치를 파악
// 
// [unordered_set / map<STRING>이 실행되도록 만드는 것이 목표이다.]

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <map>
#include <set>
#include <random>
#include <array>
// =======================================================================
//[문제] uniform 분포는 uniform 한가?
// 전체 데이터를 20개의 구간으로 나누어 개수를 센 후 화면에 출력한다.
//========================================================================

default_random_engine dre;
uniform_int_distribution uid{ 0,1'999'999 };


array<int, 20'000'000> arr;

int main()
{

	for (int& num : arr)
	{
		num = nd(dre);
	}

	map<int, size_t> TermCount;
	for (int num : arr)
		TermCount[num / 100000]++;
	
	/*for (int i = 0; i < arr.size(); ++i)
	{
		TermCount[i / (arr.size() / 20)] += arr[i];
	}*/

	for (const auto& [term, count] : TermCount)
		cout << term + 1 << " - " << count << endl;

}

#elif Prac == 2
#include <iostream>
#include <random>
#include <array>
#include <map>

// =======================================================================
//[문제] normal_distribution을 이용해 노말 분포를 이해한다.
//========================================================================
//random_device rd{};
default_random_engine dre{  };
// 분산과 편차를 인자로 받는다.
normal_distribution nd{ 0.0,0.5 };
array<int, 20'000'000> arr;


int main()
{
	for (int& num : arr)
	{
		double d = nd(dre);
		d *= 200'000;
		d += 1'000'000;
		if ((0 < d) && (d < 2'000'000))	// 전용 함수가 있는데 찾아볼 것
			num = (int)d;
	}

	map<int, size_t> TermCount;
	for (int num : arr)
		TermCount[num / 100000]++;

	/*for (int i = 0; i < arr.size(); ++i)
	{
		TermCount[i / (arr.size() / 20)] += arr[i];
	}*/

	for (const auto& [term, count] : TermCount)
		cout << term + 1 << " - " << count << endl;
}

#elif Prac == 3
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <print>
// =======================================================================
//[문제] 
//========================================================================


// 1.
//template<class T>
//struct std::hash {
//	operator() (const T&) {
//		return 1;
//	}
//};


// 2.
// 템플릿 특수화
//template<>
//struct std::hash<STRING> {
//	size_t operator() (const STRING& s) {
//		std::string str(s.begin(),s.end());
//		return hash<std::string>{}(str);
//	}
//};

// 3.
template<>
struct std::hash<STRING> {
	size_t operator() (const STRING& s) const {
		
		return hash<std::string>{}(string{ s.begin(), s.end() });
	}
};



int main()
{
	// 왜 오류?
	// 1. Hash를 제공하여야 한다.
	// 2. equal_to  : 만들어 놓음 (== 으로

	// 해결 방안
	// 이미 존재하는 hasher에 STRING값을 std::string으로 바꾸어 넣으면 된다.
	unordered_set<STRING,hash<STRING>,equal_to<STRING>> us{ "1","22","333","4444" };

	for (const STRING& s : us)
	{
		cout << s << endl;
	}

	while(true)
	{
		// unordered_set의 메모리를 화면에 출력하자.
		for (size_t bc = 0; bc < us.bucket_count(); ++bc)
		{
			print("[{:>3}]", bc);
			for (auto i = us.begin(bc); i != us.end(bc); ++i)
			{
				print(" -> {:}", std::string{ i->begin(), i->end() });
			}
			cout << endl;
		}

		cout << "추가할 STRING - ";
		STRING s;
		cin >> s;
		us.insert(s);

		// load_balancing
	}
}

#elif Prac == 4
#include <iostream>

// =======================================================================
//[문제] 
//========================================================================

int main()
{

}
#endif 



