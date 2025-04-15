#define Prac 3
// �ڡڡڽ��� == 8�� 2��, 4�� 24��(30��), ���� == (30��) - 4�� 10�� ����
// 5�� 6��(ȭ) -> 6�� 19��(����)
// =================���� ����=================
// �̵� ������ �̵��Ҵ翬���� �ε�
// 
// =================�̹� ����=================
// STL : �ڷ����� ������ Ŭ������ �Լ��� ������� �ۼ�, Ŭ������ ���� �ڷᱸ���� ����, �Լ��� ���� �˰����� ����
// �ݺ��� ������ ������ ���� �ð����⵵�� ����..?(iterator design pattern) - (GOF ������ ���� ���� ����)
// [�ܾ� ����]
// Container : �԰�ȭ��(������) ���Ҹ� ��� �ڷᱸ��(Homogeneouse data type)
// Algorithm : ����, Ž��, �׷��� �˰��� 
// Adaptor : ������ �����̳� ���� -> ���ο� �ڷᱸ���� ����� �� ��(�ڷᱸ���� �ݺ���, �˰��� ��� ���� ����)
// Predicates: Callable Type, bool���� return�ϴ� Callable Type
// FunctionObject: Function call ���۷�����[()]�� �����ε��� Ŭ���� ��ü
// Concepts : ���� �Ұ� template�� ����缭 ����� �������� �ذ��ϱ� ���� ��(C++ 20 ���� �ٽ� ����)
// Ranges: Concept�� �Բ� �̿��Ͽ� ���̺귯���� ���� ������//ranges::sort() �ľ��غ���
// Span : Contiguous �޸𸮸� ����, ������ �ٷ�� ���� ����� Ŭ����(views)(String view�� ���� �޸� ���� ����)
//
// {STL Components
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
// C++ Container library: ���� ������ �� �ֵ��� �Ϲ����� ���ø��� �˰����� ��Ƴ��� ��
//	C++ǥ�� N4917 ��ŷ �巡��Ʈ������ �ǹ�:
// Containers are objects that store other objects.
// "�ٸ� ��ü�� ���� �� �ִ� ��ü", ���� ���� ���� �� �ִٴ� ���� �߿���
// 1. Sequence Containers
//		array<T,N>
//		vector<T>
//
//	
#include "STRING.h"
using namespace std;

#if Prac == 1
#include <iostream>
#include <ranges>	// �ֽ� ����
#include <algorithm>
#include <array>

// =======================================================================
//[Array<T,N>] C++  reference ����
// std::array is a container that encapsulates fixed size arrays.
// There is a special case for a zero-length array (N == 0).
//  - In that case, array.begin() == array.end()
// 
// Iterator invalidation(�ݺ��� ��ȿȭ)
// ������ ������ ���� ������, �ݺ��ڰ� ��ȿȭ�� �� ����.(���� ��)
// 
// ���� ��� Ÿ���� ����
// begin(), cbegin() - constant
// 
//========================================================================
int main()
{
	/*array<int, 0> a1;
	cout << "is empty? - " << boolalpha << a1.empty() << endl;
	cout << typeid(array<int, 0>::value_type).name();*/

	array<int, 5> a2{ 1,2,3,4,5 };	// int a[5]�� struct�� ������
	// �� �����ߴ°�? �޸� ��ŷ�� �ʹ� ���� ������
	for (int i = -10; i < 10; ++i)
		cout << a2[i] << endl;	// ������ ������, C++Ư���� �޸𸮸� ������ �� �ֵ��� �س��� ����

	START:
	cout << "�޸� ���? ";
	int num;
	cin >> num;

	// STL�� ���� �ڵ带 ���� �ʴ� ���� ��ǥ�� �Ѵ�, �ӵ� �켱.
	try
	{
		cout << a2.at(num);	//�ڡڡڡھ��� �迭�� �˻��ϴ� ��ɡڡڡڡ�
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
		cout << "�ٽ� �Է��Ͻʽÿ�" << endl;
		goto START;
	}
}

#elif Prac == 2
#include <iostream>
#include <vector>

// =======================================================================
//[vector<T>] dynamic(run-time) array , ���� �迭
//========================================================================

vector<int>v2(6, 2);
int main()
{
	vector<int>* p = new vector<int>(6, 2);

	vector<int>v(6, 2);
	// v�� ��ü�� �˾ƺ���
	cout << "v�� ũ�� : " << sizeof(v) << endl;		// int* p, size, capacity = 24bytes, �����δ� �̷��� ������, �̷��� �˰� �־ �ȴ�.
	cout << "v�� �ּ� : " << addressof(v) << endl;
	cout << "v�� Ÿ�� : " << typeid(v).name() << endl;
	
	// v2�� ��ü�� �˾ƺ���
	cout << "v2�� ũ�� : " << sizeof(v2) << endl;
	cout << "v2�� �ּ� : " << addressof(v2) << endl;
	cout << "v2�� Ÿ�� : " << typeid(v2).name() << endl;

	// p ..
	cout << "p�� ũ�� : " << sizeof(*p) << endl;
	cout << "p�� �ּ� : " << addressof(*p) << endl;
	cout << "p�� Ÿ�� : " << typeid(*p).name() << endl;
	// {} : initiallizer-list
	/*for (int num : {1, 2, 3, 4, 5})
		cout << num << endl;*/


	// �˰����� generic�ϱ� ������,
	// �ڷᱸ������ ����ϴ� �Ϲ����� �ݺ��ڸ� ����Ͽ� access
	// �ݺ��ڴ� != end(), ++, *���� ���۷����͸� �����ϱ� ������ generic�ϰ� �˰����� ����� �� �ִ�.
	/*for (vector<int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << endl;
	}*/
	// ���並 ����ϴ� ���� ������, &�� ���� �ʿ�� ����, ���ʿ� �޸𸮰� ����
	for (auto i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << endl;
	}

	// c�� �ٿ��� �б���� ������ ���� ǥ���ϴ� ���� ������
	for (auto i = v.cbegin(); i != v.cend(); ++i)
	{
		cout << *i << endl;
		// *i = 5; error, �б⸸ ����
	}

	// rŰ����� �ݺ��� �Ųٷ� ��������
	for (auto i = v.crbegin(); i != v.crend(); ++i)
	{
		cout << *i << endl;
	}
}



#elif Prac == 3
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// =======================================================================
//[����]Ű���忡�� �Է��� ���� ���� �հ�� ����� ����Ͻÿ�
// - ������ �����Ǿ� ���� ���� (vector�� ���)
//========================================================================

int main()
{
	
	cout << "������ �Է��Ͻÿ�. " << endl;

	// vector�� Ű���� �Էº��� ����������
	vector<int> v(istream_iterator<int>{cin}, {});

	long long sum = accumulate(v.begin(), v.end(), 0LL);
	sum = reduce(v.begin(), v.end(), 0LL);
	cout << "�հ� - " << sum;
	//cout << 
	cout << "��� - " << static_cast<double>(sum / v.size());


}


#elif Prac == 4



// =======================================================================
//[����]
//========================================================================

int main()
{



}


#elif Prac == 5



// =======================================================================
//[����]
//========================================================================

int main()
{


}


#endif