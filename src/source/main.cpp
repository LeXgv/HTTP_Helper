#include <fstream>
#include "HTTP_Helper.h"
#include <string>
//int main()
//{
	//std::vector<hh::Cookie> c;
	/*std::string str;
	std::ifstream r("D:\\ПРОЕКТЫ  CPP\\mvs\\Автоспамер ВК\\Инструменты\\Подключение по HTTPS протоколу\\Библиотека простого инет соед\\tests\\request.txt");
	while (!r.eof()) str.push_back(r.get());
	hh::Cookie *stor = nullptr;
	hh::Cookie::Parse_request(str.c_str(), stor);
	hh::Cookie c;
	//char p = c.getPath();
	//p = new char[2];
	hh::Request g(str.c_str());
	char *pointer = nullptr;
	g.getHeader("Connection", pointer);*/

	/*setlocale(LC_ALL, "Russian");
	char* c = "М";
	int q = CP_ACP;
	int b = MultiByteToWideChar(q, 0, c, -1, 0, 0);
	wchar_t* o = new wchar_t[b];
	MultiByteToWideChar(q, 0, c, -1, o, b);
	int t = o[0];
	std::cout << t;*/
	//printf("%s\n", o);
	//return 0;
//}

	int unicode2utf8(unsigned ucs, char *buf, int nbuf)
	{
		if (ucs <= 0x7f) {
			if (nbuf >= 1)
				*buf = ucs;
			return 1;
		}
		else if (ucs <= 0x7ff) {
			if (nbuf >= 2) {
				*buf++ = 0xc0 | ((ucs >> 6) & 0x1f);
				*buf = 0x80 | (ucs & 0x3f);
			}
			return 2;
		}
		else if (ucs <= 0xffff) {
			if (nbuf >= 3) {
				*buf++ = 0xe0 | ((ucs >> 12) & 0xf);
				*buf++ = 0x80 | ((ucs >> 6) & 0x3f);
				*buf = 0x80 | (ucs & 0x3f);
			}
			return 3;
		}
		else if (ucs <= 0x1fffff) {
			if (nbuf >= 4) {
				*buf++ = 0xf0 | ((ucs >> 18) & 0x7);
				*buf++ = 0x80 | ((ucs >> 12) & 0x3f);
				*buf++ = 0x80 | ((ucs >> 6) & 0x3f);
				*buf++ = 0x80 | (ucs & 0x3f);
			}
			return 4;
		}

		return -1;
	}

	int main(int argc, char **argv)
	{
		char buf[10];
		int n, i;

		n = unicode2utf8('М', buf, sizeof buf);

		for (i = 0; i<n; i++)
			printf("%s%#02x", (i ? " " : ""), (unsigned char)buf);
		printf("\n");
	}