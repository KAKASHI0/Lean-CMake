#ifndef SOCKETBYTE_H
#define SOCKETBYTE_H

#include "NetLibsHeader.h"
#include <boost/thread.hpp>
#include <stdint.h>
#include "Platform.h"
#include "BaseType.h"
#include "PoolObject.h"
#include "SocketBuffer.h"

/// 表示一个网络包的类
class SocketByte : public PoolObject<SocketByte>{
	/// 使用的缓冲区内存
	SocketBufferPtr socketBuffer;
	/// 包实际在缓冲区中的起始位置
	byte_x* body;
	/// 包的长度
	int_x len;
	/// 当前位置，用于串行化
	mutable int_x pos;

	friend class SocketStream;
	friend class SocketStreamBE;

public:
	SocketByte()
	{

	}
	/**
	  * @brief 建立一个弱引用的临时SocketByte，不使用共享指针，只用于串行化
	  * @<p> <B>注*</B> 不用于网络发包 </p>
	  * @param[in] body 数据内容
	  * @param[in] len 长度
	  */
	SocketByte(byte_x* body, int_x len)
	{
		this->body = body;
		this->len = len;
		this->pos = 0;
	}
	/**
	  * @brief 建立一个接收到的包，只有网络库会用到
	  *
	  * 网络库会用这个构造函数在缓冲区上建立一个包的描述
	  * @param[in] buf 缓冲区的共享指针
	  * @param[in] offset 在缓冲区中的起始位置
	  * @param[in] len 包的长度
	  */
	SocketByte(SocketBufferPtr buf, int_x offset, int_x len)
	{
		this->socketBuffer = buf;
		this->body = buf->getPointer() + offset;
		this->pos = 0;
		this->len = len;
	}
	/**
	  * @brief 建立一个发送缓存包
	  *
	  * 申请一个包缓存，用于发送。其内部预留了网络库写头部的空间。
	  * @param[in] poolType 内存池类型，SOCKET_BYTE_POOL_CLIENT、SOCKET_BYTE_POOL_LOCAL之一
	  */
	explicit SocketByte(SOCKET_BYTE_POOL poolType)
	{
		socketBuffer.reset(new SocketBuffer(poolType));
		this->body = socketBuffer->getPointer();
		this->len = 0;
		this->pos = 0;
	}
	/**
	  * @brief 根据现有的网络包，偏移一些开始位置，建立一个新包，结尾是原有包的结尾
	  *
	  * @param[in] socketByte 现有的网络包
	  * @param[in] offset 偏移大小
	  */
	SocketByte(const SocketByte& socketByte, int_x offset)
	{
		this->socketBuffer = socketByte.socketBuffer;
		this->body = socketByte.body + offset;
		this->pos = 0;
		this->len = socketByte.len - offset;
	}
	/**
	  * @brief 根据现有的网络包，偏移一些位置，以指定长度建立一个新包
	  *
	  * @param[in] socketByte 现有的网络包
	  * @param[in] offset 偏移大小
	  * @param[in] newLen 新的包长度
	  */
	SocketByte(const SocketByte& socketByte, int_x offset, int_x newLen)
	{
		this->socketBuffer = socketByte.socketBuffer;
		this->body = socketByte.body + offset;
		this->pos = 0;
		this->len = newLen;
	}
	virtual ~SocketByte()
	{
	}

public:
	 /**
	  * 跳到流指定位置
	  * @param pos 
	  */
	void skipTo(int_x pos)
	{
		this->pos = pos;
	}

	 /**
	  * 在当前流中位置向前移动num个位置
	  * @param num 
	  */
	void advance(int_x num)
	{
		pos += num;
	}

	 /**
	  * 重置流位置，pos == 0
	  */
	void resetPos()
	{
		pos = 0;
	}

	 /**
	  * 清除数据，但不做内释放操作
	  */
	void clean()
	{
		resetPos();
		len = 0;
	}

	 /**
	  * 获得流当前位置
	  * @return 当前流位置
	  */
	int_x getPos() const
	{
		return pos;
	}

	/**
	* 获得长数据长度
	* @return 
	*/
	int_x getLen() const
	{
		return len;
	}

	/**
	  * @brief 得到包内容的指针
	  * @return 包内容的指针
	  */
	byte_x* getBody() const
	{
		return body;
	}

	/**
	  * @brief 得到包所用缓冲区
	  *
	  * @return 缓冲区的共享指针
	  */
	SocketBufferPtr getBuffer() const
	{
		return socketBuffer;
	}

	/**
	  * @brief 标志包结尾，用来记录包长度
	  */
	void markEnd()
	{
		len = pos;
	}
	
	
public:
	// 位操作
	int_x currentBitLeftInByte; ///< 当前字节内还可供读写的bit的剩余量，0～7变化
	/// 读取bits个位，作为一个无符号整数。最开始读取前应该把currentBitLeftInByte赋值为0 ；结束位流读取字节流时，会从下个整字节开始
	void readBitsStart(){currentBitLeftInByte = 0;}
	uint_x readBits(int_x bits) {
		const uint_x maskBits[] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};
		int_x result = 0;
		while (bits > 0) {
			if (currentBitLeftInByte == 0) {
				++pos;
				currentBitLeftInByte = 8;
			}
			int_x readBits = currentBitLeftInByte;
			if (readBits > bits)
				readBits = bits;
			currentBitLeftInByte -= readBits;
			bits -= readBits;
			result = (result << readBits) | ((body[pos - 1] >> currentBitLeftInByte) & maskBits[readBits]);
		}
		return result;
	}
	/// 将value作为bits个位写入缓存。最开始写入前应该把currentBitLeftInByte赋值为0；结束位流写入字节流时，会从下个整字节开始
	void writeBitsStart(){currentBitLeftInByte = 0;}
	void writeBits(uint_x value, int_x bits) {
		const uint_x maskBits[] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

		while (bits > 0) {
			if (currentBitLeftInByte == 0) {
				body[pos] = 0;
				++pos;
				currentBitLeftInByte = 8;
			}
			int_x writeBits = currentBitLeftInByte;
			if (writeBits > bits)
				writeBits = bits;
			bits -= writeBits;
			currentBitLeftInByte -= writeBits;
			body[pos - 1] |= ((value >> bits) & maskBits[writeBits]) << currentBitLeftInByte;
		}
	}
};

#endif