#ifndef NETLIBSHEADER_H
#define NETLIBSHEADER_H

#include "Platform.h"
#include "BaseType.h"

#include "NetLibsData.h"

#ifdef SYSTEM_WIN
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>    //Œ¢»Ì¿©’πµƒ¿‡ø‚
#include <Windows.h>
#else
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/unordered_set.hpp>

#include "IThread.h"
#include "XThread.h"
#include "XList.h"
#include "XMap.h"
#include "XVector.h"
#include "XHashmap.h"
#include "XSynchronization.h"

class SessionObject;
class SocketPacker;
class ServerAdapter;

#endif


