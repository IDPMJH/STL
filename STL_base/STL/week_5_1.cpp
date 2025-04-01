#define Prac 8
// ���� ����												���� == 8�� 2�� , 4�� 24��(30��),				���� == (30��) - 4�� 10�� ����
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
		bool operator()(int a, int b) const	// �Լ� ���뿡�� ���ڵ鿡 ��������� ���� ���� Ȯ���� const�� ���δ�.
		{
			return a > b;
		}
	};
	sort(a.begin(), a.end(), Dog{}); // Dog{} == predicate : ������, {}�̴ϼȶ����� ��ȣ�� ���� ���� - ()�� ���� operator()���� �������� �ָ��ϱ� ����
	for (int num : a)
		cout << num << " ";
	cout << endl;	// 10 9 8 ... 3 2 1
}
#elif Prac == 4
#include <iostream>
#include <array>
#include <algorithm>

// =======================================================================
//[����] ���� Prac == 3������ �޸�, Predicate�� Dog�� �ִٸ�?
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
	// ���� �ڵ�
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
	void (*a)();
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

// =======================================================================
//[����] Dog 10�������� ������ ���� ���� "Dog �ʸ�����"�� �����Ͽ���.
// ������ ���� �ڵ�� ������. 
// ofstream out("Dog �ʸ�����");
//
// Dog ��ü�� class Dog�� friend�Լ��� operator<<�� ����Ͽ� �����Ͽ���.
// 
// [����] �� ���Ͽ��� �����ϰ� 10������ Dog ��ü�� ����Ǿ� �ִ�.
// ���Ͽ� ����� Dog��ü�� ��� �о� �޸𸮿� �����϶�.
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
		println("{:12} - {}", _id, _name);
	}

	friend ostream& operator<<(ostream& os, const Dog& dog) {
		return os << dog._id << " " << dog._name << " ";
	}

	friend istream& operator>>(istream& is, Dog& dog) {
		return is >> dog._id >> dog._name;
	}

	int GetNameLength()
	{
		return _name.length();
	}

private:
	string	_name;
	int		_id;
};

array<Dog, 100'000> arr;

int main()
{
	/*ofstream out("Dog �ʸ�����");
	for (int i = 0; i < 100'000; ++i)
	{
		Dog dog;
		out << dog;
	}*/

	ifstream in("Dog �ʸ�����",ios::binary);
	if (not in)
		exit(2);
	
	for (Dog& dog : arr)
	{
		in >> dog;
	}

	cout << arr.back() << endl;

	sort(arr.begin(), arr.end(), [](Dog& a, Dog& b) { return a.GetNameLength() < b.GetNameLength(); });

	for (const Dog& dog : arr | views::take(1000))
		dog.show();


	cout << endl;

}





#endif