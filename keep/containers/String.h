#ifndef _STRING_H_
#define _STRING_H_

#include <string>

class String {
public:
	String() = default;
	String(String& str) = default;
	String(String&& str) noexcept = default;
	~String() = default;

	String(const char* str);
	String(const wchar_t* str);
	String(const std::string& str);
	String(const std::wstring& str);

	String& operator=(const String& str) = default;
	String& operator=(String&& str) noexcept = default;

	std::string ToString() const;
	std::wstring ToWString() const;

	const char* ToRawString() const;
	const wchar_t* ToRawWString() const;

	const uint8_t* Bytes() const;
	size_t Length() const;
	size_t Size() const;

private:
	std::wstring data;
};

//inline bool operator==(const String& lhs, const String &rhs);
//inline bool operator!=(const String& lhs, const String &rhs);

#endif