/*
 * Sockets.cpp
 *
 *  Created on: 2016年9月20日
 *      Author: gavin
 */
 
#include "Sockets.h"
#if 0
/*这是一个网络链接类*/
char BaiDuErrorCode[20][3] =
{
		{300101,"User's request is expired","用户请求过期"},
		{300102,"User call overrun per day","用户日调用量超限"},
		{300103,"Service call overrun per second","服务每秒调用量超限"},
		{300104,"Service call overrun per day","服务日调用量超限"},
		{300201,"URL cannot be resolved","url无法解析"},
		{300202,"Missing apikey","请求缺少apikey，登录即可获取"},
		{300203,"Apikey or secretkey is NULL","服务没有取到apikey或secretkey"},
		{300204,"Apikey does not exist","apikey不存在"},
		{300205,"Api does not exist","api不存在"},
		{300206,"Api out of service","api已关闭服务"},
		{300207,"Service overdue, please pay in time","余额不足，请充值"},
		{300208,"User not verified","未通过实名验证"},
		{300209,"Service provider response status error","服务商响应status非200"},
		{300301,"Internal error","内部错误"},
		{300302,"Sorry,The system is busy. Please try again late","系统繁忙稍候再试"},
		{-1,	 "手机号错误","手机号错误"},
		{-2,	 "appkey参数有误","appkey参数有误"},
		{-3,	 "手机号列表过长","	手机号列表过长"},
		{0,	 	 "succeed","查询成功"}
};
#endif
int Sockets::Server(string ServerIp, int ServerPort)
{
}
 
int Sockets::Client(string ServerIp, int ServerPort)
{
	int socketFd = 0;
	struct sockaddr_in their_addr =
	{ 0 };
	memset(&their_addr, 0, sizeof(their_addr));
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(ServerPort);
	their_addr.sin_addr.s_addr = inet_addr(ServerIp.data());
 
	socketFd = socket(PF_INET, SOCK_STREAM, 0);
	cout << "ServerIp:" << ServerIp << " Port:" << ServerPort << endl;
	if (socketFd < 0)
	{
		cout << "create socket error" << endl;
		exit(-1);
	}
	if (connect(socketFd, (struct sockaddr *) &their_addr, sizeof(their_addr))
			< 0)
	{
		cout << "connect socket error" << endl;
		exit(-1);
	}
	cout << "*****************ServerConnectOK*****************" << endl;
	ClientFd = socketFd;
	return socketFd;
}
 
string Sockets::Get(char * url, string Header, string urlParam)
{
	struct hostent *host;
	struct in_addr addr;
	char newurl[128] =
	{ 0 };
	char getfile[128] =
	{ 0 };
	char GetMessage[4096] ={0};
	char ReBuf[4096] = {0};
	char *str1 = NULL;
	char *str2 = NULL;
	/*截取有效字段*/
	str1 = strstr(url, "//");
	if (str1 != NULL)
		strcpy(newurl, str1 + 2);
	else
		strcpy(newurl, url);
	str1 = strstr(newurl, "com");
	if (str1 == NULL)
	{
		cout << "newurl no .com" << endl;
	}
	newurl[(str1 - newurl) + 3] = '\0';
	/*截取有效字段*/
	printf("%s\n", newurl);
	//获取主机信息
	host = gethostbyname(newurl); /*通过域名获取服务器的IP地址*/
 
	if (host == NULL)
	{
 
		cout << "gethostbyname error" << endl;
	}
	/*获取求求的文件*/
	str1 = strstr(url, "com");
	if (str1 == NULL)
	{
		str1 = strstr(url, "COM");
		if (str1 != NULL)
		{
			cout << "url error" << endl;
		}
		else
		{
			cout << "url error" << endl;
		}
	}
	strcpy(getfile, str1 + 3);
	addr.s_addr = *(unsigned long *) host->h_addr;
	cout << "hostname:" << host->h_name << endl;
	cout << "hostip:" << inet_ntoa(addr) << endl;
 
	Client(inet_ntoa(addr), 80);
#if 1
	memset(GetMessage,0,sizeof(GetMessage));
	sprintf(GetMessage,
			"GET %s?%s HTTP/1.1\r\n\
Host: %s\r\n\
User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:18.0)\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n\
Accept-Encoding: gzip, deflate\r\n\
Content-Type: application/x-www-form-urlencoded; charset=UTF-8 \r\n\
Apikey: %s \r\n\
Connection: close \r\n\
\r\n\
%s\r\n",
	getfile, urlParam.data(), newurl, Header.data(), urlParam.data());
#endif
 
	SendMessage(GetMessage);
	RecvMessage(ClientFd,ReBuf,4096);
 
	return ReBuf;
	return 0;
}
 
string Sockets::Post(string url)
{
 
}
 
int Sockets::SendMessage(char * Message)
{
	int ret = 0;
	int len = strlen(Message);
	cout<<"SendMessageLen:"<<len<<endl<<Message<<endl;
	ret = send(ClientFd, Message, len, 0);
	if (ret != len)
	{
		cout << "send message:" << Message << " error" << endl;
		return -1;
	}
	return 0;
}
 
int Sockets::RecvMessage(int socket, char* buff, int len)
{
	int ret = -1;
	if (buff == NULL)
	{
		cout << "ReadMessage Buff is NULL" << endl;
	}
	memset(buff, 0, len);
	ret = recv(ClientFd, buff, len, 0);
	if (ret < 0)
	{
		cout << "recv message error:" << errno << endl;
		return -1;
	}
	cout<<ret<<endl;
	return 0;
}
 
Sockets::~Sockets()
{
	// TODO Auto-generated destructor stub
}
 
int Sockets::CheckErrorCode(char * ReturnMessage)
{
	int i = 0;
	for(i =0;i<20;i++)
	{
		//if(NULL != strstr(ReturnMessage,"Internal "))
		{
 
		}
	}
}

