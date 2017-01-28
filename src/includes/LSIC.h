#pragma once
#include <vector>
#include <string>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <fstream>
#include <stdio.h>
#include <winsock.h>
#include <iostream>
#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libssl.lib")
#pragma comment(lib, "Wsock32.lib")


namespace lsic
{
	enum TypeLink { ip, url };
	enum Method{GET, POST, OPTIONS, HEAD, PUT, DELETE_ = DELETE, TRACE, CONNECT, PATCH};
	/*����� ����������� ������ ����, ������� ��������� ������������ ���������� ����������
	�� ��������� Set-Cookie. � ������������� �������� ��������� Cookie ��� ���������� http ������� � �������*/
	class Cookie
	{
	private:
		char *name;
		char *value;
		//int time[5];
		short dayWeek;
		short dayMonth;
		short hour;
		short minutes;
		short seconds;
		int year;
		int maxAge;
		short month;
		char *domain;
		char *path;
	public:
		Cookie();
		Cookie(const Cookie &obj);
		Cookie(const char * _name_, const char * _value_, const char * _path_, const char * _domain_, short _dayMonth_, short _dayWeek_, short _month_, short _hour_, short _min_, short _seconds_, int _year_);
		/*����������� ��� ���� �� ���������� ������ �������*/
		static int Parse(const std::string &str, std::vector<Cookie> &storage);
		/*static int Parse(const char *str, std::vector<Cookie> &storage);
		static int Parse(const std::string &str, Cookie **storage);
		static int Parse(const char *str, Cookie **storage);*/
		
	
	
	
		/*----������� ����������� �������� ����� ������----*/
		  char *getPath();
		  /*���������� �������� ������ ���� � ��������� ������*/
		  std::string value_string() const;
		  /*���������� �������� ������ ���� � ������� �����*/
		  const char* value_char() const;
		  /*���������� ��� ������ ���� � ��������� ������*/
		  std::string name_string() const;
		  /*���������� ��� ������ ���� � ������� �����*/
		  const char* name_char() const;
		  /*� ���������� ������, ������� �� ������ 7, ���������� ���� ������ ���� � �������:
		  [0] <����� ��� ������> [1] <����� ��� ������> [2] <����� ������ � ����>
		  [3] <���> [4] <���> [5] <������> [6] <�������>
		  (������ ��� ������ ���� �������� ����� ��� ��� ���������� ��������� �� ������)*/
		  int getExpires(int arr[7]);
		  std::vector<int> getExpiresVec();//recomend use;
		  /*���������� ������ ���� ������ ���� � �������:
		  <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT*/
		  std::string getExpiresStr();
		  //int getExpires(char arr[7]);// better don't use
		  /*----������� ��������������� �������� ����� ������----*/
		  /*�������� �������� ����*/
		  int setName(const std::string _name_);
		  int setName(const char *name);
		  /*�������� �������� ����*/
		  int setValue(const std::string v);
		  int setValue(const char *v);
		  /*�������� ���� �������� ����*/
		  int setPath(const std::string &v);
		  int setPath(const char *v);
		  /*�������� ����� ����� ����, ����� ������������ ���� ������*/
		  int setExpires(short _month_, short _dayWeek_, short _dayMonth_, int _year_, short _hour_ = 0, short _minutes_ = 0, short _seconds_ = 0);
		  int setExpires(std::string _data_);
		  /*������� ���� ������������, ����� ���������� ��������� ��� ����� ������*/
		  int notExpire();
		  /*���������� ����� ����� ���� � ��������*/
		  int setMaxAge(int _seconds_);
		  /*���������� �����, � ������� ����� �������� ����*/
		  int setDomain(const std::string _domain_);
		  int setDomain(const char *_domain_);
	private:
		static int parseExpires(const std::string &str,int &start_index ,Cookie &c, bool is = true);
		static int parseDPM(const std::string &str, char *&that, int &ind); // that = 0: Domain 1:Path 2:Max-Age
		void numToChar(std::string &str, int num);


	};
	/*����� ����������� ������� � ������� � ��� ������*/
	class Request
	{
	private:
		std::string body;
		std::vector<Cookie> cookies;
		std::string Headers;
	public:
		Request();
		Request(const std::string &r_str);
		Request(const char *r_str);
		Request(Request &Obj);
		int set(const std::string &r_str);
		int set(const char *r_str);
		std::string get_string() const;//��������� ��� ��������� � ������� �������
		char** get_char() const;//��������� ��� ��������� � ������� ���
		int http_version() const;//���������� ������������ ������ http
		int set_method(Method &m);//������������� ����� ���������/�������� ���������� � http ��������� 
		int setRequest(const std::string &r);
		int setRequest(const char &r);
		int setHeader(const std::string &h);
		int setHeader(const char &h);
	};
	/*����� ������������ �����������, ���������, ������� ������ �� �������*/
	class ServerLink
	{
	private:
		std::vector<std::string> message;
		std::string ServerConnection;
		bool ssl;
	public:
		ServerLink();
		ServerLink(ServerLink &Obj);
		ServerLink(std::string link, TypeLink flag);
		int set_server(std::string url, bool secure = false);
		int connect();
		int send();
		int send(const Request &req);
	};
}