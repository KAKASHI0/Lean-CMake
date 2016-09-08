#ifndef INETMSG_H
#define INETMSG_H

#include "NetLibsHeader.h"

#include "SocketByte.h"

/************************************************************************/
/* 网络消息接口                                                         */
/************************************************************************/
class INetMsg {
public:
	/// 创建连入网络链接
	virtual void OnAccept(SessionObject* so)=0;

	/// 创建连出网络链接
	virtual void OnConnect(SessionObject* so)=0;

	/// 网络链接关闭
	virtual void OnClose(SessionObject* so)=0;

	/// 接收到数据
	virtual void OnRecv(SessionObject* so, int_x n_ptl, SocketByte& socketByte)=0;

	/// 数据已发送
	virtual void OnSent(SessionObject* so)=0;

	/// 处理网络超时
	virtual void OnOutTime(SessionObject* so)=0;

	/// 网络出错
	virtual void OnError(SessionObject* so, std::string info, int type=0)=0;

	/// 网络服务关闭
	//virtual void OnShutdown()=0;
};

#endif


