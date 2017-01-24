#include "LSIC.h"

/*cookie - класс  описывающий объект куки, который позволяет обробатывать получаемую информацию

private:
	char *name;
	char *value;
	int time[4];
	char *domain;
	char *path;*/

lsic::Cookie::Cookie()
{
	name = nullptr;
	value = nullptr;
	domain = nullptr;
	path = nullptr;
	for (int i = 0; i < 5; i++) time[i] = 0;
}

lsic::Cookie::Cookie(const Cookie & obj)
{
	name = obj.name;
	value = obj.value;
	domain = obj.domain;
	path = obj.path;
	for (int i = 0; i < 5; i++) time[i] = obj.time[i];
}

lsic::Cookie::Cookie(const char * _name_, const char * _value_, const char * _path_, const char * _domain_, int day, int month, int hour, int min)
{
	int i = 0;
	for (; _name_[i] != '\0'; i++) name[i] = _name_[i];
	name[i] = '\0';
	i = 0;
	for (; _value_[i] != '\0'; i++) value[i] = _value_[i];
	value[i] = '\0';
	i = 0;
	for (; _path_[i] != '\0'; i++) path[i] = _path_[i];
	path[i] = '\0';
	i = 0;
	for (; _domain_[i] != '\0'; i++) domain[i] = _domain_[i];
	domain[i] = '\0';
	time[0] = day;
	time[1] = month;
	time[2] = hour;
	time[3] = min;
  }

int lsic::Cookie::Parse(const std::string & str, std::vector<Cookie>& storage)
{
	//поиск всех загаловков "Set-Cookie"
	std::vector<int> ind;
	int shift = 0;
	for (int i; (i = str.find("Set-Cookie:", shift)) != std::string::npos; )
	{
		ind.push_back(i);
		shift = i + 12;
	}
		
	//вытаскивание знанчений из заголовков
	int sizeI = ind.size();
	for (int i = 0; i <= sizeI; i++)
	{
		Cookie NewCookie;
		int itmp = ind[i];
		while (str[itmp] != ':') itmp++;
		itmp++;
		//запись имени куки
		std::string nv;
		for (; str[itmp] != '='; itmp++)
		{
			
			if (str[itmp] != ' ') nv.push_back(str[itmp]);
			
		}
		NewCookie.setName(nv);
		nv.clear();
		itmp++;
		//запись значения куки
		for (; str[itmp] != ';'; itmp++)
		{
			if (str[itmp] != ' ') nv.push_back(str[itmp]);
		}
		NewCookie.setValue(nv);
		itmp++;
		nv.clear();
		/*Вытаскивание опциональных параметров, таких как дата, хост, путь и др...*/
		while (str[itmp] != '/r')
		{
			for (; str[itmp] != '='; itmp++)
			{
				if (str[itmp] != ' ') nv.push_back(str[itmp]);

			}
			switch (nv[0])
			{
				//Expires
			case 'e':
			{
				parseExpires(str,itmp ,NewCookie);
				break;
			}
			//Domain
			case 'd':
			{
//				parseDPM(nv, NewCookie, 0);
				break;
			}
			//Path
			case 'p':
			{
			//	parseDPM(nv, NewCookie, 1);
				break;
			}
			//Max-Age
			case 'm':
			{
//				parseDPM(nv, NewCookie, 2);
				break;
			}
			default:
			{
				//error
			}
			}
		}
	}
	return 0;
}

std::string lsic::Cookie::name_string() const
{
	return std::string(name);
}

const char * lsic::Cookie::name_char() const
{
	return name;
}

std::string lsic::Cookie::value_string() const
{
	return std::string(value);
}

const char * lsic::Cookie::value_char() const
{
	return value;
}

int lsic::Cookie::setName(const std::string _name_)
{
	if (name != nullptr)
	{
		for (int i = 0; name[i] != '\0'; i++) name[i] = ' ';
		delete[] name;
	}
	int size = _name_.size();
	name = new char[size];
	for (int i = 0; i < size; i++)
		name[i] = _name_[i];
	return 0;
}

int lsic::Cookie::setName(const char * _name_)
{
	if (name != nullptr)
	{
		for (int i = 0; name[i] != '\0'; i++) name[i] = ' ';
		delete[] name;
	}
	int size = 0;
	while (_name_[size] != '\0') size++;

	name = new char[size];
	for (int i = 0; i < size; i++)
		name[i] = _name_[i];
	return 0;
}

int lsic::Cookie::setValue(const std::string _value_)
{
	if (value != nullptr)
	{
		for (int i = 0; value[i] != '\0'; i++) value[i] = ' ';
		delete[] value;
	}
	int size = _value_.size();
	value = new char[size];
	for (int i = 0; i < size; i++)
		value[i] = _value_[i];
	return 0;
}

int lsic::Cookie::setValue(const char * _value_)
{
	if (value != nullptr)
	{
		for (int i = 0; value[i] != '\0'; i++) value[i] = ' ';
		delete[] value;
	}
	int size = 0;
	while (_value_[size] != '\0') size++;
	name = new char[size];
	for (int i = 0; i < size; i++)
		value[i] = _value_[i];
	return 0;
}

int lsic::Cookie::parseExpires(std::string str,int ind , Cookie & c)
{
	//записываем название дня
	//двигаемся к записи дня
	char day[3];
	while (str[ind] != '=')ind++;
	ind++;
	/*вытаскиваем день недели и преобразуем в число от 1 до 7*/
	for (int i = 0; str[ind] != ','; i++, ind++) day[i] = str[ind];
	//доделать
	ind +=2;
	//
	for (int i = 0; str[ind] != ' '; i++, ind++) 
	return 0;
}
