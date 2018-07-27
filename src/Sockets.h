/*
 * Sockets.h
 *
 *  Created on: 2016年9月20日
 *      Author: gavin
 */
 
#ifndef SOCKETS_H_
#define SOCKETS_H_
 
#include "string.h"
#include "string"
#include "stdio.h"
#include "stdlib.h"
#include "sys/types.h"
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
 
using namespace std;
using std::string;
 
class Sockets
{
public:
	int Server(string ServerIp, int ServerPort); /*新建一个服务器*/
	int Client(string ServerIp, int ServerPort); /*客户端链接到服务器*/
	string Get(char *url,string Header,string urlParam);
	string Post(string url);
	int SendMessage(char * Message);
	int RecvMessage(int socket, char *buff, int len);
	virtual ~Sockets();
private:
	string ServerIp; /*服务器IP地址*/
	int ServerPort; /*服务器端口号*/
	int ClientFd;	/*客户端描述符*/
	int ServerFd;	/*服务器描述符*/
	int CheckErrorCode(char *ReturnMessage);
 
};
 
 
#endif /* SOCKETS_H_ */

