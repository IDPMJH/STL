// ===============================================================
// STRING.h - std::string가 유사한 클래스이다.
// STL의 container 로 동작할 수 있게 코딩해 나간다.
// 2025.04.08 - 시작
// 
// 
// ===============================================================


#include "STRING.h"
#include <memory>
#include <iostream>
#include <print>

// 2025.04.08
// 관찰을 제어하기 위한 변수 추가
extern bool inspect;

STRING::STRING(const char* str)
	:_id{ ++gid }
	, _len{ strlen(str) }
{
	_p.reset();		// lvalue : 등식의 왼쪽 값 -> location value (메모리)
	_p = std::make_unique<char[]>(_len);	// 시스템 콜 -> 불안전함..최대한 사용하지 않기?..

	memcpy(_p.get(), str, _len);		// DMA (Direct / Dynamic Memory Accesse)
	// C++ reference - SmartPointers
	// p.get()		: 확보한 메모리 주소
	// p.reset()	: 가리키고 있는 메모리(주소)를 다른 것으로 리셋
	// p.release()	: 메모리(자원)의 소유권 반환

	if (inspect)
	{
		std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			_id, "생성자(char*)", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
}

// 2025.04.08 동작 관찰을 위해 코딩
STRING::STRING()
	:_id{ ++gid }
{


	if (inspect)
	{
		std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			_id, "디폴트생성", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}

}

STRING::~STRING()
{
	if (inspect)
	{
		std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			_id, "소멸자", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
}


// 이동생성자
// 2025.04.10
STRING::STRING(STRING&& other)
	:_id{++gid}, _len{other._len}
{
	// other을 이용해서 생성
	_p.reset(other._p.release());	// other가 가리키고 있던 자원의 참조 해제 및 반환
	other._len = 0;
	if (inspect)
	 {
		 std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			 _id, "이동생성자", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	 }
}

// 이동할당연산자
// 2025.04.10
STRING& STRING::operator=(STRING&& other)
{
	if (this == &other)
		return *this;	// 무의미한 동작 감지

	_len = other._len;
	_p.release();	// ★★내가 소유한 자원의 참조 해제를 먼저
	_p.reset(other._p.release());// other._p가 가리키던 자원의 참조를 해제하고, 반환한 참조를 받아옴
	other._len = 0;
	if (inspect)
	{
		std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			_id, "이동할당연산자", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
	return *this;
}


size_t STRING::size() const
{
	return _len;
}


// 2025.04.08

STRING::STRING(const STRING& other)
	:_id{ ++gid }
	, _len(other._len) // 유의할 점 : , 를 통해  생성할 때, 순서가 보장되지 않음을 유의하자.
{
	//_p.reset();	첫 생성이므로 하지 않는다..?
	_p = std::make_unique<char[]>(_len);
	memcpy(_p.get(), other._p.get(), _len);
	if (inspect)
	{
		std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			_id, "복사생성자", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
}

// 2025.04.08
STRING& STRING::operator=(const STRING& other)
{
	// 무의미한 동작 감지
	if (this == &other)
		return *this;

	_len = other._len;

	_p.reset();		// 이미 가지고 있는 자원 해제
	// _p.release(); -> _p.reset() 다른 점을 공부하자

	// 깊은 복사
	_p = std::make_unique<char[]>(_len);
	memcpy(_p.get(), other._p.get(), _len);

	if (inspect)
	{
		std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			_id, "복사할당연산자", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
	return *this;
}


std::ostream& operator<<(std::ostream& os, const STRING& str)
{
	for (int i = 0; i < str._len; ++i)
		os << str._p[i];
	return os;
}

size_t STRING::gid{};