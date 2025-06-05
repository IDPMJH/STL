#define Prac 3

#include "STRING.h"


// 1. Map�� ���� Ž���Ѵ�.


// [Prac 3 ����]
// 2. STL, Unoredred Associative Containers - Hash ����
// 
// Containers - �ð��� ���� ������ trade off
// ã�� �Ƿ¿� ���� �з��� �����ٰ� �����ص� �ȴ�. N ���� �����͸� ���´ٰ� �����Ѵ�.
// 1. Sequence				ã�� : O(N)
// - �޸𸮸� �ּҷ� ��� (N ĭ ���)
// 
// 2. Associative			ã�� : O(log N)
// - Ʈ���� �̿��Ͽ� N�� �����͸� ���� �� ���� ã������ �����͵��� �������� ���ԵǾ� �޸𸮸� �����Ѵ�.
// 
// 3. Unordered Associative	ã�� : O(1) 
// - �ð� ���� �ְ� ������ ����
// - ������ ����ϰ� ����
// - hash�� ���� �ڸ� ��ġ�� �ľ��ϱ� ������ �̸� ���� ������ �ʿ��ϴ�.
// - vector + list
// - �� ���Ұ� ��Ŷ�� �� ����Ǿ�����
// - Hash���� ���� ������ ��ġ�� �ľ�
// 
// [unordered_set / map<STRING>�� ����ǵ��� ����� ���� ��ǥ�̴�.]

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <map>
#include <set>
#include <random>
#include <array>
// =======================================================================
//[����] uniform ������ uniform �Ѱ�?
// ��ü �����͸� 20���� �������� ������ ������ �� �� ȭ�鿡 ����Ѵ�.
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
//[����] normal_distribution�� �̿��� �븻 ������ �����Ѵ�.
//========================================================================
//random_device rd{};
default_random_engine dre{  };
// �л�� ������ ���ڷ� �޴´�.
normal_distribution nd{ 0.0,0.5 };
array<int, 20'000'000> arr;


int main()
{
	for (int& num : arr)
	{
		double d = nd(dre);
		d *= 200'000;
		d += 1'000'000;
		if ((0 < d) && (d < 2'000'000))	// ���� �Լ��� �ִµ� ã�ƺ� ��
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
//[����] 
//========================================================================


// 1.
//template<class T>
//struct std::hash {
//	operator() (const T&) {
//		return 1;
//	}
//};


// 2.
// ���ø� Ư��ȭ
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
	// �� ����?
	// 1. Hash�� �����Ͽ��� �Ѵ�.
	// 2. equal_to  : ����� ���� (== ����

	// �ذ� ���
	// �̹� �����ϴ� hasher�� STRING���� std::string���� �ٲپ� ������ �ȴ�.
	unordered_set<STRING,hash<STRING>,equal_to<STRING>> us{ "1","22","333","4444" };

	for (const STRING& s : us)
	{
		cout << s << endl;
	}

	while(true)
	{
		// unordered_set�� �޸𸮸� ȭ�鿡 �������.
		for (size_t bc = 0; bc < us.bucket_count(); ++bc)
		{
			print("[{:>3}]", bc);
			for (auto i = us.begin(bc); i != us.end(bc); ++i)
			{
				print(" -> {:}", std::string{ i->begin(), i->end() });
			}
			cout << endl;
		}

		cout << "�߰��� STRING - ";
		STRING s;
		cin >> s;
		us.insert(s);

		// load_balancing
	}
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



