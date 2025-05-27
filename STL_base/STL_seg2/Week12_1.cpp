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
//[문제] myfind 구현하기
//========================================================================

// 내가 코딩한 초기형(템플릿이 아님)
//STRING::STRING_Iterator my_find(const STRING::STRING_Iterator& begin, const STRING::STRING_Iterator& end, char c)
//{
//	for (auto a = begin; a != end; ++a)
//	{
//		if (c == *a)
//			return a;
//	}
//	return end;
//} 

// 일반 타입이 들어갈 수 있기 때문에, 반드시 class 키워드를 붙여야 한다.
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


	// [문자]소문자를 입력받아 몇 번째에 있는 문자인지 출력하자.
	while (true) {
		cout << "소문자를 입력하세요 - ";
		char c; cin >> c;

		// auto p = find(s.begin(), s.end(), c);
		auto p = my_find(s.begin(), s.end(), c);

		if (p != s.end()) {
			cout << distance(s.begin(), p) + 1 << "번째 위치에 있습니다." << endl;
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
//[문제]  v에서 처음 나오는 짝수가 무엇인지 출력하라.
// my_find_if 구현
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
		cout << "처음 만난 짝수는 -- " << *p << endl;
}

#elif Prac == 3
#include <iostream>
#include <vector>

// =======================================================================
//[문제] 
//========================================================================

template<class srcIterator, class destIterator>
void my_copy(srcIterator begin, srcIterator end, destIterator dest)
{
	while (begin != end) {
		*dest = *begin;
		// 값을 대입할 때 push_back함수가 호출되기 때문에 back_inserter이다.
		// 이때 메모리 주소가 이전되면 반복자가 무효화되어야 하는데, 내부에서
		// 어댑터를 사용하는 등?의 동작을 하기 때문에 사기꾼이라고 할 수 있다
		++dest, ++begin;
	}
}
int main()
{
	STRING s{ "반복자를 사용한 알고리즘을 연습 중" };
	vector<char> v;

	// v의 사이즈를 맞춰주지 않아도, copy자체는 실행된다.
	// 근데 사이즈를 넘어서까지 메모리를 접근하기 때문에 굉장히 위험한 동작이다.
	v.resize(s.size());

	// 화면에 출력하기
	//copy(s.begin(), s.end(), ostream_iterator<char>{cout});

	// 벡터에 카피하기
	// 그러나 back_inserter사용 시에 벡터의 사이즈가 자동 조정된다?
	//copy(s.begin(), s.end(),back_inserter(v));
	my_copy(s.begin(), s.end(), back_inserter(v));

	//copy(s.begin(), s.end(), v);

	for (char c : v)
		cout << c;

}


// 실제 Back_inserter Iterator 구조
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
// ++할 때 아무것도 안 한다.
//	_CONSTEXPR20 back_insert_iterator& operator++() noexcept {
//		return *this;
//	}
//
// 실제로는 컨테이너를 가리킨다.
//protected:
//	_Container* container;
//};

#elif Prac == 4
#include <iostream>

// =======================================================================
//[문제] 
//========================================================================

int main()
{

}
#endif 



