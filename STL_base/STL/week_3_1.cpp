#define Prac 6
const int p = 1;
// 2025/03/18 3주 1일
// 많은 수의 자료를 사용하기 - binary I/O
// -> 파일을 binary모드로 열어야 변환이 일어나지 않는다.

//#include "save.h"
// 
// 웬만하면 사용하지 말것.
using namespace std;






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
	// ★★★ 32bit int의 최대 값인 21억 어쩌구까지 파일에 textmode로 저장하면, 평균 byte 수는?(text mode)
	// -> 평균적으로 10자리 수가 나올 확률이 가장 높음 -> 10자리로 입력한다고 가정 = 10byte
	// unsigned가 아니므로 부호가 50% 확률로 붙음 -> 각 수에 0.5바이트 추가 = 10.5byte
	// 각 수마다 개행 문자를 포함한다면 = 11.5byte
	// 수의 개수 = 1000, 총 byte 수 = 1000 * 11.5 = 11500byte (예상)
	// 
	// 혹은 절반 정도의 나올 확률을 가진 9자리 수를 절반 개수만큼으로 책정하여 계산시, 
	// 10.5byte* 500 + 11.5byte*500 = 11000byte (예상)



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


	//배열 값을 채우는 다양한 방법
	//	1. std::iota
	//	연속된 값으로 배열을 채움(예: 1, 2, 3, …)
	//	이미 사용하신 방법입니다.
	//	2. std::fill / std::fill_n
	//	배열의 모든 값을 동일한 값으로 채움
	//	cpp ->
	//	std::fill(arr.begin(), arr.end(), 42); // 모든 요소를 42로 채움
	//	cpp ->
	//	std::fill_n(arr.begin(), arr.size(), 7); // 모든 요소를 7로 채움
	// 
	//3. std::generate / std::generate_n
	//	함수(람다 등)를 이용해 각 요소를 채움
	//	cpp->
	//	int v = 1;
	//std::generate(arr.begin(), arr.end(), [&v] { return v++; }); // 1, 2, 3, ...
	//std::iota와 유사하지만, 더 복잡한 패턴도 가능

	//	4. for 루프 직접 사용
	//	범용적이며, 원하는 로직을 자유롭게 적용 가능
	//	cpp
	//	for (size_t i = 0; i < arr.size(); ++i)
	//		arr[i] = static_cast<int>(i) + 1;
	// 
	//5. 초기화 리스트(컴파일 타임 상수)
	//	소규모 배열에만 실용적
	//	cpp
	//	std::array<int, 5> arr = { 1, 2, 3, 4, 5 };

	//이 외에도 std::copy, std::transform 등 다양한 표준 알고리즘을 활용하여 배열을 초기화하거나 값을 채울 수 있음
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
	// text mode로 설정 시 운영체제가, 사람이 보기 쉽게 해주는 작업을 함
	// 
	ofstream out{ "int 1000개 메모리 그대로" ,ios::binary };
	// int a = arr.size();  a == 1000 -> 원소의 개수
	// a = sizeof(arr);		a == 4000 -> 배열 자체의 크기

	//out.write(reinterpret_cast<char*>(arr.data()), sizeof(int)*arr.size());
	out.write(reinterpret_cast<char*>(arr.data()), sizeof(arr));
	// arr 배열의 모든 데이터를 바이너리(이진) 형식으로 파일에 저장한다.
	// - arr.data()는 배열의 첫 번째 요소(메모리 시작 주소)를 가리키는 int* 포인터를 반환한다.
	// - reinterpret_cast<char*>(arr.data())는 int* 포인터를 char* 포인터로 변환한다.
	// (이렇게 해야 write()가 바이트 단위로 데이터를 처리할 수 있다).
	// - sizeof(arr)는 배열 전체의 바이트 크기(예: int 1000개면 4000바이트)를 반환한다.
	// - 결과적으로 배열의 모든 메모리 내용을 바이트 단위로 파일에 그대로 기록한다.
	//
	// ※ 주의: 이 방식은 바이너리 파일에만 적합하며, 저장과 읽기 모두 같은 자료형/플랫폼이어야 데이터가 올바르게 복원된다.
	// ※ reinterpret_cast는 포인터 타입 사이의 저수준 변환에 사용되며, 비트 패턴을 그대로 해석한다는 점에 유의해야 한다


	//
	//	텍스트 모드에서 배열 저장 방법
	//		1. 반복문과 출력 연산자(<< ) 사용
	//		cpp
	//#include <fstream>
	//#include <array>
	//
	//		std::array<int, 1000> arr = {/* ... */ };
	//
	//	std::ofstream out("output.txt"); // 텍스트 모드(기본)
	//	for (const int& num : arr) {
	//		out << num << '\n'; // 각 요소를 문자열로 변환 후 한 줄씩 저장
	//	}
	//	out.close();
	//	각 요소를 문자열로 변환하여 한 줄씩 파일에 기록합니다.
	//
	//		'\n'을 붙이면 각 값이 한 줄에 하나씩 저장됩니다.
	//
	//		콤마, 탭 등 다른 구분자를 쓸 수도 있습니다.
}


#elif Prac == 4

#include <iostream>
#include <array>
#include <numeric>
#include <fstream>
int main()
{
	// [상황] 현재 하나의 int 4바이트는 0A 0A 0A 0A로 이루어져 있다.
	// -> 텍스트 파일로 Windows에서 -> 0D(캐리지 리턴),0A(라인피드)으로 변환
	// Windows의 텍스트 모드에서 0A → 0D 0A 변환이 발생했기 때문에 
	// 파일 크기가 4000바이트 → 8000바이트로 증가한 것.
	// 이를 방지하려면 바이너리 모드(std::ios::binary)를 사용하여 변환을 막아야 함.
	// 참고로 EOF(End Of File)는 0x1A로 표현되며, 파일의 크기와는 무관하게 파일의 끝을 나타냄.
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
	// 
	// 파일을 bianry mode로 열자
	// =======================================================================

	// 바이너리 모드로 세팅
	ofstream out{ "int 10만개를 바이너리모드 write함수로 기록",ios::binary };

	uniform_int_distribution<int> uid{ numeric_limits<int>::min(),numeric_limits<int>::max() };
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
		return 1;
	// 스택 공간 매우 많이 차지	
	array<int, 10'0000> arr{};

	/*for (int& num : arr)
		in.read(reinterpret_cast<char*>(&num), sizeof(int));*/
	//in.read(reinterpret_cast<char*>(arr.data()), sizeof(int) * arr.size());
	in.read(reinterpret_cast<char*>(arr.data()), sizeof(arr));

	

	cout << "가장 작은 값 : " << *min_element(arr.begin(), arr.end()) << endl;
}


#endif