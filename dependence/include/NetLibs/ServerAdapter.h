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
	* ���÷�����
	* @param sc �����ļ��ṹ����
	*/
	virtual void SetConfig(ServerConfig* sc)=0;
	/**
	* ��ʼ��������
	*/
	virtual bool_x Initialize()=0;
	/**
	* �ͷŷ�������Դ
	*/
	virtual void Release()=0;
	/**
	* ����������
	* @return �ɹ�/ʧ��
	*/
	virtual bool_x StartupServer()=0;
	/**
	* ����������
	*/
	virtual bool_x ReStartupServer()=0;
	/**
	* �رշ�����
	*/
	virtual void ShutServer()=0;

	/**
	  * @brief ��ʼ����һ���˿ڡ�
	  *
	  * һ��Server����ͬʱ��������˿ڡ�����������ͨ��config�������ã�Accept�����ӵ�����Ҳͨ��config����ָ����
	  * @param[in] port �����Ķ˿�
	  * @param[in] config ���������Ժͽ��յ����ӵ�����
	  * @return ������Socket��Ӧ�� SessionObject
	  */
	virtual SessionObject* Listen(ushort_x port, ConnectionConfig config)=0;
	/**
	  * @brief ��ʼ����һ��ָ����IP�Ͷ˿�
	  *
	  * ���ӵĲ���ͨ��configָ������ѡ�ģ��ڵ��ʶ���û��Զ�������Ҳ����ͬʱָ������������ʱ���ӻ�δ��ɣ��������Ҫ��ӦINetMsg::OnConnect()�¼�
	  * @param[in] ip Ҫ���ӵ�IP���ַ���
	  * @param[in] port Ҫ���ӵĶ˿�
	  * @param[in] config ���ӵĲ�������
	  * @param[in] nodeIdentity �ڵ��ʶ��Ĭ�ϲ�ָ��
	  * @param[in] userData �û����ݣ�Ĭ��Ϊ��
	  * @return �ɹ���ʼ���ӷ��� true��ʧ�ܷ��� false
	  */
	virtual bool_x Connect(const char* ip, unsigned short port, ConnectionConfig config, int_x networkId = 0, void *userData = NULL)=0;

	/**
	* �ر���ʱ�����û�
	* @param so 
	*/
	virtual void CloseSessionObject(SessionObject* so)=0;

	/**
	* �������ݰ�
	* @param so 
	* @param psb 
	*/
	virtual void SendPack(SessionObject* so, SocketByte& psb, int_x type)=0;

	/**
	* �������ݰ�
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
	* �����׽��ַ����������ļ�
	* @param conf �����ļ��ṹ����
	*/
	static ServerAdapter* CreateServer(ServerConfig* conf);
};

#endif