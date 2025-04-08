#define Prac 1
// �ڡڡڽ��� == 8�� 2��, 4�� 24��(30��), ���� == (30��) - 4�� 10�� ����

// ���� ����	
// STRING - std::string�� ������ Ŭ����, STL ǥ�� �����̳ʰ� �ǵ���...
// C++ ���
// 1. OOPL(Objected Oriented Programming Language)	: Ư�� �ڷ������� ���� Coding
// 2. Generic PL (Programming Language)				: �ڷ����� ������ �ڷᱸ���� �˰����� Coding (Template)
// 
// ���� Modeling �ϰ��� �Ѵ�.
// -> 
// Class Star {
// private:
// [�޸� ��û��]
// };
// �̸� ���� Compiler�� �Ʒ��� �ؼ� ������ (���� ������ �ʾƵ�) (���� ������ ����)
// Star a; 
// Star aa[100];
// new Star[];
// Star b = a;
// �޸𸮸� ����� ������ Compiler�� �ְ�, ���� �� ��� ���� ���ΰ��� �����ڿ��� �ڵ��Ѵ�.
// Star() {}	�Ҹ��ڵ� special�� �Լ��̱� ������ �⺻ �Ҹ��ڰ� �����ȴ�.
// 
// ������ Star���� ����(�޸�,Resource-�ڿ�)�� ������ ���,
// �����ڿ��� �и��� Star() {new ~~} �� ���� ���̴�..
// Star = a
// Star b = a �� �ϴ� ��� ���� ������ �����ε��� �ʿ��ϴ�. ���� �Ҵ� �����ڵ� ��Ʈ�� �����ε��Ѵ�.
// 
// �̹� ����
// 

#include <string>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;


class STRING {
	// ���� ������ (Access Modifier)
public:
	STRING(const char* str)
		:_len{ strlen(str) }
	{		// []�� -> *�� collapsing 
		_p.reset();		// lvalue : ����� ���� �� -> location value (�޸�)
		_p = make_unique<char[]>(_len);

		memcpy(_p.get(), str, _len);		// DMA (Direct / Dynamic Memory Accesse)
		// p.get() : Ȯ���� �޸� �ּ�
		// p.reset() : �޸� ����
		// p.release() : �޸� ��ȯ
	}

	size_t size() {
		return _len;
	}



private:
	size_t _len{};
	unique_ptr<char[]> _p;		// ������ �̹� ���⼭ ���� ��
	//vector<char> _string;




	friend ostream& operator<<(ostream& os, const STRING& str) {
		// nullĳ���͸� �������� ���� �ʴ� ��쿡�� for���� ���..
		for (int i = 0; i < str._len; ++i)
			os << str._p[i];
		return os;
	}
};

#if Prac == 1
#include <iostream>

class Star {
public:
	Star() { _child = nullptr; }
	~Star() {}
public:
	Star* _child;
};

int main()
{
	Star a;
	a._child = new Star();
}

#elif Prac == 2



// =======================================================================
//[����] �Ʒ� �ڵ��� ���������� ����ǵ��� ����
//========================================================================

int main()
{
	STRING s{ "std::string�� ������ Ŭ����" };

	cout << s.size() << endl; // s�� Ȯ���� �ڿ��� ����Ʈ ��

	cout << s << endl;
}


#elif Prac == 3



// =======================================================================
//[����]
//========================================================================

int main()
{


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