#ifndef _SYSTEMWINDOW_H_
#define _SYSTEMWINDOW_H_

#include <memory>
#include "../types.h"
#include "../constants.h"

struct WindowInfo {
	String title;
	u32 width;
	u32 height;
};

enum WindowStatus {
	SystemUpdate,
	GameUpdate,
	Quit
};

class SystemWindow {
public:
	SystemWindow(WindowInfo info);
	virtual ~SystemWindow();

	void Resize(u32 width, u32 height);
	void Title(String title);
	WindowStatus ProcessMessages();
	void Exit(int errorCode);

private:
	class Impl;
	std::unique_ptr<Impl> impl;
};

#endif
