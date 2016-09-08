#ifndef IMSGFILTER_H
#define IMSGFILTER_H

class SessionObject;
class SocketByte;

class IMsgFilter {
public:
	 /**
	  * 处理网络用户创建过滤
	  * @param so 
	  * @return 
	  */
	virtual int_x HandlerNetUserCreate(SessionObject& so)=0;
	 /**
	  * 处理网络接收数据过滤
	  * @param tsb 
	  * @return 
	  */
	virtual int_x HandlerRecvData(SocketByte& tsb)=0;
};

#endif


