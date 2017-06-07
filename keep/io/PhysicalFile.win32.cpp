#include "PhysicalFile.h"

#include <Windows.h>

class PhysicalFile::Impl {
public:
	bool Open(std::string filename) {
		mapFile = CreateFileA(filename.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
		mapHandle = CreateFileMapping(mapFile, NULL, PAGE_READONLY, 0, 0, NULL);
		fileData = (byte*)MapViewOfFile(mapHandle, FILE_MAP_READ, 0, 0, 0);

		DWORD sizeLow = 0, sizeHigh = 0;
		sizeLow = ::GetFileSize(mapFile, &sizeHigh);
		size = ((u64)sizeHigh << 32) | (u64)sizeLow;
		return true;
	}

	void Close() {
		if (fileData) { UnmapViewOfFile(fileData); }
		if (mapHandle) { CloseHandle((HANDLE)mapHandle); }
		CloseHandle((HANDLE)mapFile);
	}
private:
	HANDLE mapFile;
	HANDLE mapHandle;

	byte* fileData;

	u64 size;
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