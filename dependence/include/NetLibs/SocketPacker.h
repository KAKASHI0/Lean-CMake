#ifndef SOCKETPACK_H
#define SOCKETPACK_H

#include "NetLibsHeader.h"
#include "SocketByte.h"
#include "SocketStream.h"

class INetMsg;
class SessionObject;

class SocketPacker {
public:
	SocketPacker();
	/**
	  * @brief Brief 将读到的数据流解包为单个数据包
	  *
	  * 这个接口用来解包网络包。网络库用当前收到的数据构造一个SocketByte对象，其中getBody()就是可读取数据的开始，getLen()就是可读取数据的长度。
	  * SocketByte的头部之前会有PACKET_SEND_RESERVED_HEAD_SIZE字节的长度可以任意使用。
	  * 函数结束后，SocketByte的当前读取位置应该标识使用了多少缓存，即getPos()之前的数据都是已经处理的网络包，getPos()之后的数据都是不足一个包而未处理的数据。
	  * getBuffer().getSize()可以得到一个包最大长度限制。
	  * @param[in] so 关联的SessionObject
	  * @param[inout] socketByte 接收缓存的引用
	  * @return 下个包的总大小，0表示没有或未知，-1表示读取错位
	  */
	virtual int_x Unpack(SessionObject* so, SocketByte& socketByte);

	/**
	  * @brief 写入协议头部
	  *
	  * 这个函数返回新的SocketByte，但事实上不进行内存复制，协议的头部在内容SocketByte之前写入。内容SocketByte应预留足够的用来写入头部的空间。
	  * @param[in] n_ptl 协议号
	  * @param[in] socketByte 协议内容
	  * @return 新的包括协议头的SocketByte，可以直接通过ServerAdapter发出去。
	  */
	virtual SocketByte WritePackHeader(int_x n_ptl, SocketByte& socketByte);

	/**
	  * @brief 读取协议头部
	  * @param[inout] socketByte 读取缓存
	  * @param[in] maxLen 协议包的限制最大长度
	  * @param[out] len 用于接收协议包内容的大小，不包括协议头的大小
	  * @param[out] ptl 用于接收协议号
	  * @return 返回协议头部的大小；0 表示缓存中的字节数太少，需要更多数据；-1 表示协议头错误
	  */
	int_x ReadPackHeader(SocketByte& socketByte, int_x maxLen, int_x &len, int_x &ptl);

	virtual const SocketStream* GetSocketStream() const
	{
		return ss;
	}

	static SocketPacker* getInstance()
	{
		static SocketPacker instance;
		return &instance;
	}
private:
	const SocketStream *ss;
};
#endif


