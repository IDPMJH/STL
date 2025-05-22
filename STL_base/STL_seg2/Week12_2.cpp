#define Prac 4

// Associative Container - key와 '연관된' value를 항상 정렬 상태로 유지하는 Container
// 정렬은 key값을 기준으로 비교한다.
// 항상 정렬 상태로 유지하는 이유? => 탐색 용이성을 위해
// 그렇다면 데이터 추가는?
// 
// set / multiset - key == value
// map / multimap - pair<key,value>




#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1
#include <iostream>
#include <vector>


// =======================================================================
//[문제] Iterator Adaptors 핵심은 세가지 
// => 반복자처럼 사용하고 표준 반복자 인터페이스를 준수(제공) 
// 1. reverse_Iterator
// 2. insert_iterator
// - 1. back_inserter
// - 2. front_inserter
// - 3. inserter
// 3. stream_iterator
//========================================================================
template<class srcIterator, class destIterator>
void my_copy(srcIterator begin, srcIterator end, destIterator dest)
{
	while (begin != end) {
		*dest = *begin;
		// 값을 넣을 때 push_back함수를 이용하기 때문에 back_inserter이다.
		// 이때 메모리 주소가 이전되면 반복자가 무효화되어야 하는데, 내부에서
		// 어댑터를 사용하는 등?의 동작을 하기 때문에 사기꾼이라고 할 수 있다
		// 연산자가 오버로딩 되어있기 때문에 다른 동작이 일어난다.
		++dest, ++begin;
	}
}

int main()
{
	STRING s{ "반복자를 사용한 알고리즘을 연습 중" };
	vector<char> v;

	// v의 사이즈를 맞춰주지 않아도, copy자체는 실행된다.
	// 근데 사이즈를 넘어서까지 메모리를 접근,복사-하기 때문에 굉장히 위험한 동작이다.
	// v.resize(s.size());

	// 화면에 출력하기
	//copy(s.begin(), s.end(), ostream_iterator<char>{cout});

	// 벡터에 카피하기
	// 그러나 back_inserter사용 시에 벡터의 사이즈가 자동 조정된다?
	//copy(s.begin(), s.end(),back_inserter(v));
	my_copy(s.begin(), s.end(), back_inserter(v));

	// back_inserter iterator의 경우에는 연산자가 실제와 달리 오버로딩 되어있고,
	// 컨테이너 자체를 가리키고 있기 때문에, 대입연산자 실행시 pushback을 사용한다.
	//copy(s.begin(), s.end(), v);

	for (char c : v)
		cout << c;
}

#elif Prac == 2
#include <iostream>
#include <set>
#include <ranges>

// =======================================================================
//[문제] STL은 컨테이너와 알고리즘으로 구성되고, 그 둘은 반복자로 이어진다.
// Sequence Container
// 데이터 추가: O(1) 시간복잡도를 가짐
// 데이터 찾기: O(N)
// - contiguous container - []랜덤 액세스 연산자 사용 가능
// 1. array
// 2. vector
// 3. deque - amortized constant
// 4. list
// 5. forward_list
// 
// 
// Associative Container
// 데이터 추가: O(log N) 시간복잡도를 가짐 - 이분탐색
// 데이터 찾기: O(log N)
// [1]. set, 멤버 : key, Compare, Allocator로 구성
// std::set is an associative container that 
// contains a sorted set of 'unique' objects of type Key.
// 'uniqueness' is determined by using the equivalence relation.
// 1. [equivalence], 동등성 ~ equality, 상등성
// 
// => !comp(a,b) && !comp(b,a) a와 b의 순서를 확정할 수 없는 경우, equivalence하다.
// 
// 
// 2. map
//========================================================================

int main()
{
	//set<Dog>의 경우도 생각하기
	set<int> s{ 1,3,5,7,9,2,4,6,8,10 };
	// == set<STRING,std::less<STRING>,std::allocator<STRING>>
	// allocator는 굳이 신경 쓸 필요없다, 자동화된 기능임
	// 만약 메모리 관리에 자신 있으면 직접 만들어도 된다.
	// 아무튼 std::less<STRING>이 지원되어야 한다.

	// 동등성에 대해 생각해보기
	set<int> s1{ 3 };
	s1.insert(3);
	// [1] 3, 3' 이 들어감
	// [2] !comp(3 < 3') 을 실행 = true
	// [3] !comp(3' < 3) 을 실행 = true
	// [4] [2] && [3] == true
	// operator==가 나타내는 것 => 상등성
	// 왜 operator==로 비교하지 않는가?
	// => 동일 기준 순서 상의 차이로 같음도 판단할 수 있다



	for (int a : s)
	{
		cout << a << " ";
	}
	cout << endl;

	for (auto i = s.begin(); i != s.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << endl;

	// 거꾸로 출력해보기
	// filter를 사용하기
	// 출력의 결과가 입력으로, 또 그 결과가 입력으로 들어가는 구조이다
	// == 함수형 프로그래밍
	for (int a : s | ranges::views::reverse)
	{
		cout << a << " ";
	}
	cout << endl;

	for (auto i = s.rbegin(); i != s.rend(); ++i)
	{
		cout << *i << " ";
	}



}

#elif Prac == 3
#include <iostream>
#include <set>
// =======================================================================
//[문제] 키보드의 입력을 s에 저장하라.
// s의 모든 원소를 화면에 출력하라.
//========================================================================

int main()
{
	// 반복자 어댑터
	// 입출력반복자는 생성과 동시에 하드웨어(키보드 혹은 모니터)와 연결한다.
	// cin이 아닌 파일, 네트워크 스트림도 가능하다.
	set<STRING> s{ istream_iterator<STRING>{cin} ,{} };
	// == set<STRING, less<STRING>,allocator>
	// 1. less<STRING>이 있는지 찾는다.
	// 2. operator<를 찾는다.
	// 3. operator<=>를 찾는다?

	// cout << sizeof(s); // == 24byte




	for (const STRING& str : s)
		cout << str << endl;
}

#elif Prac == 4
#include <iostream>
#include <set>
// =======================================================================
//[문제] s를 기본 정렬 기준인 less를 사용하여 
// 바이트 수 기준으로 정렬되게 하여 출력하자
// (길이가 짧은 것 부터 나오도록)
//========================================================================

class fobj
{
public:
	// constant 일관성 
	bool operator()(const STRING& a, const STRING& b) const
	{
		return a.size() < b.size();
	}
};


// 이건 안 됨
//template <class T>
//struct std::less {
//	bool operator()(const T& a, const T& b) const
//	{
//		return a.size() < b.size();
//	}
//};

// 템플릿 특수화 - template Specialization
template <>
struct std::less<STRING> {
	bool operator()(const STRING& a, const STRING& b) const
	{
		return a.size() < b.size();
	}
};

int main()
{
	// 함수 객체functor 사용
	set <STRING,fobj> s{ "333","2222", "11111","44","5" };

	set <STRING,less<STRING>> s1{ "333","2222", "11111","44","5" };

	set <STRING> s2{ "333","2222", "11111","44","5" };

	for (STRING str : s2)
		cout << str << endl;

}
#endif 



