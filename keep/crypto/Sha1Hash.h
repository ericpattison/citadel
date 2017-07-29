#ifndef _SHA1HASH_H_
#define _SHA1HASH_H_

#include "Hash.h"

class Sha1Hash : Hash<Sha1> {
public:
	Sha1Hash();
	Sha1Hash(String str);
	Sha1Hash(byte* data, u32 len);

	Sha1Hash& update(const byte* data, u32 len);
	Sha1 hash();

private:
	class Impl;
	SPtr<Impl> impl;
};

#endif