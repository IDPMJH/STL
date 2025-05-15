// STL ���� ����
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
		std::print("�̸�:{}, ���̵�:{} , ����:{}, �ڿ���:{}\n", name, id, score, num);
		std::print("����� ����: ");

		// Ȥ�� �𸣴ϱ� nullptr üũ
		if (nullptr != p) {
			for (size_t i = 0; i < num; ++i) {
				std::print("{}", p[i]);
			}
		}
		std::print("\n");
	}

	// p�� ����Ű�� �޸��� char[]�� �����ϴ� ��� ����
	void sort_chars_in_p() {// Ȥ�� �𸣴�
		if (p && num > 0) { // p�� ��ȿ�ϰ� num�� 0���� ū ��쿡�� ���� ����
			std::sort(p.get(), p.get() + num);
		}
	}

	// p�� ����Ű�� char �迭���� Ư�� ������ ������ ��ȯ �ϵ��� ��
	size_t count_char_in_p(char target_char) const {
		if (p && num > 0) { // p�� ��ȿ�ϰ� num�� 0���� ū ��쿡�� ���� ���� ����
			return std::count(p.get(), p.get() + num, target_char);
		}
		// ����
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


	// �������� ǥ�� �� ������ ����, private�� �ǵ��Ͻ� �� ����...? => Getter�� ����ؾ� �ϳ�...? ��! Setter�� ������� �� ��
private:
	std::string name;				// �̸�, ����[3, 15], ['a', 'z']�θ� ����
	int score;						// ����
	size_t id;						// ���̵�, ��ġ�� ���̵� ���� �� ����
	size_t num;						// free store�� Ȯ���� ����Ʈ ��
	std::unique_ptr<char[]> p;		// free store�� Ȯ���� �޸�

};


const size_t PLAYER_COUNT = 2'500'000;
std::array<Player, PLAYER_COUNT> players;


int main() {

	//	1. ���Ͽ� ������ ��� Player ������ �о� �����̳ʿ� �����϶�.
	//	���� ������ Player�� ������ ������ ���� �������� ȭ�鿡 ����϶�.
	//	- � ������� �о����� ������ �����϶�.
	{
		std::ifstream in{ "2025 STL ���� ���� - 2021184029", std::ios::binary };
		if (not in) {
			std::cout << "������ �� �� �����ϴ�." << std::endl;
			return 1;
		}

		int i{};
		for (i = 0; i < PLAYER_COUNT; ++i) {
			players[i].read(in);

			// 10������ ���� ��Ȳ�� üũ�Ѵ�. 
			// 05.14������ ���� ��Ȱ��ȭ
			/*if (0 == i % 100'000){
				cout << "���� �ο� �� : " << i << endl;
			}*/
		}

		// ========================= 5���� ���� ��Ȱ��ȭ=========================
		// std::print("\n--- ������ Player�� ���� ---\n");
		// players.back().show();
	}

	//	2. ������ ���� ū Player�� ã�� ȭ�鿡 ����϶�.
	//	Player�� ��� ������ ����Ͽ� ȭ�鿡 ����϶�.
	//	- ��� ����Ͽ����� ������ �����϶�.
	// ������ ���� ū Player ã��, lambda ǥ���� ���, �� ���۷����� �����ε��� �̿��ؼ��� ���� ����
	// ========================= 5���� ���� ��Ȱ��ȭ=========================
	//{
	//	
	//	  
	//	
	//	auto max = std::max_element(players.begin(), players.end(),
	//		[](const Player& a, const Player& b) {
	//			return a.get_score() < b.get_score();
	//		});
	//	std::print("\n--- ������ ���� ū Player ���� ---\n");
	//	max->show();

	//	// ��� Player�� ��� ���� ���
	//	// accumulate �Լ� Ȱ��
	//	// ���� �������� reduce�� Ȱ�� �����ϳ�, Ȱ����� Ž���� ���� �� �� ����.


	//	// ========================= 5���� ���� ��Ȱ��ȭ=========================
	//	long long total_score = std::accumulate(players.begin(), players.end(), 0LL,
	//		[](long long sum, const Player& p) {
	//			return sum + p.get_score();
	//		});

	//	double ������� = static_cast<double>(total_score) / PLAYER_COUNT;

	//	// ��� ���� ���
	//	std::print("\n--- Player ���� ��� ---\n");
	//	std::print("��� ����: {:.2f}\n", �������);
	//}


	//	 3. id�� ���� ���� ��ü�� ã�� "�������̵�.txt"�� ����϶�.
	//	 id�� ���� ��ü�� ��� �� ������ ȭ�鿡 ����϶�.
	//	 ���Ͽ��� id�� ���� Player ��ü�� �̸��� ���̵� �� �� �� ����Ѵ�. 
	//   - ��� ���� id�� ã�Ҵ��� ������ �����϶�.

		// �ߺ��� id�� ���� Player�鸸 ���͸��ϱ� ���� ����
	std::vector<std::pair<size_t, std::vector<size_t>>> �ߺ��Ǵ³༮��;

	// 1�ܰ�: id�� [Ű]��, �ش� id�� ���� Player���� �ε��� ����� [��]���� �ϴ� �� ����
	std::unordered_map<size_t, std::vector<size_t>> id_map; // 5�������� ����� ����

	// ��� Player�� ��ȸ�ϸ� id���� �׷�ȭ
	for (size_t i = 0; i < PLAYER_COUNT; ++i) {
		size_t player_id = players[i].get_id();
		id_map[player_id].push_back(i);
	}

	// �ߺ��Ǵ³༮�� reserve�� ���� ���ʿ��� �̻� Ƚ���� ���δ�.
	// 
	�ߺ��Ǵ³༮��.reserve(id_map.size());

	// 2�ܰ�: �ߺ��� id�� ���� �׸� ���͸� (ranges ��� ver.)
	auto is_duplicate = [](const auto& pair) {
		return pair.second.size() > 1;
		};

	// ranges�� ����� ���͸�
	for (const auto& [id, indices] : id_map | std::views::filter(is_duplicate)) {
		�ߺ��Ǵ³༮��.push_back({ id, indices });
	}


	// �ߺ� id�� ���� Player �� ���
	size_t duplicate_count = std::accumulate(�ߺ��Ǵ³༮��.begin(), �ߺ��Ǵ³༮��.end(), 0ULL,
		[](size_t sum, const auto& pair) { return sum + pair.second.size(); });

	// ��� ���
	std::print("\n--- ���� ID�� ���� Player ��� ---\n");
	std::print("���� ID�� ���� Player ��: {}\n", duplicate_count);

	// ���Ͽ� ���
	std::ofstream out{ "�������̵�.txt" };
	if (out) {
		for (const auto& [id, indices] : �ߺ��Ǵ³༮��) {
			for (size_t idx : indices) {
				const Player& p = players[idx];
				out << p.get_name() << " " << p.get_id() << "\n";
			}
		}
		std::print("���� '�������̵�.txt'�� ��� �Ϸ�\n");
	}
	else {
		std::print("������ �� �� �����ϴ�.\n");
	}



	// 4. Player�� ��� p�� ����Ű�� �޸𸮿��� ���Ͽ��� ���� num���� char��
	//    ����Ǿ� �ִ�.
	//    �޸𸮿� ����� char�� ������������ �����϶�.
	//    'a'�� 10���� �̻��� Player�� ������ ȭ�鿡 ����϶�.
	//    - ��� �����Ͽ��� ��� ������ �������� ����϶�
	// 
	// ========================= 5���� ���� ��Ȱ��ȭ=========================
	//{
	//	std::print("\n--- Player 'p' ��� ���� �� 'a' ���� ī��Ʈ ---\n");

	//	size_t �����ٸ����÷��̾�{};

	//	// ��� Player ��ü�� ���� �ݺ�
	//	for (size_t i = 0; i < PLAYER_COUNT; ++i) {
	//		players[i].sort_chars_in_p(); // �� Player�� p ��� char �迭 ����
	//		if (players[i].count_char_in_p('a') >= 10) {
	//			++�����ٸ����÷��̾�;
	//		}
	//	}
	//}



	// 5. [LOOP] id�� �Է¹޾� �����ϴ� id��� ���� ������ �� ���� ȭ�� ���
	{
		// 1. id ���� ������ ���� ���� ���� (�ε��� ����)
		std::vector<size_t> id_sorted_indices(PLAYER_COUNT);
		std::iota(id_sorted_indices.begin(), id_sorted_indices.end(), 0); // 0���� PLAYER_COUNT-1���� ������ �ε��� �ʱ�ȭ

		// id ���� �������� ����
		std::sort(id_sorted_indices.begin(), id_sorted_indices.end(),
			[](size_t a, size_t b) {
				return players[a].get_id() < players[b].get_id();
			});

		// 2. name ���� ������ ���� ���� ����
		std::vector<size_t> name_sorted_indices(PLAYER_COUNT);
		std::iota(name_sorted_indices.begin(), name_sorted_indices.end(), 0);

		// name ���� �������� ����
		std::sort(name_sorted_indices.begin(), name_sorted_indices.end(),
			[](size_t a, size_t b) {
				return players[a].get_name() < players[b].get_name();
			});

		// 3. score ���� ������ ���� ���� ����
		std::vector<size_t> score_sorted_indices(PLAYER_COUNT);
		std::iota(score_sorted_indices.begin(), score_sorted_indices.end(), 0);

		// score ���� �������� ����
		std::sort(score_sorted_indices.begin(), score_sorted_indices.end(),
			[](size_t a, size_t b) {
				return players[a].get_score() < players[b].get_score();
			});

		// ������ ����
		while (true) {
			std::print("\n���̵� �Է��ϼ��� (-1 �Է� �� ����): ");
			int input_id;
			std::cin >> input_id;

			// ���� ���� Ȯ��
			if (input_id == -1) {
				std::print("���α׷��� �����մϴ�.\n");
				break;
			}

			// �ϴ� �Է¹��� ID�� ���� Player�� �����ϴ��� Ȯ��
			auto it = id_map.find(input_id);
			if (it == id_map.end()) {
				std::print("�Է��� ID {}�� ���� Player�� �������� �ʽ��ϴ�.\n", input_id);
				continue;
			}

			const std::vector<size_t>& player_indices = it->second;
			std::print("\n=== ID {}�� ���� Player ���� ===\n", input_id);

			// ù������,  ID ���� ���Ŀ����� ��ġ ã�� �� ���
			std::print("\n--- ID ���� ���� ��� ---\n");

			// id_sorted_indices���� �Է¹��� ID�� ù ��° ��ġ ã��
			auto id_pos = std::find_if(id_sorted_indices.begin(), id_sorted_indices.end(),
				[input_id](size_t idx) {
					return players[idx].get_id() == input_id;
				});

			if (id_pos != id_sorted_indices.end()) {
				// ���� ��ġ�� �������� �յ� Player ���� ���
				size_t pos = std::distance(id_sorted_indices.begin(), id_pos);

				// ���� Player ���� ��� (������ ���)
				if (pos > 0) {
					size_t id_prev{ players[id_sorted_indices[pos - 1]].get_id() };
					// ������ ID�� ���� ��� Player ���
					std::vector<size_t> player_indices_prev = id_map[id_prev];
					for (const auto& idx : player_indices_prev) {
						std::print("[��] ");
						players[idx].show();
					}
				}

				// ���� ID�� ���� ��� Player ���
				for (const auto& idx : player_indices) {
					std::print("[����] ");
					players[idx].show();
				}

				// ���� Player ���� ��� (�����ϰ�, �ٸ� ID�� ���� ���)
				size_t next_pos = pos + player_indices.size();
				if (next_pos < id_sorted_indices.size()) {
					size_t id_next = players[id_sorted_indices[next_pos]].get_id();
					// ������ ID�� ���� ��� Player ���
					std::vector<size_t> player_indices_next = id_map[id_next];
					for (const auto& idx : player_indices_next) {
						std::print("[��] ");
						players[idx].show();
					}
				}
			}

			// 2. name ���� ���Ŀ����� ��ġ ã�� �� ���
			std::print("\n--- name ���� ���� ��� ---\n");

			// �̹� ó���� �̸��� �� �ٽ� ������� �ʴ´� => �������� �ߺ��� �����غ���
			std::unordered_set<std::string> processed_names;

			// id�� ���� ��� Player�鿡 ���� ���� name ���� ���� ����� ����Ѵ�.
			for (const auto& player_idx : player_indices) {
				const std::string& player_name = players[player_idx].get_name();

				// �̹� ó���� �̸��� �ǳʶ�
				if (processed_names.find(player_name) != processed_names.end()) {
					continue;
				}
				processed_names.insert(player_name);

				// name_sorted_indices���� �ش� �̸��� ���� ù ��° ��ġ ã��
				auto name_pos = std::find_if(name_sorted_indices.begin(), name_sorted_indices.end(),
					[&player_name](size_t idx) {
						return players[idx].get_name() == player_name;
					});

				if (name_pos != name_sorted_indices.end()) {
					size_t pos = std::distance(name_sorted_indices.begin(), name_pos);

					std::print("\nPlayer ID: {}, Name: {} �� ���� name ���� ���:\n",
						players[player_idx].get_id(), player_name);

					// ���� Player ���� ��� (������ ���)
					if (pos > 0) {
						std::print("[��] ");
						players[name_sorted_indices[pos - 1]].show();
					}

					// ���� �̸��� ���� �̸��� ���� ��� Player ���
					size_t current_pos = pos;
					while (current_pos < name_sorted_indices.size() &&
						players[name_sorted_indices[current_pos]].get_name() == player_name) {
						std::print("[����] ");
						players[name_sorted_indices[current_pos]].show();
						current_pos++;
					}

					// ���� Player ���� ��� (�����ϰ�, �ٸ� �̸��� ���� ���)
					if (current_pos < name_sorted_indices.size()) {
						std::print("[��] ");
						players[name_sorted_indices[current_pos]].show();
					}
				}
			}

			// 3. score ���� ���Ŀ����� ��ġ ã�� �� ���
			std::print("\n--- score ���� ���� ��� ---\n");

			// ���� ��������
			std::unordered_set<int> processed_scores;

			// id�� ���� ��� Player�鿡 ���� ���� score ���� ���� ��� ���
			for (const auto& player_idx : player_indices) {
				const int player_score = players[player_idx].get_score();

				// �̹� ó���� ������ �ǳʶ�
				if (processed_scores.find(player_score) != processed_scores.end()) {
					continue;
				}
				processed_scores.insert(player_score);

				// score_sorted_indices���� �ش� ������ ���� ù ��° ��ġ ã��
				auto score_pos = std::find_if(score_sorted_indices.begin(), score_sorted_indices.end(),
					[player_score](size_t idx) {
						return players[idx].get_score() == player_score;
					});

				if (score_pos != score_sorted_indices.end()) {
					size_t pos = std::distance(score_sorted_indices.begin(), score_pos);

					std::print("\nPlayer ID: {}, Score: {} �� ���� score ���� ���:\n",
						players[player_idx].get_id(), player_score);

					// ���� Player ���� ��� (������ ���)
					if (pos > 0) {
						std::print("[��] ");
						players[score_sorted_indices[pos - 1]].show();
					}

					// ���� ������ ���� ������ ���� ��� Player ���
					size_t current_pos = pos;
					while (current_pos < score_sorted_indices.size() &&
						players[score_sorted_indices[current_pos]].get_score() == player_score) {
						std::print("[����] ");
						players[score_sorted_indices[current_pos]].show();
						current_pos++;
					}

					// ���� Player ���� ��� (�����ϰ�, �ٸ� ������ ���� ���)
					if (current_pos < score_sorted_indices.size()) {
						std::print("[��] ");
						players[score_sorted_indices[current_pos]].show();
					}
				}
			}
		}
	}
}











