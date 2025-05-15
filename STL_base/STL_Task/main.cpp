// STL 과제 구현 - Week11_1.cpp
#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <string>
#include <vector>
#include <print>
#include <unordered_map>
#include <ranges>


class Player {

public:
	Player() = default;


public:
	void show() const {
		std::print("이름:{}, 아이디:{} , 점수:{}, 자원수:{}\n", name, id, score, num);
		std::print("저장된 글자: ");

		// 혹시 모르니까 nullptr 체크
		if (nullptr != p) {
			for (size_t i = 0; i < num; ++i) {
				std::print("{}", p[i]);
			}
		}
		std::print("\n");
	}

	// Getter
	const int get_score() const { return score; }
	const std::string& get_name() const { return name; }
	const size_t get_id() const { return id; }



public:
	void write(std::ostream& os) {
		os.write((char*)this, sizeof(Player));
		os.write((char*)p.get(), num);
	}

	void read(std::istream& is) {
		is.read(reinterpret_cast<char*>(this), sizeof(Player));
		p.release();
		p = std::make_unique<char[]>(num);
		is.read(reinterpret_cast<char*>(p.get()), sizeof(char) * num);
	}


	// 과제에서 표현 된 형식을 보면, private를 의도하신 것 같다...? => Getter를 사용해야 하나...? 단! Setter는 사용하지 말 것
private:
	std::string name;				// 이름, 길이[3, 15], ['a', 'z']로만 구성
	int score;					// 점수
	size_t id;					// 아이디, 겹치는 아이디 있을 수 있음
	size_t num;					// free store에 확보한 바이트 수
	std::unique_ptr<char[]> p;		// free store에 확보한 메모리

};


const size_t PLAYER_COUNT = 2'500'000;
std::array<Player, PLAYER_COUNT> players;


int main() {

	//	1. 파일에 저장한 모든 Player 정보를 읽어 컨테이너에 저장하라.
	//	제일 마지막 Player의 정보를 다음과 같은 형식으로 화면에 출력하라.
	//	- 어떤 방식으로 읽었는지 보고서에 설명하라.
	{
		std::ifstream in{ "2025 STL 과제 파일 - 2021184029", std::ios::binary };
		if (not in) {
			std::cout << "파일을 열 수 없습니다." << std::endl;
			return 1;
		}

		int i{};
		for (i = 0; i < PLAYER_COUNT; ++i) {
			players[i].read(in);

			// 10만명마다 진행 상황을 체크한다. 
			// 05.14성능을 위해 비활성화
			/*if (0 == i % 100'000){
				cout << "읽은 인원 수 : " << i << endl;
			}*/
		}

		std::print("\n--- 마지막 Player의 정보 ---\n");
		players.back().show();
	}

	{
		//	2. 점수가 가장 큰 Player를 찾아 화면에 출력하라.
		//	Player의 평균 점수를 계산하여 화면에 출력하라.
		//	- 어떻게 계산하였는지 보고서에 설명하라.

		  // 점수가 가장 큰 Player 찾기, lambda 표현식 사용, 비교 오퍼레이터 오버로딩을 이용해서도 구현 가능
		auto max = std::max_element(players.begin(), players.end(),
			[](const Player& a, const Player& b) {
				return a.get_score() < b.get_score();
			});
		std::print("\n--- 점수가 가장 큰 Player 정보 ---\n");
		max->show();

		// 모든 Player의 평균 점수 계산
		// accumulate 함수 활용
		// 병렬 버전으로 reduce도 활용 가능하나, 활용법은 탐구 필요

		long long total_score = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.get_score();
			});

		double average_score = static_cast<double>(total_score) / PLAYER_COUNT;

		// 평균 점수 출력
		std::print("\n--- Player 점수 통계 ---\n");
		std::print("평균 점수: {:.2f}\n", average_score);
	}


	//	 3. id가 서로 같은 객체를 찾아 "같은아이디.txt"에 기록하라.
	//	 id가 같은 객체는 모두 몇 개인지 화면에 출력하라.
	//	 파일에는 id가 같은 Player 객체의 이름과 아이디를 한 줄 씩 기록한다. 
	//   - 어떻게 같은 id를 찾았는지 보고서에 설명하라.
	{
		// 중복된 id를 가진 Player들만 필터링
		std::vector<std::pair<size_t, std::vector<size_t>>> duplicates;
		{
			// 1단계: id를 키로, 해당 id를 가진 Player들의 인덱스 목록을 값으로 하는 맵 생성
			std::unordered_map<size_t, std::vector<size_t>> id_map;

			// 모든 Player를 순회하며 id별로 그룹화
			for (size_t i = 0; i < PLAYER_COUNT; ++i) {
				size_t player_id = players[i].get_id();
				id_map[player_id].push_back(i);
			}

			// 2단계: 중복된 id를 가진 항목만 필터링 (ranges 사용)
			auto is_duplicate = [](const auto& pair) {
				return pair.second.size() > 1;
				};

			// ranges를 사용한 필터링
			for (const auto& [id, indices] : id_map | std::views::filter(is_duplicate)) {
				duplicates.push_back({ id, indices });
			}
		}

		// 중복 id를 가진 Player 수 계산
		size_t duplicate_count = std::accumulate(duplicates.begin(), duplicates.end(), 0ULL,
			[](size_t sum, const auto& pair) { return sum + pair.second.size(); });

		// 결과 출력
		std::print("\n--- 같은 ID를 가진 Player 통계 ---\n");
		std::print("같은 ID를 가진 Player 수: {}\n", duplicate_count);
		std::print("중복된 ID 종류: {}\n", duplicates.size());

		// 파일에 기록
		std::ofstream out{ "같은아이디.txt" };
		if (out) {
			for (const auto& [id, indices] : duplicates) {
				for (size_t idx : indices) {
					const Player& p = players[idx];
					out << p.get_name() << " " << p.get_id() << "\n";
				}
			}
			std::print("파일 '같은아이디.txt'에 기록 완료\n");
		}
		else {
			std::print("파일을 열 수 없습니다.\n");
		}
	}





}



