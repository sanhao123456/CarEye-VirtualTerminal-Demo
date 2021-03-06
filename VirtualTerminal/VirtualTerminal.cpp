// VirtualTerminal.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "../JT808Controller/JT808VirutalTerminal.h"
#include <fstream>
#include "iniparser.h"
#include <string>
#include <vector>

std::vector<std::string> split(std::string strtem, char a)
{
	std::vector<std::string> strvec;
	std::string::size_type pos1, pos2;
	pos2 = strtem.find(a);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		strvec.push_back(strtem.substr(pos1, pos2 - pos1));

		pos1 = pos2 + 1;
		pos2 = strtem.find(a, pos1);
	}
	strvec.push_back(strtem.substr(pos1));
	return strvec;
}

int main()
{
	std::vector<JT808VirtualTerminal*> terminals;
	dictionary * dict = iniparser_load("configure.ini");
	if (!dict) return 1;
	int nsection = iniparser_getnsec(dict);
	for (int i = 0; i < nsection; i++)
	{
		const char * secname = iniparser_getsecname(dict, i);
		char key[256];
		sprintf_s(key, 256, "%s:datafile", secname);
		std::string filestr = iniparser_getstring(dict, key, nullptr);
		std::vector<std::string> filelist = split(filestr, '|');
		int n = filelist.size();
		char **fs = (char**)malloc(n * sizeof(char*));
		int m = 0;
		for (std::string & s : filelist)
		{
			fs[m++] = (char*)s.c_str();
		}
		terminals.push_back(new JT808VirtualTerminal(secname, (const char**)fs, n));
		free(fs);
	}

	for (JT808VirtualTerminal * vt : terminals)
		vt->Start("39.108.246.45", 9999);
	while (true)
	{
		Sleep(1000);
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
