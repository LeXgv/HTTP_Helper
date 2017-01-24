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
		int time[5];
		char day[3];
		char *domain;
		char *path;
	public:
		Cookie();
		Cookie(const Cookie &obj);
		Cookie(const char *_name_, const char *_value_, const char *_path_, const char *_domain_, int day = 0, int month = 0, int hour = 0, int min = 0);
		/*����������� ��� ���� �� ���������� ������ �������*/
		static int Parse(const std::string &str, std::vector<Cookie> &storage);
		static int Parse(const char *str, std::vector<Cookie> &storage);
		static int Parse(const std::string &str, Cookie **storage);
		static int Parse(const char *str, Cookie **storage);
		/*���������� ��� ������ ���� � ��������� ������*/
		std::string name_string() const;
		/*���������� ��� ������ ���� � ������� �����*/
		const char* name_char() const;
		/*���������� �������� ������ ���� � ��������� ������*/
		std::string value_string() const;
		/*���������� �������� ������ ���� � ������� �����*/
		const char* value_char() const;
		/*�������� �������� ����*/
		int setName(const std::string _name_);
		int setName(const char *name);
		/*���������� ����� �������� ��� ������ ����*/
		int setValue(const std::string v);
		int setValue(const char *v);
	private:
		static int parseExpires(std::string str,int start_index ,Cookie &c);
	//	static int parseDPM(std::string str, Cookie &c, int that); // that = 0: Domain 1:Path 2:Max-Age


	};
	/*����� ����������� ������� � ������� � ��� ������*/
	class Request
	{
	private:
		std::string **request;
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