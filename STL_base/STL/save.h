
// 2025/03/06 1주 2일
// 컴파일 환경 확인, 세이브 파일 제작
// [과제] save를 save.cpp로 분리하라

// VS version - 17.13 이상, Release x64
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <chrono>
// [문제] 문제없이 컴파일되게 하라. -> 기계어로 바꾸어질 수 있게하라
// -> [문제] 문제없이 실행되도록 하라. -> 파일이 저장되도록 하라 -> save함수를 제대로 코딩하라.
using std::cout;
using std::cin;
using std::endl;
using std::string_view;

using namespace std::chrono_literals;

void save(string_view FileName); // == [const string&] FileName