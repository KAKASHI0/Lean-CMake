#ifndef SOCKETSTREAMBE_H
#define SOCKETSTREAMBE_H

#include "BaseType.h"
#include "SocketByte.h"
#include "SocketStream.h"
#include <iostream>
#include <string>
#include <memory>
using namespace std;

#include "XString.h"

class SocketStreamBE : public SocketStream {
public:
	SocketStreamBE();
	virtual ~SocketStreamBE();
	static const SocketStreamBE* getInstance()
	{
		static SocketStreamBE instance;
		return &instance;
	}
public:
	// 写出byte型 8
	virtual void WriteByte(SocketByte& sb, byte_x value) const;
	// 写出unsigned byte型 8
	virtual void WriteUnsignedByte(SocketByte& sb, ubyte_x value) const;
	// 写出字节数组
	virtual void WriteBytes(SocketByte& sb, const byte_x* value, int_x len) const;
	// 写出short型 16
	virtual void WriteShort(SocketByte& sb, short_x value) const;
	// 写出unsigned short型 16
	virtual void WriteUnsignedShort(SocketByte& sb, ushort_x value) const;
	// 写出int型 32
	virtual void WriteInt(SocketByte& sb, int_x value) const;
	// 写出uint型 32
	virtual void WriteUnsignedInt(SocketByte& sb, uint_x value) const;
	// 写出long型 48
	virtual void WriteLong(SocketByte& sb, long_x value) const;
	// 写出bool型 8
	virtual void WriteBoolean(SocketByte& sb, bool_x value) const;
	// 写出string
	virtual void WriteString(SocketByte& sb, const char_x* value, int_x len) const; 

	// 写出string
	template<int_x Length>
	void WriteString(SocketByte& sb, XString<Length>& str) const
	{
		int_x len = str.size();
		WriteInt(sb, len);
		memcpy(sb.body + sb.pos, str.getPointer(len), len);
		sb.pos += len;
	}

	// 读取byte型 8
	virtual byte_x ReadByte(const SocketByte& value) const;
	// 读取unsigned byte型 8
	virtual ubyte_x ReadUnsignedByte(const SocketByte& value) const;
	// 读取short型 16
	virtual short_x ReadShort(const SocketByte& value) const;
	// 读取unsigned short型 16
	virtual ushort_x ReadUnsignedShort(const SocketByte& value) const;
	// 读取int型 32
	virtual int_x ReadInt(const SocketByte& value) const;
	// 读取uint型 32
	virtual uint_x ReadUnsignedInt(const SocketByte& value) const;
	// 读取long型 48
	virtual long_x ReadLong(const SocketByte& value) const;
	// 读取bool型 8
	virtual bool_x ReadBoolean(const SocketByte& value) const;
	// 读取string
	virtual void ReadString(const SocketByte& value, char_x* str, int_x len) const;

	virtual void ReadString(const SocketByte& value, std::string& str) const;
	// 读取字节数组
	virtual void ReadBytes(const SocketByte& value, byte_x* bs, int_x len) const;
	// 读取XString
	template<int_x Length>
	bool_x ReadString(SocketByte& value, XString<Length>& str) const
	{
		int_x len = ReadInt(value);
		if (len < 0 || len > Length)
		{
			return false;
		}

		ReadBytes(value, str.getPointer(len), len);

		return true;
	}
};
#endif


