#include "save.h"




void save(string_view FileName)
{
	// FileName�� �б� ���� ����
	std::ifstream in{ FileName.data() }; // {} �̴ϼȶ������� ���� �ʱ�ȭ  RAII
	if (not in)
	{
		cout << FileName << "can't be opened." << endl;
		exit(20250306);
	}
	// ���� ���� ������ ������ ����
	std::string NameToSave{ "2025_1_segment_STL_Save.txt" };
	std::ofstream out{ NameToSave, std::ios::app }; // �����̱�� ����

	
	// ���� ���Ͽ� �ִ� ��� ������ �о� �� ���Ͽ� '���ٿ�'����.
	auto size = std::filesystem::file_size(FileName);

	cout << "\""<<NameToSave << "\"" << "(where)" << FileName << "save completed - "
		<< size << "Bytes" << endl;
	// ������ �ð��� ���Ͽ� ����ϱ�
	auto now = std::chrono::system_clock::now();			// time_point�� ��´�, epoch
	auto utc = std::chrono::system_clock::to_time_t(now);	// UTC �������� ����
	auto lt = std::localtime(&utc);							// ���� �޷� �ð�����

	auto old = out.imbue(std::locale("ko_KR"));

	out << '\n' << '\n';
	out << "============================================" << '\n';
	out << "������ �ð�: " << std::put_time(lt, "%c %A") << '\n';
	out << "============================================" << '\n';
	out << '\n';

	// vector<char> v(size, 0); // ���ͷ� ������ �ű� �ʿ� ����
	std::copy(std::istreambuf_iterator{ in }, {}, std::ostreambuf_iterator{ out });
	

	// char c;
	// in >> noskipws; // ���� ���� ����
	// while (in >> c)	// ��� I/O �˻� -> ���� ���� ��ȭ�ϱ�
	// out << c;

	// �����ߴٰ� ȭ�� ���
	cout << "Save Completed" << endl;
	out.imbue(old);	// �����·� ����
}




