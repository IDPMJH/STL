#define Prac 5

#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
// =======================================================================
//[문제] 강의자료 "이상한 나라의 엘리스.txt"를 다운받는다.
// [1] 여기에 있는 모든 단어를 vector에 저장하라.
// [2] 모두 몇 단어인지 화면에 출력하라.
// [3] 찾을 단어를 물어보고 입력받아 있는지 없는지 알려주자.
//========================================================================

int main()
{
	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	cout << "읽은 단어 수 : " << v.size() << endl;

	STRING str{};
	STRING ok{};
	while (true)
	{
		cout << "찾을 단어를 입력하세요: ";
		cin >> str;

		if (v.end() != find(v.begin(), v.end(), str))
			ok = "있는";
		else
			ok = "없는";

		cout << str << "는(은) " << ok << " 단어 입니다." << endl;
	}


}

#elif Prac == 2
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

// =======================================================================
//[문제] 
// [4] 잘 찾기 위해서 set<STRING>으로 데이터를 복사하자.
// [5] set에서 찾는 단어가 있는지 알려주자.
//========================================================================

int main()
{
	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	set<STRING> s{ v.begin(),v.end() };

	// 멀티 셋의 경우에는 count 내장함수를 사용해 그 개수를 알 수 있다.
	// multiset<STRING> ms{ v.begin(),v.end() };

	cout << "set으로 복사한 단어의 수 - " << s.size() << endl;

	STRING str{};
	STRING ok{};
	while (true)
	{
		cout << "찾을 단어를 입력하세요: ";
		cin >> str;

		// set에 내장된 find,그보다 더 나은 contains를 사용하여 이진탐색을 실시한다.

		if (s.contains(str))
			cout << str << "를(을) 찾았습니다." << endl;
		else
			cout << str << "은(는) 없는 단어입니다." << endl;

	}

	// set<STRING>의 메모리구조
	// STRING을 가지는 노드인데,
	// 부모노드와 (자식노드)를 가리키는 포인터를 가진다.
	// => Node 기반 구조의 문제점 : 
	// 낮은 캐시 공간 지역성에 의해 히트율이 낮아짐
	// 그렇다면 어떻게 해결할 수 있을까?
	// vector<STRING> v를 만들고, sort(v~~)하여 정렬
	// 그렇게되면 연속적인 연속적인 단어가 메모리에 정렬될 수 있음
	// 그러면 그 벡터에 이분탐색이 가능
	// binary_search(v.begin, v.end(),str);
	// 이러한 구조가 flat_set이라고 함
	// => Container adaptors에 들어가 있음
	// 기존의 컨테이너를 변형하여 사용할 수 있는 구조다.
	// deque를 이용한 stack, queue
	// vector를 이용한 flat_set - 벡터를 항상 정렬하여 유지
	// 따라서 push_back이 빈번이 일어나는 경우에는 사용하지 않는 편이 좋다.
	// 그런 상황에는 set을 사용하자.
	vector<STRING> s2{ s.begin(),s.end() };


}

#elif Prac == 3
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
// =======================================================================
//[문제] [6] 특정 문자가 들어가 있는 단어는 몇 개인가를 출력하라
// (예 : 'A'가 포함되는 단어 수는?)
//========================================================================

int main()
{
	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	set<STRING> s{ v.begin(),v.end() };
	//set에서 찾아 개수를 세기 - 특정 문자가 있는 단어 'A'

	char c;
	while (true)
	{
		cout << "특정 문자 입력, 문자를 가진 단어의 개수를 세겠습니다" << endl;
		cin >> c;

		auto count = count_if(s.begin(), s.end(), [c](const STRING& str) {
			auto p = find(str.begin(), str.end(), c);
			if (p != str.end())
				return true;
			return false;
			});

		cout << "글자 " << c << "가 포함된 단어의 수 - " << count << endl;
	}
}

#elif Prac == 4
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ranges>
// =======================================================================
//[문제] [7] 특정 단어가 포함되는 단어는 모두 몇 개인가?
// (예 : ion이 들어간 단어는 모두 몇개?)
//========================================================================

int main()
{
	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	set<STRING> s{ v.begin(),v.end() };
	//set에서 찾아 개수를 세기 - 특정 문자가 있는 단어 'A'

	STRING substr{};
	while (true)
	{
		cout << "특정 단어 입력 시 단어를 포함하는 단어의 개수를 세겠습니다" << endl;
		cin >> substr;

		auto count = count_if(s.begin(), s.end(), [substr](const STRING& str) {

			auto result = search(str.begin(), str.end(), substr.begin(), substr.end());
			if (str.end() != result)
			{
				cout << str << " ";
				return true;
			}
			return false;
		});
		cout << endl;
		cout << "단어 " << substr << "가 포함된 단어의 수 - " << count << endl;

	}
}



#elif Prac == 5
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <ranges>
// =======================================================================
//[문제] [1] 여기에 있는 모든 단어를 multiset<STRING>에 저장하라
// [2] 모두 몇 단어인지 화면에 출력하라.
//========================================================================

int main()
{
	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250529;
	}

	// sequential 하지 않다.
	multiset<STRING> ms{ istream_iterator<STRING>{in},{} };
	
	// sequential하다.
	// #include <vector>
	//vector<STRING> ms{ istream_iterator<STRING>{in},{} };

	// 컨테이너의 구조에 따라 그 사용 목적이 달라진다.
	
	

	set<STRING> s{ ms.begin(),ms.end() };
	
	cout << "읽은 단어 수 - " << ms.size() << endl;	// 26626

	for (const STRING& s : ms)
		cout << s << " ";
	cout << endl;

	while (true) {

		cout << "찾을 단어? ";
		STRING searchStr;
		cin >> searchStr;

		/*cout << searchStr << " 단어의 개수 : "<< ms.count(searchStr) << endl;*/
		//ms.count에 관련해서, multiset에 특화된 알고리즘을 사용한다.
		// 그 중복되는 단어들은 lower bound, upper bound를 통해 관리된다.
		// 이는 begin과 end구조와 비슷하다.

		// 좀 더 원형적인 코드
		// [문제 변형]
		// 입력한 단어가 추가되어도 multiset의 정렬 상태가 바뀌지 않을
		// 위치를 알고 싶다.
		// auto로 많은 반환 값을 받는 법 
		// ★★★ structured binding
		auto [lowerbound,upperbound] = ms.equal_range(searchStr);
		if (lowerbound == upperbound) {
			cout << "찾는 단어가 없습니다." << endl;
		}
		else {
			cout << distance(lowerbound, upperbound) << endl;
		}
	}


	// 특정 단어의 개수를 셀 때, 벡터에서 count_if를 사용하면
	// O(n)시간 복잡도를 가지지만

	// multiset.count()를 사용하면 컨테이너 크기의 log, + 찾은 원소 개수
	// 만큼, 즉 O(log n)알고리즘을 가진다.

	// set과 multiset에 삽입, 삭제 등의 동작을 할 때, 추가되는 위치 등을 고려
	// 어떻게 들어갈 것인가? - 정렬 순서를 깨지 않는 위치
	// > begin()과 end() (= 마지막 원소 다음 위치)까지 들어가도 아무 상관 없음
	// > 상한선과 하한선
}
#endif 



