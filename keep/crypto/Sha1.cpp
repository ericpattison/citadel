#include "Sha1.h"

Sha1::Sha1(byte bytes[20]) {
	if (bytes != nullptr) {
		for (u32 i = 0; i < 20; ++i) {
			data[i] = bytes[i];
		}
	}
}

Sha1::Sha1(const Sha1& sha1) {
	for (u32 i = 0; i < 20; ++i) {
		data[i] = sha1.data[i];
	}
}

Sha1::Sha1(Sha1&& sha1) {
	for (u32 i = 0; i < 20; ++i) {
		data[i] = sha1.data[i];
	}
}

Sha1& Sha1::operator=(const Sha1& sha1) {
	for (u32 i = 0; i < 20; ++i) {
		data[i] = sha1.data[i];
	}
	return *this;
}

Sha1& Sha1::operator=(Sha1&& sha1) {
	for (u32 i = 0; i < 20; ++i) {
		data[i] = sha1.data[i];
	}
	return *this;
}

const byte* Sha1::bytes() const {
	return data;
}