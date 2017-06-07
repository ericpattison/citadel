#ifndef _WINDOW_H_
#define _WINDOW_H_

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

class Window {
public:
	Window(WindowInfo info);
	virtual ~Window();

	void Resize(u32 width, u32 height);
	void Title(String title);
	WindowStatus ProcessMessages();
	void Exit(int errorCode);

private:
	class Impl;
	std::unique_ptr<Impl> impl;
};

#endif