#define Prac 1
// ����
// smart pointer�� �����Ҵ�, RAII
// �� RAII�� �߿��Ѱ�? - ���� �������� �����ϱ� ����
// RAII - �ڿ��� �����ֱ�� ��ü�� �����ֱ⸦ ��ġ��Ű�� ��
// C++ stack-unwinding�� �����ϱ�
// 
// �̶� Dog ��ü�� �޸� ����
// 1. ����
// 2. ������ (�ʱ�ȭ�� ������ ���� + �ʱ�ȭ ���� ���� ������ ����)
// 3. free-store (HEAP) ������ �θ���� ������ ��
// 4. CODE ���� - �ڵ尡 ����Ǵ� ����

// 1,2���� 3���� ���� - �޸� ũ�⸦ ���� ������ �� �ִ°�. 
// 1,2���� ������ Ÿ�ӿ� �����ȴ�. 3���� ��Ÿ�ӿ� �����ȴ�.
// 
// 1���� 2���� ����	  - �޸� ũ�Ⱑ �󸶳� ū��.


using namespace std;

#if Prac == 1

#include <iostream>
#include <array>
#include <memory>
#include <numeric>


// =======================================================================
//[����] (int�� �ִ� ������ ����)���� ���� num�� �Է¹޴´�.
// 1���� num������ ������ ������ �� �ִ� �޸𸮸� Ȯ���ϰ�,
// �޸��� ���� 1���� num���� ä���.
// �޸𸮿� ����� ���� �հ踦 ȭ�鿡 ����Ѵ�.
// ȭ�鿡 ��µ� �հ�� ��������� �ۼ��Ѵ�.
// �� ������ �ƹ��� ���� ���� ������ �ݺ������ �� �ְ� �ڵ��϶�.
//========================================================================

int main()
{
	while (true)
	{
		size_t num;
		cout << "���� ������ �Է��ϼ���: ";
		cin >> num;

		{
			// �ٷ� �ؿ��� ä�� �ٵ�, �ʱ�ȭ �� ������ ���� ����.
			// ����Ʈ ver. shared_ptr<size_t[]> arr;
			size_t* arr2;
			try
			{
				//����Ʈ ver. arr = make_shared<size_t[]>(num);
				arr2 = new size_t[num];	// free-store�� ����: heap�� void *�� ��ȯ�Ѵ�.
			}
			catch (exception& e)
			{
				cout << e.what() << endl; // bad allocation - delete�� �� �ҽ�

				return 20250325;
			}


			// 1���� ä���
			//����Ʈ ver. iota(arr.get(), arr.get() + num, 1);
			iota(arr2, arr2 + num, 1);

			long long sum{};

			// ���� ���� �Լ��� ã�ƺ���? -> reduce
			sum = accumulate(arr2, arr2 + num, 0LL); // 3��° ���ڷ� Ÿ���� ����
			// �������� for ������ ����� ����, �׻� ���� �˰����� �����غ���
			//for (size_t i = 0; i < num; i++)
			//{
			//	//arr.get()[i] = i + 1;
			//	 arr2[i] = i + 1;
			//	 //sum += arr.get()[i];
			//	 sum += arr2[i];
			//	
			//}
			cout << "1����" << num << "������  �հ�: " << sum << endl;
			delete[](arr2);	// �߿�
		}
	}

	return 0;

}

#elif Prac == 2

#include <iostream>
#include <numeric>
// =======================================================================
//[����]
//=======================================================================

void f() // ���ܸ� �߻���Ű�� ���� ��쿡 ��� Ű���� : noexcept 
{
	shared_ptr<int> sp(new int[10], [](int* p) { delete[] p; });
	int* p = new int[10] {}; // 0���� �ʱ�ȭ

	// ���� �����ϱ�
	cout << "free-store�� �޸� �ּ� - " << p << ", ";
	cout << "�հ� : " << accumulate(p, p + 10, 0) << endl;

	// ����
	throw 20250325;

	// 1. ���ܷ� ���� ���� �Ұ� - �޸� ����
	delete[] p;


	// 2. ���� ���ܰ� �߻����� �ʰ�, �ð� ��� ��... �������� �ϴ� ��� - ��� ���α׷� ���(��۸������� ����)
	delete[] p;
}

int main()
{
	// ���ܸ� ���α� 
	// but ���� üũ �ڵ�� �ӵ��� ������ �ֱ� ������ �����ϸ� ������� ����
	try {
		f();
	}
	catch (int& e)
	{
		cout << "���� �߻� : " << e << endl;
		 
	}
}


#elif Prac == 3

#include <iostream>
#include <numeric>
#include <memory>
// =======================================================================
//[����]
//=======================================================================

class Dog {
public:
	Dog() { cout << "Dog ����" << endl; }
	~Dog() { cout << "Dog �Ҹ�" << endl; }
};

class mysmartptr {
public:
	mysmartptr(Dog* p) : _p(p) {}
	~mysmartptr() { delete _p; }

private:
	Dog* _p;

};
void f()
{
	// ������ ������� ��ü�� ������ ���� �� �ݵ�� �Ҹ��ϱ�
	// stack unwinding

	//mysmartptr p{ new Dog }; // RAII �ʱ�ȭ

	// RAII�� �����ϱ�
	unique_ptr<Dog[]> up = make_unique<Dog[]>(10);	// �迭 ���� �� ()�ȿ�
	shared_ptr<Dog[]> sp = make_shared<Dog[]>(10);	// �迭 ũ�� ����

	// RAII �� �ƴ�
	//Dog* p;	
	//p = new Dog;

	throw 1;
	//cout << "���� ��µ��� ����" << endl;
}

int main()
{

	try {
		f();
	}
	catch (int& e)
	{
		cout << "���� �߻� : " << e << endl;

	}
}

#elif Prac == 4

#include <iostream>
#include <fstream>
#include <algorithm>
#include "save.h"

// =======================================================================
//[����] "main.cpp"�� ���� �߿� �ҹ��ڸ� ��� �빮�ڷ� �ٲپ� 
// "main_upper.cpp"�� �����϶�.
// 
//=======================================================================

int main()
{
	ifstream in{ "main.cpp" };
	ofstream out{ "main_upper.cpp" };
	in >> noskipws;
	// ���� ���
	/*char c;

	while (in >> c)
	{
		if (islower(c)) <- ���� üũ ���ص�
		{
			c = toupper(c); <- ���⼭ üũ��
		}
		out << c;
	}*/

	// STL -> while�� for�� ����ϱ� ���� ���̺귯������, Generic Programming
	//  �� �Լ� �� copy() �ݵ�� ���캼 ��
	transform(istreambuf_iterator<char>{in}, {},
		ostreambuf_iterator<char>{out},
		[](char c) {return toupper(c); });

	//save("main.cpp");

}

#endif