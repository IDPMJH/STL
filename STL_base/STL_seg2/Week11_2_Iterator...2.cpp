#define Prac 7



#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <list>
#include <deque>
#include <forward_list>
#include <vector>
#include <array>
#include <print>
// =======================================================================
//[����] �ݺ��ڴ� ����(6 category)�� �ִ�.
// �Լ� f�� �ݺ��ڸ� ���ڷ� �޾� � ������ �ݺ������� ȭ�鿡 ����ϴ� �Լ��̴�.
// ���� �ڵ尡 ���� ���� ����ǵ��� �غ���.
//========================================================================

template<class Iterator>
void f(Iterator i)
{
	// � ������ �ݺ������� ���
	print("[{}] �� �ݺ��� catergory \n {:20}", typeid(i).name(), typeid(Iterator::iterator_category).name());
	//cout << "[" << typeid(i).name() << "�� �ݺ��� category]  " << endl << typeid(Iterator::iterator_category).name() << endl;
	cout << endl;
}
int main()
{

	// �ݺ��ڵ��� ���� ���
	f(istream_iterator<char>{cin});
	f(ostream_iterator<char>{cout});

	f(forward_list<int>{}.begin());
	f(list<STRING>::iterator{});

	f(deque<int>::reverse_iterator{});

}

#elif Prac == 2
#include <iostream>

template<class Iterator>
void f(Iterator i)
{




	// � ������ �ݺ������� ���
	print("[{}] �� �ݺ��� catergory \n {:20}", typeid(i).name(), typeid(Iterator::iterator_category).name());
	//cout << "[" << typeid(i).name() << "�� �ݺ��� category]  " << endl << typeid(Iterator::iterator_category).name() << endl;
	cout << endl;
}

// =======================================================================
//[����] f���� �����͸� �ѱ��? int*::iterator_category�� �������� �ʴ´�. => ����
// "Iterator �� Pointer�� �Ϲ�ȭ �� ���̴�."
// 
// [������ �� ����]
// �����͸� �Ϲ�ȭ �ߴ�. �����Ͱ� �ݺ����� Ư���� ����̴�.
// �� �����ʹ� �ݺ��ڿ� ���Եȴ�.
// 
// [���ø��� �߷�, Concept] - �ݺ������� �Ǵ��ϴ� ���(Ŭ������)���� ����
// std::iterator_traits
// 
// 
// [Metaprogramming]
// ���α׷��� ����� ���� ���α׷���
// ��Ÿ - ���α׷��� ���� �� �ִ� ���, ������� ���?
// 
// [Type traits]�ڷ����� Ư��
// Type traits define compile-time template-based interfaces to query the properties of types.
// ���ø� ������� ���� ����� ���޵� Ÿ���� � Ư���� ������ �ִ��� Ȯ���ϴ� ��
// => run�ð��� �ƴ϶� compile �ð��� Ȯ�εǴ� ����
//========================================================================

int main()
{
	int* p{};
	f(p);
	f(1111);
}

#elif Prac == 3
#include <iostream>

// =======================================================================
//[����] Type_tratisȮ���ϱ�
//========================================================================



template<class Iterator>
void f(Iterator i)
{
	cout << typeid(iterator_traits<Iterator>::iterator_category).name();
}
int main()
{
	int* a;
	f(a);
}

#elif Prac == 4
#include <iostream>
#include <vector>
#include <deque>

// =======================================================================
//[����]  
// vector�� ��¥ �޸𸮰� contiguous
// deque��  contiguous �� �ƴϴ�.
// �׷���, �� ���� �����׼���?
//========================================================================

template<class Iterator>
void f(Iterator i)
{
	cout << typeid(iterator_traits<Iterator>::iterator_category).name() << endl;;

}

int main()
{
	f(vector<int>{}.begin());

	f(deque<int>{}.begin());
}


#elif Prac == 5
#include <iostream>
#include <vector>
#include <deque>

// =======================================================================
//[����] C++ standard�� ����
// 1. input
// 2. output
// 3. forward
// 4. bidirectional
// 5. randomaccess
// 
// �ٵ� randomaccess�� ���۹���� vector�� deque���� �ٸ�
// => 6������ �������� ������, ���� ȣȯ���� ����� �ʿ���
// 
// 
//========================================================================

template<class Iterator>
void f(Iterator i)
{
	// ���� C++ standard�� ����
	cout << typeid(iterator_traits<Iterator>::iterator_category).name() << endl;;

	// �ڡ�vector�� C++20�� concept�� �̿��Ͽ� contiguous���� ������ �� �ִ�.�ڡ�
	// list�� ��쿡�� ::iterator_concept�� ������ ����. �̶� ����ϴ°� cexpr
	cout << "������ �ݺ��� - " << typeid(Iterator::iterator_concept).name() << endl;

	// =============������ ��� ��µǴ� ��=============
	// struct std::random_access_iterator_tag - iterator_category
	// ������ �ݺ��� - struct std::contiguous_iterator_tag - iterator_concept
}

template<class �ݺ���, class ȣ�Ⱑ��Ÿ��>
void sort(�ݺ��� a, �ݺ��� e, ȣ�Ⱑ��Ÿ�� f)
{

}
int main()
{
	f(vector<int>{}.begin());

	//f(deque<int>{}.begin());
}


#elif Prac == 6
#include <iostream>
#include <vector>
#include <concepts>
#include <deque>

// =======================================================================
//[����] 
//========================================================================


int main()
{
	//contiguous_iterator �ܼ�
	cout << boolalpha << contiguous_iterator<vector<int>::iterator> << endl;
	cout << boolalpha << contiguous_iterator<deque<int>::iterator> << endl;
}

#elif Prac == 7
#include <iostream>
#include <vector>
#include <concepts>
#include <deque>
#include <algorithm>

// =======================================================================
//[����] sort�� �������� ����ǵ��� �϶�.
//========================================================================




int main()
{
	STRING s{ "2025 5 20" };

	sort(s.begin(), s.end(), greater<>());

	// ���ٵ� ����
	/*sort(s.begin(), s.end(), [](char a, char b) {
		return a > b;
		});*/

	cout << s << endl;	// "  0122555"

	// �̰ɷ� Random Access Iterator���� �ɷ������� ����
	//template< class RandomIt >
	//void sort(RandomIt first, RandomIt last);


	// ��� ranges::sort���
	// RandomAcccessIterator�� �ʿ�� �ϴ� ���ǵ��� ������ �����ε� �� ���� ������ ����
	// ���ͷ������� ��Һ񱳰� ����
	// => �׻� ���� ���ͷ����ͺ��� ���� ���ͷ������� �޸� �ּҰ� ũ�� ����?

	char* a{};
	char* b{};
	auto d = a <=> b;
	cout << typeid(d).name();

	
}
#endif 



