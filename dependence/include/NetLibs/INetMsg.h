#ifndef INETMSG_H
#define INETMSG_H

#include "NetLibsHeader.h"

#include "SocketByte.h"

/************************************************************************/
/* ������Ϣ�ӿ�                                                         */
/************************************************************************/
class INetMsg {
public:
	/// ����������������
	virtual void OnAccept(SessionObject* so)=0;

	/// ����������������
	virtual void OnConnect(SessionObject* so)=0;

	/// �������ӹر�
	virtual void OnClose(SessionObject* so)=0;

	/// ���յ�����
	virtual void OnRecv(SessionObject* so, int_x n_ptl, SocketByte& socketByte)=0;

	/// �����ѷ���
	virtual void OnSent(SessionObject* so)=0;

	/// �������糬ʱ
	virtual void OnOutTime(SessionObject* so)=0;

	/// �������
	virtual void OnError(SessionObject* so, std::string info, int type=0)=0;

	/// �������ر�
	//virtual void OnShutdown()=0;
};

#endif


