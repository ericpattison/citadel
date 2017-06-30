#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <vector>
#include "../types.h"

template<class T>
class Vector {
public:
	u32 size() { return data.size() * sizeof(T); }
	u32 count() { return data.size(); }
	T head() { return data[0]; }
	T tail() { return data[data.size() - 1]; }

	void push(T item) { data.push_back(item); }
	T pop() { return data.pop_back(); }

	T at(u32 index) { return data[index]; }
private:
	std::vector<T> data;
};

#endif