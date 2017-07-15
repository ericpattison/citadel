#ifndef _TYPES_H_
#define _TYPES_H_

#include <stdint.h>

typedef	int64_t		s64;
typedef	uint64_t	u64;
typedef	int32_t		s32;
typedef	uint32_t	u32;
typedef	int16_t		s16;
typedef	uint16_t	u16;
typedef	int8_t		s8;
typedef	uint8_t		u8;

typedef	uint8_t		byte;

typedef	float		real;
typedef	float		real32;
typedef	double		real64;

#include <string>
typedef std::wstring String;

#include <functional>
template<class func>
using Delegate = std::function<func>;

#include <memory>
using next_t = Delegate<void()>;
using Next = std::shared_ptr<next_t>;
using Callback = Delegate<void(Next)>;

template<class T>
using UPtr = std::unique_ptr<T>;
template<class T>
using SPtr = std::shared_ptr<T>;

template<class T, typename ...Args>
UPtr<T> MakeUPtr(Args&& ...args) {
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<class T, typename ...Args>
SPtr<T> MakeSPtr(Args&& ...args) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

typedef SPtr<void*> handle;

struct WindowInfo {
	String title;
	u32 width;
	u32 height;
};

#endif
