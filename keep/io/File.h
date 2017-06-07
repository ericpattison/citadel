#ifndef _FILE_H_
#define _FILE_H_

#include <string>
#include "../../keep/types.h"

class File {
public:
	File() { }
	virtual ~File() { }

	void SetVirtualFilename(const std::string& name) { virtualFilename = name; }
	void SetFilename(const std::string& name) { filename = name; }

	std::string GetVirtualFilename() { return virtualFilename; }
	std::string GetFilename() { return filename; }

	virtual const byte* GetFileData() const = 0;
	virtual u64 GetFileSize() const = 0;

protected:
	std::string filename;
	std::string virtualFilename;
};

#endif