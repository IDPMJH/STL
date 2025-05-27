// ===============================================================
// STRING.cpp - std::string�� ������ Ŭ�����̴�.
// STL�� container �� ������ �� �ְ� �ڵ��� ������.
// 2025.04.08 - ����
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
// ������ �����ϱ� ���� ���� �߰�
bool inspect = false;

STRING::STRING(const char* str)
	:_id{ ++gid }
	, _len{ strlen(str) }
{
	_p.reset();		// lvalue : ����� ���� �� -> location value (�޸�) -> ���ص� �Ǵ� �� ���� �ѵ� �� �𸣰ڴ�;
	_p = std::make_unique<char[]>(_len);	// �ý��� �� -> �Ҿ�����..�ִ��� ������� �ʱ�?..

	memcpy(_p.get(), str, _len);		// DMA (Direct / Dynamic Memory Accesse)
	// C++ reference - SmartPointers
	// p.get()		: Ȯ���� �޸� �ּ�
	// p.reset()	: ����Ű�� �ִ� �޸�(�ּ�)�� �ٸ� ������ ����
	// p.release()	: �޸�(�ڿ�)�� ������ ��ȯ

	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "������(char*)", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
}

// 2025.04.08 ���� ������ ���� �ڵ�
STRING::STRING()
	:_id{ ++gid }
{


	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "����Ʈ����", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}

}

STRING::~STRING()
{
	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "�Ҹ���", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
}




/*
move semantics�� C++11���� ���Ե� ��������, ��ü�� ���ҽ��� �������� �ʰ� "�̵�"�ϴ� ����� �ǹ��մϴ�.

������ ����(copy semantics)�� ��ü�� ��� �����͸� �� ��ü�� ����������, move semantics�� ������(���ҽ� ������ ��)�� �ѱ�� ������ ��� �δ� ����Դϴ�.

�̷ν� ���ʿ��� �޸� ����� �Ҵ��� �ٿ� ������ ũ�� ���� �� �ֽ��ϴ�.

move semantics�� ���� C++11���� rvalue reference(T&&), move constructor, move assignment operator�� ���ԵǾ����ϴ�.

��ǥ������ std::move �Լ��� ��ü�� rvalue�� ĳ�����Ͽ� move semantics�� Ȱ��ȭ�մϴ�.
*/

// �̵�������
// 2025.04.10
STRING::STRING(STRING&& other) noexcept
	:_id{ ++gid }, _len{ other._len }
{
	// other�� �̿��ؼ� ����
	_p.reset(other._p.release());	// other�� ����Ű�� �ִ� �ڿ��� ���� ���� �� ��ȯ
	other._len = 0;
	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "�̵�������", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
}

// �̵��Ҵ翬����
// 2025.04.10
STRING& STRING::operator=(STRING&& other)noexcept
{
	if (this == &other)
		return *this;	// ���ǹ��� ���� ����

	_len = other._len;
	_p.release();	// �ڡڳ��� ������ �ڿ��� ���� ������ ����, �׷��� �ʰ� ���� �ٸ� �ڿ��� ������ ������ �� ����
	_p.reset(other._p.release());// other._p�� ����Ű�� �ڿ��� ������ �����ϰ�, ��ȯ�� ������ �޾ƿ� ������
	other._len = 0;
	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "�̵��Ҵ翬����", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
	return *this;
}

// 2025 04.22 ���� �����ڵ�
bool STRING::operator==(const STRING& rhs) const
{
	// std::equal(�����ּ�, ���ּ�, ���� ����� �����ּ�) -> ���ڰ� ������ �ǹ��ϴ��� �ľ�����.


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
	// ���� �ǹ��̴�. return STRING_Reverse_Iterator{ _p.get() };

}


// 2025.04.08
// ���������
STRING::STRING(const STRING& other)
	:_id{ ++gid }
	, _len(other._len) // ������ �� : , �� ����  ������ ��, ������ ������� ������ ��������.
{
	//_p.reset();	ù �����̹Ƿ� ���� �ʴ´�..?
	_p = std::make_unique<char[]>(_len);
	memcpy(_p.get(), other._p.get(), _len);
	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "���������", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
	}
}

// 2025.04.08
// �����Ҵ翬����
STRING& STRING::operator=(const STRING& other)
{
	// ���ǹ��� ���� ����
	if (this == &other)
		return *this;

	_len = other._len;

	_p.reset();		// �̹� ������ �ִ� �ڿ� ����
	// _p.release(); -> _p.reset() �ٸ� ���� ��������

	// ���� ����
	_p = std::make_unique<char[]>(_len);
	memcpy(_p.get(), other._p.get(), _len);		// DMA (Direct / Dynamic Memory Accesse)

	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "�����Ҵ翬����", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
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
	// ����̰�, ���߿� �⸻ ���迡 ���� ���� ���� (STRING �о���� ��)
	std::string s;
	is >> s;
	str._len = s.length();
	str._p.release();
	str._p = std::make_unique<char[]>(str._len);

	// unique ������ ���� �����ϴ� ����̱⿡ �̷��� �ϸ� �� ��
	// - ���� ��ü�� �޸��� ������ ������ ����
	// str._p.reset(s.data());
	memcpy(str._p.get(), s.data(), str._len);
	return is;
	//is.read(str._p.get(), str._len);
}

size_t STRING::gid{};

