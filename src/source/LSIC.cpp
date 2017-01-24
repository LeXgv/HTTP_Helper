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
	dayWeek = -1;
	dayMonth = -1;
	hour = -1;
	minutes = -1;
	seconds = -1;
	year = -1;
	month = -1;
}

lsic::Cookie::Cookie(const Cookie & obj)
{
	name = obj.name;
	value = obj.value;
	domain = obj.domain;
	path = obj.path;
	dayMonth = obj.dayMonth;
	dayWeek = obj.dayWeek;
	hour = obj.hour;
	minutes = obj.minutes;
	seconds = obj.seconds;
	year = obj.year;
	month = obj.month;
}

lsic::Cookie::Cookie(const char * _name_, const char * _value_, const char * _path_, const char * _domain_, short _day_, short _month_, short _hour_, short _min_, short _seconds_, int _year_)
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
	dayMonth = _day_;
	hour = _hour_;
	minutes = _min_;
	seconds = _seconds_;
	year = _year_;
	month = _month_;
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
	char _day[5];
	while (str[ind] != '=')ind++;
	ind++;
	/*вытаскиваем день недели и преобразуем в число от 1 до 7*/
	for (int i = 0; i<2; i++, ind++) _day[i] = str[ind];
	switch (_day[0])
	{
		//One of "Mon1", "Tue2", "Wed3", "Thu4", "Fri5", "Sat6", or "Sun7"
	//Mon
	case 'M':
		c.dayWeek = 1;
		break;
	//Tue or Thu
	case 'T':
		if(_day[1] == 'u') c.dayWeek = 2;
		else c.dayWeek = 4;
		break;
	//Wed
	case 'W':
		c.dayWeek = 3;
		break;
	//Fri
	case 'F':
		c.dayWeek = 5;
		break;
	//Sat or Sun
	case 'S':
		if (_day[1] == 'a') c.dayWeek = 6;
		else c.dayWeek = 7;
			break;
	default:
		//error
		break;

	}
	//вытаскиваем номер дня в месяце
	ind += 3; // перепригивам заптую и пробел
	_day[0] = str[ind++];
	_day[1] = str[ind];
	_day[2] = '\0';
	c.dayMonth = atoi(_day);
	//вытаскиваем месяц
	ind += 2; // перепрыгиваем пробел
	for (int i = 0; i<3; i++, ind++) _day[i] = str[ind];
	_day[3] = '\0';
	switch (_day[0])
		//One of "Jan1", "Feb2", "Mar3", "Apr4", "May5", "Jun6", "Jul7", "Aug8", "Sep9", "Oct10", "Nov11", "Dec12" 
	{
	case'J':
		if (_day[1] == 'a') c.month = 1;
		else if (_day[2] == 'n') c.month = 6;
		else c.month = 7;
			break;
	case 'F':
		c.month = 2;
		break;
	case 'M':
		if (_day[2] == 'r') c.month = 3;
		else c.month = 5;
		break;
	case 'A':
		if (_day[1] == 'p') c.month = 4;
		else c.month = 8;
		break;
	case 'S':
		c.month = 9;
		break;
	case 'O':
		c.month = 10;
		break;
	case 'N':
		c.month = 11;
		break;
	case 'D':
		c.month = 12;
		break;
	default:
		//error
		break;
	}
	//вытаскивание года
	ind++;//пропускаем пробел
	for (int i = 0; i < 4; i++, ind++) _day[i] = str[ind];
	_day[4] = '\0';
	c.year = atoi(_day);
	ind++;//пропускаем пробел
	//вытаскивание времени
	for (int i = 0; str[ind] != ':'; ind++, i++) _day[i] = str[ind];
	ind++;
	_day[2] = '\0';
	c.hour = atoi(_day);
	for (int i = 0; str[ind] != ':'; ind++, i++) _day[i] = str[ind];
	ind++;
	_day[2] = '\0';
	c.minutes = atoi(_day);
	for (int i = 0; str[ind] != ' '; ind++, i++) _day[i] = str[ind];
	_day[2] = '\0';
	c.seconds = atoi(_day);
	return 0;
}
