
// 2025/03/18 3�� 1��
// ���� ���� �ڷḦ ����ϱ� - binary I/O
// -> ������ binary���� ����� ��ȯ�� �Ͼ�� �ʴ´�.

//#include "save.h"
// �����ϸ� ������� ����.
using namespace std;



#define Prac 4

#if Prac == 1
#include <iostream>
#include <bitset>

int main()
{
	// ========================================================
	// [����] ���� �ð��� int 1000���� ���Ͽ� ����Ͽ���.
	// int 1000���� �����ϱ� ���� �󸶸�ŭ�� ���� ����Ʈ�� ����Ͽ��°�? 
	// => 8200byte
	// ========================================================
	// �ڡڡ� 32bit int�� �ִ� ���� 21�� ��¼������ ���Ͽ� textmode�� �����ϸ�, ��� byte ����?(text mode)
	// -> ��������� 10�ڸ� ���� ���� Ȯ���� ���� ���� -> 10�ڸ��� �Է��Ѵٰ� ���� = 10byte
	// unsigned�� �ƴϹǷ� ��ȣ�� 50% Ȯ���� ���� -> �� ���� 0.5����Ʈ �߰� = 10.5byte
	// �� ���� ���� ���� ���� = 11.5byte
	// ���� ���� = 1000, �� byte �� = 1000 * 11.5 = 11500byte (����)
	// Ȥ�� ���� ������ ���� Ȯ���� ���� 9�ڸ� ���� ���� ������ŭ ����, 
	// 10.5byte* 500 + 11.5byte*500 = 11000byte (����)



	int num{ 0x01'02'03'04 };

	cout << "16���� : " << hex << num << endl;
	cout << "10���� : " << dec << num << endl;
	cout << "2����  : " << bitset<32>(num) << endl;

	//save("main_week_3.cpp");
}
#elif Prac == 2
// ========================================================
// [����] �޸𸮿� ����� bit�� �״�� ���Ͽ� ������ �� �ִ�.
// -> ������ ����� �Լ��� ����Ѵ�.
// ========================================================
#include <iostream>
#include <array>
#include <numeric>
int main()
{
	// {}(����Ʈ ������)�̴ϼȶ������� �ʱ�ȭ���� ���� ��, �ʱ�ȭ ���� ����.
	array<int, 1000> arr{};
	// �ڡڡ� �޸𸮰� �پ� ����(������ ���Ӽ�) - > Contiguous memory
	// �ð��� ���Ӽ� -> Continuous time
	// ���ڰ����� �ִ� �������� 1�� �÷����� ä���
	std::iota(arr.begin(), arr.end(), 1);

	for (int num : arr)
		cout << num << " ";

	cout << endl;
}


#elif Prac == 3
#include <iostream>
#include <array>
#include <numeric>
#include <fstream>

// =======================================================================
// [����] arr�� data�� ����"int 1000�� �޸� �״��"�� ����϶�.
// =======================================================================
int main()
{
	// {}(����Ʈ ������)�̴ϼȶ������� �ʱ�ȭ���� ���� ��, �ʱ�ȭ ���� ����.
	array<int, 1000> arr{};
	// �ڡڡ� �޸𸮰� �پ� ����(������ ���Ӽ�) - > Contiguous memory
	// �ð��� ���Ӽ� -> Continuous time
	// ���ڰ����� �ִ� �������� 1�� �÷����� ä���
	std::iota(arr.begin(), arr.end(), 1);

	//ofstream out{ "int 1000�� �޸� �״��" }; -> mode ������ ������ text mode
	// text mode�� ���� ��, �ü���� ���� ���� ���ִ� �۾��� ��
	// 
	ofstream out{ "int 1000�� �޸� �״��" ,ios::binary};
	// int a = arr.size();  a == 1000 -> ������ ����
	// a = sizeof(arr);		a == 4000 -> �迭 ��ü�� ũ��

	//out.write(reinterpret_cast<char*>(arr.data()), sizeof(int)*arr.size());
	out.write(reinterpret_cast<char*>(arr.data()),sizeof(arr));
}


#elif Prac == 4

#include <iostream>
#include <array>
#include <numeric>
#include <fstream>
int main()
{
	// [��Ȳ] ���� �ϳ��� int 4����Ʈ�� 0A 0A 0A 0A�� �̷���� �ִ�.
	// -> �ؽ�Ʈ ���Ϸ� Windows���� -> 0D(ĳ���� ����),0A(�����ǵ�)���� ��ȯ
	// Windows�� �ؽ�Ʈ ��忡�� 0A �� 0D 0A ��ȯ�� �߻��߱� ������ 
	// ���� ũ�Ⱑ 4000����Ʈ �� 8000����Ʈ�� ������ ��.
	// �̸� �����Ϸ��� ���̳ʸ� ���(std::ios::binary)�� ����Ͽ� ��ȯ�� ���ƾ� ��.
	// ����� EOF(End Of File)�� 0x1A�� ǥ���Ǹ�, ������ ũ��ʹ� �����ϰ� ������ ���� ��Ÿ��.
	array<int, 1000> arr{};
	arr.fill(0x0a0a0a0a);

	ofstream out{ "int 1000�� �޸� �״��" };
	out.write(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());
}

#elif Prac == 5

#include <iostream>
#include <fstream>
#include <random>

// main�� ���� ���� (���� ������ �ſ� ���� ������)
mt19937 mt{};

int main()
{
	// =======================================================================
	// [����] ���� "int 10������ ���̳ʸ���� write�Լ��� ���"
	// �� 10������ ���� int���� �������.
	// �� int ���� �޸� ũ�� �״�� ����Ѵ�.
	// ������ bianry mode�� ����
	// =======================================================================

	// ���̳ʸ� ���� ����
	ofstream out{ "int 10������ ���̳ʸ���� write�Լ��� ���",ios::binary };

	uniform_int_distribution<int> uid{ numeric_limits<int>::min(),numeric_limits<int>::max()};
	int num{};
	for (int i = 0; i < 10'000; ++i)
	{
		num = uid(mt); // ���⼭ �ʱ�ȭ �ص� �ڵ� ����ȭ ���ֱ� ��, �׷��� ������ �ʱ�ȭ����.
		out.write(reinterpret_cast<char*>(&num), sizeof(int));
	}
}

#elif Prac == 6

#include <iostream>
#include <fstream>
#include <array>
// ���� �� ���ɼ��� ���� ��쿡�� ������ array�� �������. (inplace_vector�� ���� ��(c++26) ����� ��)

int main()
{
	// =======================================================================
	// [����] binary�� ���� ����� ���� "int 10������ ���̳ʸ���� write�Լ��� ���"��
	// int�� 10������ �޸� ũ�� �״�� ��ϵǾ� �ִ�. (ostream�� write �Լ��� ���)
	// 1. �� int�� 10������ �о �޸𸮿� �����϶�.
	// 2. ���� ���� ���� ã�� ȭ�鿡 ����϶�. ȭ�鿡 ����� ���� ������ �����.
	// 3. �� ������ �ذ��ϴ� �ڵ带 ������ �����.
	// =======================================================================

	// ���̳ʸ� ���� ����
	ifstream in{ "int 10������ ���̳ʸ���� write�Լ��� ���",ios::binary };
	
	// ���� �� text mode�� ����?
	//ifstream in{ "int 10������ ���̳ʸ���� write�Լ��� ���" };
	if (not in)
		return;
	// ���� ���� �ſ� ���� ����	
	array<int, 10'0000> arr{};

	/*for (int& num : arr)
		in.read(reinterpret_cast<char*>(&num), sizeof(int));*/
	in.read(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());

	cout << "���� ���� �� : " << *min_element(arr.begin(), arr.end()) << endl;
}


#endif