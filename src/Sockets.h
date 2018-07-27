/*
 * Sockets.h
 *
 *  Created on: 2016��9��20��
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
	int Server(string ServerIp, int ServerPort); /*�½�һ��������*/
	int Client(string ServerIp, int ServerPort); /*�ͻ������ӵ�������*/
	string Get(char *url,string Header,string urlParam);
	string Post(string url);
	int SendMessage(char * Message);
	int RecvMessage(int socket, char *buff, int len);
	virtual ~Sockets();
private:
	string ServerIp; /*������IP��ַ*/
	int ServerPort; /*�������˿ں�*/
	int ClientFd;	/*�ͻ���������*/
	int ServerFd;	/*������������*/
	int CheckErrorCode(char *ReturnMessage);
 
};
 
 
#endif /* SOCKETS_H_ */

