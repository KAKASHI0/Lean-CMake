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
	//// ������Ϣ�������
	//INetMsg* obj_net_msg;

	//// ������Ϣ����������
	//IMsgFilter* obj_msg_filt;

	// �������� (ͨ������ģʽ��iocpģʽ��epollģʽ)
	int_x v_server_type;

	//// ����˿�
	//int_x v_server_port;

	// �������ӳ�ʱʱ��ֵ
	int_x v_time_out;

	// ���紦������û���
	int_x v_usr_size;

	//// ��������Ŷ��û���
	//int_x v_usr_ranks_size;

	//// �û����緢�Ͱ��������
	//int_x v_usr_pack_size;

	//// �û����緢�Ͱ������С
	//int_x v_usr_pack_buf_size;



	// TODO...
	;
};

class ConnectionConfig {
public:
	///@name ͨ������
	//@{
	// ������Ϣ�������
	INetMsg* msg;
	// ������Ϣ��������
	SocketPacker* sp;

	// �����û����ڷ��͵���������������а���С��
	int_x sendMaxSendingSize;
	// �û����ͻ����в��ɶ����������Ŀ����������в��ɶ�������������֣����Ͽ����ӣ�
	int_x sendMaxUndropableSize;
	// �û����ͻ��濪ʼ����ʱ�Ļ������Ŀ��������������а�����Ŀ�ܺͳ���������֣���ô�ɶ������ᱻ������
	int_x sendStartDropSize;
	// �û��հ�����
	int_x recvBufferPoolType;
	/// �Ƿ�ҪGracefully�Ͽ�
	bool_x bLinger;
	//@}
	// �������δ���ܶ��д�С
	int_x listenBacklog;
	// �������Ԥ׼����socket����
	int_x listenPreparedSocket;
};

#endif


