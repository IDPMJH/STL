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

	// p�� ����Ű�� char �迭���� Ư�� ������ ������ ��ȯ�մϴ�.
	size_t count_char_in_p(char target_char) const {
		if (p && num > 0) { // p�� ��ȿ�ϰ� num�� 0���� ū ��쿡�� ���� ���� ����
			return std::count(p.get(), p.get() + num, target_char);
		}
		return 0; // p�� ��ȿ���� �ʰų� num�� 0�� ��� 0 ��ȯ
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
		// ���� �������� reduce�� Ȱ�� �����ϳ�, Ȱ����� Ž���� ���� �� �� ����.

		long long total_score = std::accumulate(players.begin(), players.end(), 0LL,
			[](long long sum, const Player& p) {
				return sum + p.get_score();
			});

		double ������� = static_cast<double>(total_score) / PLAYER_COUNT;

		// ��� ���� ���
		std::print("\n--- Player ���� ��� ---\n");
		std::print("��� ����: {:.2f}\n", �������);
	}


	//	 3. id�� ���� ���� ��ü�� ã�� "�������̵�.txt"�� ����϶�.
	//	 id�� ���� ��ü�� ��� �� ������ ȭ�鿡 ����϶�.
	//	 ���Ͽ��� id�� ���� Player ��ü�� �̸��� ���̵� �� �� �� ����Ѵ�. 
	//   - ��� ���� id�� ã�Ҵ��� ������ �����϶�.
	{
		// �ߺ��� id�� ���� Player�鸸 ���͸��ϱ� ���� ����
		std::vector<std::pair<size_t, std::vector<size_t>>> �ߺ��Ǵ³༮��;
		{
			// 1�ܰ�: id�� [Ű]��, �ش� id�� ���� Player���� �ε��� ����� [��]���� �ϴ� �� ����
			std::unordered_map<size_t, std::vector<size_t>> id_map;

			// ��� Player�� ��ȸ�ϸ� id���� �׷�ȭ
			for (size_t i = 0; i < PLAYER_COUNT; ++i) {
				size_t player_id = players[i].get_id();
				id_map[player_id].push_back(i);
			}

			// 2�ܰ�: �ߺ��� id�� ���� �׸� ���͸� (ranges ��� ver.)
			auto is_duplicate = [](const auto& pair) {
				return pair.second.size() > 1;
				};

			// ranges�� ����� ���͸�
			for (const auto& [id, indices] : id_map | std::views::filter(is_duplicate)) {
				�ߺ��Ǵ³༮��.push_back({ id, indices });
			}
		}

		// �ߺ� id�� ���� Player �� ���
		size_t duplicate_count = std::accumulate(�ߺ��Ǵ³༮��.begin(), �ߺ��Ǵ³༮��.end(), 0ULL,
			[](size_t sum, const auto& pair) { return sum + pair.second.size(); });

		// ��� ���
		std::print("\n--- ���� ID�� ���� Player ��� ---\n");
		std::print("���� ID�� ���� Player ��: {}\n", duplicate_count);
		std::print("�ߺ��� ID ����: {}\n", �ߺ��Ǵ³༮��.size());

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
	}


	// 4. Player�� ��� p�� ����Ű�� �޸𸮿��� ���Ͽ��� ���� num���� char��
	//    ����Ǿ� �ִ�.
	//    �޸𸮿� ����� char�� ������������ �����϶�.
	//    'a'�� 10���� �̻��� Player�� ������ ȭ�鿡 ����϶�.
	//    - ��� �����Ͽ��� ��� ������ �������� ����϶�
	{
		std::print("\n--- 4. Player 'p' ��� ���� �� 'a' ���� ī��Ʈ ---\n");

		size_t �����ٸ����÷��̾� = 0;

		// ��� Player ��ü�� ���� �ݺ�
		for (size_t i = 0; i < PLAYER_COUNT; ++i) {
			players[i].sort_chars_in_p(); // �� Player�� p ��� char �迭 ����
			if (players[i].count_char_in_p('a') >= 10) {
				++�����ٸ����÷��̾�;
			}
		}

		std::print("'a'�� 10���� �̻��� Player�� ����: {}\n", �����ٸ����÷��̾�);
		std::print("\n[4�� �׸� ����]\n");
		std::print("���� ���:\n");
		std::print("�� Player ��ü�� ��� ���� p (std::unique_ptr<char[]>)�� ����Ű�� �޸𸮿� ����� num���� char ���ڸ� ������������ �����߽��ϴ�. ");
		std::print("�̸� ���� C++ ǥ�� ���̺귯�� <algorithm>�� ���ǵ� std::sort �Լ��� ����߽��ϴ�. ");
		std::print("��ü������ Player Ŭ������ �߰��� sort_chars_in_p() ��� �Լ� ������ std::sort(p.get(), p.get() + num); �� ���� ȣ���Ͽ� ������ �����߽��ϴ�. ");
		std::print("std::sort�� �Ϲ������� ��� O(N log N)�� �ð� ���⵵�� ������ ȿ������ ���� �˰���(��: IntroSort)���� �����˴ϴ�[3][5].\n\n");

		std::print("���� ���� ���:\n");
		std::print("���ڿ��� ���ĵ� ��, �� Player ��ü�� p ����� ����Ű�� char �迭���� 'a' ������ ������ �������ϴ�. ");
		std::print("�̸� ���� C++ ǥ�� ���̺귯�� <algorithm>�� ���ǵ� std::count �Լ��� ����߽��ϴ�. ");
		std::print("��ü������ Player Ŭ������ �߰��� count_char_in_p('a') ��� �Լ� ������ std::count(p.get(), p.get() + num, 'a'); �� ���� ȣ���Ͽ� 'a'�� ������ ����߽��ϴ�. ");
		std::print("����, 'a'�� ������ 10�� �̻��� Player ��ü�� �� ���� �����Ͽ� ȭ�鿡 ����߽��ϴ�[4].\n");
	}







}



