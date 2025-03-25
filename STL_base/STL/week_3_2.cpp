
// 2025/03/18 3주 2일
// 많은 수의 자료를 사용하기 - binary I/O
// -> 파일을 binary모드로 열어야 변환이 일어나지 않는다.

//#include "save.h"
// 웬만하면 사용하지 말것.
using namespace std;

#define Prac 4

#if Prac == 1

// ========================================================
// [문제 - 복습] binary mode로 열어 write 함수로 int 10만개를 기록한
// 파일 "int 10만개를 바이너리모드 write함수로 기록.txt"가 있다.
// 읽어서 메모리에 모두 저장하라.
// 메모리에 있는 값 중 가장 작은 것과 가장 큰 것을 찾아 화면에 출력하라.
// 출력된 값을 답지에도 적어라.
// ========================================================
#include <iostream>
#include <array>
#include <fstream>
#include <algorithm>

int main()
{
	// ★ 바이너리모드로 기록된 것을, 바이너리 모드로 읽지 않으면 정보가 왜곡될 가능성이 있다.
	ifstream in("int 10만개를 바이너리모드 write함수로 기록", ios::binary);
	if (not in)
	{
		cout << "파일을 열 수 없습니다." << endl;
		exit(1);
	}
	array<int, 100'000> arr{};

	in.read(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());

	// 최대 최소를 알아내기	위해 max_element, min_element 사용 -> 두번
	// ★ 최대 최소를 알아내기	위해 minmax_element 사용 -> 한번
	int max = {};
	int min = {};
	// ★ structured binding	auto의 사용법 - 가독성 향상
	auto [IterofMin, IterofMax] = minmax_element(arr.begin(), arr.end());
	IterofMin != arr.end() ? min = *IterofMin : min = 0;
	IterofMax != arr.end() ? max = *IterofMax : max = 0;

	cout << "Max : " << max << endl;
	cout << "Min : " << min << endl;

}

#elif Prac == 2
// 많은 수의 자료를 처리하기 - Dog를 읽고 쓴다, read/write
#include <iostream>
#include <string>
#include <random>
#include <print>
#include <fstream>
#include <array>

// Dog 만마리를 생성하여 파일에 저장(write), 메모리에 읽어와서 처리(정렬)

// 변동 될 가능성이 없는 경우에는 무조건 array를 사용하자. (inplace_vector가 나올 시(c++26) 고려할 것)

// =======================================================================
// [문제] class Dog 객체 10만개를 binary mode로 연 파일"Dog 10만 마리" 에 저장하였다.
// 객체 크기 그대로 write함수를 사용하여 저장하였다. 
// =======================================================================
// class 를 작성할 때는 중괄호를 클래스 이름 옆에 작성
// 40 바이트 - > 32바이트 + int 4바이트

default_random_engine dre{};
uniform_int_distribution<int> uid{ 'a','z' };
class Dog {
public:
	Dog() {		// name(15글자 고정, 임의의 소문자)과 id를 초기화(
		_id = ++_sid;	// 생성시 1씩 증가하는 static 정수
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

	static int _sid;	// padding을 차지함, scope - local, life time - global
};

int Dog::_sid{};	// 초기화

int main()
{
	ofstream out{ "Dog 10만 마리",ios::binary };
	if (not out)
	{
		cout << "파일을 열 수 없습니다." << endl;
		exit(1);
	}
	for (int i = 0; i < 100'000; ++i)
	{
		Dog dog;
		out.write(reinterpret_cast<char*>(&dog), sizeof(Dog));
	}

	// 파일을 읽어서 메모리에 저장
	ifstream in{ "Dog 10만 마리",ios::binary };
	if (not in)
	{
		cout << "파일을 열 수 없습니다." << endl;
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

	// friend는 가장 밑에
	friend ostream& operator<< (ostream& os, const Dog& dog)
	{
		os << "ID : " << dog._id << " , Name : " << dog._name;
		return os;
	}
};
// =======================================================================
// [문제] e-class에서 다운로드 받은 파일 "Dog 10만마리"는 binary mode로 열었고,
// 위에 적은 class Dog를 스트림의 write함수를 사용하여 메모리 그대로 10만개 저장하였다.
// Dog 객체 10만개를 메모리에 저장하라.
// 가장 마지막 객체의 정보를 화면에 출력하라.
// =======================================================================

// 1 .전역 변수 ver
array<Dog, 100'000> Dogs;

int main()
{
	// 2. array* ver
	// array<Dog, 100'000>* Dogs = new array<Dog,100'000> ;

	ifstream in{ "Dog 10만 마리",ios::binary };
	if (not in)
	{
		cout << "파일을 열 수 없습니다." << endl;
		return 1;
	}


	// 1 .전역 변수 ver
	in.read(reinterpret_cast<char*>(Dogs.data()), sizeof(Dogs));
	// 2. array* ver
	//in.read(reinterpret_cast<char*>(Dogs), sizeof(Dog) * (*Dogs).size());


	// 1 .전역 변수 ver
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
// [문제]e-class에서 다운로드 받은 파일 "Dog 10만마리"는 binary mode로 열었고,
// 위에 적은 class Dog를 스트림의 write함수를 사용하여 메모리 그대로 10만개 저장하였다.
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

	// friend는 가장 밑에
	friend ostream& operator<< (ostream& os, const Dog& dog)
	{
		os << "ID : " << dog._id << " , Name : " << dog._name;
		return os;
	}
	
	// [문제1] 해결방안
	friend istream& operator>> (istream& is,  Dog& dog)
	{
		is.read(reinterpret_cast<char*>(&dog), sizeof(Dog));
		return is;
	}
};
array<Dog, 100'000> Dogs;

int main()
{
	ifstream in{"Dog 10만 마리",ios::binary };
	if (not in)
	{
		cout << "파일을 열 수 없습니다." << endl;
		return 1;
	}


	// [문제1] 다음 코드가 수정없이 실행되도록 필요한 코드를 class Dog에 추가하라.
	for (Dog& dog : Dogs)
	{
		in >> dog;
	}
	cout << Dogs.back();
}

// 정리
// 1. 파일에는 모드가 있다. -> text mode, binary mode
// 2. 파일의 I/O level에는 2가지가 있다. -> low level(read(),write() 함수로 속도 우수), high level(<<, >> 함수 속에서 다양한 코딩)
// 3. 따라서 textmode로 저장시 high level로 저장하고, binary mode로 저장시 low level로 저장하는 것이 좋다.
// 4. 파일에 저장할 때는 binary mode로 저장하는 것이 좋다. (용량 측면)

#elif Prac == 5
// 문제 형식
// 
#include <iostream>

// ======================================================================
//[문제]
//=======================================================================

int main()
{

}
#endif