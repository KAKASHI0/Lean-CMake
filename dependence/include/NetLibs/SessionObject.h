#ifndef SESSIONOBJECT_H
#define SESSIONOBJECT_H

#include "NetLibsHeader.h"
#include "SocketPacker.h"
#include "SocketBuffer.h"
#include "ServerConfig.h"
class INetMsg;

class SessionObject{
protected:
	ConnectionConfig config;
	ServerAdapter* server;
	int_x networkId;
	void *userData;

protected:
	SessionObject(ConnectionConfig config, ServerAdapter* server)
	{
		this->config = config;
		this->server = server;
		userData = NULL;
		networkId = 0;
	}

	virtual ~SessionObject()
	{

	}
public:
	virtual const char* getSocketIpPort() const = 0;
	virtual const uint_x getSocketIp() const = 0;
	virtual const ushort_x getSocketPort() const = 0;
	virtual time_x getLastRecvTime() const = 0;
	const ConnectionConfig& getConfig() const
	{
		return config;
	}
	ServerAdapter* getServer() const
	{
		return server;
	}
	SocketPacker* getSocketPacker() const
	{
		return config.sp;
	}
	INetMsg* getNetMsgHandler() const
	{
		return config.msg;
	}
	const SocketStream* getSocketStream() const
	{
		return config.sp->GetSocketStream();
	}

	int_x getNetworkId() const {
		return networkId;
	}
	void setNetworkId(int_x val) {
		networkId = val;
	}

	void * getUserData() const
	{
		return userData;
	}
	void setUserData(void * val)
	{
		userData = val;
	}
};

#endif