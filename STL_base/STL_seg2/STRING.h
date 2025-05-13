

// ===============================================================
// STRING.h - std::string가 유사한 클래스이다.
// STL의 container 로 동작할 수 있게 코딩해 나간다.
// 2025.04.08 - 시작
// >> 연산자								2025 / 05 / 01
// < 연산자								2025 / 05 / 08
// begin(), end()						2025 / 05 / 13
// 역방향 반복자는 반드시 클래스로 제공	2025 / 05 / 13
// ===============================================================
#pragma once
#include <memory>




class STRING {

	// 반복자 어댑터
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

		// end와의 비교를 위해 필수 불가결
		bool operator==(const STRING_Reverse_Iterator& rhs) const
		{
			return _p == rhs._p; 
		}


	private:
		char* _p;
	};
	
	// 접근 제한자 (Access Modifier)
public:
	STRING(const char* str);
	STRING();
	~STRING();									// 2025.04.08 - 코딩할 이유가 전혀 없지만, 관찰을 위해

	// 복사생성과 복사할당연산자
	STRING(const STRING& other);				//2025.04.08
	STRING& operator=(const STRING& other);		//2025.04.08

	// 이동생성과 이동할당연산자						// 2025.04.10
	STRING(STRING&&) noexcept;						// && -> rvalue reference
	STRING& operator=(STRING&&)noexcept;

	bool operator==(const STRING& rhs) const;
	bool operator<(const STRING& rhs) const;	// 2025 05 08


	// 인터페이스 함수들
	size_t size() const;
	char* begin() const;
	char* end() const;
	STRING_Reverse_Iterator rbegin() const;
	STRING_Reverse_Iterator rend() const;


private:
	size_t _len{};
	std::unique_ptr<char[]> _p;		// 생성은 이미 여기서 진행 됨

	// 2025.04.08
	size_t _id;

	friend std::ostream& operator<<(std::ostream& os, const STRING& str);

	friend std::istream& operator>>(std::istream& is, STRING& str);

	// 2025.04.08
	static size_t gid;
	
	
};







