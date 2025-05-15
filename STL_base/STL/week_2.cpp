using namespace std;

// 이미 있는 것을 만들지 말기
// 많은 수의 자료를 처리하기

#define Prac 4

#if Prac == 1

#include <iostream>
#include <random>
#include <print>
#include <array>

int main()
{
	// ========================================================
	//[문제1] 랜덤 int 값 1000개를 생성해 메모리에 저장하고,
	// 가장 큰 값을 찾아 출력한다.
	// ========================================================
	random_device rd{};
	auto A = rd();	// 이 값은 추적 불가능
	int B = rd();	// 이 값은 추적 불가능
	mt19937 mt{ };
	// mt19937 mt{ random_device{}() };	// 이 값은 추적 가능
	// == default_random_engine dre(rd());
	// == mt19937 mt{ random_device{}()};
	uniform_int_distribution<int> id{ 0, 999'9999 };
	
	array<int, 1000> arr{};		// T[N] -> array<T,N> 

	for (int& num : arr)
	{
		num = { id(mt) };
		print("{:8}", num);
	}
	cout << endl;
	//auto MaxIter = max_element(arr.begin(), arr.end());
	//int a{ *MaxIter };
	cout << "최댓값 - " << *max_element(arr.begin(), arr.end()) << endl;
}

#elif Prac == 2

#include <iostream>
#include <print>
#include <fstream>
#include <random>
int main()
{
	//========================================================
	//	[문제2] 랜덤 int 값 1000개를 파일"int 1000개.txt"에 저장하라.
	//	파일을 열었을 때 사람이 읽을 수 있어야 한다.
	//	파일을 읽어 원래 int 값을 가져올 수 있어야 한다. (= 텍스트 모드로 저장하라.)
	//	========================================================

	//	std::print
	//{: N} N칸만큼 제시된 자리의 마지막에  갖다 놓음(오른쪽 정렬)
	//{:<N} : 왼쪽 정렬
	//{:^N} : 가운데 정렬
	//{:.N} : 소수점 N자리까지 출력
	// {:,} : 천단위 구분자
	// {0:b} : 2진수
	// {0:o} : 8진수...
	// print("{:^80}", 20250311);

	default_random_engine dre{ };
	uniform_int_distribution<int> id{ 0, 999'9999 };

	//그냥 열면 텍스트 모드, 두번째 인자에ios::binary : 바이너리 모드
	ofstream out{ "int 1000개.txt" };	// RAII : 객체와 자원의 라이프 사이클을 일치시킨다.

	int cnt{};
	// Dellmiter : 구문문자
	for (int i = 0; i < 1000; ++i)
	{
		print(out, "{:8}", id(dre));
		if (not(++cnt % 10))	// 10개마다 줄바꿈
			out << endl;
	}
}

#elif Prac == 3

#include <fstream>
#include <print>

int main()
{
	// ========================================================
	// [문제3] 파일 "int 1000개.txt"에는 int 1000개가 text형식으로 기록되어 있다.
	// 가장 큰 값을 찾아 화면에 출력하라, 출력된 값이 무엇인지 답지에 써라.
	// ========================================================
	ifstream in{ "int 1000개.txt" };
	if (not in)
		return(1);
	
	// iterator adaptor : stream iterator
	print("최댓값 : {}\n",*max_element(istream_iterator<int>{in}, {}));

	//파일 크기 예상 계산
	//	1. 각 숫자의 출력 형식 분석
	//	print(out, "{:8}", id(dre)) 형식으로 출력합니다.
	//{:8}은 최소 8자리 너비로 오른쪽 정렬하여 출력하는 형식입니다.
	//	즉, 각 숫자는 최소 8바이트를 차지합니다.
	//	숫자가 8자리 미만이면 앞에 공백이 채워집니다.
	// 
	//	2. 줄바꿈 문자 계산
	//	10개마다 줄바꿈을 하므로 총 100번의 줄바꿈이 있습니다.
	//	Windows 환경에서는 줄바꿈이 \r\n으로 2바이트입니다.
	//	따라서 줄바꿈에 필요한 바이트 : 100 × 2 = 200바이트
	// 
	//	3. 총 파일 크기 계산
	//	숫자 데이터 : 1000개 × 8바이트 = 8, 000바이트
	//	줄바꿈 : 100개 × 2바이트 = 200바이트
	//	총 예상 크기 : 8, 000 + 200 = 8, 200바이트
}
	

#elif Prac ==  4

#include <fstream>
#include <array>
#include <print>
#include <algorithm>
int main()
{
	//[문제4] 파일 "int 1000개.txt"에는 int 1000개가 text형식으로 기록되어 있다.
	// 이 데이터를 메모리에 저장하라.
	// 메모리에 있는 데이터를 화면에 출력하라
	// array = 컴파일 시 유일하게 용량이 정해져 있음 ->    가변이 아님
	ifstream in{ "int 1000개.txt" };
	array<int, 1000> arr;
	// ★★★ array를 파일에서 읽어 초기화 하는 방법 찾아보기
	if (not in)
		exit(1);
	// 1. for문을 사용
	//for (int& i : arr)
	//{
	//	in >> i;
	//	print("{:8}", i);
	//}
	// 2. copy_n을 사용 (copy와 차이점) ★★★
	// std::copy[first, last, dest.begin()) 범위의 모든 요소를 복사
	// std::copy_n[first, n, dest.begin()] n개를 복사
	std::copy_n(std::istream_iterator<int>{in}, arr.size(), arr.begin());

	// 3. generate 사용
	//std::generate(arr.begin(), arr.end(), [&in]() {int i; in >> i; return i; });

	// 2번 방식이 코드 간결성, 표준/가독성 면에서 우수함

	sort(arr.begin(), arr.end());

	for (const int& i : arr)
	{
		print("{:8}", i);
	}
}

#endif 

















