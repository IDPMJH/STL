
// 2025/03/18 3�� 2��
// ���� ���� �ڷḦ ����ϱ� - binary I/O
// -> ������ binary���� ����� ��ȯ�� �Ͼ�� �ʴ´�.

//#include "save.h"
// �����ϸ� ������� ����.
using namespace std;

#define Prac 4

#if Prac == 1

// ========================================================
// [���� - ����] binary mode�� ���� write �Լ��� int 10������ �����
// ���� "int 10������ ���̳ʸ���� write�Լ��� ���.txt"�� �ִ�.
// �о �޸𸮿� ��� �����϶�.
// �޸𸮿� �ִ� �� �� ���� ���� �Ͱ� ���� ū ���� ã�� ȭ�鿡 ����϶�.
// ��µ� ���� �������� �����.
// ========================================================
#include <iostream>
#include <array>
#include <fstream>
#include <algorithm>

int main()
{
	// �� ���̳ʸ����� ��ϵ� ����, ���̳ʸ� ���� ���� ������ ������ �ְ�� ���ɼ��� �ִ�.
	ifstream in("int 10������ ���̳ʸ���� write�Լ��� ���", ios::binary);
	if (not in)
	{
		cout << "������ �� �� �����ϴ�." << endl;
		exit(1);
	}
	array<int, 100'000> arr{};

	in.read(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());

	// �ִ� �ּҸ� �˾Ƴ���	���� max_element, min_element ��� -> �ι�
	// �� �ִ� �ּҸ� �˾Ƴ���	���� minmax_element ��� -> �ѹ�
	int max = {};
	int min = {};
	// �� structured binding	auto�� ���� - ������ ���
	auto [IterofMin, IterofMax] = minmax_element(arr.begin(), arr.end());
	IterofMin != arr.end() ? min = *IterofMin : min = 0;
	IterofMax != arr.end() ? max = *IterofMax : max = 0;

	cout << "Max : " << max << endl;
	cout << "Min : " << min << endl;

}

#elif Prac == 2
// ���� ���� �ڷḦ ó���ϱ� - Dog�� �а� ����, read/write
#include <iostream>
#include <string>
#include <random>
#include <print>
#include <fstream>
#include <array>

// Dog �������� �����Ͽ� ���Ͽ� ����(write), �޸𸮿� �о�ͼ� ó��(����)

// ���� �� ���ɼ��� ���� ��쿡�� ������ array�� �������. (inplace_vector�� ���� ��(c++26) ����� ��)

// =======================================================================
// [����] class Dog ��ü 10������ binary mode�� �� ����"Dog 10�� ����" �� �����Ͽ���.
// ��ü ũ�� �״�� write�Լ��� ����Ͽ� �����Ͽ���. 
// =======================================================================
// class �� �ۼ��� ���� �߰�ȣ�� Ŭ���� �̸� ���� �ۼ�
// 40 ����Ʈ - > 32����Ʈ + int 4����Ʈ

default_random_engine dre{};
uniform_int_distribution<int> uid{ 'a','z' };
class Dog {
public:
	Dog() {		// name(15���� ����, ������ �ҹ���)�� id�� �ʱ�ȭ(
		_id = ++_sid;	// ������ 1�� �����ϴ� static ����
		for (int i = 0; i < 15; ++i)
		{
			_name += uid(dre);
		}
	}

public:
	void show() const {
		println("ID : {:7} ,Name : {}",_id, _name);
	}
	
	


private:
	string	_name{};	// 32
	int		_id{};	// 4 -> 36 bytes, 4 bytes padding => 40bytes

	static int _sid;	// padding�� ������, scope - local, life time - global
};

int Dog::_sid{};	// �ʱ�ȭ

int main()
{
	ofstream out{ "Dog 10�� ����",ios::binary };
	if (not out)
	{
		cout << "������ �� �� �����ϴ�." << endl;
		exit(1);
	}
	for (int i = 0; i < 100'000; ++i)
	{
		Dog dog;
		out.write(reinterpret_cast<char*>(&dog), sizeof(Dog));
	}

	// ������ �о �޸𸮿� ����
	ifstream in{ "Dog 10�� ����",ios::binary };
	if (not in)
	{
		cout << "������ �� �� �����ϴ�." << endl;
		exit(1);
	}
	/*array<Dog, 100'000> arr;

	in.read(reinterpret_cast<char*>(arr.data()), sizeof(Dog) * arr.size());

	for (const Dog& dog : arr)
	{
		dog.show();
	}*/



}


#elif Prac == 3
#include <iostream>
#include <array>
#include <fstream>

class Dog {
private:
	string	_name{};	// 32
	int		_id{};	// 4 -> 36 bytes, 4 bytes padding => 40bytes

public:
	void show () const
	{
		cout << "ID : " << _id << " , Name : " << _name << endl;
	}

	// friend�� ���� �ؿ�
	friend ostream& operator<< (ostream& os, const Dog& dog)
	{
		os << "ID : " << dog._id << " , Name : " << dog._name;
		return os;
	}
};
// =======================================================================
// [����] e-class���� �ٿ�ε� ���� ���� "Dog 10������"�� binary mode�� ������,
// ���� ���� class Dog�� ��Ʈ���� write�Լ��� ����Ͽ� �޸� �״�� 10���� �����Ͽ���.
// Dog ��ü 10������ �޸𸮿� �����϶�.
// ���� ������ ��ü�� ������ ȭ�鿡 ����϶�.
// =======================================================================

// 1 .���� ���� ver
array<Dog, 100'000> Dogs;

int main()
{
	// 2. array* ver
	// array<Dog, 100'000>* Dogs = new array<Dog,100'000> ;

	ifstream in{ "Dog 10�� ����",ios::binary };
	if (not in)
	{
		cout << "������ �� �� �����ϴ�." << endl;
		return 1;
	}


	// 1 .���� ���� ver
	in.read(reinterpret_cast<char*>(Dogs.data()), sizeof(Dogs));
	// 2. array* ver
	//in.read(reinterpret_cast<char*>(Dogs), sizeof(Dog) * (*Dogs).size());


	// 1 .���� ���� ver
	cout << Dogs.back();
	cout << Dogs.front();
	// 2. array* ver
	// cout << Dogs->back();
}

#elif Prac == 4

#include <iostream>
#include <array>
#include <numeric>
#include <fstream>

// =======================================================================
// [����]e-class���� �ٿ�ε� ���� ���� "Dog 10������"�� binary mode�� ������,
// ���� ���� class Dog�� ��Ʈ���� write�Լ��� ����Ͽ� �޸� �״�� 10���� �����Ͽ���.
// =======================================================================
class Dog {
private:
	string	_name{};	// 32
	int		_id{};	// 4 -> 36 bytes, 4 bytes padding => 40bytes

public:
	void show() const
	{
		cout << "ID : " << _id << " , Name : " << _name << endl;
	}

	// friend�� ���� �ؿ�
	friend ostream& operator<< (ostream& os, const Dog& dog)
	{
		os << "ID : " << dog._id << " , Name : " << dog._name;
		return os;
	}
	
	// [����1] �ذ���
	friend istream& operator>> (istream& is,  Dog& dog)
	{
		is.read(reinterpret_cast<char*>(&dog), sizeof(Dog));
		return is;
	}
};
array<Dog, 100'000> Dogs;

int main()
{
	ifstream in{"Dog 10�� ����",ios::binary };
	if (not in)
	{
		cout << "������ �� �� �����ϴ�." << endl;
		return 1;
	}


	// [����1] ���� �ڵ尡 �������� ����ǵ��� �ʿ��� �ڵ带 class Dog�� �߰��϶�.
	for (Dog& dog : Dogs)
	{
		in >> dog;
	}
	cout << Dogs.back();
}

// ����
// 1. ���Ͽ��� ��尡 �ִ�. -> text mode, binary mode
// 2. ������ I/O level���� 2������ �ִ�. -> low level(read(),write() �Լ��� �ӵ� ���), high level(<<, >> �Լ� �ӿ��� �پ��� �ڵ�)
// 3. ���� textmode�� ����� high level�� �����ϰ�, binary mode�� ����� low level�� �����ϴ� ���� ����.
// 4. ���Ͽ� ������ ���� binary mode�� �����ϴ� ���� ����. (�뷮 ����)

#elif Prac == 5
// ���� ����
// 
#include <iostream>

// ======================================================================
//[����]
//=======================================================================

int main()
{

}
#endif