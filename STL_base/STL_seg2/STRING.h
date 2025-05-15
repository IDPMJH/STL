

// ===============================================================
// STRING.h - std::string�� ������ Ŭ�����̴�.
// STL�� container �� ������ �� �ְ� �ڵ��� ������.
// 2025.04.08 - ����
// >> ������								2025 / 05.01
// < ������								2025 / 05.08
// begin(), end()						2025 / 05.13
// ������ �ݺ��ڴ� �ݵ�� Ŭ������ ����	2025 / 05.13
// �ݺ��ڵ� �翬�� Ŭ������ �ڵ��ؾ� �Ѵ�. 2025 / 05.15
// ===============================================================

//iterator_traits
//provides uniform interface to the properties of an iterator

#pragma once
#include <memory>





class STRING {
	class STRING_Iterator {
		// ǥ�� �ݺ��ڴ� ���� �ټ����� ������ ����� �� �־�� �Ѵ�. - 2025 05 15
	public:
		// queory�� ������ �� �ִ� �����̹Ƿ� public:
		using difference_type = ptrdiff_t;
		using value_type = char;
		using pointer = char*;
		using reference = char&;
		using iterator_category = std::random_access_iterator_tag;

	public:
		STRING_Iterator(char* p) : _p{ p } {}


		// �ݺ��ڶ�� �ּ��� ���� ����� �����ؾ� �ݺ����̴�.
		char operator*()const {
			return *_p;
		}
		char* operator++() {
			return ++_p;
		}
		bool operator==(const STRING_Iterator& rhs)const {
			return _p == rhs._p;
		}
	private:
		char* _p;

	};
	

	// �ݺ��� �����
	class STRING_Reverse_Iterator {
	public:
		STRING_Reverse_Iterator(char* p) :_p(p) {}
		char operator *()
		{
			return *(_p - 1);
		}
		STRING_Reverse_Iterator& operator ++()
		{
			--_p;
			return *this;
		}

		// end���� �񱳸� ���� �ʼ� �Ұ���
		bool operator==(const STRING_Reverse_Iterator& rhs) const
		{
			return _p == rhs._p; 
		}


	private:
		char* _p;
	};
	
	// ���� ������ (Access Modifier)
public:
	STRING(const char* str);
	STRING();
	~STRING();									// 2025.04.08 - �ڵ��� ������ ���� ������, ������ ����

	// ��������� �����Ҵ翬����
	STRING(const STRING& other);				//2025.04.08
	STRING& operator=(const STRING& other);		//2025.04.08

	// �̵������� �̵��Ҵ翬����						// 2025.04.10
	STRING(STRING&&) noexcept;						// && -> rvalue reference
	STRING& operator=(STRING&&)noexcept;

	bool operator==(const STRING& rhs) const;
	bool operator<(const STRING& rhs) const;	// 2025 05 08


	// �������̽� �Լ���
	size_t size() const;
	STRING_Iterator begin() const;
	STRING_Iterator end() const;
	STRING_Reverse_Iterator rbegin() const;
	STRING_Reverse_Iterator rend() const;


private:
	size_t _len{};
	std::unique_ptr<char[]> _p;		// ������ �̹� ���⼭ ���� ��

	// 2025.04.08
	size_t _id;

	friend std::ostream& operator<<(std::ostream& os, const STRING& str);

	friend std::istream& operator>>(std::istream& is, STRING& str);

	// 2025.04.08
	static size_t gid;
	
	
};







