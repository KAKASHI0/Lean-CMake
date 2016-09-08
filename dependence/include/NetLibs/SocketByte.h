#ifndef SOCKETBYTE_H
#define SOCKETBYTE_H

#include "NetLibsHeader.h"
#include <boost/thread.hpp>
#include <stdint.h>
#include "Platform.h"
#include "BaseType.h"
#include "PoolObject.h"
#include "SocketBuffer.h"

/// ��ʾһ�����������
class SocketByte : public PoolObject<SocketByte>{
	/// ʹ�õĻ������ڴ�
	SocketBufferPtr socketBuffer;
	/// ��ʵ���ڻ������е���ʼλ��
	byte_x* body;
	/// ���ĳ���
	int_x len;
	/// ��ǰλ�ã����ڴ��л�
	mutable int_x pos;

	friend class SocketStream;
	friend class SocketStreamBE;

public:
	SocketByte()
	{

	}
	/**
	  * @brief ����һ�������õ���ʱSocketByte����ʹ�ù���ָ�룬ֻ���ڴ��л�
	  * @<p> <B>ע*</B> ���������緢�� </p>
	  * @param[in] body ��������
	  * @param[in] len ����
	  */
	SocketByte(byte_x* body, int_x len)
	{
		this->body = body;
		this->len = len;
		this->pos = 0;
	}
	/**
	  * @brief ����һ�����յ��İ���ֻ���������õ�
	  *
	  * ��������������캯���ڻ������Ͻ���һ����������
	  * @param[in] buf �������Ĺ���ָ��
	  * @param[in] offset �ڻ������е���ʼλ��
	  * @param[in] len ���ĳ���
	  */
	SocketByte(SocketBufferPtr buf, int_x offset, int_x len)
	{
		this->socketBuffer = buf;
		this->body = buf->getPointer() + offset;
		this->pos = 0;
		this->len = len;
	}
	/**
	  * @brief ����һ�����ͻ����
	  *
	  * ����һ�������棬���ڷ��͡����ڲ�Ԥ���������дͷ���Ŀռ䡣
	  * @param[in] poolType �ڴ�����ͣ�SOCKET_BYTE_POOL_CLIENT��SOCKET_BYTE_POOL_LOCAL֮һ
	  */
	explicit SocketByte(SOCKET_BYTE_POOL poolType)
	{
		socketBuffer.reset(new SocketBuffer(poolType));
		this->body = socketBuffer->getPointer();
		this->len = 0;
		this->pos = 0;
	}
	/**
	  * @brief �������е��������ƫ��һЩ��ʼλ�ã�����һ���°�����β��ԭ�а��Ľ�β
	  *
	  * @param[in] socketByte ���е������
	  * @param[in] offset ƫ�ƴ�С
	  */
	SocketByte(const SocketByte& socketByte, int_x offset)
	{
		this->socketBuffer = socketByte.socketBuffer;
		this->body = socketByte.body + offset;
		this->pos = 0;
		this->len = socketByte.len - offset;
	}
	/**
	  * @brief �������е��������ƫ��һЩλ�ã���ָ�����Ƚ���һ���°�
	  *
	  * @param[in] socketByte ���е������
	  * @param[in] offset ƫ�ƴ�С
	  * @param[in] newLen �µİ�����
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
	  * ������ָ��λ��
	  * @param pos 
	  */
	void skipTo(int_x pos)
	{
		this->pos = pos;
	}

	 /**
	  * �ڵ�ǰ����λ����ǰ�ƶ�num��λ��
	  * @param num 
	  */
	void advance(int_x num)
	{
		pos += num;
	}

	 /**
	  * ������λ�ã�pos == 0
	  */
	void resetPos()
	{
		pos = 0;
	}

	 /**
	  * ������ݣ����������ͷŲ���
	  */
	void clean()
	{
		resetPos();
		len = 0;
	}

	 /**
	  * �������ǰλ��
	  * @return ��ǰ��λ��
	  */
	int_x getPos() const
	{
		return pos;
	}

	/**
	* ��ó����ݳ���
	* @return 
	*/
	int_x getLen() const
	{
		return len;
	}

	/**
	  * @brief �õ������ݵ�ָ��
	  * @return �����ݵ�ָ��
	  */
	byte_x* getBody() const
	{
		return body;
	}

	/**
	  * @brief �õ������û�����
	  *
	  * @return �������Ĺ���ָ��
	  */
	SocketBufferPtr getBuffer() const
	{
		return socketBuffer;
	}

	/**
	  * @brief ��־����β��������¼������
	  */
	void markEnd()
	{
		len = pos;
	}
	
	
public:
	// λ����
	int_x currentBitLeftInByte; ///< ��ǰ�ֽ��ڻ��ɹ���д��bit��ʣ������0��7�仯
	/// ��ȡbits��λ����Ϊһ���޷����������ʼ��ȡǰӦ�ð�currentBitLeftInByte��ֵΪ0 ������λ����ȡ�ֽ���ʱ������¸����ֽڿ�ʼ
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
	/// ��value��Ϊbits��λд�뻺�档�ʼд��ǰӦ�ð�currentBitLeftInByte��ֵΪ0������λ��д���ֽ���ʱ������¸����ֽڿ�ʼ
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