

// ===============================================================
// STRING.h - std::string가 유사한 클래스이다.
// STL의 container 로 동작할 수 있게 코딩해 나간다.
// 2025.04.08 - 시작
// >> 연산자								2025 / 05.01
// < 연산자								2025 / 05.08
// begin(), end()						2025 / 05.13
// 역방향 반복자는 반드시 클래스로 제공	2025 / 05.13
// 반복자도 당연히 클래스로 코딩해야 한다. 2025 / 05.15
// 반복자라면 제공해야 할 연산자를 오버로딩2025 / 05.20
// ===============================================================

//iterator_traits
//provides uniform interface to the properties of an iterator

#pragma once
#include <memory>





class STRING {
public:
	class STRING_Iterator {
		// 표준 반복자는 다음 다섯가지 물음에 대답할 수 있어야 한다. - 2025 05 15
	public:
		// queory에 응답할 수 있는 응답이므로 public:
		using difference_type = ptrdiff_t;
		using value_type = char;
		using pointer = char*;
		using reference = char&;
		using iterator_category = std::random_access_iterator_tag;

	public:
		STRING_Iterator() = default;
		explicit STRING_Iterator(char* p) : _p{ p } {}


		// 반복자라면 최소한 다음 기능을 제공해야 반복자이다.
		// 05.15
		// 05.20 이걸 복사가 아니라 계속 참조(&)할 수 있도록 해준다.(메모리 접근)
		char& operator*()const {
			return *_p;
		}
		STRING_Iterator operator++() {
			return static_cast<STRING_Iterator>(++_p);
		}
		bool operator==(const STRING_Iterator& rhs)const {
			return _p == rhs._p;
		}

		// 반복자가 만족해야할 조건, 연산자들 - 05.20
		// _p가 변할 이유가 없기 떄문에 const로 선언
		//
		difference_type operator-(const STRING_Iterator& rhs) const {
			return _p - rhs._p;
		}
		STRING_Iterator operator--() {
			return static_cast<STRING_Iterator>(--_p);
		}
		STRING_Iterator operator+(const difference_type n) const {
			return static_cast<STRING_Iterator>(_p + n);
		}

		// strong_ordering 을 반환할 때  sort하기 위함
		STRING_Iterator operator-(const difference_type n) const {
			return static_cast<STRING_Iterator>(_p - n);
		}

		auto operator <=>(const STRING_Iterator& rhs) const {
			return _p <=> rhs._p;
		}

		// 05.20
		// 기본생성자를 만들 때는 여기서 세팅하라
	private:
		char* _p{};

	};


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
	STRING_Iterator begin() const;
	STRING_Iterator end() const;
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









