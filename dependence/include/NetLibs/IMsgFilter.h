#ifndef IMSGFILTER_H
#define IMSGFILTER_H

class SessionObject;
class SocketByte;

class IMsgFilter {
public:
	 /**
	  * ���������û���������
	  * @param so 
	  * @return 
	  */
	virtual int_x HandlerNetUserCreate(SessionObject& so)=0;
	 /**
	  * ��������������ݹ���
	  * @param tsb 
	  * @return 
	  */
	virtual int_x HandlerRecvData(SocketByte& tsb)=0;
};

#endif


