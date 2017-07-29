#include "String.h"

#include <codecvt>

String::String(const char* str): String(std::string(str)) { }

String::String(const wchar_t* str): String(std::wstring(str)) { }

String::String(const std::string& str) {
	typedef std::codecvt_utf8<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;
	data = converter.from_bytes(str);
}

String::String(const std::wstring& str) {
	data = str;
}

std::string String::ToString() const {
	typedef std::codecvt_utf8<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(data);
}

std::wstring String::ToWString() const {
	return data;
}

const char* String::ToRawString() const {
	return ToString().c_str();
}

const wchar_t* String::ToRawWString() const {
	return data.c_str();
}

const uint8_t* String::Bytes() const {
	return (const uint8_t*)ToRawString();
}

size_t String::Length() const {
	return data.length();
}

size_t String::Size() const {
	return data.length() * sizeof(data[0]);
}