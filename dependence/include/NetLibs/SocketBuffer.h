/** @file SocketBuffer.h
* @date 2009-9-22
* @author Jiaohang
* 
* @brief Brief
* 
* Detail
*/

#ifndef SOCKETBUFFER_H
#define SOCKETBUFFER_H

#include "PoolObject.h"
#include "NetLibsData.h"
#include "NetLibsHeader.h"

class SocketBufferPoolType;

// 表示缓冲区的内存，放在内存池中
class SocketBuffer : public PoolObject<SocketBuffer>
{
	/// 这个缓冲区所用的内存池的类型
	int_x poolType;
	/// 申请到的内存
	byte_x* buf;

public:
	explicit SocketBuffer(int_x poolType);
	virtual ~SocketBuffer();

	byte_x* getPointer() const
	{
		return static_cast<byte_x*>(buf);
	}

	int_x getSize() const
	{
		return s_RequestedSize[poolType];
	}

	int_x getPoolType() const
	{
		return poolType;
	}

	static int_x getBufferSize(int_x poolType);
	static int_x getBufferNum(int_x poolType);
	static int_x getBufferMaxNum(int_x poolType);
	static bool_x isStartDrop(int_x poolType);

private:
	GLOBAL_MUTEX_DECLARE(s_BufferPool);
	static SocketBufferPoolType *s_BufferPool[SOCKET_BYTE_POOL_NUM];
	static int_x s_RequestedSize[SOCKET_BYTE_POOL_NUM];

	static int_x s_BufferMaxNum[SOCKET_BYTE_POOL_NUM];
	static int_x s_BufferNum[SOCKET_BYTE_POOL_NUM];
	static int_x s_BufferStartDropNum[SOCKET_BYTE_POOL_NUM];
public:
	static void initPool(int_x poolType, int_x len, int_x initNum, int_x incNum, int_x startDropNum);
};

typedef shared_ptr_pool<SocketBuffer> SocketBufferPtr;

#endif // SOCKETBUFFER_H
