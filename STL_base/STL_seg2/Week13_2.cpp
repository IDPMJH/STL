#define Prac 3

#include "STRING.h"

using namespace std;
extern bool inspect;

#if  Prac == 1

#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <ranges>

// =======================================================================
//[문제] [1] 이 읽은 파일에 사용된 알파벳의 개수를 다음과 같이 출력하라
// multiset에 저장되어 있기 때문에, 이를 이용한다.
// 대문자는 모두 소문자로 바꿔라.
// a - 1030
// b - 300
// .
// .
// z - 30
// 
// 
// 
//========================================================================

int main()
{
	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250529;
	}

	multiset<STRING> ms{ istream_iterator<STRING>{in},{} };

	cout << "읽은 단어 수 - " << ms.size() << endl;	// 26626

	// 항상 초기화를 잊지 말것
	array<size_t, 26> a{};

	for (const STRING& str : ms)
		for (char c : str)
		{
			a[tolower(c) - 'a']++;
		}

	for (size_t i = 0; i < a.size(); ++i)
	{
		cout << static_cast<char>(i + 'a') << " - " << a[i] << endl;
	}

	// 효율적이지 않은 방식임, map을 사용하자



}

#elif Prac == 2
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <ranges>

// =======================================================================
//[문제] 문자의 개수를 기준으로 출력되게 해보자
//========================================================================


int main()
{

	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250529;
	}

	multiset<STRING> ms{ istream_iterator<STRING>{in},{} };

	// 배열의 장점
// int a[10]  => 메모리가 연속적, random-access 가능
// contiguous 하다
// [] => array operator, index operator 등 여러 이름이 있지만
// subscript operator가 원래 이름이다.(의미만 통하면 상관없다.)
// 
// index가 숫자가 아닌 것을 지원하는 배열 
// => 연관 배열,Associative Array
	map<char, size_t> alphaNum{};

	for (const STRING& str : ms) {
		for (char c : str) {
			if (isalpha(c))
				++alphaNum[tolower(c)];
		}
	}
	/*for (const auto& [key, value] : alphaMap)
	{
		cout << key << " - " << value << endl;
	}*/

	map<size_t, char, greater<size_t>> numAlpha{};

	for (const auto& [st, cnt] : alphaNum)
	{
		numAlpha[cnt] = st;
	}
	for (const auto& [key, value] : numAlpha /*| views::reverse*/)
	{
		cout << value << " - " << key << endl;
	}
	// rbegin(),rend()를 사용해도 똑같은 결과


}

#elif Prac == 3
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>
#include <ranges>
#include <print>


// =======================================================================
//[문제] 단어와 사용횟수를 화면에 출력하라.
//========================================================================

int main()
{
	ifstream in{ "이상한 나라의 앨리스.txt" };
	if (not in)
	{
		cout << "파일 읽기 실패" << endl;
		return 20250529;
	}

	STRING str;
	map<STRING, size_t> wordNum{};

	while (in >> str)
		wordNum[str]++;

	/*multiset<STRING> ms{ istream_iterator<STRING>{in},{} };

	

	for (const auto& str : ms)
	{
		wordNum[str] = ms.count(str);
	}*/

	for (const auto& [str, num] : wordNum)
	{
		cout << str << " - " << num << endl;
		//println("{:20} - {:} ", str.begin(), num);
	}
}

#elif Prac == 4
#include <iostream>

// =======================================================================
//[문제] 
//========================================================================

int main()
{

}
#endif 



