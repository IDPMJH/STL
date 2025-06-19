#define Prac 3

#include "STRING.h"

using namespace std;
extern bool inspect;

// [prac 1] - [prac 2]
// �����̳ʵ��� ã�� �Ƿ� ����
// 1. Sequance				- vector		O(N)
// 2. Associative			- set, map		O(log N)
// 3. Unordered Associative	- unordered_set	O(1)
// 4. ������ vector�� ���� - set�� ������


// [prac 3] - [prac 4]
// �˰���
// C++20�� �ٽ� Ranges library, Concepts library, Constrained Algorithm

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
const int FIND_NUM{ 5 };	// ã�� int

array<int, NUM> a;
array<int, FIND_NUM> fa;

default_random_engine dre;
uniform_int_distribution uid{ 1,10'000'000 };


// =======================================================================
//[����] // int �� 1000���� �߿��� ������ int�� ã�ƺ���.
// �켱 int��1000������ array�� �ִ´�.
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
		cout << "vector - 1000������ int�߿��� ������ int�� ã�ƺ���." << endl;
		vector<int> v(a.begin(), a.end());
		cout << "vector�� ���� ���� - " << v.size() << endl;

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
		cout << "10000�� �߿��� ã�� ���� - " << cnt << endl;
		cout << "ã�µ� �ɸ� �ð� - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}

	// set
	{
		cout << "�����͸� multiset���� �����ϴ� ��...";
		multiset<int> ms(a.begin(), a.end());

		cout << endl;
		cout << "multiset�� ���� ���� - " << ms.size() << endl;

		cout << "multiset - 1000������ int�߿��� ������ int�� ã�ƺ���." << endl;
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
		cout << "10000�� �߿��� ã�� ���� - " << cnt << endl;
		cout << "ã�µ� �ɸ� �ð� - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}


	// unordered_multiset
	{
		cout << "�����͸� unordered_multiset���� �����ϴ� ��...";
		unordered_multiset<int> ums(a.begin(), a.end());

		cout << endl;
		cout << "unordered_multiset�� ���� ���� - " << ums.size() << endl;

		cout << "unordered_multiset - 1000������ int�߿��� ������ int�� ã�ƺ���." << endl;
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
		cout << "10000�� �߿��� ã�� ���� - " << cnt << endl;
		cout << "ã�µ� �ɸ� �ð� - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
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
const int FIND_NUM{ 10'000 };	// ã�� int

array<int, NUM> a;
array<int, FIND_NUM> fa;

default_random_engine dre;
uniform_int_distribution uid{ 1,10'000'000 };


// =======================================================================
//[����] // int �� 1000���� �߿��� ������ int�� ã�ƺ���.
// �켱 int��1000������ array�� �ִ´�.
// - multiset�� unordered_mulitset�� ����� Ȱ���Ͽ� ã�´�.
// ���ʹ� ã������ ���� �ְ� �ƴϴ�?
// ���͸� �����Ͽ� �����ϸ� mulitset�� ������ ������ ������ - flat set
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
	// ������ �����ϰ� ���� ���鵵�� ���� ���� �ۼ��Ѵ�.


	//// vector
	//{
	//	cout << "vector - 1000������ int�߿��� ������ int�� ã�ƺ���." << endl;
	//	vector<int> v(a.begin(), a.end());
	//	cout << "vector�� ���� ���� - " << v.size() << endl;

	//	cout << "ã�� ��...";

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
	//	cout << "10000�� �߿��� ã�� ���� - " << cnt << endl;
	//	cout << "ã�µ� �ɸ� �ð� - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	//}

	cout << endl;
	// multiset
	{
		cout << "�����͸� multiset���� �����ϴ� ��...";
		multiset<int> ms(a.begin(), a.end());

		cout << endl;
		cout << "multiset�� ���� ���� - " << ms.size() << endl;

		cout << "multiset - 1000������ int�߿��� ������ int�� ã�ƺ���." << endl;
		cout << "ã�� ��...";
		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			if (ms.contains(num))
				++cnt;
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << endl;
		cout << "10000�� �߿��� ã�� ���� - " << cnt << endl;
		cout << "ã�µ� �ɸ� �ð� - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}

	cout << endl;
	// unordered_multiset
	{
		cout << "�����͸� unordered_multiset���� �����ϴ� ��...";
		unordered_multiset<int> ums(a.begin(), a.end());

		cout << endl;
		cout << "unordered_multiset�� ���� ���� - " << ums.size() << endl;

		cout << "unordered_multiset - 1000������ int�߿��� ������ int�� ã�ƺ���." << endl;
		cout << "ã�� ��...";
		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			if (ums.contains(num))
				++cnt;
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << endl;
		cout << "10000�� �߿��� ã�� ���� - " << cnt << endl;
		cout << "ã�µ� �ɸ� �ð� - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}

	cout << endl;
	// ������ vector - flat set
	// Ŭ���� �������� ��� �Ϲ� set���� ���� ���� �ִ�.
	// ������ ���� �� �ƴϴ�.
	{
		cout << "������ vector - 1000������ int�߿��� ������ int�� ã�ƺ���." << endl;
		vector<int> v(a.begin(), a.end());
		cout << "�����ϴ� ��...";
		sort(v.begin(), v.end());
		cout << endl;
		cout << "������ vector�� ���� ���� - " << v.size() << endl;

		cout << "ã�� ��...";

		size_t cnt{};
		auto begin = chrono::steady_clock::now();
		for (int& num : fa)
		{
			if (binary_search(v.begin(), v.end(), num))
				++cnt;
		}
		auto duration = chrono::steady_clock::now() - begin;
		cout << endl;
		cout << "10000�� �߿��� ã�� ���� - " << cnt << endl;
		cout << "ã�µ� �ɸ� �ð� - " << chrono::duration_cast<chrono::milliseconds>(duration) << endl;
	}
}

#elif Prac == 3
#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
// =======================================================================
//[����] 
//========================================================================

int main()
{
	vector<string> v{ "1,22,333" };
	// Constrained Algorithm
	ranges::sort(v);

	// Algorithms library
	//Non 
	// - modifying sequence operations
	// - Batch operations,   range-based for ������� ���� �� �� ����
	// 
	//	- Search operations
	// all_of => begin ���� end���� �����ڸ� �����ϴ°�
	// adjacent_find - ������ ���� ���� ã��
	// find�� search�� ���̴�?

	// Fold operation�� �Ѿ
	//
	// Modifying sequence operations
	// Copy operations.....Order-changing operations,Sampling operations





}

#elif Prac == 4
#include <iostream>

// =======================================================================
//[����] 
//========================================================================

int main()
{

}
#endif 



