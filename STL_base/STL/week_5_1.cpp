#define Prac 8
// ���� ����			�ڡڡڽ��� == 8�� 2�� , 4�� 24��(30��),	���� == (30��) - 4�� 10�� ����
// generic - �ڷ����� ������	
// Callable type : ȣ�� ������ Ÿ�� - C++���� ()�� �ٿ��� ȣ���� �� �ִ� ��� ���� Callable�̶�� �Ѵ�, C++�� �ٽ�
// ��� ���� ��ǥ�ϴ� �ڡڡ�funchtion�ڡڡ� (include <functional>)
// 1. �Լ�
// -> �Լ� ���� �Լ��� �ּ�(���۹���), ���� ȣ�� ��� => (*�Լ���)() == (*save)()
// 2. �Լ��� �޾ƿ� �Լ� ������
// 3. ����(�̸����� �Լ�), ��ü�� �־�� �Ѵ�.(VS - class�� �ڵ�)
// 4. �Լ���ü(FunctionObject) - "�Լ�ȣ�⿬����(operator())�� �����ε��� Ŭ���� ��ü"
// 5. ����Լ�
// C++ stack-unwinding�� �����ϱ�
// 
// �̹� ����
// 
// 
using namespace std;

#if Prac == 1
#include <iostream>

void save()
{

}


int main()
{
	int n{};
	typeid(int);

	int* saveaddr = (int*)save;
	cout << "save�Լ��� ����� �޸� ����: " << saveaddr << endl;

	// ���ٴ� ����ü �����ΰ�? -> typeid Ȱ�� 
	// class `int __cdecl main(void)'::`2'::<lambda_1> : main�ȿ��� ������� Ŭ����
	// '�����Ϸ�'(VisualStudio)�� �ڵ�ȭ => class lambda ����, lambda�� ��ü ������ ���ؼ�
	// 
	[]() {
		cout << "�ȳ� �� �̸��� ���� ~" << endl;
		}();
}

#elif Prac == 2
#include <iostream>
#include <fstream>
#include <algorithm>



// =======================================================================
//[Ȯ��] �Լ� ��ü�� ���� ������ �۵���� Ȯ���ϱ�
//=======================================================================

int main()
{

	// �Լ� ��ü
	class Dog
	{
	public:
		// �Լ� ȣ�� ������ FunctionCallOperator
		void operator()()
		{
			cout << "�Լ� ��ü �Դϴ�." << endl;
		}
	};
	Dog dog;
	dog();
	cout << typeid(dog).name() << endl; // class `int __cdecl main(void)'::`2'::Dog -> ���� �Լ����� Ŭ������ ������ ���, ������ ��İ� �����ϴ�.
	// ���� ȣ�� ���
	//dog.operator()();

}
#elif Prac == 3
#include <iostream>
#include <array>
#include <algorithm>


// =======================================================================
//[����] ���� �ڵ尡 �ǵ���� ����� �� �ְ� �ʿ��� �ڵ��� �߰��϶�.
//=======================================================================

int main()
{
	array<int, 10> a{ 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };
	class Dog {
	public:
		bool operator()(int a, int b) const	// �Լ� ���뿡�� ���ڵ鿡 ��������� ���� ���� Ȯ���� const�� ���δ�.�١١١�
		{
			return a > b;
		}
	};
	sort(a.begin(), a.end(), Dog{}); // Dog{} == predicate : ������, {}�̴ϼȶ����� ��ȣ�� ���� ���� - ()�� ���� operator()���� �������� �ָ��ϱ� ���� - �����ڸ� ���� �� �ִ� ����? Callable Type�� ���ڷ� ���� - �Լ� ��ü, �Լ� ������ ���
	for (int num : a)
		cout << num << " ";
	cout << endl;	// 10 9 8 ... 3 2 1
}
#elif Prac == 4
#include <iostream>
#include <array>
#include <algorithm>

// =======================================================================
//[����] ���� Prac == 3������ �޸�, Callable Type - Predicate�� Dog�� �ִٸ�?
// ���ٸ� ���� Dog�� ������ �� �ִ�.
//=======================================================================

int main()
{
	array<int, 10> a{ 1, 3, 5, 7, 9, 2, 4, 6, 8, 10 };

	// �����Ϸ��� �����ϴ� �ڵ�
	//class ���� {
	//public:
	//	bool operator()(int a, int b) { return a > b; }
	//};
	// ���� �ڵ� - auto�� Ŀ�� �뺸��
	auto Dog = [](int a, int b) {
		return a > b;	// ��ȯ ������ �߷��� ���� bool�� ����
		};

	sort(a.begin(), a.end(), Dog); // Dog == predicate : ������

	//sort(a.begin(), a.end(), Dog)
	//{
	//	? ? ? (3, 4); // �� ���� ����� ����((3,4)�� Callabe�� �� ������)�Ѵٸ� ������� sort�Լ�
	//};


	for (int num : a)
		cout << num << " ";
	cout << endl;	// 10 9 8 ... 3 2 1
}

#elif Prac == 5
#include <iostream>
#include <algorithm>

// =======================================================================
//[����] 
//=======================================================================

int main()
{
	// �Լ��� ���� �ϳ��� �޶� Ÿ���� �޶����� ������ ȣȯ�� �� ����. a = b ��
	void b();
	//void b( int );
	void (*a)();	// �Լ� ������ ����
	// b�� Ÿ�԰� a�� Ÿ�� ��ġ
	a = b;
}

#elif Prac == 6
#include <iostream>
#include <array>
#include <functional>
#include <algorithm>

// =======================================================================
//[����] 
//=======================================================================

int main()
{
	int num;
	int a[10];
	array<int, 10> a_new;

	void(*aFunc) ();
	function<int> a_newFunc;	// generic
}

#elif Prac == 7
#include <iostream>
#include <array>
#include <functional>
#include <algorithm>

// =======================================================================
//[����] 
//=======================================================================

int main()
{
	auto ptr = [](int a, int b) {return a > b; };
	// true - false ��½� boolalpha
	cout << boolalpha << ptr(3, 4) << endl;


	// funchtion Ȱ�� - �ڷ����� ����, �̸��� ������ ���� ���� ǥ��
	function<bool(int, int)> ptr2 = ptr;

}


#elif Prac == 8
#include <iostream>
#include <string>
#include <random>
#include <array>
#include <print>
#include <fstream>
#include <algorithm>
#include <ranges>
#include <chrono>



// �ڡڡ������� �����ڡڡ�
// =======================================================================
//[����] Dog 10�������� ������ ���� ���� "Dog �ʸ�����"�� �����Ͽ���.
// ������ ���� �ڵ�� ������. 
// ofstream out("Dog �ʸ�����");
//
// Dog ��ü�� class Dog�� friend�Լ��� operator<<�� ����Ͽ� �����Ͽ���.
// 
// [����] ���Ͽ�"Dog �ʸ�����"���� ��Ȯ�ϰ� 10������ Dog ��ü�� ����Ǿ� �ִ�.
// ���Ͽ� ����� Dog��ü�� ��� �о� �޸𸮿� �����϶�.		==> ������ ��ü�� '��'�� ������ ���� = Array�� ����
// ���� ������ ��ü�� ������ ȭ�鿡 ����ϰ� �������� ��� ������ �����.
// ��� �� ���� ��ü�� ����Ǿ� �ִ��� ����϶�.
// �޸𸮿� ����� Dog ��ü�� ��� name ���� ���� ������������ �����϶�.
// ���ĵ� Dog ��ü�� �տ������� 1000���� ȭ�鿡 ����϶�.
//========================================================================

default_random_engine dre;
uniform_int_distribution<int> uidName{ 'a', 'z' };
uniform_int_distribution uidNameLen{ 3,30 };
uniform_int_distribution uidId{  };

class Dog {

public:
	Dog() {
		int len = uidNameLen(dre);
		for (int i = 0; i < len; ++i)
		{
			_name += uidName(dre);
		}
		_id = uidId(dre);
	}

	void show() const {
		println("[{:12}] - {}", _id, _name);
	}

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		return os << dog._id << " " << dog._name << " ";
	}

	friend istream& operator>>(istream& is, Dog& dog) {
		return is >> dog._id >> dog._name;
	}

	size_t GetNameLength() const // �Լ��� const���̴� �� �׻� �����ϱ�
	{
		// == name.size(), length�� ���� �� �ڿ�������
		return _name.length();
	}

	bool operator<(const Dog& other) const // �Լ��� const���̴� �� �׻� �����϶��
	{
		return GetNameLength() < other.GetNameLength();
	}
private:
	string	_name;
	int		_id;
};

array<Dog, 100'000> arr;

int main()
{
	// ������ ��İ� ������ ������� ����.
	/*ofstream out("Dog �ʸ�����");
	for (int i = 0; i < 100'000; ++i)
	{
		Dog dog;
		out << dog;
	}*/

	ifstream in("Dog �ʸ�����", ios::binary);

	// �ݵ�� üũ�� ��
	if (not in)
	{
		cout << "Dog �ʸ����� - ������ �� �� �����ϴ�." << endl;
		return 20250403;
	}

	// �̷��� ����� �����ϴ�. (���� �� �ƴ�)
	/*int num{};
	string name;
	int count{};
	while (in >> num >> name)
	{
		println("[{:7}] - {:12}{:}", ++count, num, name);
	}*/

	// �������� �ڵ�
	for (Dog& dog : arr)
	{
		in >> dog;
	}

	// Ŭ������ Getter�� �ִ��� ���� �ڵ��������� - ĸ��ȭ�� ��߳�
	// -> Setter�� ����� ��찡 �ʿ��� ���, Ŭ������ �ٽ� �����ϴ� ���� ����
	// cout << "���� ������ ��ü�� ���� : "<< arr.back() << endl;
	arr.back().show();

	// ������ ��� sort�� ����.
	cout << "Dog name ���� ���� �������� (ascending oredr) �����մϴ�." << endl;
	//ranges::sort(arr); https://velog.io/@minsu_lighting--/C20-Range
	auto start = chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end(), [](const Dog& a, const Dog& b) { return a.GetNameLength() < b.GetNameLength(); });
	auto end = chrono::high_resolution_clock::now();

	cout << "����ð�(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

	// �ڡڡ�sort�� ����
	// int data�� ���� ���ٷ� �������� �Լ��� �ۼ����� �ʾƵ� �Ǵ� ����?
	// �̹� int�� < �����ڰ� �ֱ� ������ ���� ���� �ۼ����� �ʾƵ� default�� ascendingorder�� ����
	// [������] ����� ���� �ڷ���(class ��)�� < �����ڰ� ���� ������ default ���ĵ��� ����
	// ���� �Լ� ��ü�� �������־ ������, < �����ڸ� ����(�����ε�)�ص� ��.
	// �̿� ���� < �����ڸ� �����ε� �ϸ�, �Ʒ����� default sort�� �����ϴ�

	// �̹� ���ĵǾ� �ֱ⿡ �ð� ������ ������ ��
	auto start2 = chrono::high_resolution_clock::now();
	sort(arr.begin(), arr.end());
	auto end2 = chrono::high_resolution_clock::now();
	cout << "����ð�(duration)ms - " << chrono::duration_cast<chrono::milliseconds>(end2 - start2).count() << "ms" << endl;

	// range-based for ������ const�� &�� �׻� �����ϱ�, 
	// auto�� �ʿ��� ��찡 �ƴ� �̻� ������� Ÿ�� Ȱ���ϱ�
	for (const Dog& dog : arr | views::take(1000)) // ranges::views::take(1000) - ����
		dog.show();

	// [Ȯ��]===========filter�� �������� �˾ƺ���============
	//for (const Dog& dog : arr | views::reverse) // ���� ���
	//	dog.show();

	cout << endl;

}





#endif