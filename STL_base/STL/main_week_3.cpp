
// 2025/03/18 3주 1일
// 많은 수의 자료를 사용하기 - binary I/O
// -> 파일을 binary모드로 열어야 변환이 일어나지 않는다.

//#include "save.h"
// 웬만하면 사용하지 말것.
using namespace std;



#define Prac 7

#if Prac == 1
#include <iostream>
#include <bitset>

int main()
{
	// ========================================================
	// [문제] 지난 시간에 int 1000개를 파일에 기록하였다.
	// int 1000개를 저장하기 위해 얼마만큼의 파일 바이트를 사용하였는가? 
	// => 8200byte
	// ========================================================
	// ★★★ 32bit int의 최대 값인 21억 어쩌구까지 파일에 저장하면, 평균 byte 수는?(text mode)



	int num{ 0x01'02'03'04 };

	cout << "16진수 : " << hex << num << endl;
	cout << "10진수 : " << dec << num << endl;
	cout << "2진수  : " << bitset<32>(num) << endl;

	//save("main_week_3.cpp");
}
#elif Prac == 2
// ========================================================
// [문제] 메모리에 저장된 bit를 그대로 파일에 저장할 수 있다.
// -> 저수준 입출력 함수를 사용한다.
// ========================================================
#include <iostream>
#include <array>
#include <numeric>
int main()
{
	// {}(디폴트 생성자)이니셜라이저로 초기화하지 않을 시, 초기화 되지 않음.
	array<int, 1000> arr{};
	// ★★★ 메모리가 붙어 있음(공간적 연속성) - > Contiguous memory
	// 시간적 연속성 -> Continuous time
	// 인자값부터 최대 공간까지 1씩 늘려가며 채우기
	std::iota(arr.begin(), arr.end(), 1);

	for (int num : arr)
		cout << num << " ";

	cout << endl;
}


#elif Prac == 3
#include <iostream>
#include <array>
#include <numeric>
#include <fstream>

// =======================================================================
// [문제] arr의 data를 파일"int 1000개 메모리 그대로"에 기록하라.
// =======================================================================
int main()
{
	// {}(디폴트 생성자)이니셜라이저로 초기화하지 않을 시, 초기화 되지 않음.
	array<int, 1000> arr{};
	// ★★★ 메모리가 붙어 있음(공간적 연속성) - > Contiguous memory
	// 시간적 연속성 -> Continuous time
	// 인자값부터 최대 공간까지 1씩 늘려가며 채우기
	std::iota(arr.begin(), arr.end(), 1);

	//ofstream out{ "int 1000개 메모리 그대로" }; -> mode 설정이 없으면 text mode
	// text mode로 설정 시, 운영체제가 보기 쉽게 해주는 작업을 함
	// 
	ofstream out{ "int 1000개 메모리 그대로", ios::binary };

	out.write(reinterpret_cast<char*>(arr.data()), sizeof(int)*arr.size());
}


#elif Prac == 4

#include <iostream>
#include <array>
#include <numeric>
#include <fstream>
int main()
{
	// [상황] 현재 하나의 int 4바이트는 0A 0A 0A 0A로 이루어져 있다.
	// -> 텍스트 파일로 Windows에서 -> 0A(라인피드),0D(캐리지 리턴)으로 변환

	array<int, 1000> arr{};
	arr.fill(0x0a0a0a0a);

	ofstream out{ "int 1000개 메모리 그대로" };
	out.write(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());
}

#elif Prac == 5

#include <iostream>
#include <fstream>
#include <random>

// main에 넣지 말것 (스택 공간을 매우 많이 차지함)
mt19937 mt{};

int main()
{
	// =======================================================================
	// [문제] 파일 "int 10만개를 바이너리모드 write함수로 기록"
	// 에 10만개의 랜덤 int값을 기록하자.
	// 이 int 값은 메모리 크기 그대로 기록한다.
	// 파일을 bianry mode로 열자
	// =======================================================================

	// 바이너리 모드로 세팅
	ofstream out{ "int 10만개를 바이너리모드 write함수로 기록",ios::binary };

	uniform_int_distribution<int> uid{ numeric_limits<int>::min(),numeric_limits<int>::max()};
	int num{};
	for (int i = 0; i < 10'000; ++i)
	{
		num = uid(mt); // 여기서 초기화 해도 자동 최적화 해주긴 함, 그래도 위에서 초기화하자.
		out.write(reinterpret_cast<char*>(&num), sizeof(int));
	}
}

#elif Prac == 6

#include <iostream>
#include <fstream>
#include <array>
// 변동 될 가능성이 없는 경우에는 무조건 array를 사용하자. (inplace_vector가 나올 시(c++26) 고려할 것)

int main()
{
	// =======================================================================
	// [문제] binary로 열어 기록한 파일 "int 10만개를 바이너리모드 write함수로 기록"에
	// int값 10만개가 메모리 크기 그대로 기록되어 있다. (ostream의 write 함수를 사용)
	// 1. 이 int값 10만개를 읽어서 메모리에 저장하라.
	// 2. 가장 작은 값을 찾아 화면에 출력하라. 화면에 출력한 값도 답지에 적어라.
	// 3. 이 문제를 해결하는 코드를 답지에 적어라.
	// =======================================================================

	// 바이너리 모드로 세팅
	ifstream in{ "int 10만개를 바이너리모드 write함수로 기록",ios::binary };
	
	// 읽을 때 text mode로 열면?
	//ifstream in{ "int 10만개를 바이너리모드 write함수로 기록" };
	if (not in)
		exit(1);

	// 스택 공간 매우 많이 차지	
	array<int, 10'0000> arr{};

	/*for (int& num : arr)
		in.read(reinterpret_cast<char*>(&num), sizeof(int));*/
	in.read(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());

	cout << "가장 작은 값 : " << *min_element(arr.begin(), arr.end()) << endl;
}

#elif Prac == 7
// 많은 수의 자료를 처리하기 - Dog를 읽고 쓴다, read/write
#include <iostream>
#include <string>

class Dog
{
public:
	Dog()
	{
		// 다음 시간에
	}

private:
	string	_name;	// 32
	size_t	_id;	// 8 -> 40 bytes
};

// Dog 만마리를 생성하여 파일에 저장(write), 메모리에 읽어와서 처리(정렬)

// 변동 될 가능성이 없는 경우에는 무조건 array를 사용하자. (inplace_vector가 나올 시(c++26) 고려할 것)

int main()
{
	// =======================================================================
	// [문제] binary로 열어 기록한 파일 "int 10만개를 바이너리모드 write함수로 기록"에
	// int값 10만개가 메모리 크기 그대로 기록되어 있다. (ostream의 write 함수를 사용)
	// 1. 이 int값 10만개를 읽어서 메모리에 저장하라.
	// 2. 가장 작은 값을 찾아 화면에 출력하라. 화면에 출력한 값도 답지에 적어라.
	// 3. 이 문제를 해결하는 코드를 답지에 적어라.
	// =======================================================================

}

#endif