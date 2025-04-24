#define Prac 5
// �ڡڡڽ��� == 8�� 2��, 4�� 24��(30��) �ڽ��� ��ҡ�: E��320ȣ
// ������ 4~5����
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
//	- inplace_vector:  ��Ÿ�ӿ����� ������ �����Ǵ� vector
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
// 1. Sequence Containers
//		array<T,N>
//		vector<T> - dynamic(run - time) array
// 
// [�̹� ����]
// 
//
//	

#include "STRING.h"
using namespace std;

#if Prac == 1
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


// =======================================================================
//[����] Ű���忡�� �Է��� �ܾ ���������� ������ �� ����϶�.
// - > �뷮�� ������ �ð��� �������� �ʱ� ������ dynamic�޸𸮸� Ȱ���Ͽ� �ذ��Ѵ�.
//========================================================================

int main()
{
	// ����Է��۾��� ���� Ű���忡�� �о���� �ǹ�
	vector<std::string> v{ istream_iterator<string>{cin},{} };			// Ű���� �Է� ����/��
	

	// [����] �̰� �� ���ĵǴ°�?
	// 1. v.begin()���κ��� ����(Ÿ��, �����ּ� ��)�� ����
	// 2. std::string�� �񱳿����� operator<�� �⺻������ ������ (���� ��)
	// �̿� ���� <�� ����ϴ� sort�Լ��� ���� �⺻ ������ �����ϰ� �ȴ�.
	
	sort(v.begin(), v.end());

	for (const std::string& str : v)
	{
		cout << str << endl;
	}

}

#elif Prac == 2
#include <iostream>
#include <vector>


// =======================================================================
// [����] vector�� ��� �޸𸮸� �����ϴ°�?
//========================================================================


int main()
{
	// �����ϸ� STL���� for������ ���� ���̱�
	vector<int> v;
	v.reserve(10);

	for(int i = 0; i < 10; ++i) {

		cout << "--------------------------------" << endl;
		cout << "���� ���� - " << v.size() << endl;
		cout << "�뷮	  - " << v.capacity() << endl;
		cout << "�޸�	  - " << v.data() << endl;

		// ���� ������Ʈ v �� ���ÿ� ����
		// v�� ��, �������
		// 1. size		(8byte)				== 0
		// 2. capacity	(8byte)				== 0
		// 3. data		(8byte - pointer)	== nullptr (���� NULL�� �ƴ�)

		//https://en.cppreference.com/w/cpp/container/vector/push_back
		v.push_back(i);
		// push_back�� ��ȭ�� size()�� old capacity���� ũ�ٸ�, �޸� ���Ҵ� �ǽ�
		// �̿� ���� ��� ���ͷ����Ϳ�(end()����) ������ ��ȿȭ ��

		// v�� ����
		// size			0 -> 1
		// capacity		0 -> 1
		// data			free-store�� ��򰡸� ����Ű�� 8byte ptr�� �Ҵ�
		// - *data = 1 (�̵� �Ҵ� �����ڿ� ����)

		//cout << "���Ҹ� �� �� �߰��� ���� " << endl;
		cout << endl;
	}
}



#elif Prac == 3
#include <iostream>
#include <vector>

// =======================================================================
//[����]vector�� �޸𸮸� ���Ҵ� �ϴ� ������ ���
//========================================================================

int main()
{
	// visual studio������ vector capacity�� 50%�� �ø�
	// ������ 2�辿 �ø�
	// ȿ�������δ� ó���� ���� �÷ȴٰ�, �ø��� �뷮�� ���� ���� ����
	vector<int> v;
	size_t old = v.capacity();
	for (int i = 0; i < 1000000; ++i) {
		if (v.capacity() != old)
		{
			/*cout << "���� �� - " << v.size() << endl;*/
			cout << "�뷮	 -" << v.capacity() << endl;
			old = v.capacity();
		}
		v.push_back(i);
	}


}


#elif Prac == 4
#include <vector>
#include <iostream>


// =======================================================================
//[����]
//========================================================================
bool extern inspect;
int main()
{
	inspect = true;
	vector<STRING> v;
	v.reserve(100);	// ���� �� �����ؼ� reserve�ϴ°� �����ϴ�.
	// STACK - v�� ���α���
	// v [0] [0] [nullptr]

	//v.push_back(STRING{ "12345" });
	//v.push_back("12345");	// �̸����� ��ü�� ������
	// ���ڸ� �ѱ� �� �����Ϸ��� �̷��� �Ǵ�
	// v.push_back(move(STRING{ "12345" }));
	// v.push_back(static_cast<STRING&&>(STRING{ "12345" }));
	
	//const STRING& s = v.back();
	// �̸����� STRING ��ü ���� [size:5] [ptr] [id:1] ���� free-store�� 5���� �� �޸𸮸� ����� �װ� pointing
	// []�� "1,2,3,4,5" ä��
	// push_back �ǽ�
	// capacity�� ���� ����, 24����Ʈ �� ���ο� ������� ����
	// copy(copy constructor)�ؼ� v�� ���δ�
	// v�� ����Ű�� ���� [size:5] [ptr:"1,2,3,4,5"] [id:2]
	// �̸����� ��ü�� xvalue, �̰� �ӽð�ürvalue�� �������� �ν���, copy�� �ƴ� move construction�� ����
	
	// �޸𸮰� �̻簡�� ������ vector���� ���� ���ǵǴ� ����
	// push_back�� armortized O(1), ������ O(1)�� �ƴ�
	// vector�� ���Ҽ��� �����ؼ� v.reserve(); ��Ű��
	// 
	// dynamic ������ run-time�� ���ڰ� �����Ǵ� ���
	// => inplace_vector - ����ÿ� ũ�⿡ �������� �Ͼ�� ���� ����

	// ������ �׸��׸���
	// stack �ּҴ� ���α׷��Ӱ� ���� ��Ұ� �ƴ� ������ �� �����Ǵ� ��ü - �׷��� �̸����� ���� ������ ����
	// baseoffset�� ����������, code���忡���� �����Ǿ� ����
	// 
	// 
	// freestore�� ��쿡�� �ּҰ� ������ �� �����ϱ� �̸��� ������ ���� = ptr�� ����
	// freestore�� �ִ� ��ü�� �׻� ���� �����ؾ� �� - xvalue�� �Ǿ �� ��
	// ��? delete������ �ݵ�� ���־�� �ϱ� ����
	// vector���� deque�� ���� ū �ִ� �뷮�� ���� �� �ִ� ����
	// vector�� contiguous �޸𸮱� ������ �ݵ�� �̾����־�� ��
	// deque�� linkedlist�� �����ϱ� ������ �޸𸮰� �̾��� ���� �ʿ� x
	// deque : vector�� list�� �߰�
	// vectoró�� v[i]�� ���� "���� �׼���"�� ����������, �� �ӵ��� ������ ����
	

	
	// [emplace_back]
	// �߸��� ��� :
	//v.emplace_back(STRING{"12345" }); // STRING{"12345"}�� Stack�� ������
	// 
	// �̸����� ��ü : [size:5] [id:1] [ptr] -> "12345"
	// �ý��ۿ� ��û�ϴ� �۾��� ���ӿ��� ����ؼ� �� �ȴ�.(new ��)
	// -> �ð��� �󸶳� �ɸ� �� ��, 
	// ���� �޸𸮸� �����Ӱ�, inplace vector���, Ȥ�� operator new()�� ���ڵ��Ͽ� memory pool�� ������..?

	// v : [size:0] [1] [ptr] -> �̵������ڿ� ���� ä������ free-store �޸� :
	//		 [size:5] [id:2] [ptr] -> "12345"
	// ���ݱ����� ������ push_back�� ����

	// emplace_back,
	// �̵������ڷκ��� �ٷ� free-store�� �޸𸮿� ���� ä��
	// �̸����� ��ü �޸𸮰� ���ÿ� �����ż�  �̵������ڰ� ����ǳ�,
	// vector�� ���� �޸𸮰� free-store�� �����ż� �����ڰ� ����ǳ��� ����?
	// �޸� ��ġ�� �����Ϸ��� �����ϴ� ���̴�. �̸� �����ϴ� ���� emplace_back?
	// STRING("12345")���� �Ѱ��ִ� ������this�� ���� free-store�� ��Ҹ� �ȴ�
	// ��ġ�� ���� ����
	
	// emplace_back�� �� ����, ��ü�� ��������� �ڵ带 ��� �� �ȴ�.
	// ���(����)�� ����.

	cout << "push_back_copy" << endl;
	STRING d = "12345";
	v.push_back(d);

	cout << "push_back_move" << endl;
	v.push_back(std::move(d));	// d�� �̵���, d�� �� �̻� ��� �Ұ�

	cout << "push_back_move_xvalue" << endl;
	v.push_back("12345");	// d�� �̵���, d�� �� �̻� ��� �Ұ�

	cout << "emplace_back" << endl;
	v.emplace_back("12345");
	
	cout << "main end" << endl;
	
	
	

	int a = 0;
}


#elif Prac == 5
#include <iostream>
#include <utility>

// =======================================================================
//[����] perfect forwarding
// 
//lvalue(Left Value)
//�̸��� �ּҸ� ���� ��ü
//
//���� �������� ���ʿ� �� �� �ִ� ǥ����
//
//�Լ� ȣ�� �Ŀ��� ��� �����ϴ� ��ü*/
//
//
//rvalue(Right Value)
//	�ӽ� ��ü
//
//	�̸� ���� ��ü
//
//	�ּҰ� ���� ��ü*/
//========================================================================




void process(int& lval) {
	std::cout << "L-value reference" << std::endl;
}

void process(int&& rval) {
	std::cout << "R-value reference" << std::endl;
}

template<typename T>
void forwarder(T&& arg) {
	// std::forward�� ����Ͽ� arg�� ���� value category ����
	process(std::forward<T>(arg));
}

int main() {
	int x = 10;
	forwarder(x);    // x�� lvalue, "L-value reference" ���
	forwarder(10);   // 10�� rvalue, "R-value reference" ���
	return 0;
}



#endif