#ifndef _OSTREAM_H_
#define _OSTREAM_H_

#include <string>
#include "../keep/types.h"

class OStream {
public:
	OStream() {}
	virtual ~OStream() { }

	virtual std::string	GetFilename() const = 0;
	virtual void		Seek(const u64 position) = 0;
	virtual u64			GetFilePosition() const = 0;
	virtual u64			Write(const handle buffer, const u64 size) = 0;
};

#endif