// STL 과제 구현
#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <string>
#include <vector>
#include <print>
#include <unordered_map>
#include <unordered_set>
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

	// p가 가리키는 메모리의 char[]를 정렬하는 멤버 변수
	void sort_chars_in_p() {// 혹시 모르니
		if (p && num > 0) { // p가 유효하고 num이 0보다 큰 경우에만 정렬 수행
			std::sort(p.get(), p.get() + num);
		}
	}

	// p가 가리키는 char 배열에서 특정 문자의 개수를 반환 하도록 함
	size_t count_char_in_p(char target_char) const {
		if (p && num > 0) { // p가 유효하고 num이 0보다 큰 경우에만 개수 세기 수행
			return std::count(p.get(), p.get() + num, target_char);
		}
		// 오류
		return 0;
	}

	// Getter
	const int get_score() const { return score; }
	const std::string& get_name() const { return name; }
	const size_t get_id() const { return id; }
	const size_t get_num() const { return num; }



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
	int score;						// 점수
	size_t id;						// 아이디, 겹치는 아이디 있을 수 있음
	size_t num;						// free store에 확보한 바이트 수
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

		// ========================= 5번을 위해 비활성화=========================
		// std::print("\n--- 마지막 Player의 정보 ---\n");
		// players.back().show();
	}

	//	2. 점수가 가장 큰 Player를 찾아 화면에 출력하라.
	//	Player의 평균 점수를 계산하여 화면에 출력하라.
	//	- 어떻게 계산하였는지 보고서에 설명하라.
	// 점수가 가장 큰 Player 찾기, lambda 표현식 사용, 비교 오퍼레이터 오버로딩을 이용해서도 구현 가능
	// ========================= 5번을 위해 비활성화=========================
	//{
	//	
	//	  
	//	
	//	auto max = std::max_element(players.begin(), players.end(),
	//		[](const Player& a, const Player& b) {
	//			return a.get_score() < b.get_score();
	//		});
	//	std::print("\n--- 점수가 가장 큰 Player 정보 ---\n");
	//	max->show();

	//	// 모든 Player의 평균 점수 계산
	//	// accumulate 함수 활용
	//	// 병렬 버전으로 reduce도 활용 가능하나, 활용법은 탐구해 봐야 할 것 같다.


	//	// ========================= 5번을 위해 비활성화=========================
	//	long long total_score = std::accumulate(players.begin(), players.end(), 0LL,
	//		[](long long sum, const Player& p) {
	//			return sum + p.get_score();
	//		});

	//	double 평균점수 = static_cast<double>(total_score) / PLAYER_COUNT;

	//	// 평균 점수 출력
	//	std::print("\n--- Player 점수 통계 ---\n");
	//	std::print("평균 점수: {:.2f}\n", 평균점수);
	//}


	//	 3. id가 서로 같은 객체를 찾아 "같은아이디.txt"에 기록하라.
	//	 id가 같은 객체는 모두 몇 개인지 화면에 출력하라.
	//	 파일에는 id가 같은 Player 객체의 이름과 아이디를 한 줄 씩 기록한다. 
	//   - 어떻게 같은 id를 찾았는지 보고서에 설명하라.

		// 중복된 id를 가진 Player들만 필터링하기 위한 벡터
	std::vector<std::pair<size_t, std::vector<size_t>>> 중복되는녀석들;

	// 1단계: id를 [키]로, 해당 id를 가진 Player들의 인덱스 목록을 [값]으로 하는 맵 생성
	std::unordered_map<size_t, std::vector<size_t>> id_map; // 5번에서도 사용할 것임

	// 모든 Player를 순회하며 id별로 그룹화
	for (size_t i = 0; i < PLAYER_COUNT; ++i) {
		size_t player_id = players[i].get_id();
		id_map[player_id].push_back(i);
	}

	// 중복되는녀석들 reserve를 통해 불필요한 이사 횟수를 줄인다.
	// 
	중복되는녀석들.reserve(id_map.size());

	// 2단계: 중복된 id를 가진 항목만 필터링 (ranges 사용 ver.)
	auto is_duplicate = [](const auto& pair) {
		return pair.second.size() > 1;
		};

	// ranges를 사용한 필터링
	for (const auto& [id, indices] : id_map | std::views::filter(is_duplicate)) {
		중복되는녀석들.push_back({ id, indices });
	}


	// 중복 id를 가진 Player 수 계산
	size_t duplicate_count = std::accumulate(중복되는녀석들.begin(), 중복되는녀석들.end(), 0ULL,
		[](size_t sum, const auto& pair) { return sum + pair.second.size(); });

	// 결과 출력
	std::print("\n--- 같은 ID를 가진 Player 통계 ---\n");
	std::print("같은 ID를 가진 Player 수: {}\n", duplicate_count);

	// 파일에 기록
	std::ofstream out{ "같은아이디.txt" };
	if (out) {
		for (const auto& [id, indices] : 중복되는녀석들) {
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



	// 4. Player의 멤버 p가 가리키는 메모리에는 파일에서 읽은 num개의 char가
	//    저장되어 있다.
	//    메모리에 저장된 char를 오름차순으로 정렬하라.
	//    'a'가 10글자 이상인 Player의 개수를 화면에 출력하라.
	//    - 어떻게 정렬하였고 어떻게 개수를 세었는지 명시하라
	// 
	// ========================= 5번을 위해 비활성화=========================
	//{
	//	std::print("\n--- Player 'p' 멤버 정렬 및 'a' 개수 카운트 ---\n");

	//	size_t 열명보다많은플레이어{};

	//	// 모든 Player 객체에 대해 반복
	//	for (size_t i = 0; i < PLAYER_COUNT; ++i) {
	//		players[i].sort_chars_in_p(); // 각 Player의 p 멤버 char 배열 정렬
	//		if (players[i].count_char_in_p('a') >= 10) {
	//			++열명보다많은플레이어;
	//		}
	//	}
	//}



	// 5. [LOOP] id를 입력받아 존재하는 id라면 다음 내용을 한 번에 화면 출력
	{
		// 1. id 기준 정렬을 위한 벡터 생성 (인덱스 저장)
		std::vector<size_t> id_sorted_indices(PLAYER_COUNT);
		std::iota(id_sorted_indices.begin(), id_sorted_indices.end(), 0); // 0부터 PLAYER_COUNT-1까지 값으로 인덱스 초기화

		// id 기준 오름차순 정렬
		std::sort(id_sorted_indices.begin(), id_sorted_indices.end(),
			[](size_t a, size_t b) {
				return players[a].get_id() < players[b].get_id();
			});

		// 2. name 기준 정렬을 위한 벡터 생성
		std::vector<size_t> name_sorted_indices(PLAYER_COUNT);
		std::iota(name_sorted_indices.begin(), name_sorted_indices.end(), 0);

		// name 기준 오름차순 정렬
		std::sort(name_sorted_indices.begin(), name_sorted_indices.end(),
			[](size_t a, size_t b) {
				return players[a].get_name() < players[b].get_name();
			});

		// 3. score 기준 정렬을 위한 벡터 생성
		std::vector<size_t> score_sorted_indices(PLAYER_COUNT);
		std::iota(score_sorted_indices.begin(), score_sorted_indices.end(), 0);

		// score 기준 오름차순 정렬
		std::sort(score_sorted_indices.begin(), score_sorted_indices.end(),
			[](size_t a, size_t b) {
				return players[a].get_score() < players[b].get_score();
			});

		// 루프를 시작
		while (true) {
			std::print("\n아이디를 입력하세요 (-1 입력 시 종료): ");
			int input_id;
			std::cin >> input_id;

			// 종료 조건 확인
			if (input_id == -1) {
				std::print("프로그램을 종료합니다.\n");
				break;
			}

			// 일단 입력받은 ID를 가진 Player가 존재하는지 확인
			auto it = id_map.find(input_id);
			if (it == id_map.end()) {
				std::print("입력한 ID {}를 가진 Player가 존재하지 않습니다.\n", input_id);
				continue;
			}

			const std::vector<size_t>& player_indices = it->second;
			std::print("\n=== ID {}를 가진 Player 정보 ===\n", input_id);

			// 첫번쨰로,  ID 기준 정렬에서의 위치 찾기 및 출력
			std::print("\n--- ID 기준 정렬 결과 ---\n");

			// id_sorted_indices에서 입력받은 ID의 첫 번째 위치 찾기
			auto id_pos = std::find_if(id_sorted_indices.begin(), id_sorted_indices.end(),
				[input_id](size_t idx) {
					return players[idx].get_id() == input_id;
				});

			if (id_pos != id_sorted_indices.end()) {
				// 현재 위치를 기준으로 앞뒤 Player 정보 출력
				size_t pos = std::distance(id_sorted_indices.begin(), id_pos);

				// 앞의 Player 정보 출력 (존재할 경우)
				if (pos > 0) {
					size_t id_prev{ players[id_sorted_indices[pos - 1]].get_id() };
					// 동일한 ID를 가진 모든 Player 출력
					std::vector<size_t> player_indices_prev = id_map[id_prev];
					for (const auto& idx : player_indices_prev) {
						std::print("[앞] ");
						players[idx].show();
					}
				}

				// 동일 ID를 가진 모든 Player 출력
				for (const auto& idx : player_indices) {
					std::print("[현재] ");
					players[idx].show();
				}

				// 뒤의 Player 정보 출력 (존재하고, 다른 ID를 가질 경우)
				size_t next_pos = pos + player_indices.size();
				if (next_pos < id_sorted_indices.size()) {
					size_t id_next = players[id_sorted_indices[next_pos]].get_id();
					// 동일한 ID를 가진 모든 Player 출력
					std::vector<size_t> player_indices_next = id_map[id_next];
					for (const auto& idx : player_indices_next) {
						std::print("[뒤] ");
						players[idx].show();
					}
				}
			}

			// 2. name 기준 정렬에서의 위치 찾기 및 출력
			std::print("\n--- name 기준 정렬 결과 ---\n");

			// 이미 처리한 이름은 또 다시 출력하진 않는다 => 집합으로 중복을 제거해보자
			std::unordered_set<std::string> processed_names;

			// id가 같은 모든 Player들에 대해 각각 name 기준 정렬 결과를 출력한다.
			for (const auto& player_idx : player_indices) {
				const std::string& player_name = players[player_idx].get_name();

				// 이미 처리한 이름은 건너뜀
				if (processed_names.find(player_name) != processed_names.end()) {
					continue;
				}
				processed_names.insert(player_name);

				// name_sorted_indices에서 해당 이름을 가진 첫 번째 위치 찾기
				auto name_pos = std::find_if(name_sorted_indices.begin(), name_sorted_indices.end(),
					[&player_name](size_t idx) {
						return players[idx].get_name() == player_name;
					});

				if (name_pos != name_sorted_indices.end()) {
					size_t pos = std::distance(name_sorted_indices.begin(), name_pos);

					std::print("\nPlayer ID: {}, Name: {} 에 대한 name 정렬 결과:\n",
						players[player_idx].get_id(), player_name);

					// 앞의 Player 정보 출력 (존재할 경우)
					if (pos > 0) {
						std::print("[앞] ");
						players[name_sorted_indices[pos - 1]].show();
					}

					// 현재 이름과 같은 이름을 가진 모든 Player 출력
					size_t current_pos = pos;
					while (current_pos < name_sorted_indices.size() &&
						players[name_sorted_indices[current_pos]].get_name() == player_name) {
						std::print("[현재] ");
						players[name_sorted_indices[current_pos]].show();
						current_pos++;
					}

					// 뒤의 Player 정보 출력 (존재하고, 다른 이름을 가질 경우)
					if (current_pos < name_sorted_indices.size()) {
						std::print("[뒤] ");
						players[name_sorted_indices[current_pos]].show();
					}
				}
			}

			// 3. score 기준 정렬에서의 위치 찾기 및 출력
			std::print("\n--- score 기준 정렬 결과 ---\n");

			// 위와 마찬가지
			std::unordered_set<int> processed_scores;

			// id가 같은 모든 Player들에 대해 각각 score 기준 정렬 결과 출력
			for (const auto& player_idx : player_indices) {
				const int player_score = players[player_idx].get_score();

				// 이미 처리한 점수는 건너뜀
				if (processed_scores.find(player_score) != processed_scores.end()) {
					continue;
				}
				processed_scores.insert(player_score);

				// score_sorted_indices에서 해당 점수를 가진 첫 번째 위치 찾기
				auto score_pos = std::find_if(score_sorted_indices.begin(), score_sorted_indices.end(),
					[player_score](size_t idx) {
						return players[idx].get_score() == player_score;
					});

				if (score_pos != score_sorted_indices.end()) {
					size_t pos = std::distance(score_sorted_indices.begin(), score_pos);

					std::print("\nPlayer ID: {}, Score: {} 에 대한 score 정렬 결과:\n",
						players[player_idx].get_id(), player_score);

					// 앞의 Player 정보 출력 (존재할 경우)
					if (pos > 0) {
						std::print("[앞] ");
						players[score_sorted_indices[pos - 1]].show();
					}

					// 현재 점수와 같은 점수를 가진 모든 Player 출력
					size_t current_pos = pos;
					while (current_pos < score_sorted_indices.size() &&
						players[score_sorted_indices[current_pos]].get_score() == player_score) {
						std::print("[현재] ");
						players[score_sorted_indices[current_pos]].show();
						current_pos++;
					}

					// 뒤의 Player 정보 출력 (존재하고, 다른 점수를 가질 경우)
					if (current_pos < score_sorted_indices.size()) {
						std::print("[뒤] ");
						players[score_sorted_indices[current_pos]].show();
					}
				}
			}
		}
	}
}











