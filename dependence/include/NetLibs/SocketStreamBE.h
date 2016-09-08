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
	// д��byte�� 8
	virtual void WriteByte(SocketByte& sb, byte_x value) const;
	// д��unsigned byte�� 8
	virtual void WriteUnsignedByte(SocketByte& sb, ubyte_x value) const;
	// д���ֽ�����
	virtual void WriteBytes(SocketByte& sb, const byte_x* value, int_x len) const;
	// д��short�� 16
	virtual void WriteShort(SocketByte& sb, short_x value) const;
	// д��unsigned short�� 16
	virtual void WriteUnsignedShort(SocketByte& sb, ushort_x value) const;
	// д��int�� 32
	virtual void WriteInt(SocketByte& sb, int_x value) const;
	// д��uint�� 32
	virtual void WriteUnsignedInt(SocketByte& sb, uint_x value) const;
	// д��long�� 48
	virtual void WriteLong(SocketByte& sb, long_x value) const;
	// д��bool�� 8
	virtual void WriteBoolean(SocketByte& sb, bool_x value) const;
	// д��string
	virtual void WriteString(SocketByte& sb, const char_x* value, int_x len) const; 

	// д��string
	template<int_x Length>
	void WriteString(SocketByte& sb, XString<Length>& str) const
	{
		int_x len = str.size();
		WriteInt(sb, len);
		memcpy(sb.body + sb.pos, str.getPointer(len), len);
		sb.pos += len;
	}

	// ��ȡbyte�� 8
	virtual byte_x ReadByte(const SocketByte& value) const;
	// ��ȡunsigned byte�� 8
	virtual ubyte_x ReadUnsignedByte(const SocketByte& value) const;
	// ��ȡshort�� 16
	virtual short_x ReadShort(const SocketByte& value) const;
	// ��ȡunsigned short�� 16
	virtual ushort_x ReadUnsignedShort(const SocketByte& value) const;
	// ��ȡint�� 32
	virtual int_x ReadInt(const SocketByte& value) const;
	// ��ȡuint�� 32
	virtual uint_x ReadUnsignedInt(const SocketByte& value) const;
	// ��ȡlong�� 48
	virtual long_x ReadLong(const SocketByte& value) const;
	// ��ȡbool�� 8
	virtual bool_x ReadBoolean(const SocketByte& value) const;
	// ��ȡstring
	virtual void ReadString(const SocketByte& value, char_x* str, int_x len) const;

	virtual void ReadString(const SocketByte& value, std::string& str) const;
	// ��ȡ�ֽ�����
	virtual void ReadBytes(const SocketByte& value, byte_x* bs, int_x len) const;
	// ��ȡXString
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


