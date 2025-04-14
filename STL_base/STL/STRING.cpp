// ===============================================================
// STRING.h - std::string�� ������ Ŭ�����̴�.
// STL�� container �� ������ �� �ְ� �ڵ��� ������.
// 2025.04.08 - ����
// 
// 
// ===============================================================


#include "STRING.h"
#include <memory>
#include <iostream>
#include <print>

// 2025.04.08
// ������ �����ϱ� ���� ���� �߰�
extern bool inspect;

STRING::STRING(const char* str)
	:_id{ ++gid }
	, _len{ strlen(str) }
{
	_p.reset();		// lvalue : ����� ���� �� -> location value (�޸�)
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


// �̵�������
// 2025.04.10
STRING::STRING(STRING&& other)
	:_id{++gid}, _len{other._len}
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
STRING& STRING::operator=(STRING&& other)
{
	if (this == &other)
		return *this;	// ���ǹ��� ���� ����

	_len = other._len;
	_p.release();	// �ڡڳ��� ������ �ڿ��� ���� ������ ����
	_p.reset(other._p.release());// other._p�� ����Ű�� �ڿ��� ������ �����ϰ�, ��ȯ�� ������ �޾ƿ�
	other._len = 0;
	if (inspect)
	{
		std::println("[{:8}] {:16} �ڿ� ��:{:<10} �޸�:{:<12} �ڿ��޸�:{:<12}",
			_id, "�̵��Ҵ翬����", _len, reinterpret_cast<void*>(this), reinterpret_cast<void*>(_p.get()));
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
	memcpy(_p.get(), other._p.get(), _len);

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

size_t STRING::gid{};