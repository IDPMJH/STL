// ���� ����												���� 8�� 2�� , 4�� 24��
// smart pointer�� �����Ҵ�, RAII
// �� RAII�� �߿��Ѱ�? - ���� �������� �����ϱ� ����
// RAII - �ڿ�(�޸� ��)�� �����ֱ�� ��ü�� �����ֱ⸦ ��ġ��Ű�� ��(��ü�� �����ֱ⿡ ����ȭ)
// 
// �̹� ����
// generic - �ڷ����� ������	
// Callable type : ȣ�� ������ Ÿ�� - C++���� ()�� �ٿ��� ȣ���� �� �ִ� ��� ���� Callable�̶�� �Ѵ�, C++�� �ٽ�
// 1. �Լ� (������)
// -> �Լ� ���� �Լ��� �ּ�(���۹���) ���� ȣ�� ��� => (*�Լ���)()
// 2. 
// C++ stack-unwinding�� �����ϱ�
// 
// �̶� Dog ��ü�� �޸� ����
// 1. ����
// 2. ������ (�ʱ�ȭ�� ������ ���� + �ʱ�ȭ ���� ���� ������ ����)
// 3. free-store (HEAP) ������ �θ���� ������ ��
// 4. CODE ���� - �ڵ尡 ����Ǵ� ����

// 1,2���� 3���� ���� - �޸� ũ�⸦ ���� ������ �� �ִ°�. 
// 1,2���� ������ Ÿ�ӿ� �����ȴ�. 3���� ��Ÿ�ӿ� �����ȴ�.
// 
// 1���� 2���� ����	  - �޸� ũ�Ⱑ �󸶳� ū��.

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
//[����] ���� int 1000������ �޸𸮿� ��������. 
// => ���ÿ����÷ο� - ��������, 1000���� ���� - array���
// ���� int���� 7�ڸ� [0,1'000'0000) ������ ������ �Ѵ�. == 1'000'0000 �� �������� ����
// "qsort"�� ����Ͽ� ������������ �����϶�
// ������ ����� �տ������� 1000���� ȭ�鿡 ����϶�.
//========================================================================


int sortstandard(const void* a, const void* b)
{
	int p = *const_cast<int*>(reinterpret_cast<const int*>(a));
	int q = *const_cast<int*>(reinterpret_cast<const int*>(b));

	// ��������(Ascending Order)
	//return p - q;

	// ��������(Descending Order)
	return q - p;

	// �ڡڡ�Ư�� ������ ����
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

	// ���� ���� �׻� �� ������, �׷��ٸ� �Լ������ʹ�?
	int (*sortingMethod)(const void*, const void*) = sortstandard;
	std::function<int(const void*, const void*)> f = sortstandard;


	for (int& element : arr)
		element = uid(dre);

	// C����� generic function
	// ����:contiquous container�� ���� - O(1)�� ������ ���� �ð�
	// sizeof(array<int,maxCount>::value_type) - int�� ũ��, ���� ȣ�� ���
	// ���� ���ڴ� ���� �ѹ��� ����ؼ� �ȵȴ�.
	qsort(arr.data(), maxCount, sizeof(array<int, maxCount>::value_type), sortingMethod);
	// ���� ����
	// [](const void* a, const void* b)
	//{
	//	
	//	return *(const_cast<int*>(reinterpret_cast<const int*>(a))) - 
	//		*const_cast<int*>(reinterpret_cast<const int*>(b));
	//	// ������ ������ ����Ѵ�. (���� �Լ��ε� ����)
	//	// ���� �ڸ��� �ٲ�� �ϸ� 1�� return, �׷��� ������ 0�� return
	//	// ���� ���� ���� �� ������ ���̶�� 0�� return
	//	// �׷��ٸ� ���ڷ� ������ ��, a�� b��	�����ΰ�?
	//	// const void* - void*�� �޾Ƶ��̸�, ��� �����͸� �޾Ƶ��� �� �ִ�.
	//	// generic�� qsort�� �� �� ���� ����.
	//	// ���� a�� b�� Ÿ���� �츮�� ��ȯ�ؾ� ��.
	//});

// ���� ����� for loop
//const int printCount = 1000;
//for (int i = 0; i < printCount; ++i)
//{
//	//cout << arr[i] << " ";
//	print("{0:8}", arr[i]);
//}
//===========================================
// range-based for loop, filter - include <ranges> ranges::views::take
// �Ҽ��� ���, �ڿ���  n�� ���, Ư�� ���� �����ÿ��� ��� etc..
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
//[����]���� int 1000������ �޸𸮿� ��������. 
// => ���ÿ����÷ο� - ��������, 1000���� ���� - array���
// ���� int���� 7�ڸ� [0,1'000'0000) ������ ������ �Ѵ�. == 1'000'0000 �� �������� ����
// C++��"sort"�� ����Ͽ� ������������ �����϶�
// ������ ����� �տ������� 1000���� ȭ�鿡 ����϶�.
//=======================================================================

const int maxCount = 1'000'0000;
array<int, maxCount> arr;

default_random_engine dre{ random_device{}() };
uniform_int_distribution<int> uid{ 0, maxCount - 1 };

// C++ ����
inline bool compare(int a, int b)
{
	return a < b;
}

int main()
{
	{
		for (int& element : arr)
			element = uid(dre);

		// ����
		// ���� : Contiguous �޸𸮿��� �Ѵ�.
		// C++20 ���Ŀ��� ����? �� �̿��� contiquous container���� �Ǵ��Ѵ�.
		// �� ���ڸ� ���� ��ü ũ��, ������ ũ��, ���� �ּҸ� �� �� �� �ִ�.
		// �⺻ ���� ���ڰ� �����Ѵ�. ( �������� )
		// default sort : operator< (less operator) ���
		// sort(arr.begin(), arr.end());

		// ���Ŀ� �ɸ��� �ð� ����, �����ġ
		auto start = chrono::high_resolution_clock::now();
		sort<array<int, maxCount>::iterator>(arr.begin(), arr.end(), compare);
		auto end = chrono::high_resolution_clock::now();

		// �⺻�� ����
		cout << "����ð�(duration) - " << end - start << endl;
		cout << "����ð�(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
	}

	// �������� ���� - �ڿ� �������� ������ �� ������?��
	{
		//for (int& element : arr)
		//	element = uid(dre);
		shuffle(arr.begin(), arr.end(), dre);

		// ���Ŀ� �ɸ��� �ð� ����, �����ġ
		auto start = chrono::high_resolution_clock::now();
		sort(arr.begin(), arr.end(), [](const int a, const int b) {return a > b; });
		auto end = chrono::high_resolution_clock::now();

		// �⺻�� ����
		cout << "����ð�(duration) - " << end - start << endl;
		cout << "����ð�(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
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
//[����]
//=======================================================================


int main()
{


}

#elif Prac == 4

#include <iostream>
#include <fstream>
#include <algorithm>

// =======================================================================
//[����] 
// 
//=======================================================================

int main()
{

}

#endif