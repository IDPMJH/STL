#define Prac 4

// Associative Container - key�� '������' value�� �׻� ���� ���·� �����ϴ� Container
// ������ key���� �������� ���Ѵ�.
// �׻� ���� ���·� �����ϴ� ����? => Ž�� ���̼��� ����
// �׷��ٸ� ������ �߰���?
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
//[����] Iterator Adaptors �ٽ��� ������ 
// => �ݺ���ó�� ����ϰ� ǥ�� �ݺ��� �������̽��� �ؼ�(����) 
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
		// ���� ���� �� push_back�Լ��� �̿��ϱ� ������ back_inserter�̴�.
		// �̶� �޸� �ּҰ� �����Ǹ� �ݺ��ڰ� ��ȿȭ�Ǿ�� �ϴµ�, ���ο���
		// ����͸� ����ϴ� ��?�� ������ �ϱ� ������ �����̶�� �� �� �ִ�
		// �����ڰ� �����ε� �Ǿ��ֱ� ������ �ٸ� ������ �Ͼ��.
		++dest, ++begin;
	}
}

int main()
{
	STRING s{ "�ݺ��ڸ� ����� �˰����� ���� ��" };
	vector<char> v;

	// v�� ����� �������� �ʾƵ�, copy��ü�� ����ȴ�.
	// �ٵ� ����� �Ѿ���� �޸𸮸� ����,����-�ϱ� ������ ������ ������ �����̴�.
	// v.resize(s.size());

	// ȭ�鿡 ����ϱ�
	//copy(s.begin(), s.end(), ostream_iterator<char>{cout});

	// ���Ϳ� ī���ϱ�
	// �׷��� back_inserter��� �ÿ� ������ ����� �ڵ� �����ȴ�?
	//copy(s.begin(), s.end(),back_inserter(v));
	my_copy(s.begin(), s.end(), back_inserter(v));

	// back_inserter iterator�� ��쿡�� �����ڰ� ������ �޸� �����ε� �Ǿ��ְ�,
	// �����̳� ��ü�� ����Ű�� �ֱ� ������, ���Կ����� ����� pushback�� ����Ѵ�.
	//copy(s.begin(), s.end(), v);

	for (char c : v)
		cout << c;
}

#elif Prac == 2
#include <iostream>
#include <set>
#include <ranges>

// =======================================================================
//[����] STL�� �����̳ʿ� �˰������� �����ǰ�, �� ���� �ݺ��ڷ� �̾�����.
// Sequence Container
// ������ �߰�: O(1) �ð����⵵�� ����
// ������ ã��: O(N)
// - contiguous container - []���� �׼��� ������ ��� ����
// 1. array
// 2. vector
// 3. deque - amortized constant
// 4. list
// 5. forward_list
// 
// 
// Associative Container
// ������ �߰�: O(log N) �ð����⵵�� ���� - �̺�Ž��
// ������ ã��: O(log N)
// [1]. set, ��� : key, Compare, Allocator�� ����
// std::set is an associative container that 
// contains a sorted set of 'unique' objects of type Key.
// 'uniqueness' is determined by using the equivalence relation.
// 1. [equivalence], ��� ~ equality, ��
// 
// => !comp(a,b) && !comp(b,a) a�� b�� ������ Ȯ���� �� ���� ���, equivalence�ϴ�.
// 
// 
// 2. map
//========================================================================

int main()
{
	//set<Dog>�� ��쵵 �����ϱ�
	set<int> s{ 1,3,5,7,9,2,4,6,8,10 };
	// == set<STRING,std::less<STRING>,std::allocator<STRING>>
	// allocator�� ���� �Ű� �� �ʿ����, �ڵ�ȭ�� �����
	// ���� �޸� ������ �ڽ� ������ ���� ���� �ȴ�.
	// �ƹ�ư std::less<STRING>�� �����Ǿ�� �Ѵ�.

	// ����� ���� �����غ���
	set<int> s1{ 3 };
	s1.insert(3);
	// [1] 3, 3' �� ��
	// [2] !comp(3 < 3') �� ���� = true
	// [3] !comp(3' < 3) �� ���� = true
	// [4] [2] && [3] == true
	// operator==�� ��Ÿ���� �� => ��
	// �� operator==�� ������ �ʴ°�?
	// => ���� ���� ���� ���� ���̷� ������ �Ǵ��� �� �ִ�



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

	// �Ųٷ� ����غ���
	// filter�� ����ϱ�
	// ����� ����� �Է�����, �� �� ����� �Է����� ���� �����̴�
	// == �Լ��� ���α׷���
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
//[����] Ű������ �Է��� s�� �����϶�.
// s�� ��� ���Ҹ� ȭ�鿡 ����϶�.
//========================================================================

int main()
{
	// �ݺ��� �����
	// ����¹ݺ��ڴ� ������ ���ÿ� �ϵ����(Ű���� Ȥ�� �����)�� �����Ѵ�.
	// cin�� �ƴ� ����, ��Ʈ��ũ ��Ʈ���� �����ϴ�.
	set<STRING> s{ istream_iterator<STRING>{cin} ,{} };
	// == set<STRING, less<STRING>,allocator>
	// 1. less<STRING>�� �ִ��� ã�´�.
	// 2. operator<�� ã�´�.
	// 3. operator<=>�� ã�´�?

	// cout << sizeof(s); // == 24byte




	for (const STRING& str : s)
		cout << str << endl;
}

#elif Prac == 4
#include <iostream>
#include <set>
// =======================================================================
//[����] s�� �⺻ ���� ������ less�� ����Ͽ� 
// ����Ʈ �� �������� ���ĵǰ� �Ͽ� �������
// (���̰� ª�� �� ���� ��������)
//========================================================================

class fobj
{
public:
	// constant �ϰ��� 
	bool operator()(const STRING& a, const STRING& b) const
	{
		return a.size() < b.size();
	}
};


// �̰� �� ��
//template <class T>
//struct std::less {
//	bool operator()(const T& a, const T& b) const
//	{
//		return a.size() < b.size();
//	}
//};

// ���ø� Ư��ȭ - template Specialization
template <>
struct std::less<STRING> {
	bool operator()(const STRING& a, const STRING& b) const
	{
		return a.size() < b.size();
	}
};

int main()
{
	// �Լ� ��üfunctor ���
	set <STRING,fobj> s{ "333","2222", "11111","44","5" };

	set <STRING,less<STRING>> s1{ "333","2222", "11111","44","5" };

	set <STRING> s2{ "333","2222", "11111","44","5" };

	for (STRING str : s2)
		cout << str << endl;

}
#endif 



