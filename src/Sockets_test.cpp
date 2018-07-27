//============================================================================
// Name        : Sockets_test.cpp
// Author      : xiegui
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
 
#include <iostream>
#include "Sockets.h"
using namespace std;
 
int main() {
 
	Sockets *sockets = new Sockets();
	string rebacj = sockets->Get("http://apis.baidu.com/showapi_open_bus/txt_like/txt_like","4ba22baecaffaa517b2efdeacca5ad18","t1=%E8%BF%99%E6%98%AF%E6%B5%8B%E8%AF%95%E6%96%87%E6%9C%AC&t2=%E8%BF%99%E6%98%AF%E6%96%87%E6%9C%AC");
	cout<<rebacj<<endl;
	return 0;
}

