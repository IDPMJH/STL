

// ===============================================================
// STRING.h - std::string�� ������ Ŭ�����̴�.
// STL�� container �� ������ �� �ְ� �ڵ��� ������.
// 2025.04.08 - ����
// >> ������								2025 / 05 / 01
// < ������								2025 / 05 / 08
// begin(), end()						2025 / 05 / 13
// ������ �ݺ��ڴ� �ݵ�� Ŭ������ ����	2025 / 05 / 13
// ===============================================================
#pragma once
#include <memory>




class STRING {

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
	char* begin() const;
	char* end() const;
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







