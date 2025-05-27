#define Prac 3

#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1
#include <iostream>
#include <vector>
#include <concepts>
#include <deque>
#include <algorithm>

// =======================================================================
//[����] myfind �����ϱ�
//========================================================================

// ���� �ڵ��� �ʱ���(���ø��� �ƴ�)
//STRING::STRING_Iterator my_find(const STRING::STRING_Iterator& begin, const STRING::STRING_Iterator& end, char c)
//{
//	for (auto a = begin; a != end; ++a)
//	{
//		if (c == *a)
//			return a;
//	}
//	return end;
//} 

// �Ϲ� Ÿ���� �� �� �ֱ� ������, �ݵ�� class Ű���带 �ٿ��� �Ѵ�.
template<class Iterator, class Value>
Iterator my_find(Iterator begin, Iterator end, Value c)
{
	while (begin != end)
	{
		if (*begin == c)
			break;
		++begin;
	}

	return begin;
}

int main()
{
	STRING s{ "the quick brown fox jumps over the lazy dog" };

	sort(s.begin(), s.end());

	unique(s.begin(), s.end());

	cout << s << endl;


	// [����]�ҹ��ڸ� �Է¹޾� �� ��°�� �ִ� �������� �������.
	while (true) {
		cout << "�ҹ��ڸ� �Է��ϼ��� - ";
		char c; cin >> c;

		// auto p = find(s.begin(), s.end(), c);
		auto p = my_find(s.begin(), s.end(), c);

		if (p != s.end()) {
			cout << distance(s.begin(), p) + 1 << "��° ��ġ�� �ֽ��ϴ�." << endl;
		}
	}
	cout << s << endl;
}

#elif Prac == 2
#include <iostream>
#include <vector>
#include <algorithm>

template<class Iterator, class Predicate>
Iterator my_find_if(Iterator begin, Iterator end, Predicate f)
{
	while (begin != end)
	{
		if (f(*begin))
			break;
		++begin;
	}

	return begin;
}

// =======================================================================
//[����]  v���� ó�� ������ ¦���� �������� ����϶�.
// my_find_if ����
//========================================================================

int main()
{
	vector<int> v{1, 3, 5, 7, 9, 2, 4, 6, 8, 10};


	/*auto p = find_if(v.begin(), v.end(), [](int n) {
		return not (n & 1);
		});*/
	auto p = my_find_if(v.begin(), v.end(), [](int n) {
		return not (n & 1);
		});

	if (p != v.end())
		cout << "ó�� ���� ¦���� -- " << *p << endl;
}

#elif Prac == 3
#include <iostream>
#include <vector>

// =======================================================================
//[����] 
//========================================================================

template<class srcIterator, class destIterator>
void my_copy(srcIterator begin, srcIterator end, destIterator dest)
{
	while (begin != end) {
		*dest = *begin;
		// ���� ������ �� push_back�Լ��� ȣ��Ǳ� ������ back_inserter�̴�.
		// �̶� �޸� �ּҰ� �����Ǹ� �ݺ��ڰ� ��ȿȭ�Ǿ�� �ϴµ�, ���ο���
		// ����͸� ����ϴ� ��?�� ������ �ϱ� ������ �����̶�� �� �� �ִ�
		++dest, ++begin;
	}
}
int main()
{
	STRING s{ "�ݺ��ڸ� ����� �˰����� ���� ��" };
	vector<char> v;

	// v�� ����� �������� �ʾƵ�, copy��ü�� ����ȴ�.
	// �ٵ� ����� �Ѿ���� �޸𸮸� �����ϱ� ������ ������ ������ �����̴�.
	v.resize(s.size());

	// ȭ�鿡 ����ϱ�
	//copy(s.begin(), s.end(), ostream_iterator<char>{cout});

	// ���Ϳ� ī���ϱ�
	// �׷��� back_inserter��� �ÿ� ������ ����� �ڵ� �����ȴ�?
	//copy(s.begin(), s.end(),back_inserter(v));
	my_copy(s.begin(), s.end(), back_inserter(v));

	//copy(s.begin(), s.end(), v);

	for (char c : v)
		cout << c;

}


// ���� Back_inserter Iterator ����
_EXPORT_STD template <class _Container>
//class back_insert_iterator {
//public:
//	using iterator_category = output_iterator_tag;
//	using value_type = void;
//	using pointer = void;
//	using reference = void;
//	// ...
//
//	_CONSTEXPR20 back_insert_iterator& operator=(const typename _Container::value_type& _Val) {
//		container->push_back(_Val);
//		return *this;
//	}
//
//	_NODISCARD _CONSTEXPR20 back_insert_iterator& operator*() noexcept {
//		return *this;
//	}
//
// ++�� �� �ƹ��͵� �� �Ѵ�.
//	_CONSTEXPR20 back_insert_iterator& operator++() noexcept {
//		return *this;
//	}
//
// �����δ� �����̳ʸ� ����Ų��.
//protected:
//	_Container* container;
//};

#elif Prac == 4
#include <iostream>

// =======================================================================
//[����] 
//========================================================================

int main()
{

}
#endif 



