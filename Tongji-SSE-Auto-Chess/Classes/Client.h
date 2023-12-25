// Client.cpp  
#pragma once
#include <windows.h>
#include <process.h>
#include <iostream>
using namespace std;
#pragma comment(lib,"ws2_32.lib") 
#include "CSocket.h"

#define BUF_LEN 1024
#define serverIp  "192.168.22.192"
#define serverPort 1986

void receive(PVOID pt)
{
	CSocket* csocket=(CSocket*)pt;
	if(csocket!=NULL)
	{
		csocket->Receive(BUF_LEN); 
		_endthread(); 
	} 
}
 //int argc, char* argv[]
int connect_to_server(){
	CSocket csocket;
	bool connect=csocket.Connect(serverIp,serverPort);
	csocket.SetBlocking(false);
	if(connect)
	{
		cout<<"connected"<<endl;
		uintptr_t threadId=_beginthread(receive,0,&csocket);//启动一个线程接收数据的线程 
		while(1)
		{
			char buf[BUF_LEN];
			cin>>buf;

			csocket.Send(buf,strlen(buf));
			if(csocket.IsExit())
			{  
				csocket.Close(); 
				cout<<"exit success"<<endl;
				break;
			} 
		}
	}else
	{
		cout<<"not connect"<<endl;
		cout<<csocket.GetSocketError()<<endl;
	}
	 
	getchar();
	return 0;
} 

