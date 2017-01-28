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
	maxAge = -1;
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
	maxAge = obj.maxAge;
}

lsic::Cookie::Cookie(const char * _name_, const char * _value_, const char * _path_, const char * _domain_,short _dayMonth_ ,short _dayWeek_, short _month_, short _hour_, short _min_, short _seconds_, int _year_)
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
	/*dayMonth = _day_;
	hour = _hour_;
	minutes = _min_;
	seconds = _seconds_;
	year = _year_;
	month = _month_;*/
	setExpires(_month_ , _dayWeek_, _dayMonth_, _year_, _hour_, _min_, _seconds_);
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
		//itmp++;
		nv.clear();
		/*Вытаскивание опциональных параметров, таких как дата, хост, путь и др...*/
		while (str[itmp] != '/r' && str[itmp] != '/n')
		{
			//todo минимизировать количество проверок на конец куки
			itmp++;
			for (; str[itmp] != '='; itmp++)
			{
				if (str[itmp] != ' ') nv.push_back(str[itmp]);

			}
			switch (nv[0])
			{
				//Expires
			case 'e':
			{
				int err = parseExpires(str,itmp ,NewCookie);
				nv.clear();
				if (err < 0) return err;
				break;
			}
			//Domain
			case 'd':
			{
				parseDPM(str, NewCookie.domain, itmp);
				nv.clear();
				break;
			}
			//Path
			case 'p':
			{
			parseDPM(str, NewCookie.path, itmp);
				nv.clear();
				break;
			}
			//Max-Age
			case 'm':
			{
			//parseDPM(nv, NewCookie.maxAge);
				nv.clear();
				break;
			}
			default:
			{
				return -7;
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

int lsic::Cookie::getExpires(int arr[7])
{
	if (arr == nullptr)
		return -1;
	arr[0] = dayWeek;
	arr[1] = dayMonth;
	arr[2] = month;
	arr[3] = year;
	arr[4] = hour;
	arr[5] = minutes;
	arr[6] = seconds;
	return 0;
}

std::vector<int> lsic::Cookie::getExpiresVec()
{
	std::vector<int> Expires;
	Expires.push_back(dayWeek);
	Expires.push_back(dayMonth);
	Expires.push_back(month);
	Expires.push_back(year);
	Expires.push_back(hour);
	Expires.push_back(minutes);
	Expires.push_back(seconds);
	return Expires;
}

std::string lsic::Cookie::getExpiresStr()
{
	std::string Expires;
	switch (dayWeek)
	{
	case 1:
		Expires += "Mon, ";
		break;
	case 2:
		Expires += "Tue, ";
		break;
	case 3:
		Expires += "Wed, ";
		break;
	case 4:
		Expires += "Thu, ";
		break;
	case 5:
		Expires += "Fri, ";
		break;
	case 6:
		Expires += "Sat, ";
		break;
	case 7:
		Expires += "Sun, ";
		break;
	default:
		break;
	}
	numToChar(Expires, dayMonth);
	Expires += ' ';
	switch (month)
	{
	case 1:
		Expires += "Jan ";
		break;
	case 2:
		Expires += "Feb ";
		break;
	case 3:
		Expires += "Mar ";
		break;
	case 4:
		Expires += "Apr ";
		break;
	case 5:
		Expires += "May ";
		break;
	case 6:
		Expires += "Jun ";
		break;
	case 7:
		Expires += "Jul ";
		break;
	case 8:
		Expires += "Aug ";
		break;
	case 9:
		Expires += "Sep ";
		break;
	case 10:
		Expires += "Oct ";
		break;
	case 11:
		Expires += "Nov ";
		break;
	case 12:
		Expires += "Dec ";
		break;
	default:
		break;
	}
	numToChar(Expires, year);
	Expires += ' ';
	numToChar(Expires, hour);
	Expires += ':';
	numToChar(Expires, minutes);
	Expires += ':';
	numToChar(Expires, seconds);
	Expires += " GMT";
	return Expires;
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

char * lsic::Cookie::getPath()
{
	return path;
}

int lsic::Cookie::setPath(const std::string & v)
{
	if (path != nullptr)
	{
		for (int i = 0; path[i] != '\0'; i++) path[i] = ' ';
		delete[] path;
	}
	int size = v.size();
	path = new char[size];
	for (int i = 0; i < size; i++)
		path[i] = v[i];
	return 0;
}

int lsic::Cookie::setPath(const char * v)
{
	if (path != nullptr)
	{
		for (int i = 0; path[i] != '\0'; i++) path[i] = ' ';
		delete[] path;
	}
	int size = 0;
	while (v[size] != '\0') size++;
	size++;
	path = new char[size];
	for (int i = 0; i < size; i++)
		path[i] = v[i];
	return 0;
}

int lsic::Cookie::setExpires(short _month_, short _dayWeek_, short _dayMonth_, int _year_, short _hour_, short _minutes_, short _seconds_)
{
	if (_month_ > 0 && _month_ < 13 && _dayWeek_ > 0 && _dayWeek_ < 8 && _dayMonth_ > 0 && _dayMonth_ < 32 && _hour_ > -1
		&& _hour_ < 24 && _minutes_ > -1 && _minutes_ < 60 && _seconds_ > -1 && _seconds_ < 60)
	{
		dayWeek = _dayWeek_;
		dayMonth = _dayMonth_;
		year = _year_;
		hour = _hour_;
		minutes = _minutes_;
		seconds = _seconds_;
		return 0;
	}
	else 
		return -1;
}

int lsic::Cookie::setExpires(std::string _data_)
{
	int ind = 0;
	parseExpires(_data_, ind, *this, false);
	return 0;
}

int lsic::Cookie::notExpire()
{
	dayWeek = -1;
	dayMonth = -1;
	year = -1;
	hour = -1;
	minutes = -1;
	seconds = -1;
	return 0;
}

int lsic::Cookie::setMaxAge(int _seconds_)
{
	if (_seconds_ > 0)
	{
		maxAge = _seconds_;
	}
	else
	{
		if (_seconds_ == 0);// немнедленное уничтожение куки;
		else maxAge = -1;
	} 
	return 0;
}

int lsic::Cookie::setDomain(const std::string _domain_)
{
	int size = _domain_.size();
	domain = new char[size];
	for (int i = 0; i < size; i++) domain[i] = _domain_[i];
	return 0;
}

int lsic::Cookie::setDomain(const char * _domain_)
{
	int size = 0;
	while (_domain_[size] != '\0') size++;
	size++;
	domain = new char[size];
	for (int i = 0; i < size; i++) domain[i] = _domain_[i];
	return 0;
}

int lsic::Cookie::parseExpires(const std::string &str,int &ind , Cookie & c, bool is)
{
	//записываем название дня
	//двигаемся к записи дня
	char _day[5];
	if (is)
	{
		while (str[ind] != '=')ind++;
		ind++;
	}
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
		return -1;
		break;

	}
	//вытаскиваем номер дня в месяце
	ind += 3; // перепригивам заптую и пробел
	_day[0] = str[ind++];
	_day[1] = str[ind];
	_day[2] = '\0';
	short tmpDay = atoi(_day);
	if (tmpDay < 0 && tmpDay > 31) return -2;
	c.dayMonth = tmpDay;
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
		return -3;
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
	tmpDay = atoi(_day);
	if (tmpDay < 0 && tmpDay > 60) return -4;
	c.hour = tmpDay;
	for (int i = 0; str[ind] != ':'; ind++, i++) _day[i] = str[ind];
	ind++;
	_day[2] = '\0';
	tmpDay = atoi(_day);
	if (tmpDay < 0 && tmpDay > 60) return -5;
	c.minutes = tmpDay;
	for (int i = 0; str[ind] != ' '; ind++, i++) _day[i] = str[ind];
	_day[2] = '\0';
	tmpDay = atoi(_day);
	if (tmpDay < 0 && tmpDay > 60) return -6;
	c.seconds = tmpDay;
	//пропускаем все остальные флаги даты, так как код пока их не обрабатывает
	//todo Доделлать обработку остальных флагов даты
	for (; str[ind] != ';' && str[ind] != '\n'; ind++);
	ind++;
	return 0;
}

int lsic::Cookie::parseDPM(const std::string &str, char *&that, int &ind)
{
	ind++; // пропуск знака равно
	//считаем длину значения
	int size = 0;
	for (int i = ind; str[i] != ';' && str[i] != '\n'; i++)
	{
		if (str[ind] != ' ') size++;
	}
	that = new char[size + 1];
	for (int i = 0; i < size; i++, ind++)
	{
		char tmp = str[ind];
		if (tmp != ' ') that[i] = tmp;
	}
	that[size] = '\0';
	return 0;
}

void lsic::Cookie::numToChar(std::string & str, int num)
{
	if (num < 10)
	{
		str += '0';
		str += (num + '0');
	}
	while (num > 9)
	{
		str += ((num % 10) + '0');
		num = num / 10;
	}
	str += (num + '0');
}


