//#include "stdafx.h"                     //Ԥ�軷��
#include <stdio.h>
#include "winsock2.h"                   //�������紦����ͷ�ļ�
#pragma comment(lib,"Ws2.lib")       //������̬���ӿ�
int WINAPI 
_tmain(int argc, char* argv[])        //��������ʼ
{
    WSADATA server;                     //�������ṹ��
    WSAStartup(MAKEWORD(2,2),&server);  //��ʼ�����绷��
    SOCKET serversock=socket(AF_INET,SOCK_DGRAM,IPPROTO_IP);    //����socket�׽ӿ�
    SOCKADDR_IN local;                  //�����ַ�ṹ
    memset(&local,0,sizeof(local));     //��ַ�ṹ����
    local.sin_addr.s_addr=INADDR_ANY;   //�����ַ�ṹ��IP
    local.sin_family=AF_INET;           //�����ַ�ṹ����
    local.sin_port=htons(8000);         //�����ַ�ṹ�Ķ˿�
    SOCKADDR_IN client;                 //�������ṹ��
    int len=sizeof(client);             //����ͻ��ṹ��
    int ret=1;                          //���������
    bind(serversock,(SOCKADDR*)&local,sizeof(local));       //���׽ӿ�
    char buf[512]={0};                  //������յ�ַ�ռ�
	char *ptrip=NULL;
	char name[32]="";

	 PHOSTENT hostinfo;
	 if(gethostname (name, sizeof(name)) == 0)
	 { 
		  //����ɹ� �����������������name������
		  if((hostinfo = gethostbyname(name)) != NULL) 
		  { 
		   //��ȡ����IP
		   ptrip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		  }
	 }

	 printf("Host name:%s Host IP:%s\r\n",name, ptrip);

	 printf("This project was added to github\r\n");
	 
    while(ret!=0)                       //ѭ������
    {
        ret =recvfrom(serversock,buf,512,0,(SOCKADDR*)&client,&len);    //����socket�˿���Ϣ
        buf[ret] = '\0';                //���ý�����Ϣ������
        printf("%s\n",buf);             //�����ʾ��Ϣ
    }
    closesocket(serversock);            //�ر�socket
    WSACleanup();                       //�������绷��
    return 0;                           //����0
}
 