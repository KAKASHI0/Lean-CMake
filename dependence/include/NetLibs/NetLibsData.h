#ifndef NETLIBSDATA_H
#define NETLIBSDATA_H

/** 服务相关定议 */

// 每个用户的发送缓冲包最大数量
#define GAME_PLAYER_MAX_SEND_PACK 100
// 每个用户的接受缓冲包最大数量
#define GAME_PLAYER_MAX_RECV_PACK 10

// 服务器排队
#define GAME_SERVER_QUEUING_MAX 500

// 服务器用户最大承载量
#define GAME_SERVER_MAX_PLAYER 500

// 单次发包的最大组包数目
#define GAME_SERVER_MAX_PACK_NUM_SINGLE_SEND 500

// 服务器数据包缓冲池最大数量
#define GAME_SERVER_MAX_SEND_BUFFER (GAME_SERVER_MAX_PLAYER * GAME_PLAYER_MAX_SEND_PACK + GAME_SERVER_QUEUING_MAX + 100)
// 服务器网关客户端收包缓存最大数量
#define GAME_SERVER_MAX_RECV_BUFFER_NUM (GAME_SERVER_MAX_PLAYER * GAME_PLAYER_MAX_RECV_PACK + 100)
// 服务器接收到包数据最大长度
#define GAME_SERVER_PACK_MAX_LEN 4000
#define GAME_SERVER_PACK_MEMORY_POOL_SIZE 100
#define GAME_SERVER_PACK_START_DROP_NUM 100000

#define GAME_SERVER_PACK_MAX_LEN_LOCAL 200000
#define GAME_SERVER_PACK_MEMORY_POOL_SIZE_LOCAL 10
#define GAME_SERVER_PACK_START_DROP_NUM_LOCAL 10000

#define GAME_SERVER_PACK_MAX_LEN_SMALL 400
#define GAME_SERVER_PACK_MEMORY_POOL_SIZE_SMALL 100
#define GAME_SERVER_PACK_START_DROP_NUM_SMALL 100000

// 服务器阻塞模式
#define SOCKET_SERVER_BLOCKING_METHOD 0x0

// 服务器IOCP模式
#define SOCKET_SERVER_IOCP_METHOD 0xFF

// 服务器epoll模式
#define SOCKET_SERVER_EPOLL_METHOD 0xFF00

enum SEND_PACK_TYPE
{
	SEND_PACK_TYPE_UNDROPABLE,
	SEND_PACK_TYPE_DROPABLE,
	SEND_PACK_TYPE_DELAYABLE
};

// 缓冲区内存池类型
enum SOCKET_BYTE_POOL
{
	SOCKET_BYTE_POOL_CLIENT, // 发送给客户端的发送缓存
	SOCKET_BYTE_POOL_LOCAL, // 局域网通信、本地角色数据串行等
	SOCKET_BYTE_POOL_SMALL, // 用于确定比较小(400B)的发送缓存，很多消息都可以用这个，防止内存池占用过多内存
	SOCKET_BYTE_POOL_NUM
};

// 给发送缓存预留的头部的空间字节数
const int_x PACKET_SEND_RESERVED_HEAD_SIZE = 24;

// 连接IP字符串最大大小
const int_x SOCKET_SERVER_IP_STRING_MAX_LEN = 30;

#endif