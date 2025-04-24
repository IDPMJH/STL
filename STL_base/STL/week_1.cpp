// ---------------------------------------------------------------------
//			2025-1 STL ��910��910 3�� 13�� ����� (2�� 1��)
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Generic Programming�� �ٽ�Ű���� - template 
// ---------------------------------------------------------------------


// C++ PL
// 1. Procedural P/L
// 2. Object Oriented P/L -> virtual 
// 3. Generic P/L -> template
// 4. Meta P/L
// 5. Functional P/L

#include <iostream>
#include "save.h"

using namespace std;
// [����] main�� �������� �ʰ� �ǵ���� ����ǰ� �ڵ��϶�.
// Dog�� Class�� �ڵ��Ͻÿ�.

// �����Ϸ��� ����

class Dog {
public:
	Dog() = default;
	explicit Dog(const int _n) :num(_n) {}
	Dog(const Dog& other) :num(other.num) {}
	
	friend ostream& operator << (ostream& out, const Dog& dog) { return out << dog.num; }
	// operator int() { return num; }
	// friend istream& operator >> (istream& in, Dog& dog) { return in >> dog; }

private:
	int num;	// 4 + 4
	double d;	// 8

};
// void change(int& a, int& b);

// Ambiguous
// void change(Dog, Dog);
// void change(Dog& a, Dog& b); // ->�Լ��� Code segment�� ���., �޸� ���� ���� == �Լ��̸�(���� - jmp)

// [����] ����ü �� ���� change�� ����� �ǰڴ�?
// -> C++���� ����ü �ڷ����� �� ���ϱ�? : ����
// -> �ڵ������ �ڵ�ȭ����
// -> template

// Stack
// Free Store
// Code
// template-> �ҽ��ڵ带 �����ϴ� �ڵ� 



// cpp, header �и� ���� 
// template�ڵ�� �ݵ�� cpp�����Ǿ�� ��
// cpp�ڵ尡 �־�ߵ�

// ���ø��� ����� ���Ǹ� ���ÿ� �ؾ���.
// �˰���
// Generic ���α׷��� - �ڷ����� ���ֹ����ʴ�,
template<class T> - 3����
void change(T& a, T& b)
{
	T temp{ a };
	a = b;
	b = temp;
}
// �˰����Լ��� ���� ���ø�
// �ڷᱸ���� ��������.

// ���ø� Ư��ȭ - 2����
template<class Dog>
void change(Dog& a, Dog& b)
{

	Dog temp{ a };
	a = b;
	b = temp;
}

// �Ϲ� �Լ� - 1����
void change(Dog& a, Dog& b)
{
	Dog temp{ a };
	a = b;
	b = temp;
}

// ------------
int main()
// ------------
{
	{
		Dog a{ 1 }, b{ 2 };
		change(a, b);	// ����ü � �Լ��� ȣ���ϴ� ���ΰ�? 

		// �켱���� Ž��
		// 1. �Ϲ� �Լ� Dog Ÿ��
		// 2. ���ø� Ư��ȭ DogŸ��
		// 3. �Ϲ� ���ø�
		// // �Ʒ��� �� �� ã�ƺ��� �ҵ�
		// 1. change(Dog, Dog);
		// 2. change(Dog& Dog&);
		// 3. �����Ϸ��� ���� ���� �� ������? -> template
		
		std::cout << a << "," << b << std::endl; // [���] 2, 1
	}

	//{
	//	int a{ 1 }, b{ 2 };
	//	change(a, b);
	//	std::cout << a << "," << b << std::endl; // [���] 2, 1
	//}

	// name mangling - �Լ� �̸��� ������ ���ڰ� �ٸ� �� ��� �����ϳ���? �����Ϸ��� ���� �̸��� ������
	//-> change1, change2

	//save("main.cpp");
}

//
//void change(int& a, int& b)
//{
//	int temp{ a };
//	a = b;
//	b = temp;
//	// swap(a, b);
//}
//
//void change(Dog& a, Dog& b)
//{
//	Dog temp{ a };
//	a = b;
//	b = temp;
//}

