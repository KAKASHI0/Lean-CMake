#ifndef SERVERADAPTER_H
#define SERVERADAPTER_H

#include "NetLibsHeader.h"
#include "INetMsg.h"
#include "ServerConfig.h"
#include "SocketPacker.h"
#include "SessionObject.h"

class SocketByte;
class SessionObject;

class ServerAdapter {
public:
	ServerAdapter();
	virtual ~ServerAdapter();
public:
	/**
	* 配置服务器
	* @param sc 配置文件结构对像
	*/
	virtual void SetConfig(ServerConfig* sc)=0;
	/**
	* 初始化服务器
	*/
	virtual bool_x Initialize()=0;
	/**
	* 释放服务器资源
	*/
	virtual void Release()=0;
	/**
	* 开启服务器
	* @return 成功/失败
	*/
	virtual bool_x StartupServer()=0;
	/**
	* 重启服务器
	*/
	virtual bool_x ReStartupServer()=0;
	/**
	* 关闭服务器
	*/
	virtual void ShutServer()=0;

	/**
	  * @brief 开始监听一个端口。
	  *
	  * 一个Server可以同时监听多个端口。监听的属性通过config参数设置，Accept的连接的属性也通过config参数指定。
	  * @param[in] port 监听的端口
	  * @param[in] config 监听的属性和接收的连接的属性
	  * @return 监听的Socket对应的 SessionObject
	  */
	virtual SessionObject* Listen(ushort_x port, ConnectionConfig config)=0;
	/**
	  * @brief 开始连接一个指定的IP和端口
	  *
	  * 连接的参数通过config指定。可选的，节点标识和用户自定义数据也可以同时指定。函数返回时连接还未完成，完成连接要响应INetMsg::OnConnect()事件
	  * @param[in] ip 要连接的IP的字符串
	  * @param[in] port 要连接的端口
	  * @param[in] config 连接的参数设置
	  * @param[in] nodeIdentity 节点标识，默认不指定
	  * @param[in] userData 用户数据，默认为空
	  * @return 成功开始连接返回 true，失败返回 false
	  */
	virtual bool_x Connect(const char* ip, unsigned short port, ConnectionConfig config, int_x networkId = 0, void *userData = NULL)=0;

	/**
	* 关闭临时网络用户
	* @param so 
	*/
	virtual void CloseSessionObject(SessionObject* so)=0;

	/**
	* 发送数据包
	* @param so 
	* @param psb 
	*/
	virtual void SendPack(SessionObject* so, SocketByte& psb, int_x type)=0;

	/**
	* 发送数据包
	* @param so 
	* @param psb 
	*/
	virtual void SendPack(SessionObject* so, int_x ptl, SocketByte& psb, int_x type)
	{
		SocketByte temp = so->getSocketPacker()->WritePackHeader(ptl, psb);
		SendPack(so, temp, type);
	}

public:
	/**
	* 建立套接字服务器配置文件
	* @param conf 配置文件结构对像
	*/
	static ServerAdapter* CreateServer(ServerConfig* conf);
};

#endif