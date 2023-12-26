#include "CSocket.h"
#define BUF_LEN 1024


CSocket::CSocket(SocketEnum::SocketType _socketType):csocket(INVALID_SOCKET),isConnected(false),buffer_recv(NULL),
sendCount(0),recvCount(0),isBlocking(true),socketError(SocketEnum::InvalidSocket),socketType(_socketType) 
{
	
}
 
bool CSocket::Connect(const char* ip,int port)
{
	isConnected=true;
	socketError=SocketEnum::Success;
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)//初始化套接字DLL
	{
		SetSocketError(SocketEnum::WSAStartupError); 
		isConnected=false;
	}

	if(isConnected)
	{
		if((csocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==INVALID_SOCKET){
			SetSocketError();
			isConnected=false;
		}
	}

	if(isConnected){
		memset(&serverAddress,0,sizeof(sockaddr_in));//初始化指定长度的内存
		serverAddress.sin_family=AF_INET;
		long lip=inet_addr(ip);
		if(lip==INADDR_NONE)
		{ 
			SetSocketError(SocketEnum::InvalidAddress); 
		    isConnected=false;
		} else{
			if(port<0)
			{
				SetSocketError(SocketEnum::InvalidPort);
				isConnected=false;
			}else{
				serverAddress.sin_addr.S_un.S_addr= lip;
				serverAddress.sin_port = htons(port);
				if(connect(csocket,(sockaddr*)&serverAddress,sizeof(serverAddress))==SOCKET_ERROR){
					SetSocketError(); 
					isConnected=false;
				} 
			}
		}
	}
 
	return isConnected; 
}

//设置阻塞模式
bool CSocket::SetBlocking(bool isBlock)
{
	int block=isBlock?0:1;
	if (ioctlsocket(csocket, FIONBIO, (ULONG *)&block) != 0)
	{
	  return false;
	}
	isBlocking=isBlock;
	return true;
}

bool CSocket::IsExit()
{
	if (buffer_recv == NULL)
		buffer_recv = new char[BUF_LEN];
	int len=strlen(buffer_recv);
	int i=0;
	int size=4;
	if(len==size)
	{
		char* exit="EXIT"; 
		for(i=0;i<size;i++)
		{
			if(buffer_recv[i]!=*(exit+i) && buffer_recv[i]-32!=*(exit+i))
			{
				break;
			}
		}
	}
	return i==size;
}
 
int CSocket::Send(char* pBuf,int len)
{
	if(!IsSocketValid() || !isConnected)
	{
		return 0;
	}
	if(pBuf==NULL || len<1)
	{
		return 0;
	}
	sendCount=send(csocket,pBuf,len,0);
	if(sendCount<=0)
	{
		SetSocketError();
	}
	return sendCount; 
}
 
int CSocket::Receive(int strLen)
{
	recvCount=0;
	if(!IsSocketValid() || !isConnected)
	{
		return recvCount;
	} 
	if(strLen<1)
	{
		return recvCount;
	} 
	if(buffer_recv!=NULL)
	{
		delete buffer_recv;
		buffer_recv=NULL;
	} 
	buffer_recv=new char[strLen];
	SetSocketError(SocketEnum::Success); 
	while(1){
		recvCount=recv(csocket,buffer_recv,strLen,0) ; 
		if(recvCount>0){
			buffer_recv[recvCount]='\0';

			if(IsExit())
			{
				delete buffer_recv;
				buffer_recv=NULL;
				recvCount=0;
				break;
			}else{
				//cout<<buffer_recv<<endl;
			}
		}
	}
	 
	return recvCount;
}

//设置错误信息
void CSocket::SetSocketError(SocketEnum::SocketError error)
{
	socketError=error;
}

void CSocket::SetSocketError(void)
{ 
    int nError = WSAGetLastError();
    switch (nError)
    {
        case EXIT_SUCCESS:
            SetSocketError(SocketEnum::Success);
            break;
        case WSAEBADF:
        case WSAENOTCONN:
            SetSocketError(SocketEnum::Notconnected);
            break;
        case WSAEINTR:
            SetSocketError(SocketEnum::Interrupted);
            break;
        case WSAEACCES:
        case WSAEAFNOSUPPORT:
        case WSAEINVAL:
        case WSAEMFILE:
        case WSAENOBUFS:
        case WSAEPROTONOSUPPORT:
            SetSocketError(SocketEnum::InvalidSocket);
            break;
        case WSAECONNREFUSED :
            SetSocketError(SocketEnum::ConnectionRefused);
            break;
        case WSAETIMEDOUT:
            SetSocketError(SocketEnum::Timedout);
            break;
        case WSAEINPROGRESS:
            SetSocketError(SocketEnum::Einprogress);
            break;
        case WSAECONNABORTED:
            SetSocketError(SocketEnum::ConnectionAborted);
            break;
        case WSAEWOULDBLOCK:
            SetSocketError(SocketEnum::Ewouldblock);
            break;
        case WSAENOTSOCK:
            SetSocketError(SocketEnum::InvalidSocket);
            break;
        case WSAECONNRESET:
            SetSocketError(SocketEnum::ConnectionReset);
            break;
        case WSANO_DATA:
            SetSocketError(SocketEnum::InvalidAddress);
            break;
        case WSAEADDRINUSE:
            SetSocketError(SocketEnum::AddressInUse);
            break;
        case WSAEFAULT:
            SetSocketError(SocketEnum::InvalidPointer);
            break;
        default:
            SetSocketError(SocketEnum::UnknownError);
            break;	
    } 
}
 
bool CSocket::IsSocketValid(void)
{
	return socketError==SocketEnum::Success;
}

SocketEnum::SocketError CSocket::GetSocketError()
{
	return socketError;
}

CSocket::~CSocket()
{ 
	Close();
}

void CSocket::Close()
{
	if(buffer_recv!=NULL)
	{
		delete buffer_recv;
		buffer_recv=NULL;
	}
	ShutDown(SocketEnum::Both);
	if( closesocket(csocket)!=SocketEnum::Error)
	{
		csocket= INVALID_SOCKET;
	}
	WSACleanup();//清理套接字占用的资源
}

bool CSocket::ShutDown(SocketEnum::ShutdownMode mode)
{ 
	SocketEnum::SocketError nRetVal = (SocketEnum::SocketError)shutdown(csocket, SocketEnum::Both);
	SetSocketError(); 
	return (nRetVal == SocketEnum::Success) ? true: false;
}

const char* CSocket::GetData() const
{
	return buffer_recv;
}

void CSocket::SetSocketHandle(SOCKET socket)
{
	if(socket!=SOCKET_ERROR)
	{
		csocket=socket;
		isConnected=true;
		socketError=SocketEnum::Success;
	}
}
 