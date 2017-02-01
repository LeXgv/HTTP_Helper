#include "LSIC.h"


lsic::Request::Request()
{
	cookies = nullptr;
	body = nullptr;
	headers = nullptr;
}

lsic::Request::Request(const char *r_str)
{
	if (r_str == nullptr)
	{
		cookies = nullptr;
		body = nullptr;
		headers = nullptr;
		return;
	}
	else
	{
		int headersSize = 0;
		int bodySize = -1;
    //counting size Headers
		while (r_str[headersSize] != '\0')
		{
			if (r_str[headersSize] == '\n' && r_str[headersSize + 1] == '\r')
			{
				headersSize += 3;
				break;
			}
			//check header for Content-Length
			if (r_str[headersSize] == 'C')
			{
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
					while (r_str[headersSize] != '\r') headersSize++;//todo проверит
					int num_index = headersSize - 1;
					while (r_str[num_index] != ' ')
					{
						bodySize++;
						bodySize += (r_str[num_index] - '0')*zero;
						zero *= 10;
						num_index--;
					}
					break;
				}
			}
			headersSize++;
		}
		headers = new char[headersSize];
		//record headers in char array
		for (int i = 0; i < headersSize; i++) headers[i] = r_str[i];
		if (bodySize == 0)
		{
			body = nullptr;
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
				body = new char[bodySize];
				ind = headersSize;
				for (int i = 0; r_str[ind] != '\0'; ind++, i++) body[i] = r_str[ind];
			}
		}

	}
}
