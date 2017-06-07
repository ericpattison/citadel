#ifndef _IOSTREAM_H_
#define _IOSTREAM_H_

#include <string>
#include "../keep/types.h"

class IStream {
public:
	IStream() { }
	virtual ~IStream() { }

	virtual std::string	GetVirtualFilename() const = 0;
	virtual std::string	GetFilename() const = 0;
	virtual void		Seek(const u64 position) = 0;
	virtual u64			Read(handle buffer, const u64 size) = 0;
	virtual	bool		EndOfFile() const = 0;
	virtual u64			GetSize() const = 0;
	virtual u64			GetPosition() const = 0;
	virtual u64			GetBytesLeft() const { return GetSize() - GetPosition(); }

	virtual const byte*	MapStream() const = 0;
	virtual const byte*	MapStreamFromCurrentPosition() const = 0;
};

#endif