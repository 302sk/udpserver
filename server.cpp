//#include "stdafx.h"                     //预设环境
#include <stdio.h>
#include "winsock2.h"                   //包含网络处理函数头文件
#pragma comment(lib,"Ws2.lib")       //包含静态链接库
int WINAPI 
_tmain(int argc, char* argv[])        //主函数开始
{
    WSADATA server;                     //定义服务结构体
    WSAStartup(MAKEWORD(2,2),&server);  //初始化网络环境
    SOCKET serversock=socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);    //创建socket套接口
    SOCKADDR_IN local;                  //定义地址结构
    memset(&local,0,sizeof(local));     //地址结构清零
    local.sin_addr.s_addr=INADDR_ANY;   //定义地址结构的IP
    local.sin_family=AF_INET;           //定义地址结构类型
    local.sin_port=htons(8000);         //定义地址结构的端口
    SOCKADDR_IN client;                 //定义服务结构体
    int len=sizeof(client);             //定义客户结构体
    int ret=1;                          //定义出错函数
    bind(serversock,(SOCKADDR*)&local,sizeof(local));       //绑定套接口
    char buf[512]={0};                  //定义接收地址空间
	char *ptrip=NULL;
	char name[32]="";

	 PHOSTENT hostinfo;
	 if(gethostname (name, sizeof(name)) == 0)
	 { 
		  //如果成功 将本地主机名存放入name缓冲区
		  if((hostinfo = gethostbyname(name)) != NULL) 
		  { 
		   //获取主机IP
		   ptrip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		  }
	 }

	 printf("Host name:%s Host IP:%s\r\n",name, ptrip);

	 printf("This project was added to github\r\n");
	 
    while(ret!=0)                       //循环接收
    {
        ret =recvfrom(serversock,buf,512,0,(SOCKADDR*)&client,&len);    //接收socket端口信息
        buf[ret] = '\0';                //设置接收信息结束符
        printf("%s\n",buf);             //输出显示信息
    }
    closesocket(serversock);            //关闭socket
    WSACleanup();                       //清理网络环境
    return 0;                           //返回0
}
 