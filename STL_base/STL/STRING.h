

// ===============================================================
// STRING.h - std::string�� ������ Ŭ�����̴�.
// STL�� container �� ������ �� �ְ� �ڵ��� ������.
// 2025.04.08 - ����
// 
// 
// ===============================================================
#pragma once
#include <memory>


class STRING {
	// ���� ������ (Access Modifier)
public:
	STRING(const char* str);
	STRING();
	~STRING();									// 2025.04.08 - �ڵ��� ������ ���� ������, ������ ����

	// ��������� �����Ҵ�
	STRING(const STRING& other);				//2025.04.08
	STRING& operator=(const STRING& other);		//2025.04.08

	// �̵������� �̵��Ҵ�

	size_t size() const;
	

private:
	size_t _len{};
	std::unique_ptr<char[]> _p;		// ������ �̹� ���⼭ ���� ��

	// 2025.04.08
	size_t _id;							

	friend std::ostream& operator<<(std::ostream& os, const STRING& str);

	// 2025.04.08
	static size_t gid;


};

