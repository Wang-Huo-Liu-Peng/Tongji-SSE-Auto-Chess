#include "CSocket.h"
#define BUF_LEN 1024


CSocket::CSocket(SocketEnum::SocketType _socketType) :csocket(INVALID_SOCKET), isConnected(false),
sendCount(0), recvCount(0), isBlocking(true), socketError(SocketEnum::InvalidSocket), socketType(_socketType)
{
	_passInfo = new passinfo;
}

bool CSocket::Connect(const char* ip, int port)
{
	isConnected = true;
	socketError = SocketEnum::Success;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)//初始化套接字DLL
	{
		SetSocketError(SocketEnum::WSAStartupError);
		isConnected = false;
	}

	if (isConnected)
	{
		if ((csocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
			SetSocketError();
			isConnected = false;
		}
	}

	if (isConnected) {
		memset(&serverAddress, 0, sizeof(sockaddr_in));//初始化指定长度的内存
		serverAddress.sin_family = AF_INET;
		long lip = inet_addr(ip);
		if (lip == INADDR_NONE)
		{
			SetSocketError(SocketEnum::InvalidAddress);
			isConnected = false;
		}
		else {
			if (port < 0)
			{
				SetSocketError(SocketEnum::InvalidPort);
				isConnected = false;
			}
			else {
				serverAddress.sin_addr.S_un.S_addr = lip;
				serverAddress.sin_port = htons(port);
				if (connect(csocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
					SetSocketError();
					isConnected = false;
				}
			}
		}
	}

	return isConnected;
}

//设置阻塞模式
bool CSocket::SetBlocking(bool isBlock)
{
	int block = isBlock ? 0 : 1;
	if (ioctlsocket(csocket, FIONBIO, (ULONG*)&block) != 0)
	{
		return false;
	}
	isBlocking = isBlock;
	return true;
}

bool CSocket::IsExit()
{
	if (strcmp(_passInfo->event, Exit) == 0)
	{
		return 1;
	}
	return 0;
}

int CSocket::Send(passinfo* passInfo, int len)
{
	if (!IsSocketValid() || !isConnected)
	{
		return 0;
	}
	if (passInfo == NULL || len < 1)
	{
		return 0;
	}
	sendCount = send(csocket, (char*)passInfo, len, 0);
	//cout << "sc: " << sendCount << endl;
	if (sendCount <= 0)
	{
		SetSocketError();
	}
	return sendCount;
}

int CSocket::Send() {
	if (!IsSocketValid() || !isConnected)
	{
		return 0;
	}
	if (_passInfo == NULL)
	{
		return 0;
	}
	sendCount = send(csocket, (char*)_passInfo, sizeof(passinfo), 0);
	//cout << "sc: " << sendCount << endl;
	if (sendCount <= 0)
	{
		SetSocketError();
	}
	return sendCount;
}

int CSocket::Receive(int strLen)
{
	recvCount = 0;
	if (!IsSocketValid() || !isConnected)
	{
		return recvCount;
	}
	if (strLen < 1)
	{
		return recvCount;
	}
	SetSocketError(SocketEnum::Success);
	while (1) {
		recvCount = recv(csocket, (char*)_passInfo, strLen, 0);
		if (recvCount > 0) {
			if (IsExit())
			{
				delete _passInfo;
				_passInfo = NULL;
				recvCount = 0;
				break;
			}
			else {
				//cout << _passInfo->_result << endl;
			}
		}
	}

	return recvCount;
}

//设置错误信息
void CSocket::SetSocketError(SocketEnum::SocketError error)
{
	socketError = error;
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
	case WSAECONNREFUSED:
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
	return socketError == SocketEnum::Success;
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
	if (_passInfo != NULL)
	{
		delete _passInfo;
		_passInfo = NULL;
	}
	ShutDown(SocketEnum::Both);
	if (closesocket(csocket) != SocketEnum::Error)
	{
		csocket = INVALID_SOCKET;
	}
	WSACleanup();//清理套接字占用的资源
}

bool CSocket::ShutDown(SocketEnum::ShutdownMode mode)
{
	SocketEnum::SocketError nRetVal = (SocketEnum::SocketError)shutdown(csocket, SocketEnum::Both);
	SetSocketError();
	return (nRetVal == SocketEnum::Success) ? true : false;
}

const passinfo* CSocket::GetData() const
{
	return _passInfo;
}

void CSocket::SetSocketHandle(SOCKET socket)
{
	if (socket != SOCKET_ERROR)
	{
		csocket = socket;
		isConnected = true;
		socketError = SocketEnum::Success;
	}
}
