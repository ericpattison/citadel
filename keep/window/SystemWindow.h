#ifndef _SYSTEMWINDOW_H_
#define _SYSTEMWINDOW_H_

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
	SystemWindow(WindowInfo& info) { }
	virtual ~SystemWindow() { }

	virtual void Resize(u32 width, u32 height) = 0;
	virtual void Title(String title) = 0;
	virtual WindowStatus ProcessMessages() = 0;
	virtual void Exit(int errorCode) = 0;
};

#endif
