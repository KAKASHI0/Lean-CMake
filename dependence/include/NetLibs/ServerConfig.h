#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include "NetLibsHeader.h"
#include "INetMsg.h"
#include "IMsgFilter.h"

class ServerConfig {
public:
	ServerConfig() 
	{
	}
	virtual ~ServerConfig()
	{

	}
public:
	//// 网络消息处理对像
	//INetMsg* obj_net_msg;

	//// 网络消息过滤器对像
	//IMsgFilter* obj_msg_filt;

	// 网络类型 (通用阻塞模式、iocp模式、epoll模式)
	int_x v_server_type;

	//// 网络端口
	//int_x v_server_port;

	// 网络链接超时时间值
	int_x v_time_out;

	// 网络处理最大用户数
	int_x v_usr_size;

	//// 网络最大排队用户数
	//int_x v_usr_ranks_size;

	//// 用户网络发送包最大数量
	//int_x v_usr_pack_size;

	//// 用户网络发送包缓冲大小
	//int_x v_usr_pack_buf_size;



	// TODO...
	;
};

class ConnectionConfig {
public:
	///@name 通用设置
	//@{
	// 网络消息处理对像
	INetMsg* msg;
	// 网络消息打包解包器
	SocketPacker* sp;

	// 单个用户正在发送的最大数据量（即切包大小）
	int_x sendMaxSendingSize;
	// 用户发送缓存中不可丢包的最大数目（如果缓存中不可丢包超过这个数字，则会断开连接）
	int_x sendMaxUndropableSize;
	// 用户发送缓存开始丢包时的缓存包数目（如果缓存中所有包的数目总和超过这个数字，那么可丢包将会被丢弃）
	int_x sendStartDropSize;
	// 用户收包缓冲
	int_x recvBufferPoolType;
	/// 是否要Gracefully断开
	bool_x bLinger;
	//@}
	// 网络监听未接受队列大小
	int_x listenBacklog;
	// 网络监听预准备的socket个数
	int_x listenPreparedSocket;
};

#endif


