#ifndef _LSIC_H_
#define _LSIC_H_
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


namespace hh
{
	/*class Options
	{
	private:
		static char *pathConfigurateFile;
		Options(){}
	public:


	};*/
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
		Cookie(const char * _name_, const char * _value_, const char * _path_, const char * _domain_, short _dayMonth_, short _dayWeek_, short _month_, short _hour_, short _min_, short _seconds_, int _year_);
		/*вытаскивает все куки из заголовков ответа сервера*/
		static int Parse_answer(const std::string &str, std::vector<Cookie> &storage);
		/*static int Parse(const char *str, std::vector<Cookie> &storage);
		static int Parse(const std::string &str, Cookie **storage);*/
		static int Parse_request(const char *str, Cookie *&storage, int start = 0);
		
	
	
	
		/*----Функции возвращающи значения полей класса----*/
		  char *getPath();
		  /*возвращает значение данной куки в хранилище стринг*/
		  std::string value_string() const;
		  /*возвращает значение данной куки в массиве чаров*/
		  const char* value_char() const;
		  /*возвращает имя данной куки в хранилище стринг*/
		  std::string name_string() const;
		  /*возвращает имя данной куки в массиве чаров*/
		  const char* name_char() const;
		  /*в переданный массив, размера не меньще 7, записывает дату смерти куки в формате:
		  [0] <номер дня недели> [1] <номер дня месяца> [2] <номер месяца в году>
		  [3] <год> [4] <Час> [5] <минуты> [6] <секунды>
		  (память уже должна быть выделена перед тем как передавать указатель на массив)*/
		  int getExpires(int arr[7]);
		  std::vector<int> getExpiresVec();//recomend use;
		  /*возвращает строку даты смерти куки в формате:
		  <day-name>, <day> <month> <year> <hour>:<minute>:<second> GMT*/
		  std::string getExpiresStr();
		  //int getExpires(char arr[7]);// better don't use
		  /*----Функции устанавливающие значения полей класса----*/
		  /*изменить название куки*/
		  int setName(const std::string _name_);
		  int setName(const char *name);
		  /*изменить значение куки*/
		  int setValue(const std::string v);
		  int setValue(const char *v);
		  /*изменить путь действия куки*/
		  int setPath(const std::string &v);
		  int setPath(const char *v);
		  /*изменить время жизни куки, путем установления даты смерти*/
		  int setExpires(short _month_, short _dayWeek_, short _dayMonth_, int _year_, short _hour_ = 0, short _minutes_ = 0, short _seconds_ = 0);
		  int setExpires(std::string _data_);
		  /*сделать куки одноразывами, после зовершения программы они будут забыты*/
		  int notExpire();
		  /*установить время жизни куки в секундах*/
		  int setMaxAge(int _seconds_);
		  /*установить домен, в котором будут работать куки*/
		  int setDomain(const std::string _domain_);
		  int setDomain(const char *_domain_);
	private:
		static int parseExpires(const std::string &str,int &start_index ,Cookie &c, bool is = true);
		static int parseDPM(const std::string &str, char *&that, int &ind); // that = 0: Domain 1:Path 2:Max-Age
		void numToChar(std::string &str, int num);


	};
	/*Класс описывающий запросы к серверу и его ответы
	автоматическая генерация заголовков. Хранения и обработка ответа сервера*/
	class Request
	{
	private:
		char *pointer_body;
		//Cookie *cookies;
		char *bufer;
	public:
		/*Creating empty request-object*/
		Request();
		/*processing string, which must be written in format:
		<HTTP_method> <Path> HTTP/<Version_HTTP = 1.1>\r\nHost:<Host>\r\n<HTTP_Header>\r\n<HTTP_Header>\r\n......\r\n\r\n<BODY>
		*/
		//Message(const std::string &r_str);
		Request(const char *r_str);
		Request(const std::string &http_headers, const std::string &body);
		Request(const Request &Obj);
		int set(const char *r_str);//set http request;
		const char* get() const;//return all HTTP-Request
		char* get_notConst();
		/*return value definite HTTP-Header, if Header absent, that return -1, if Header was found , that will be return 0*/
		int getHeader(char *headerName, char* &bucket) const; 
		double httpVersion() const;//возвращает используемую версию http
		int set_method(Method &m, char *uri = nullptr);//устанавливает метод получения/передачи информации в http протоколе 
		int setHeader(const std::string &h);
		int setHeader(const char *h);
		int addHeader(const std::string &h);
		int addHeader(const char *h);
	};

	class Response
	{

	};
	/*класс занимающийся подключение, отправкой, приемом даннах от сервера, КЛИЕНТА*/
	class Linker
	{
	private:
		std::vector<std::string> message;
		std::string ServerConnection;
		bool ssl;
	public:
		Linker();
		Linker(Linker &Obj);
		Linker(std::string link, TypeLink flag);
		int set_server(std::string url, bool secure = false);
		int connect();
		int send();
		int send(const Linker &req);
	};

	class LinkManager
	{

	};

	//helper functions
	//return size char-array(string). string must be ended zero-simbole('\0') 
	inline int sizeArrChar(const char *arr)
	{
		if (arr == nullptr)
		{
			return 0;
		}
		else
		{
			int sizeResult = 0;
			while (arr[sizeResult] != '\0') sizeResult++;
			sizeResult++;
			return sizeResult;
		}
	}
	//substring is searched in string. returns the index of substring or return -1 if substring not found. -2 <- other error
	inline int searchSubstr(const char *sub, const char *str, int subSize = -1, int strSize = -1,  int i = 0)
	{
		if (sub == nullptr || str == nullptr) return -1;
		if(subSize == -1)
			subSize = sizeArrChar(sub);
		if (strSize == -1)
			strSize = sizeArrChar(str);
		int resultInd = -1;
		for (; i < strSize; i++)
		{
			if (str[i] == sub[0])
			{
				resultInd = i;
				bool is = true;
				i++;
				for (int j = 1; j < subSize - 1 && i < strSize; j++, i++)
				{
					if (sub[j] != str[i])
					{
						is = false;
						break;
					}
				}
				if (is) return resultInd;
				else resultInd = -1;
			}
		}
		return -1;
	}

}

#endif _LSIC_H_