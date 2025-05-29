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
//[����] �����ڷ� "�̻��� ������ ������.txt"�� �ٿ�޴´�.
// [1] ���⿡ �ִ� ��� �ܾ vector�� �����϶�.
// [2] ��� �� �ܾ����� ȭ�鿡 ����϶�.
// [3] ã�� �ܾ ����� �Է¹޾� �ִ��� ������ �˷�����.
//========================================================================

int main()
{
	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	cout << "���� �ܾ� �� : " << v.size() << endl;

	STRING str{};
	STRING ok{};
	while (true)
	{
		cout << "ã�� �ܾ �Է��ϼ���: ";
		cin >> str;

		if (v.end() != find(v.begin(), v.end(), str))
			ok = "�ִ�";
		else
			ok = "����";

		cout << str << "��(��) " << ok << " �ܾ� �Դϴ�." << endl;
	}


}

#elif Prac == 2
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

// =======================================================================
//[����] 
// [4] �� ã�� ���ؼ� set<STRING>���� �����͸� ��������.
// [5] set���� ã�� �ܾ �ִ��� �˷�����.
//========================================================================

int main()
{
	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	set<STRING> s{ v.begin(),v.end() };

	// ��Ƽ ���� ��쿡�� count �����Լ��� ����� �� ������ �� �� �ִ�.
	// multiset<STRING> ms{ v.begin(),v.end() };

	cout << "set���� ������ �ܾ��� �� - " << s.size() << endl;

	STRING str{};
	STRING ok{};
	while (true)
	{
		cout << "ã�� �ܾ �Է��ϼ���: ";
		cin >> str;

		// set�� ����� find,�׺��� �� ���� contains�� ����Ͽ� ����Ž���� �ǽ��Ѵ�.

		if (s.contains(str))
			cout << str << "��(��) ã�ҽ��ϴ�." << endl;
		else
			cout << str << "��(��) ���� �ܾ��Դϴ�." << endl;

	}

	// set<STRING>�� �޸𸮱���
	// STRING�� ������ ����ε�,
	// �θ���� (�ڽĳ��)�� ����Ű�� �����͸� ������.
	// => Node ��� ������ ������ : 
	// ���� ĳ�� ���� �������� ���� ��Ʈ���� ������
	// �׷��ٸ� ��� �ذ��� �� ������?
	// vector<STRING> v�� �����, sort(v~~)�Ͽ� ����
	// �׷��ԵǸ� �������� �������� �ܾ �޸𸮿� ���ĵ� �� ����
	// �׷��� �� ���Ϳ� �̺�Ž���� ����
	// binary_search(v.begin, v.end(),str);
	// �̷��� ������ flat_set�̶�� ��
	// => Container adaptors�� �� ����
	// ������ �����̳ʸ� �����Ͽ� ����� �� �ִ� ������.
	// deque�� �̿��� stack, queue
	// vector�� �̿��� flat_set - ���͸� �׻� �����Ͽ� ����
	// ���� push_back�� ����� �Ͼ�� ��쿡�� ������� �ʴ� ���� ����.
	// �׷� ��Ȳ���� set�� �������.
	vector<STRING> s2{ s.begin(),s.end() };


}

#elif Prac == 3
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <fstream>
// =======================================================================
//[����] [6] Ư�� ���ڰ� �� �ִ� �ܾ�� �� ���ΰ��� ����϶�
// (�� : 'A'�� ���ԵǴ� �ܾ� ����?)
//========================================================================

int main()
{
	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	set<STRING> s{ v.begin(),v.end() };
	//set���� ã�� ������ ���� - Ư�� ���ڰ� �ִ� �ܾ� 'A'

	char c;
	while (true)
	{
		cout << "Ư�� ���� �Է�, ���ڸ� ���� �ܾ��� ������ ���ڽ��ϴ�" << endl;
		cin >> c;

		auto count = count_if(s.begin(), s.end(), [c](const STRING& str) {
			auto p = find(str.begin(), str.end(), c);
			if (p != str.end())
				return true;
			return false;
			});

		cout << "���� " << c << "�� ���Ե� �ܾ��� �� - " << count << endl;
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
//[����] [7] Ư�� �ܾ ���ԵǴ� �ܾ�� ��� �� ���ΰ�?
// (�� : ion�� �� �ܾ�� ��� �?)
//========================================================================

int main()
{
	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
		return 20250527;
	}

	vector<STRING> v{ istream_iterator<STRING>{in},{} };

	set<STRING> s{ v.begin(),v.end() };
	//set���� ã�� ������ ���� - Ư�� ���ڰ� �ִ� �ܾ� 'A'

	STRING substr{};
	while (true)
	{
		cout << "Ư�� �ܾ� �Է� �� �ܾ �����ϴ� �ܾ��� ������ ���ڽ��ϴ�" << endl;
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
		cout << "�ܾ� " << substr << "�� ���Ե� �ܾ��� �� - " << count << endl;

	}
}



#elif Prac == 5
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <ranges>
// =======================================================================
//[����] [1] ���⿡ �ִ� ��� �ܾ multiset<STRING>�� �����϶�
// [2] ��� �� �ܾ����� ȭ�鿡 ����϶�.
//========================================================================

int main()
{
	ifstream in{ "�̻��� ������ �ٸ���.txt" };
	if (not in)
	{
		cout << "���� �б� ����" << endl;
		return 20250529;
	}

	// sequential ���� �ʴ�.
	multiset<STRING> ms{ istream_iterator<STRING>{in},{} };
	
	// sequential�ϴ�.
	// #include <vector>
	//vector<STRING> ms{ istream_iterator<STRING>{in},{} };

	// �����̳��� ������ ���� �� ��� ������ �޶�����.
	
	

	set<STRING> s{ ms.begin(),ms.end() };
	
	cout << "���� �ܾ� �� - " << ms.size() << endl;	// 26626

	for (const STRING& s : ms)
		cout << s << " ";
	cout << endl;

	while (true) {

		cout << "ã�� �ܾ�? ";
		STRING searchStr;
		cin >> searchStr;

		/*cout << searchStr << " �ܾ��� ���� : "<< ms.count(searchStr) << endl;*/
		//ms.count�� �����ؼ�, multiset�� Ưȭ�� �˰����� ����Ѵ�.
		// �� �ߺ��Ǵ� �ܾ���� lower bound, upper bound�� ���� �����ȴ�.
		// �̴� begin�� end������ ����ϴ�.

		// �� �� �������� �ڵ�
		// [���� ����]
		// �Է��� �ܾ �߰��Ǿ multiset�� ���� ���°� �ٲ��� ����
		// ��ġ�� �˰� �ʹ�.
		// auto�� ���� ��ȯ ���� �޴� �� 
		// �ڡڡ� structured binding
		auto [lowerbound,upperbound] = ms.equal_range(searchStr);
		if (lowerbound == upperbound) {
			cout << "ã�� �ܾ �����ϴ�." << endl;
		}
		else {
			cout << distance(lowerbound, upperbound) << endl;
		}
	}


	// Ư�� �ܾ��� ������ �� ��, ���Ϳ��� count_if�� ����ϸ�
	// O(n)�ð� ���⵵�� ��������

	// multiset.count()�� ����ϸ� �����̳� ũ���� log, + ã�� ���� ����
	// ��ŭ, �� O(log n)�˰����� ������.

	// set�� multiset�� ����, ���� ���� ������ �� ��, �߰��Ǵ� ��ġ ���� ���
	// ��� �� ���ΰ�? - ���� ������ ���� �ʴ� ��ġ
	// > begin()�� end() (= ������ ���� ���� ��ġ)���� ���� �ƹ� ��� ����
	// > ���Ѽ��� ���Ѽ�
}
#endif 



