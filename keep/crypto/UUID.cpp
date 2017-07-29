#include "UUID.h"

#include "Sha1Hash.h"

#include <sstream>

UUID::UUID() {
	for (int i = 0; i < 16; ++i) { data[i] = 0; }
}

UUID::UUID(const byte* name, u32 len) {
	Sha1Hash hashFunc;
	Sha1 sha = hashFunc.update(name, len).hash();

	const byte* bytes = sha.bytes();
	for (int i = 0; i < 16; ++i) {
		data[i] = bytes[i];
	}
	data[6] = ((data[6] & 0x0f) | 80);
	data[8] = ((data[8] & 0x3f) | 0x80);
}

UUID::UUID(const byte* name, u32 len, const UUID& ns) {
	Sha1Hash hashFunc;
	Sha1 sha = hashFunc.update(ns.data, 16).update(name, len).hash();

	const byte* bytes = sha.bytes();
	for (int i = 0; i < 16; ++i) {
		data[i] = bytes[i];
	}
	data[6] = ((data[6] & 0x0f) | 80);
	data[8] = ((data[8] & 0x3f) | 0x80);
}

UUID::UUID(const UUID& uuid) {
	for (int i = 0; i < 16; ++i) {
		data[i] = uuid.data[i];
	}
}

UUID::UUID(UUID&& uuid) {
	for (int i = 0; i < 16; ++i) {
		data[i] = uuid.data[i];
	}
}

UUID::UUID(String& str) {
	const byte* strBytes = str.Bytes();
	uint8_t* bp = data;
	for (int i = 0; i < 32; i+=2) {
		sscanf_s((const char*)(strBytes + i), "%2hhx", bp++);
	}
}

UUID& UUID::operator=(const UUID& uuid) {
	for (int i = 0; i < 16; ++i) {
		data[i] = uuid.data[i];
	}

	return *this;
}

UUID& UUID::operator=(UUID&& uuid) {
	for (int i = 0; i < 16; ++i) {
		data[i] = uuid.data[i];
	}
	return *this;
}

bool operator==(const UUID& lhs, const UUID& rhs) {
	for (s32 i = 15; i >= 0; --i) {
		if (lhs.data[i] != rhs.data[i]) return false;
	}
	return true;
}