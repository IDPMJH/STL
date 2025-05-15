// STL ���� ���� - Week11_1.cpp
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


	// �������� ǥ�� �� ������ ����, private�� �ǵ��Ͻ� �� ����...? => Getter�� ����ؾ� �ϳ�...? ��! Setter�� ������� �� ��
private:
	std::string name;				// �̸�, ����[3, 15], ['a', 'z']�θ� ����
	int score;					// ����
	size_t id;					// ���̵�, ��ġ�� ���̵� ���� �� ����
	size_t num;					// free store�� Ȯ���� ����Ʈ ��
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

		std::print("\n--- ������ Player�� ���� ---\n");
		players.back().show();
	}

	{
		//	2. ������ ���� ū Player�� ã�� ȭ�鿡 ����϶�.
		//	Player�� ��� ������ ����Ͽ� ȭ�鿡 ����϶�.
		//	- ��� ����Ͽ����� ������ �����϶�.

		  // ������ ���� ū Player ã��, lambda ǥ���� ���, �� ���۷����� �����ε��� �̿��ؼ��� ���� ����
		auto max = std::max_element(players.begin(), players.end(),
			[](const Player& a, const Player& b) {
				return a.get_score() < b.get_score();
			});
		std::print("\n--- ������ ���� ū Player ���� ---\n");
		max->show();

		// ��� Player�� ��� ���� ���
		// accumulate �Լ� Ȱ��
		// ���� �������� reduce�� Ȱ�� �����ϳ�, Ȱ����� Ž�� �ʿ�

		long long total_score = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.get_score();
			});

		double average_score = static_cast<double>(total_score) / PLAYER_COUNT;

		// ��� ���� ���
		std::print("\n--- Player ���� ��� ---\n");
		std::print("��� ����: {:.2f}\n", average_score);
	}


	//	 3. id�� ���� ���� ��ü�� ã�� "�������̵�.txt"�� ����϶�.
	//	 id�� ���� ��ü�� ��� �� ������ ȭ�鿡 ����϶�.
	//	 ���Ͽ��� id�� ���� Player ��ü�� �̸��� ���̵� �� �� �� ����Ѵ�. 
	//   - ��� ���� id�� ã�Ҵ��� ������ �����϶�.
	{
		// �ߺ��� id�� ���� Player�鸸 ���͸�
		std::vector<std::pair<size_t, std::vector<size_t>>> duplicates;
		{
			// 1�ܰ�: id�� Ű��, �ش� id�� ���� Player���� �ε��� ����� ������ �ϴ� �� ����
			std::unordered_map<size_t, std::vector<size_t>> id_map;

			// ��� Player�� ��ȸ�ϸ� id���� �׷�ȭ
			for (size_t i = 0; i < PLAYER_COUNT; ++i) {
				size_t player_id = players[i].get_id();
				id_map[player_id].push_back(i);
			}

			// 2�ܰ�: �ߺ��� id�� ���� �׸� ���͸� (ranges ���)
			auto is_duplicate = [](const auto& pair) {
				return pair.second.size() > 1;
				};

			// ranges�� ����� ���͸�
			for (const auto& [id, indices] : id_map | std::views::filter(is_duplicate)) {
				duplicates.push_back({ id, indices });
			}
		}

		// �ߺ� id�� ���� Player �� ���
		size_t duplicate_count = std::accumulate(duplicates.begin(), duplicates.end(), 0ULL,
			[](size_t sum, const auto& pair) { return sum + pair.second.size(); });

		// ��� ���
		std::print("\n--- ���� ID�� ���� Player ��� ---\n");
		std::print("���� ID�� ���� Player ��: {}\n", duplicate_count);
		std::print("�ߺ��� ID ����: {}\n", duplicates.size());

		// ���Ͽ� ���
		std::ofstream out{ "�������̵�.txt" };
		if (out) {
			for (const auto& [id, indices] : duplicates) {
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
	}





}



