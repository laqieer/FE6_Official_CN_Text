// FE6_Official_CN_Text_Dumper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
// by laqieer

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		string s = argv[0];
		int pos = s.find_last_of('\\');
		s = s.substr(pos + 1);
		cerr << "Usage: " << s << " ROM Text\n";
		return -1;
	}
	ifstream rom;
	rom.open(argv[1], ios::in | ios::binary);
	if (!rom)
	{
		cerr << "fail to open the rom: " << argv[1] << endl;
		return -2;
	}
	ofstream text;
	text.open(argv[2], ios::out | ios::trunc);
	if (!text)
	{
		cerr << "fail to open the text: " << argv[2] << endl;
		rom.close();
		return -3;
	}
	text << "火纹战记 封印之剑 文本" << endl;
	rom.seekg(0x6dc);
	unsigned int pBase = 0;
	rom.read((char*)&pBase, sizeof(int));
	pBase -= 0x8000000;
	unsigned int pSlot = pBase + 8;
	for (int i = 1;; i++, pSlot += 4)
	{
		unsigned int pText = 0;
		rom.seekg(pSlot);
		rom.read((char*)&pText, sizeof(int));
		if ((pText >= 0x2000000 && pText <= 0x203FFFF) || (pText >= 0x3000000 && pText <= 0x3007FFF))
		{
			continue;
		}
		else
		{
			if (pText < 0x8000000 || pText >= 0xA000000)
			{
				//cout << "End at " << hex << i << ": " << pSlot << " " << hex << pText << endl;
				break;
			}
		}
		text << endl << hex << i << ":" << endl;
		pText -= 0x8000000;
		rom.seekg(pText);
		int len = 0;
		for (int j = 0; j < 1000; j++)
		{
			char c = 0;
			rom.read(&c, 1);
			if (c == 0)
			{
				len = j;
			}
		}
		if (len > 0)
		{
			char *txt = new char[len];
			rom.seekg(pText);
			rom.read(txt, len);
			text << txt << endl;
			delete[] txt;
		}
	}
	rom.close();
	text.close();
	return 1;
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
