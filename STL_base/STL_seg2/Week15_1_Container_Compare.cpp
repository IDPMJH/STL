#define Prac 3

#include "STRING.h"

using namespace std;
extern bool inspect;

// [prac 1] - [prac 2]
// 컨테이너들의 찾기 실력 검증
// 1. Sequance				- vector		O(N)
// 2. Associative			- set, map		O(log N)
// 3. Unordered Associative	- unordered_set	O(1)
// 4. 정렬한 vector의 성능 - set과 유사함


// [prac 3] - [prac 4]
// 알고리즘
// C++20의 핵심 Ranges library, Concepts library, Constrained Algorithm

#if  Prac == 1
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <chrono>

const int NUM{ 10'000'000 };
const int FIND_NUM{ 5 };	// 찾을 int

array<int, NUM> a;
array<int, FIND_NUM> fa;

default_random_engine dre;
uniform_int_distribution uid{ 1,10'000'000 };


// =======================================================================
//[문제] // int 값 1000만개 중에서 만개의 int를 찾아본다.
// 우선 int값1000만개는 array에 넣는다.
//========================================================================

int main()
{
	for (int& num : a)
	{
		num = uid(dre);
	}
	for (int& num : fa)
	{
		num = uid(dre);
	}

	// vector
	{
		cout << "vector - 1000만개의 int중에서 만개의 int를 찾아본다." << endl;
		vector<int> v(a.begin(), a.end());
		cout << "vector의 원소 개수 - " << v.size() << endl;

		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			auto p = find(v.begin(), v.end(), num);
			if (p != v.end())
			{
				++cnt;
			}
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << "10000개 중에서 찾은 개수 - " << cnt << endl;
		cout << "찾는데 걸린 시간 - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}

	// set
	{
		cout << "데이터를 multiset으로 구성하는 중...";
		multiset<int> ms(a.begin(), a.end());

		cout << endl;
		cout << "multiset의 원소 개수 - " << ms.size() << endl;

		cout << "multiset - 1000만개의 int중에서 만개의 int를 찾아본다." << endl;
		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			auto p = find(ms.begin(), ms.end(), num);
			if (p != ms.end())
			{
				++cnt;
			}
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << "10000개 중에서 찾은 개수 - " << cnt << endl;
		cout << "찾는데 걸린 시간 - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}


	// unordered_multiset
	{
		cout << "데이터를 unordered_multiset으로 구성하는 중...";
		unordered_multiset<int> ums(a.begin(), a.end());

		cout << endl;
		cout << "unordered_multiset의 원소 개수 - " << ums.size() << endl;

		cout << "unordered_multiset - 1000만개의 int중에서 만개의 int를 찾아본다." << endl;
		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			auto p = find(ums.begin(), ums.end(), num);
			if (p != ums.end())
			{
				++cnt;
			}
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << "10000개 중에서 찾은 개수 - " << cnt << endl;
		cout << "찾는데 걸린 시간 - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}


}

#elif Prac == 2
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <chrono>

const int NUM{ 10'000'000 };
const int FIND_NUM{ 10'000 };	// 찾을 int

array<int, NUM> a;
array<int, FIND_NUM> fa;

default_random_engine dre;
uniform_int_distribution uid{ 1,10'000'000 };


// =======================================================================
//[문제] // int 값 1000만개 중에서 만개의 int를 찾아본다.
// 우선 int값1000만개는 array에 넣는다.
// - multiset과 unordered_mulitset의 기능을 활용하여 찾는다.
// 벡터는 찾으려고 만든 애가 아니다?
// 벡터를 정렬하여 유지하면 mulitset과 유사한 성능을 가진다 - flat set
//========================================================================


int main()
{
	for (int& num : a)
	{
		num = uid(dre);
	}
	for (int& num : fa)
	{
		num = uid(dre);
	}
	// 스택을 정리하고 새로 만들도록 각각 블럭에 작성한다.


	//// vector
	//{
	//	cout << "vector - 1000만개의 int중에서 만개의 int를 찾아본다." << endl;
	//	vector<int> v(a.begin(), a.end());
	//	cout << "vector의 원소 개수 - " << v.size() << endl;

	//	cout << "찾는 중...";

	//	size_t cnt{};
	//	auto begin = chrono::steady_clock::now();
	//	for (int& num : fa)
	//	{
	//		auto p = find(v.begin(), v.end(), num);
	//		if (p != v.end())
	//		{
	//			++cnt;
	//		}
	//	}
	//	auto duration = chrono::steady_clock::now() - begin;
	//	cout << endl;
	//	cout << "10000개 중에서 찾은 개수 - " << cnt << endl;
	//	cout << "찾는데 걸린 시간 - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	//}

	cout << endl;
	// multiset
	{
		cout << "데이터를 multiset으로 구성하는 중...";
		multiset<int> ms(a.begin(), a.end());

		cout << endl;
		cout << "multiset의 원소 개수 - " << ms.size() << endl;

		cout << "multiset - 1000만개의 int중에서 만개의 int를 찾아본다." << endl;
		cout << "찾는 중...";
		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			if (ms.contains(num))
				++cnt;
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << endl;
		cout << "10000개 중에서 찾은 개수 - " << cnt << endl;
		cout << "찾는데 걸린 시간 - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}

	cout << endl;
	// unordered_multiset
	{
		cout << "데이터를 unordered_multiset으로 구성하는 중...";
		unordered_multiset<int> ums(a.begin(), a.end());

		cout << endl;
		cout << "unordered_multiset의 원소 개수 - " << ums.size() << endl;

		cout << "unordered_multiset - 1000만개의 int중에서 만개의 int를 찾아본다." << endl;
		cout << "찾는 중...";
		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			if (ums.contains(num))
				++cnt;
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << endl;
		cout << "10000개 중에서 찾은 개수 - " << cnt << endl;
		cout << "찾는데 걸린 시간 - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}

	cout << endl;
	// 정렬한 vector - flat set
	// 클래스 데이터의 경우 일반 set보다 빠를 수도 있다.
	// 무조건 빠른 건 아니다.
	{
		cout << "정렬한 vector - 1000만개의 int중에서 만개의 int를 찾아본다." << endl;
		vector<int> v(a.begin(), a.end());
		cout << "정렬하는 중...";
		sort(v.begin(), v.end());
		cout << endl;
		cout << "정렬한 vector의 원소 개수 - " << v.size() << endl;

		cout << "찾는 중...";

		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			if (binary_search(v.begin(), v.end(), num))
				++cnt;
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << endl;
		cout << "10000개 중에서 찾은 개수 - " << cnt << endl;
		cout << "찾는데 걸린 시간 - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}
}

#elif Prac == 3
#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
// =======================================================================
//[문제] 
//========================================================================

int main()
{
	vector<string> v{ "1,22,333" };
	// Constrained Algorithm
	ranges::sort(v);

	// Algorithms library
	//Non 
	// - modifying sequence operations
	// - Batch operations,   range-based for 사용으로 인해 잘 안 쓰임
	// 
	//	- Search operations
	// all_of => begin 부터 end까지 조건자를 만족하는가
	// adjacent_find - 인접한 같은 원소 찾기
	// find와 search의 차이는?

	// Fold operation은 넘어감
	//
	// Modifying sequence operations
	// Copy operations.....Order-changing operations,Sampling operations





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



