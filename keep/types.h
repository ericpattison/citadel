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

typedef	void *		handle;

#include <string>
typedef std::string String;

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

template<class T>
using MakeUPtr = std::make_unique<T>;
template<class T>
using MakeSPtr = std::make_shared<T>;

#endif