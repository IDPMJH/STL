using namespace std;

// �̹� �ִ� ���� ������ ����
// ���� ���� �ڷḦ ó���ϱ�

#define Prac 4

#if Prac == 1

#include <iostream>
#include <random>
#include <print>
#include <array>

int main()
{
	// ========================================================
	//[����1] ���� int �� 1000���� ������ �޸𸮿� �����ϰ�,
	// ���� ū ���� ã�� ����Ѵ�.
	// ========================================================
	random_device rd{};
	auto A = rd();	// �� ���� ���� �Ұ���
	int B = rd();	// �� ���� ���� �Ұ���
	mt19937 mt{ };
	// mt19937 mt{ random_device{}() };	// �� ���� ���� ����
	// == default_random_engine dre(rd());
	// == mt19937 mt{ random_device{}()};
	uniform_int_distribution<int> id{ 0, 999'9999 };
	
	array<int, 1000> arr{};		// T[N] -> array<T,N> 

	for (int& num : arr)
	{
		num = { id(mt) };
		print("{:8}", num);
	}
	cout << endl;
	//auto MaxIter = max_element(arr.begin(), arr.end());
	//int a{ *MaxIter };
	cout << "�ִ� - " << *max_element(arr.begin(), arr.end()) << endl;
}

#elif Prac == 2

#include <iostream>
#include <print>
#include <fstream>
#include <random>
int main()
{
	//========================================================
	//	[����2] ���� int �� 1000���� ����"int 1000��.txt"�� �����϶�.
	//	������ ������ �� ����� ���� �� �־�� �Ѵ�.
	//	������ �о� ���� int ���� ������ �� �־�� �Ѵ�. (= �ؽ�Ʈ ���� �����϶�.)
	//	========================================================

	//	std::print
	//{: N} Nĭ��ŭ ���õ� �ڸ��� ��������  ���� ����(������ ����)
	//{:<N} : ���� ����
	//{:^N} : ��� ����
	//{:.N} : �Ҽ��� N�ڸ����� ���
	// {:,} : õ���� ������
	// {0:b} : 2����
	// {0:o} : 8����...
	// print("{:^80}", 20250311);

	default_random_engine dre{ };
	uniform_int_distribution<int> id{ 0, 999'9999 };

	//�׳� ���� �ؽ�Ʈ ���, �ι�° ���ڿ�ios::binary : ���̳ʸ� ���
	ofstream out{ "int 1000��.txt" };	// RAII : ��ü�� �ڿ��� ������ ����Ŭ�� ��ġ��Ų��.

	int cnt{};
	// Dellmiter : ��������
	for (int i = 0; i < 1000; ++i)
	{
		print(out, "{:8}", id(dre));
		if (not(++cnt % 10))	// 10������ �ٹٲ�
			out << endl;
	}
}

#elif Prac == 3

#include <fstream>
#include <print>

int main()
{
	// ========================================================
	// [����3] ���� "int 1000��.txt"���� int 1000���� text�������� ��ϵǾ� �ִ�.
	// ���� ū ���� ã�� ȭ�鿡 ����϶�, ��µ� ���� �������� ������ ���.
	// ========================================================
	ifstream in{ "int 1000��.txt" };
	if (not in)
		return(1);
	
	// iterator adaptor : stream iterator
	print("�ִ� : {}\n",*max_element(istream_iterator<int>{in}, {}));

	//���� ũ�� ���� ���
	//	1. �� ������ ��� ���� �м�
	//	print(out, "{:8}", id(dre)) �������� ����մϴ�.
	//{:8}�� �ּ� 8�ڸ� �ʺ�� ������ �����Ͽ� ����ϴ� �����Դϴ�.
	//	��, �� ���ڴ� �ּ� 8����Ʈ�� �����մϴ�.
	//	���ڰ� 8�ڸ� �̸��̸� �տ� ������ ä�����ϴ�.
	// 
	//	2. �ٹٲ� ���� ���
	//	10������ �ٹٲ��� �ϹǷ� �� 100���� �ٹٲ��� �ֽ��ϴ�.
	//	Windows ȯ�濡���� �ٹٲ��� \r\n���� 2����Ʈ�Դϴ�.
	//	���� �ٹٲ޿� �ʿ��� ����Ʈ : 100 �� 2 = 200����Ʈ
	// 
	//	3. �� ���� ũ�� ���
	//	���� ������ : 1000�� �� 8����Ʈ = 8, 000����Ʈ
	//	�ٹٲ� : 100�� �� 2����Ʈ = 200����Ʈ
	//	�� ���� ũ�� : 8, 000 + 200 = 8, 200����Ʈ
}
	

#elif Prac ==  4

#include <fstream>
#include <array>
#include <print>
#include <algorithm>
int main()
{
	//[����4] ���� "int 1000��.txt"���� int 1000���� text�������� ��ϵǾ� �ִ�.
	// �� �����͸� �޸𸮿� �����϶�.
	// �޸𸮿� �ִ� �����͸� ȭ�鿡 ����϶�
	// array = ������ �� �����ϰ� �뷮�� ������ ���� ->    ������ �ƴ�
	ifstream in{ "int 1000��.txt" };
	array<int, 1000> arr;
	// �ڡڡ� array�� ���Ͽ��� �о� �ʱ�ȭ �ϴ� ��� ã�ƺ���
	if (not in)
		exit(1);
	// 1. for���� ���
	//for (int& i : arr)
	//{
	//	in >> i;
	//	print("{:8}", i);
	//}
	// 2. copy_n�� ��� (copy�� ������) �ڡڡ�
	// std::copy[first, last, dest.begin()) ������ ��� ��Ҹ� ����
	// std::copy_n[first, n, dest.begin()] n���� ����
	std::copy_n(std::istream_iterator<int>{in}, arr.size(), arr.begin());

	// 3. generate ���
	//std::generate(arr.begin(), arr.end(), [&in]() {int i; in >> i; return i; });

	// 2�� ����� �ڵ� ���Ἲ, ǥ��/������ �鿡�� �����

	sort(arr.begin(), arr.end());

	for (const int& i : arr)
	{
		print("{:8}", i);
	}
}

#endif 

















