#include "HTTP_Helper.h"


hh::Request::Request()
{
	//cookies = nullptr;
	pointer_body = nullptr;
	bufer = nullptr;
}

hh::Request::Request(const char *r_str)
{
	set(r_str);
}

hh::Request::Request(const std::string &http_headers, const std::string &body)
{
	int size = http_headers.size() + body.size();
	bufer = new char[size];
	int index = 0;
	int i = 0;
	for (; http_headers[i] != '\0'; i++, index++) bufer[index] = http_headers[i];
	for (i = 0; body[i] != '\0'; i++, index++) bufer[index] = body[i];
	bufer[index] = body[i];
}

hh::Request::Request(const Request & Obj)
{
	if (Obj.bufer == nullptr)
	{
		bufer = nullptr;
		pointer_body = nullptr;
	}
	else
	{
		bufer = Obj.bufer;
		pointer_body = Obj.pointer_body;
	}
}

int hh::Request::set(const char *r_str)
{//1. counting size bufer substring
	// 1.1 cheking for Content-length header
	// 1.2 if Content-length header found that we are getting size from header
	//2. counting size body substring if Content-length header not found
	//3. creating one array for bufer and boyd
	//4. write in array
	if (r_str == nullptr)
	{
		//cookies = nullptr;
		pointer_body = nullptr;
		bufer = nullptr;
		return 1;
	}
	else
	{
		int headersSize = 0;
		int bodySize = -1;
		//counting size Headers
		while (r_str[headersSize] != '\0')
		{
			if (r_str[headersSize] == '\n' && r_str[headersSize + 1] == '\n')
			{
				headersSize += 3;
				break;
			}
			//check header for Content-Length
			if (r_str[headersSize] == '\n')
			{
				if (r_str[headersSize + 1] == 'C')
				{
					headersSize++;
					bool isContentLength = true;
					char check[] = "Content-Length";
					for (int i = 0; check[i] != '\0' && r_str[headersSize] != '\0'; i++, headersSize++)
					{
						if (check[i] != r_str[headersSize])
						{
							isContentLength = false;
							break;
						}
					}

					//variable is readed from string
					if (isContentLength)
					{
						headersSize += 2;//skip colon and space
						int zero = 1;
						while (r_str[headersSize] != '\n') headersSize++;
						//todo проверить
						int num_index = headersSize - 1;
						bodySize++;
						while (r_str[num_index] != ' ')
						{
							bodySize += (r_str[num_index] - '0')*zero;
							zero *= 10;
							num_index--;
							headersSize++;
						}
						break;
					}
				}
			}
			headersSize++;
		}
		if (bodySize == 0)
		{
			pointer_body = nullptr;
			return 3;
		}
		else
		{
			if (bodySize == -1)//size body not known
			{
				bodySize++;
				//countin body size
				int ind = headersSize;
				while (r_str[ind] != '\0')
				{
					ind++;
					bodySize++;
				}
				bodySize++;
			}
		}
		bufer = new char[headersSize + bodySize];
		pointer_body = bufer + headersSize - 1;
		//record bufer in char array
		int i = 0;
		for (; r_str[i] != '\0'; i++) bufer[i] = r_str[i];
		bufer[i] = r_str[i];
		//for (int ind = 0; r_str[i] != '\0'; i++) pointer_body[ind] = r_str[i];


	}
	return 0;
}

const char * hh::Request::get() const
{
	return bufer;
}

char * hh::Request::get_notConst()
{
	return bufer;
}

int hh::Request::getHeader(char * headerName, char *& bucket) const
{
	for (int index = 0; bufer[index] != '\0'; index++)
	{
		if ((bufer + index) == pointer_body) return -1;
		if (bufer[index] == '\n' && bufer[index + 1] == headerName[0])
		{
			int i = 0;
			index++;
			for (; headerName[i] != '\0' && bufer[index] != '\0'; i++, index++)
			{
				if (headerName[i] != bufer[index]) break;
			}
			if (headerName[i] == '\0')
			{
				//we are recording value header in bucket
				//skip colon
				index++;
				//counting value size
				int index2 = index;
				while (bufer[index] != '\n') index++;
				bucket = new char[index - index2+1];
				//recording value
				int p = 0;
				for (; bufer[index2] != '\n'; index2++, p++) bucket[p] = bufer[index2];
				bucket[p] = '\0';
				return p;
			}
		}
	}
}

double hh::Request::httpVersion() const
{
	/*int i = 0;
	while()*/
	return 0;
}
