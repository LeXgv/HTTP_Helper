<p align="center"><img src="https://img-fotki.yandex.ru/get/196486/458685827.0/0_1a7976_8e2c00e0_orig" width=370></p>
# Library: HTTP_Helper (HH)

**This library in development. most of the functions is not available now . [Go to the topic #1](https://github.com/LeXgv/HTTP_Helper/issues/1). Express your opinion about this library and  would you  suggest a new functionality.**:trollface:

## Description
This library was created for simple working with HTTP Protocol. You must only determine server and communicate with him. all secondary information ( example: Cookie) will be automatically processed. you do not need to be concerned about encryption. The library does everything for you. 


## Features
* HTTP connection to the server
* Encoding for ssh connection
* Automatic processing of http header
   * Example: automatic redirection on the server instructions
   * Processing of cookies: the adoption and inclusion in the request
* Fast Working
* Simple API
* Detailed documentation

This library is constantly  upgraded. Adding new features

## Simple start!
```C++
	#include "HTTP_Helper.h"
	#include <string>
	int main()
	{
	std::string answer 
	ServerLink super("https://github.com/");
	answer = super.get();
	}
```
