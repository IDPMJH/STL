// ===============================================================
// STRING.cpp - std::string가 유사한 클래스이다.
// STL의 container 로 동작할 수 있게 코딩해 나간다.
// 2025.04.08 - 시작
// 
// 
// ===============================================================


#include "STRING.h"
#include <string>
#include <memory>
#include <iostream>
#include <print>
#include <algorithm>

// 2025.04.08
// 관찰을 제어하기 위한 변수 추가
bool inspect = false;

STRING::STRING(const char* str)
	:_id{ ++gid }
	, _len{ strlen(str) }
{
	_p.reset();		// lvalue : 등식의 왼쪽 값 -> location value (메모리) -> 안해도 되는 거 같긴 한데 잘 모르겠다;
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




/*
move semantics는 C++11에서 도입된 개념으로, 객체의 리소스를 복사하지 않고 "이동"하는 방식을 의미합니다.

기존의 복사(copy semantics)는 객체의 모든 데이터를 새 객체에 복제하지만, move semantics는 소유권(리소스 포인터 등)만 넘기고 원본은 비워 두는 방식입니다.

이로써 불필요한 메모리 복사와 할당을 줄여 성능을 크게 높일 수 있습니다.

move semantics를 위해 C++11에는 rvalue reference(T&&), move constructor, move assignment operator가 도입되었습니다.

대표적으로 std::move 함수는 객체를 rvalue로 캐스팅하여 move semantics를 활성화합니다.
*/

// 이동생성자
// 2025.04.10
STRING::STRING(STRING&& other) noexcept
	:_id{ ++gid }, _len{ other._len }
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
STRING& STRING::operator=(STRING&& other)noexcept
{
	if (this == &other)
		return *this;	// 무의미한 동작 감지

	_len = other._len;
	_p.release();	// ★★내가 소유한 자원의 참조 해제를 먼저, 그렇지 않고 먼저 다른 자원을 받으면 해제할 수 없음
	_p.reset(other._p.release());// other._p가 가리키던 자원의 참조를 해제하고, 반환한 참조를 받아와 소유함
	other._len = 0;
	if (inspect)
	{
		std::println("[{:8}] {:16} 자원 수:{:<10} 메모리:{:<12} 자원메모리:{:<12}",
			_id, "이동할당연산자", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
	return *this;
}

// 2025 04.22 관계 연산자들
bool STRING::operator==(const STRING& rhs) const
{
	// std::equal(시작주소, 끝주소, 비교할 대상의 시작주소) -> 인자가 무엇을 의미하는지 파악하자.


	return std::equal(&_p[0], &_p[_len], &rhs._p[0], &rhs._p[rhs._len]);
}

bool STRING::operator<(const STRING& rhs) const
{
	// (&_p[0], &_p[_len], &rhs._p[0], &rhs._p[rhs._len]) == 
	return std::lexicographical_compare(_p.get(), _p.get() + _len,
		rhs._p.get(), rhs._p.get() + rhs._len);
}





//bool STRING::operator<=>(const STRING& rhs) const
//{
//	if (lhs.x < rhs.x or (lhs.x == rhs.x and lhs.y < rhs.y))
//		return std::lexicographical_compare(_p.get(), _p.get() + _len,
//			rhs._p.get(), rhs._p.get() + rhs._len);
//	if (lhs.x > rhs.x or (lhs.x == rhs.x and lhs.y > rhs.y))
//		return std::strong_ordering::greater;
//	return std::strong_ordering::equivalent;
//}

size_t STRING::size() const
{
	return _len;
}

STRING::STRING_Iterator STRING::begin() const
{
	return static_cast<STRING_Iterator>(_p.get());	// == return &_p[0];

}

STRING::STRING_Iterator STRING::end() const
{
	return static_cast<STRING_Iterator>(_p.get() + _len); // == return &_p[_len];
}

STRING::STRING_Reverse_Iterator STRING::rbegin() const
{
	return STRING_Reverse_Iterator{ _p.get() + _len };
}

STRING::STRING_Reverse_Iterator STRING::rend() const
{
	return _p.get();
	// 같은 의미이다. return STRING_Reverse_Iterator{ _p.get() };

}


// 2025.04.08
// 복사생성자
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
// 복사할당연산자
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
	memcpy(_p.get(), other._p.get(), _len);		// DMA (Direct / Dynamic Memory Accesse)

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

std::istream& operator>>(std::istream& is, STRING& str)
{
	// 편법이고, 나중에 기말 시험에 문제 출제 가능 (STRING 읽어오기 등)
	std::string s;
	is >> s;
	str._len = s.length();
	str._p.release();
	str._p = std::make_unique<char[]>(str._len);

	// unique 포인터 끼리 동작하는 방식이기에 이렇게 하면 안 됨
	// - 지역 객체의 메모리의 번지를 가져온 거임
	// str._p.reset(s.data());
	memcpy(str._p.get(), s.data(), str._len);
	return is;
	//is.read(str._p.get(), str._len);
}

size_t STRING::gid{};

