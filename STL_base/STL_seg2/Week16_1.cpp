#define Prac 2
#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <ranges>

// =======================================================================
//[����] ranges - ���� (C++20 ����)�� [begin, end) �ݺ��� ���� �̿���
// ������ Ȯ��, Ȯ��� ������ ������ ������ ����
// 1. [begin, end)
// 2. [begin, count)
// 3. [begin, predicate)
// 4. [begin, ....) - ����
// cppref -  Range ���̺귯��
// Range primitives��Ҵ� �Ű澵 �ʿ�� �Ƹ� ����.
// Range factories - range ����
//========================================================================

int main()
{
	// range
	/*for (int num : {1, 2, 3, 4, 5})
		cout << num << " ";*/

	// range factory, ����
	// lazy-evaluation, ���� ��
	for (int num : views::iota(1)	// 4. ���� ����
				| views::take(1000)	// 2. ������ ���� ����
				| views::filter([](int n) {return n & 1; })	//3. �����ڸ� ���� ����
				| views::reverse
		)
		cout << num << " ";
}

#elif Prac == 2
#include <iostream>
#include <concepts>

// =======================================================================
// concepts :
// ���ø� �Լ��� ���ڴ� �ڷ���(�ƴ� ��쵵 ���� - non-type template paramete)�ε�,
// �� �ڷ����� ������, �ǹ̿����� �ۼ��ڰ� �ǵ��� �������� 'compile-time'��
// �Ǵ��ϱ� ���� C++����� ����̴�.
// ��, template �ڷ����� �ǹ̸� �ο��Ѵ�.
// 
// [����]
// add�� �ۼ��Ͽ� main�Լ��� ���������� �۵��ϵ��� �϶�.
//========================================================================


// ���� ���ø� �Լ�, no concepts
//template<class T>
//T add(T a, T b)
//{
//	return a + b;
//}

// �ҽ��ڵ� Ȯ��, ���ø����� �Լ� ����
//template<>
//STRING add<STRING>(STRING a, STRING b)
//{
//	return a + b; <= ����
//}

// concepts���, type traits�� �̿��Ѵ�. 
// is_???������ ���.
// 1. concept ����
template <class T>
concept Addable = is_integral_v<T> or is_floating_point_v<T>;

// 2. ������ concept�� �̿��Ͽ� ���ø� ����
template <Addable T>
T add(T a, T b)
{
	return a + b;
}





int main()
{
	cout << add<int>(1, 2) << endl;
	cout << add<float>(1.2, 3.4) << endl;

	// [����] +�����ڸ� �����ε����� ����, compile�� ������ ��µ�
	// => �ҽ��ڵ� Ȯ��, ���ø��� �̿��� �Լ� ���� �� ���� �߻�
	// cout << add<STRING>(STRING{"2025"}, STRING{"0617"}) << endl;
	// concept �̿� ���ø� �̿�� ������ ������ ���� �޽��� ��� (���� ��)

}

#elif Prac == 3
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <concepts>
#include <ranges>

// =======================================================================
//[����] concept�� �����Ѵ�.
// ǥ�� concept�� �������� �䱸����(������)�� ����
// ���ÿ� �ǹ̰� ������ �䱸������ ������ �� �𵨸� �Ǿ��ٰ� ��
//========================================================================

int main()
{
	vector<int> v{ 1,2,3 };
	list<int> c{ 1,2,3 };

	
	sort(v.begin(), v.end());
	// 1. �����̳�  2. ���Ĺ�� 3. projection
	ranges::sort(v);// {}, );
	

	// ������ ���� ����
	sort(c.begin(), c.end());
	// ���� �߻�
	// ranges::sort(c);
	
}

#elif Prac == 4
#include <iostream>

// =======================================================================
//[����] ranges�� concepts�� ����Ͽ� STL�� ���̺귯���� ���ۼ��� ����
// constrained algorithm�̴�.
// �� �˰������ ranges::algorithm�� �� �ִ�.
//========================================================================

int main()
{

}
#endif 



// ����
// STL�� Container , Iteator, Algorithm���� �����ȴ�.
// 1. ������ ���α׷��� ���
// 2. ��ü���� ���α׷��� ���
// 3. ���׸� .. 
// 4. �Լ��� ..


// ��class �ٽ� 6���� �������
// 1. ����Ʈ ������
// 2. �Ҹ���
// 3. ���� ������
// 4. ���� �Ҵ� ������
// 5. �̵� ������
// 6. �̵� �Ҵ� ������
// => operator - overloading
// 
// ���� / å�� / ����
// -> SOLID
// -> Inheritance , virtual
// 
// STL�� �����̳ʸ� �����غ�����
// class STRING{
// unique_ptr; => RAII
// };
// 

// ��Container - ã�� �Ƿ¿� ���� �з�
// 1. Sequence Container				- O(n)
// - array <T,N>
// - vector<T>
// - deque<T>
// - list<T>
// - forward_list<T>
// 2. Associative Container				- O(log n)
// - set<T>, multiset<T>, flatset<T>
// - map<key,value>, mulitmap<key,value>
// 3. Unordered Associative Container	- O(1), �޸�/�������⵵�� ����Կ� ����
// - unorderd_set<T>, unordered_multiset<T>
// - unorderd_map<key,value>, unordered_multimap<key,value>

// STRING���� ����
// STRING�� T�� Key�� ����
// 2. Associative Container�� ���� ���ؼ� less<STRING> �ʿ�
// 3. Unordered Associative Container�� ���� ���ؼ� Hash�ʿ�


// ��Iterator - Week_11~12
// 6 Category�� ���� - hierarchy
// 1. input_iterator_tag
// 2. output_iterator_tag
// 3. forward_iterator_tag : 1���� 2�� ���, ������ ������
// 4. bidirectional_iterator_tag : ����Ʈ�� �ݺ���
// 5. random_access_iterator_tag : �ְ� ������ �ݺ���
// 6. contiguouse_iterator_tag : 5�� �߿����� ���������� ������ �ݺ���

// for (char c : STRING a)
// ���� ���ؼ� �ݺ��ڸ� �����ؾ��Ѵ�. (����)
// class STRING_Iterator{
// iterator_traits; => �ݺ����� Ư��
// using iterator_category = random_access_iterator_tag;
//};
// 
// class STRING_Reverse_Iterator{
// Iterator Adaptor;  => ������ ���� (++, *, == ��)
// };

// STRING���� ����
// begin() -> return STRING_Iterator
// rbegin() -> return STRING_Reverse_Iterator

// ��Algorithm - Range�� ���ڷ� �޴´�.
// 1. Non-Modifying Sequence - ��κ� O(n)
// 2. Modifying Sequence
// 3. Sort and Related
//
// distance�� �����غ����ν�
// iterator category�� ����
// => concept���� ���ǿ� �´� T������ compile-time�� validity���� (C++20)
// if constexpr���� �ڵ忡�� ����
// concept�� ����Ͽ� dispatch�Ѵ�.
// 
// ranges::algorithm
// ->���� STL algorithm�� ���ۼ�
// concept�� �̿��� ������ validity�� �Ǵ�
// constrained algorithm���� �θ�
// ranges::views�� ���� �� functional programming paradigm