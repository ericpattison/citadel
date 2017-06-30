#ifndef _OPENGLWINDOW_H_
#define _OPENGLWINDOW_H_

#include "SystemWindow.h"
#include "../types.h"
#include "../constants.h"
#include "../../watchtower/device/Device.h"

class OpenGLWindow : public SystemWindow {
public:
	OpenGLWindow(WindowInfo& info);
	virtual ~OpenGLWindow();

	virtual void Resize(u32 width, u32 height);
	virtual void Title(String title);
	virtual WindowStatus ProcessMessages();
	virtual void Exit(int errorCode);

	virtual SPtr<Device> AcquireDevice();

private:
	class Impl;
	UPtr<Impl> impl;
};

#endif