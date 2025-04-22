#define Prac 7
// �ڡڡڽ��� == 8�� 2��, 4�� 24��(30��) �ڽ��� ��ҡ�: E��320ȣ
// ������ 4~5����, 1�ð�
// �������� ���� ������ ���� ����, ��� �ڷ� ���, ������ 8�� 1�ϱ���
// 
// ���� == (30��) - 4�� 10�� ����
// 5�� 6��(ȭ) -> 6�� 19��(����)
// ======================================����======================================
// STL : �ڷ����� ������ Ŭ������ �Լ��� ������� �ۼ�, Ŭ������ ���� �ڷᱸ���� ����, �Լ��� ���� �˰����� ����
// �ݺ��� ������ ������ ���� �ð����⵵�� ����..?(iterator design pattern) - (GOF ������ ���� ���� ����)
// [�ܾ� ����]
// Container : �԰�ȭ��(������) ���Ҹ� ��� �ڷᱸ��(Homogeneouse data type)
// Algorithm : ����, Ž��, �׷��� �˰��� 
// Adapter : Container adapter�� ���� �����̳ʸ� ����(modify, adapt)�Ͽ� Ư�� �������̽�(���)���� �����ϵ��� ���� �����̳ʸ� �ǹ��Ѵ�
//	�����̳� ����ʹ� vector, list, deque �� ���� �����̳�(underlying container)�� �������̽��� �����Ͽ� Ư�� ��ɸ��� �����ϰԲ� ������� �����̳� ����ü�̴�.
// Predicates: Callable Type, bool���� return�ϴ� Callable Type
// FunctionObject: Function call ���۷�����[()]�� �����ε��� Ŭ���� ��ü
// Concepts : ���� �Ұ� template�� ����缭 ����� �������� �ذ��ϱ� ���� ��(C++ 20 ���� �ٽ� ����)
// � Ÿ���� �������ϴ� ������ ������ �ֱ� ���� ���� ���� Concept��� �� �� �ִ�.
// Ranges: Concept�� �Բ� �̿��Ͽ� ���̺귯���� ���� ������		
// //https://velog.io/@minsu_lighting--/C20-Range
// Span : contiguous �޸𸮸� ����, ������ �ٷ�� ���� ����� Ŭ����(views)(String view�� ���� �޸� ���� ����)
//
// {STL Components}
// STL�� ������Ʈ(�����̳�[�ڷᱸ��], �ݺ���, �˰���)�� ����� ������
// 
// [�����̳�(�ڷᱸ��)]
// 1. Sequence Containers : Contiguous : [array, vector], deque, forward_list, list
// ���ϴ� ��ġ�� ���� Access�ؼ� read/write �ص� ���� ���� Container
//	- array : ���� ������ ���� �������� ���� - ���� ���� �Ұ���
//  - vector : data�� �������� �÷��� �� �ִ� �ڷᱸ��
//	- inplace_vector:
//	- hive : 
//  - deque : front/back���� ���Ҹ� �����ϱ� �ſ� ������ ����
// 2. Associative Containers : Key - Value�� assosiation�� (set, map)
//	Ű ���� ���� ������ �� �־�� ��
//	- set : key �� value�� ����
//	- map : key �� ���� value�� ����
// 3. Unordered Associative Containers: Hash table�� ���� ������ ���� ���� Associative Containers
//	���Ҹ� ���� ���� ã�� Container��, �޸𸮸� ����ؼ� �ӵ��� ����.
// 
// Container��?
// 	C++ǥ�� N4917 ��ŷ �巡��Ʈ������ �ǹ�:
// Containers are objects that store other objects.
// "�ٸ� ��ü�� ���� �� �ִ� ��ü", ���� ���� ���� �� �ִٴ� ���� �߿���
// 
// C++ Container library: ���� ������ �� �ֵ��� �Ϲ����� ���ø��� �˰����� ��Ƴ��� ��
//
// [���� ����]
// 
// 
// [�̹� ����]
// array<T, N>
// vector<T>
// deque<T> - vector���� �� ���� ���Ҹ� ���� �� �ִ�.
//
//	

#include "STRING.h"
using namespace std;
extern bool inspect;
#if Prac == 1
#include <vector>


// =======================================================================
// [����]
//========================================================================

int main()
{
	// ������ ����
	vector<STRING> v{};
	//v.reserve(1'000);
	// v�� �ִ� �󸶸�ŭ�� ���Ҹ� ������ ������ �����Ѵ�.
	// �׸��� ������ ��ŭ ������ Ȯ���Ѵ� -> reserve
	// 24����Ʈ �޸� v�� �ȿ���
	// size : 0
	// capacity : 1000
	// STRING(24b) 1000�� ��ŭ�� �޸��� �ּ�
	// 1. ���� ���� �þ �� �ִ� ��Ȳ���� �����
	// 2. capacity�� ���������� size�� ������ �� �ִ� ��� -> inplace_vector





}

#elif Prac == 2
#include <iostream>
#include <fstream>
#include <array>



// =======================================================================
// [����]"week_8_1"������ �ҹ��� ���ĺ� ��(freequency)�� ������ ���� ����϶�.
// ex)
// a -> 10
// b -> 3
// ...
// z -> 0 
// [�ذ�]
// array�� ����. (���ĺ��� �� ���� ������ �ֱ� ����)
//========================================================================


int main()
{
	// �׻� {}�� ���� default �ʱ�ȭ�� ���� ����
	array<int, 26> a{};
	//for (int n : a)
	//	cout << n << " ";
	//cout << endl;

	ifstream in("week_8_1.cpp");

	char c;
	while (in >> c)
	{
		if (islower(c))
		{
			a[c - 'a']++;
		}
	}

	for (int i = 0; i < a.size(); ++i)
		cout << static_cast<char>(i + 'a') << " -> " << a[i] << endl;;
}



#elif Prac == 3
#include <iostream>
#include <vector>
#include <algorithm>

// =======================================================================
//[����] v���� 3�� �����϶�
//========================================================================

int main()
{
	// remove�� new end itrerator�� ��ȯ
	// �� �̷��� �Ǿ� ������?
	// �˰��� ��ü�� �ڷᱸ���� ���� �޸𸮿��� ���� ��������,
	// �ڷᱸ�� ��ü(��� ����) ��� ������ �� ���� 
	// - �ڷᱸ�� ���� ó�� ������ �����ϱ� ����(vector�� ���� ��� ��)
	// �׷��� new end �ݺ��ڸ� ��ȯ�ϰ� �װ� �˾Ƽ� ó���ϵ��� �ñ��.

	vector<int> v{ 1, 2, 3, 3, 3,4, 5,6,7 };
	// idiom
	v.erase(remove(v.begin(), v.end(), 3), v.end());
	// ==auto new_end =  remove(v.begin(), v.end(), 3)
	// v.erase(new_end, v.end())

	// ���� ���� ����� �����ϰ� �Ͽ� vector���� �Լ��� �����Ѵ�.
	// �ٵ� �̷� �� ��������� ��Ģ�� ���� ���ϰ� ǥ���ȴ�.
	// erase(v, 3);

	// [����] v���� Ȧ���� �����϶�
	// remove���� ������ �Ǵ�(predicate�� ���)�ϴ� ���, remove_if�� ����Ѵ�.

	// idiom
	v.erase(remove_if(v.begin(), v.end(), [](int a)
		{
			return a & 1;
		}), v.end());

	// == 
	/*erase_if(v, [](int a)
		{
			return a & 1;
		});*/

	for (int a : v)
	{
		cout << a << " ";
	}
}


#elif Prac == 4
#include <iostream>
#include <vector>


// =======================================================================
//[����] v����"3"�� �����϶�
//========================================================================

int main()
{
	vector<STRING> v{ "11","22","33","3","44","55" };

	//v.erase(remove(v.begin(), v.end(), "3"));
	erase(v, "3");


	for (const STRING& str : v) {
		cout << str << endl;
	}
	cout << "size : " << v.size() << endl;
}


#elif Prac == 5
#include <iostream>
#include <vector>

extern bool inspect;
// =======================================================================
//[����] v���� "2" �� "4"���̿� "3"�� �����϶�.
//========================================================================

int main()
{

	vector<STRING> v{ "1","2","4","5" };

	inspect = true;
	// ������ insert�� ���Ǵ� ������ �ִٸ�, �װ� �߸��� ¥���̴�.
	v.insert(v.begin() + 2, "3");
	inspect = false;
	for (const STRING& s : v)
	{
		cout << s << endl;
	}

}

#elif Prac == 6
#include <iostream>
#include <list>

// =======================================================================
//[����] l���� "3"�� �����϶� - list ver / ���Ŵ� ���� �����ϱ�
//========================================================================

int main()
{

	//list<STRING> l{ "1","2","3","4","5" };
	list<STRING> l{ "1","2","4","5" };

	STRING temp{ "333" };

	inspect = true;
	// ������ insert�� ���Ǵ� ������ �ִٸ�, �װ� �߸��� ¥���̴�.
	//remove(l.begin(), l.end(), "3");
	//l.insert(++ ++l.begin(), "3");	// �ӽ� ��ü ����, �̵� ������ ����
	//l.insert(++++l.begin(), temp);	// ���� ������ ����
	l.emplace(++++l.begin(), "3");		// emplace, ���ڸ��� �ٷ� ������ ����
	inspect = false;


	for (const STRING& s : l)
	{
		cout << s << endl;
	}

}

#elif Prac == 7
#include <iostream>
#include <deque>

// =======================================================================
//[����] 
//========================================================================

int main()
{
	inspect = true;
	deque<STRING> d{ "1","22","333","4444", "55555" };
	inspect = false;

	
	inspect = true;
	d.emplace_front("0");
	inspect = false;
	
	d.push_front("-1");
	// ���� ũ��
	//cout << "VS���� x64����� �� deque�� ũ�� - " << sizeof(d) << endl;

	//for (int i = 0; i < d.size(); ++i)
	//{
	//	// [] random_access�� �����ϴ�.
	//	cout << &d[i] << endl;
	//}

	
	for (const STRING& s : d)
	{
		cout << &s << endl;
	}
	

}



#endif