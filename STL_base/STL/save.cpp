#include "save.h"




void save(string_view FileName)
{
	// FileName을 읽기 모드로 열기
	std::ifstream in{ FileName.data() }; // {} 이니셜라이져를 통해 초기화  RAII
	if (not in)
	{
		cout << FileName << "can't be opened." << endl;
		exit(20250306);
	}
	// 쓰기 모드로 저장할 파일을 열기
	std::string NameToSave{ "2025_1_segment_STL_Save.txt" };
	std::ofstream out{ NameToSave, std::ios::app }; // 덧붙이기로 열기

	
	// 읽을 파일에 있는 모든 내용을 읽어 쓸 파일에 '덧붙여'쓴다.
	auto size = std::filesystem::file_size(FileName);

	cout << "\""<<NameToSave << "\"" << "(where)" << FileName << "save completed - "
		<< size << "Bytes" << endl;
	// 저장한 시간을 파일에 기록하기
	auto now = std::chrono::system_clock::now();			// time_point를 얻는다, epoch
	auto utc = std::chrono::system_clock::to_time_t(now);	// UTC 형식으로 변경
	auto lt = std::localtime(&utc);							// 지역 달력 시간으로

	auto old = out.imbue(std::locale("ko_KR"));

	out << '\n' << '\n';
	out << "============================================" << '\n';
	out << "저장한 시간: " << std::put_time(lt, "%c %A") << '\n';
	out << "============================================" << '\n';
	out << '\n';

	// vector<char> v(size, 0); // 벡터로 데이터 옮길 필요 없음
	std::copy(std::istreambuf_iterator{ in }, {}, std::ostreambuf_iterator{ out });
	

	// char c;
	// in >> noskipws; // 공백 무시 금지
	// while (in >> c)	// 고급 I/O 검사 -> 루프 조건 완화하기
	// out << c;

	// 저장했다고 화면 출력
	cout << "Save Completed" << endl;
	out.imbue(old);	// 원상태로 복귀
}




