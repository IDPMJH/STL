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
//[����] [1] �� ���� ���Ͽ� ���� ���ĺ��� ������ ������ ���� ����϶�
// multiset�� ����Ǿ� �ֱ� ������, �̸� �̿��Ѵ�.
// �빮�ڴ� ��� �ҹ��ڷ� �ٲ��.
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
	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
		return 20250529;
	}

	multiset<STRING> ms{ istream_iterator<STRING>{in},{} };

	cout << "���� �ܾ� �� - " << ms.size() << endl;	// 26626

	// �׻� �ʱ�ȭ�� ���� ����
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

	// ȿ�������� ���� �����, map�� �������



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
//[����] ������ ������ �������� ��µǰ� �غ���
//========================================================================


int main()
{

	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
		return 20250529;
	}

	multiset<STRING> ms{ istream_iterator<STRING>{in},{} };

	// �迭�� ����
// int a[10]  => �޸𸮰� ������, random-access ����
// contiguous �ϴ�
// [] => array operator, index operator �� ���� �̸��� ������
// subscript operator�� ���� �̸��̴�.(�ǹ̸� ���ϸ� �������.)
// 
// index�� ���ڰ� �ƴ� ���� �����ϴ� �迭 
// => ���� �迭,Associative Array
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
	// rbegin(),rend()�� ����ص� �Ȱ��� ���


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
//[����] �ܾ�� ���Ƚ���� ȭ�鿡 ����϶�.
//========================================================================

int main()
{
	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
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
//[����] 
//========================================================================

int main()
{

}
#endif 



