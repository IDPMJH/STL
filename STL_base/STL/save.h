
// 2025/03/06 1�� 2��
// ������ ȯ�� Ȯ��, ���̺� ���� ����
// [����] save�� save.cpp�� �и��϶�

// VS version - 17.13 �̻�, Release x64
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <chrono>
// [����] �������� �����ϵǰ� �϶�. -> ����� �ٲپ��� �� �ְ��϶�
// -> [����] �������� ����ǵ��� �϶�. -> ������ ����ǵ��� �϶� -> save�Լ��� ����� �ڵ��϶�.
using std::cout;
using std::cin;
using std::endl;
using std::string_view;

using namespace std::chrono_literals;

void save(string_view FileName); // == [const string&] FileName