

// ===============================================================
// STRING.h - std::string가 유사한 클래스이다.
// STL의 container 로 동작할 수 있게 코딩해 나간다.
// 2025.04.08 - 시작
// 
// 
// ===============================================================
#pragma once
#include <memory>


class STRING {
	// 접근 제한자 (Access Modifier)
public:
	STRING(const char* str);
	STRING();
	~STRING();									// 2025.04.08 - 코딩할 이유가 전혀 없지만, 관찰을 위해

	// 복사생성과 복사할당
	STRING(const STRING& other);				//2025.04.08
	STRING& operator=(const STRING& other);		//2025.04.08

	// 이동생성과 이동할당

	size_t size() const;
	

private:
	size_t _len{};
	std::unique_ptr<char[]> _p;		// 생성은 이미 여기서 진행 됨

	// 2025.04.08
	size_t _id;							

	friend std::ostream& operator<<(std::ostream& os, const STRING& str);

	// 2025.04.08
	static size_t gid;


};

