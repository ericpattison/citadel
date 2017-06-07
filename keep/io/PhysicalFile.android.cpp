#include "PhysicalFile.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <memory>

class PhysicalFile::Impl {
public:
	bool Open(std::string filename) {
		fileHandle = open(filename.c_str(), O_RDONLY);

		struct stat FileInfo;
		fstat(fileHandle, &FileInfo);
		size = static_cast<u64>(FileInfo.st_size);
		if (size) {
			fileData = (byte*)(mmap(NULL, size, PROT_READ, MAP_PRIVATE, fileHandle, 0));
		}
		close(fileHandle);
	}

	void Close() {
		if (fileData) { munmap(reinterpret_cast<handle>(fileData), size); }
	}

	byte* GetFileData() {
		return fileData;
	}

private:
	int fileHandle;
	u64 size;
	byte* fileData;

};

PhysicalFile::PhysicalFile() : impl(std::make_unique<PhysicalFile::Impl>()) {

}

bool PhysicalFile::Open(const std::string& filename, const std::string& virtualFilename) {
	SetFilename(filename);
	SetVirtualFilename(virtualFilename);
	return impl->Open(filename);
}

void PhysicalFile::Close() {
	impl->Close();
}

byte* PhysicalFile::GetFileData() {
	return impl->GetFileData();
}