#ifndef _SHA1_H_
#define _SHA1_H_

#include "../types.h"

class Sha1 {
public:
	Sha1(byte* bytes = nullptr);
	~Sha1() = default;
	Sha1(const Sha1& sha1);
	Sha1(Sha1&& sha1);
	Sha1& operator=(const Sha1& sha1);
	Sha1& operator=(Sha1&& sha1);

	const byte* bytes() const;
private:
	byte data[20];
};

#endif