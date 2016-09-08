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
	  * @brief Brief �����������������Ϊ�������ݰ�
	  *
	  * ����ӿ���������������������õ�ǰ�յ������ݹ���һ��SocketByte��������getBody()���ǿɶ�ȡ���ݵĿ�ʼ��getLen()���ǿɶ�ȡ���ݵĳ��ȡ�
	  * SocketByte��ͷ��֮ǰ����PACKET_SEND_RESERVED_HEAD_SIZE�ֽڵĳ��ȿ�������ʹ�á�
	  * ����������SocketByte�ĵ�ǰ��ȡλ��Ӧ�ñ�ʶʹ���˶��ٻ��棬��getPos()֮ǰ�����ݶ����Ѿ�������������getPos()֮������ݶ��ǲ���һ������δ��������ݡ�
	  * getBuffer().getSize()���Եõ�һ������󳤶����ơ�
	  * @param[in] so ������SessionObject
	  * @param[inout] socketByte ���ջ��������
	  * @return �¸������ܴ�С��0��ʾû�л�δ֪��-1��ʾ��ȡ��λ
	  */
	virtual int_x Unpack(SessionObject* so, SocketByte& socketByte);

	/**
	  * @brief д��Э��ͷ��
	  *
	  * ������������µ�SocketByte������ʵ�ϲ������ڴ渴�ƣ�Э���ͷ��������SocketByte֮ǰд�롣����SocketByteӦԤ���㹻������д��ͷ���Ŀռ䡣
	  * @param[in] n_ptl Э���
	  * @param[in] socketByte Э������
	  * @return �µİ���Э��ͷ��SocketByte������ֱ��ͨ��ServerAdapter����ȥ��
	  */
	virtual SocketByte WritePackHeader(int_x n_ptl, SocketByte& socketByte);

	/**
	  * @brief ��ȡЭ��ͷ��
	  * @param[inout] socketByte ��ȡ����
	  * @param[in] maxLen Э�����������󳤶�
	  * @param[out] len ���ڽ���Э������ݵĴ�С��������Э��ͷ�Ĵ�С
	  * @param[out] ptl ���ڽ���Э���
	  * @return ����Э��ͷ���Ĵ�С��0 ��ʾ�����е��ֽ���̫�٣���Ҫ�������ݣ�-1 ��ʾЭ��ͷ����
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


