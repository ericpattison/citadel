#include "Sha1Hash.h"
#include "Sha1.h"

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class Sha1Hash::Impl {
public:
	Impl(){
		h[0] = 0x67452301;
		h[1] = 0xEFCDAB89;
		h[2] = 0x98BADCFE;
		h[3] = 0x10325476;
		h[4] = 0xC3D2E1F0;
	}
	~Impl() = default;

	void update(const byte* bytes, u32 len) {
		for (u32 i = 0; i < len; ++i) {
			rawBytes.push_back(bytes[i]);
		}
	}

	std::vector<byte>& process() {
		preprocess();
		for (u32 i = 0; i < rawBytes.size(); i += 64) {
			processBlock(i);
		}


		std::vector<byte> bytes(20);
		
		bytes[0] = (h[0] >> 24) & 0xFF;
		bytes[1] = (h[0] >> 16) & 0xFF;
		bytes[2] = (h[0] >> 8) & 0xFF;
		bytes[3] = (h[0] >> 0) & 0xFF;

		bytes[4] = (h[1] >> 24) & 0xFF;
		bytes[5] = (h[1] >> 16) & 0xFF;
		bytes[6] = (h[1] >> 8) & 0xFF;
		bytes[7] = (h[1] >> 0) & 0xFF;

		bytes[8] = (h[2] >> 24) & 0xFF;
		bytes[9] = (h[2] >> 16) & 0xFF;
		bytes[10] = (h[2] >> 8) & 0xFF;
		bytes[11] = (h[2] >> 0) & 0xFF;

		bytes[12] = (h[3] >> 24) & 0xFF;
		bytes[13] = (h[3] >> 16) & 0xFF;
		bytes[14] = (h[3] >> 8) & 0xFF;
		bytes[15] = (h[3] >> 0) & 0xFF;

		bytes[16] = (h[4] >> 24) & 0xFF;
		bytes[17] = (h[4] >> 16) & 0xFF;
		bytes[18] = (h[4] >> 8) & 0xFF;
		bytes[19] = (h[4] >> 0) & 0xFF;

		return bytes;
	}
	
private:
	void preprocess() {
		u32 len = rawBytes.size();
		rawBytes.push_back(0x80);

		while (((rawBytes.size() + 8) % 64) != 0) {
			rawBytes.push_back(0);
		}

		u64 ml = len * 8;
		rawBytes.push_back((ml >> 56) & 0xFF);
		rawBytes.push_back((ml >> 48) & 0xFF);
		rawBytes.push_back((ml >> 40) & 0xFF);
		rawBytes.push_back((ml >> 32) & 0xFF);
		rawBytes.push_back((ml >> 24) & 0xFF);
		rawBytes.push_back((ml >> 16) & 0xFF);
		rawBytes.push_back((ml >> 8) & 0xFF);
		rawBytes.push_back(ml & 0xFF);
	}

	void processBlock(u32 chunkOffset) {
		u32 w[80];
		u32 blockIndex = chunkOffset;
		for (u32 i = 0; i < 16; ++i) {
			w[i] = rawBytes[blockIndex++] << 24;
			w[i] |= rawBytes[blockIndex++] << 16;
			w[i] |= rawBytes[blockIndex++] << 8;
			w[i] |= rawBytes[blockIndex++];
		}

		for (u32 i = 16; i < 80; ++i) {
			w[i] = rol((w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16]), 1);
		}

		u32 a = h[0];
		u32 b = h[1];
		u32 c = h[2];
		u32 d = h[3];
		u32 e = h[4];
		u32 f = 0;
		u32 k = 0;
		u32 t = 0;

		for (u32 i = 0; i < 80; ++i) {
			if (i >= 0 && i <= 19) {
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if (i >= 20 && i <= 39) {
				f = (b ^ c ^ d);
				k = 0x6ED9EBA1;
			}
			else if (i >= 40 && i <= 59) {
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else {
				f = (b ^ c ^ d);
				k = 0xCA62C1D6;
			}

			t = rol(a, 5) + f + e + k + w[i];
			e = d;
			d = c;
			c = rol(b, 30);
			b = a;
			a = t;
		}

		h[0] += a;
		h[1] += b;
		h[2] += c;
		h[3] += d;
		h[4] += e;
	}

	inline u32 rol(u32 v, size_t c) { return (v << c) | (v >> (32 - c)); }

	u32 h[5];

	std::vector<byte> rawBytes;
};

Sha1Hash::Sha1Hash() {
	impl = MakeSPtr<Impl>();
}

Sha1Hash::Sha1Hash(String str) : Sha1Hash() {
	update(str.Bytes(), str.Length());
}

Sha1Hash& Sha1Hash::update(const byte* data, u32 len) {
	impl->update(data, len);
	return *this;
}

Sha1 Sha1Hash::hash() {
	std::vector<byte> result = impl->process();
	return Sha1(result.data());
}