#ifndef _PHYSICALFILE_H_
#define _PHYSICALFILE_H_

#include "File.h"
#include <memory>

class PhysicalFile : File {
public:
	PhysicalFile();
	virtual ~PhysicalFile() { Close(); }

	bool Open(const std::string& filename, const std::string& virtualFilename);
	void Close();

	byte* GetFileData();

private:
	class Impl;
	std::unique_ptr<Impl> impl;
};

#endif