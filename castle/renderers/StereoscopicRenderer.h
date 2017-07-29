#ifndef _STEREOSCOPICRENDERER_H_
#define _STEREOSCOPICRENDERER_H_

#include "./Renderer.h"
#include "../../watchtower/device/Device.h"

class StereoscopicRenderer : Renderer {
public:
	StereoscopicRenderer(SPtr<Device> device) {
		_device = device;
	}

	virtual Callback RenderMethod() { return { this, &StereoscopicRenderer::process }; }
	void process(Next next) {
		(*next)();
	}

private:
	SPtr<Device> _device;
};

#endif