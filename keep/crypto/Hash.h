#ifndef _HASH_H_
#define _HASH_H_

#include "../types.h"

template<class T>
class Hash {
public:
	virtual Hash& update(const byte* data, u32 len) = 0;
	virtual T hash() = 0;
};

#endif