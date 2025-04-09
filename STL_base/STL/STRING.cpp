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
	_p = std::make_unique<char[]>(_len);

	memcpy(_p.get(), str, _len);		// DMA (Direct / Dynamic Memory Accesse)
	// p.get() : 확보한 메모리 주소
	// p.reset() : 메모리 리셋
	// p.release() : 메모리 반환

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