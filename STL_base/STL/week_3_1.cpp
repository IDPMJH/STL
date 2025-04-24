#define Prac 6
const int p = 1;
// 2025/03/18 3�� 1��
// ���� ���� �ڷḦ ����ϱ� - binary I/O
// -> ������ binary���� ����� ��ȯ�� �Ͼ�� �ʴ´�.

//#include "save.h"
// 
// �����ϸ� ������� ����.
using namespace std;






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
	// �� ������ ���� ���ڸ� �����Ѵٸ� = 11.5byte
	// ���� ���� = 1000, �� byte �� = 1000 * 11.5 = 11500byte (����)
	// 
	// Ȥ�� ���� ������ ���� Ȯ���� ���� 9�ڸ� ���� ���� ������ŭ���� å���Ͽ� ����, 
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


	//�迭 ���� ä��� �پ��� ���
	//	1. std::iota
	//	���ӵ� ������ �迭�� ä��(��: 1, 2, 3, ��)
	//	�̹� ����Ͻ� ����Դϴ�.
	//	2. std::fill / std::fill_n
	//	�迭�� ��� ���� ������ ������ ä��
	//	cpp ->
	//	std::fill(arr.begin(), arr.end(), 42); // ��� ��Ҹ� 42�� ä��
	//	cpp ->
	//	std::fill_n(arr.begin(), arr.size(), 7); // ��� ��Ҹ� 7�� ä��
	// 
	//3. std::generate / std::generate_n
	//	�Լ�(���� ��)�� �̿��� �� ��Ҹ� ä��
	//	cpp->
	//	int v = 1;
	//std::generate(arr.begin(), arr.end(), [&v] { return v++; }); // 1, 2, 3, ...
	//std::iota�� ����������, �� ������ ���ϵ� ����

	//	4. for ���� ���� ���
	//	�������̸�, ���ϴ� ������ �����Ӱ� ���� ����
	//	cpp
	//	for (size_t i = 0; i < arr.size(); ++i)
	//		arr[i] = static_cast<int>(i) + 1;
	// 
	//5. �ʱ�ȭ ����Ʈ(������ Ÿ�� ���)
	//	�ұԸ� �迭���� �ǿ���
	//	cpp
	//	std::array<int, 5> arr = { 1, 2, 3, 4, 5 };

	//�� �ܿ��� std::copy, std::transform �� �پ��� ǥ�� �˰����� Ȱ���Ͽ� �迭�� �ʱ�ȭ�ϰų� ���� ä�� �� ����
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
	// text mode�� ���� �� �ü����, ����� ���� ���� ���ִ� �۾��� ��
	// 
	ofstream out{ "int 1000�� �޸� �״��" ,ios::binary };
	// int a = arr.size();  a == 1000 -> ������ ����
	// a = sizeof(arr);		a == 4000 -> �迭 ��ü�� ũ��

	//out.write(reinterpret_cast<char*>(arr.data()), sizeof(int)*arr.size());
	out.write(reinterpret_cast<char*>(arr.data()), sizeof(arr));
	// arr �迭�� ��� �����͸� ���̳ʸ�(����) �������� ���Ͽ� �����Ѵ�.
	// - arr.data()�� �迭�� ù ��° ���(�޸� ���� �ּ�)�� ����Ű�� int* �����͸� ��ȯ�Ѵ�.
	// - reinterpret_cast<char*>(arr.data())�� int* �����͸� char* �����ͷ� ��ȯ�Ѵ�.
	// (�̷��� �ؾ� write()�� ����Ʈ ������ �����͸� ó���� �� �ִ�).
	// - sizeof(arr)�� �迭 ��ü�� ����Ʈ ũ��(��: int 1000���� 4000����Ʈ)�� ��ȯ�Ѵ�.
	// - ��������� �迭�� ��� �޸� ������ ����Ʈ ������ ���Ͽ� �״�� ����Ѵ�.
	//
	// �� ����: �� ����� ���̳ʸ� ���Ͽ��� �����ϸ�, ����� �б� ��� ���� �ڷ���/�÷����̾�� �����Ͱ� �ùٸ��� �����ȴ�.
	// �� reinterpret_cast�� ������ Ÿ�� ������ ������ ��ȯ�� ���Ǹ�, ��Ʈ ������ �״�� �ؼ��Ѵٴ� ���� �����ؾ� �Ѵ�


	//
	//	�ؽ�Ʈ ��忡�� �迭 ���� ���
	//		1. �ݺ����� ��� ������(<< ) ���
	//		cpp
	//#include <fstream>
	//#include <array>
	//
	//		std::array<int, 1000> arr = {/* ... */ };
	//
	//	std::ofstream out("output.txt"); // �ؽ�Ʈ ���(�⺻)
	//	for (const int& num : arr) {
	//		out << num << '\n'; // �� ��Ҹ� ���ڿ��� ��ȯ �� �� �پ� ����
	//	}
	//	out.close();
	//	�� ��Ҹ� ���ڿ��� ��ȯ�Ͽ� �� �پ� ���Ͽ� ����մϴ�.
	//
	//		'\n'�� ���̸� �� ���� �� �ٿ� �ϳ��� ����˴ϴ�.
	//
	//		�޸�, �� �� �ٸ� �����ڸ� �� ���� �ֽ��ϴ�.
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
	// 
	// ������ bianry mode�� ����
	// =======================================================================

	// ���̳ʸ� ���� ����
	ofstream out{ "int 10������ ���̳ʸ���� write�Լ��� ���",ios::binary };

	uniform_int_distribution<int> uid{ numeric_limits<int>::min(),numeric_limits<int>::max() };
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
		return 1;
	// ���� ���� �ſ� ���� ����	
	array<int, 10'0000> arr{};

	/*for (int& num : arr)
		in.read(reinterpret_cast<char*>(&num), sizeof(int));*/
	//in.read(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());
	in.read(reinterpret_cast<char*>(arr.data()), sizeof(arr));

	

	cout << "���� ���� �� : " << *min_element(arr.begin(), arr.end()) << endl;
}


#endif