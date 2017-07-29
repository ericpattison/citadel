#ifndef _UUID_H_
#define _UUID_H_

#include "../types.h"

class UUID {
public:
	UUID();
	UUID(const byte* name, u32 len);
	UUID(const byte* name, u32 len, const UUID& ns);
	~UUID() = default;
	UUID(const UUID& uuid);
	UUID(UUID&& uuid);
	UUID(String& str);
	UUID& operator=(const UUID& uuid);
	UUID& operator=(UUID&& uuid);

	friend bool operator==(const UUID& lhs, const UUID& rhs);
private:
	byte data[16];
};

UUID UUID_NIL(String("00000000000000000000000000000000"));
UUID UUID_NS_DNS(String("6ba7b8109dad11d180b400c04fd430c8"));
UUID UUID_NS_URL(String("6ba7b8119dad11d180b400c04fd430c8"));
UUID UUID_NS_OID(String("6ba7b8129dad11d180b400c04fd430c8"));
UUID UUID_NS_X500(String("6ba7b8149dad11d180b400c04fd430c8"));

#endif