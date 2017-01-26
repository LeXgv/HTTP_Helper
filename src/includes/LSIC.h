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
	/*класс описывающий объект куки, который позволяет обробатывать получаемую информацию
	из заголовка Set-Cookie. И автоматически собирать зоголовок Cookie для следующего http запроса к серверу*/
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
		Cookie(const char * _name_, const char * _value_, const char * _path_, const char * _domain_, short _day_, short _month_, short _hour_, short _min_, short _seconds_, int _year_);
		/*вытаскивает все куки из заголовков ответа сервера*/
		static int Parse(const std::string &str, std::vector<Cookie> &storage);
		static int Parse(const char *str, std::vector<Cookie> &storage);
		static int Parse(const std::string &str, Cookie **storage);
		static int Parse(const char *str, Cookie **storage);
		/*возвращает имя данной куки в хранилище стринг*/
		std::string name_string() const;
		/*возвращает имя данной куки в массиве чаров*/
		const char* name_char() const;
		/*возвращает значение данной куки в хранилище стринг*/
		std::string value_string() const;
		/*возвращает значение данной куки в массиве чаров*/
		const char* value_char() const;
		/*изменить название куки*/
		int setName(const std::string _name_);
		int setName(const char *name);
		/*установить новое значение для данной куки*/
		int setValue(const std::string v);
		int setValue(const char *v);
	private:
		static int parseExpires(std::string str,int &start_index ,Cookie &c);
		static int parseDPM(const std::string &str, char *&that, int &ind); // that = 0: Domain 1:Path 2:Max-Age
		static int getNumber(std::string str, int ind);


	};
	/*Класс описывающий запросы к серверу и его ответы*/
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
		std::string get_string() const;//возвращет все заголовки в формате стиринг
		char** get_char() const;//возвращет все заголовки в формате чар
		int http_version() const;//возвращает используемую версию http
		int set_method(Method &m);//устанавливает метод получения/передачи информации в http протоколе 
		int setRequest(const std::string &r);
		int setRequest(const char &r);
		int setHeader(const std::string &h);
		int setHeader(const char &h);
	};
	/*класс занимающийся подключение, отправкой, приемом даннах от сервера*/
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