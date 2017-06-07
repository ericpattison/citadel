#include "Window.h"

#include <xcb/xcb.h>
#include <stdlib.h>
#include <string.h>
#include <memory>

class Window::Impl {
public:
	Impl() {
		int screenIndex = 0;
		connection = xcb_connect(NULL, &screenIndex);
		xcb_screen_iterator_t iter = xcb_setup_roots_iterator( xcb_get_setup(connection) );
		for(int s = screenIndex; s > 0; --s) { xcb_screen_next(&iter); }
		screen = iter.data;
	}

	void CreateWindow(WindowInfo info) {
		window = xcb_generate_id( connection );
		uint32_t eventMask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
		uint32_t valueList[] = { screen->white_pixel, 0 };

		xcb_create_window(
			connection,
			XCB_COPY_FROM_PARENT,
			window,
			screen->root,
			0, 0,
			info.width, info.height,
			10,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			screen->root_visual,
			eventMask,
			valueList
		);

		xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
			connection, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW"
		);
		xcb_intern_atom_cookie_t wmProtocolsCookie = xcb_intern_atom(
			connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS"
		);

		xcb_intern_atom_reply_t* wmDeleteReply = xcb_intern_atom_reply(
			connection, wmDeleteCookie, NULL
		);
		xcb_intern_atom_reply_t* wmProtocolsReply = xcb_intern_atom_reply(
			connection, wmProtocolsCookie, NULL
		);

		wmDeleteWin = wmDeleteReply->atom;
		wmProtocols = wmProtocolsReply->atom;

		xcb_change_property(
			connection, XCB_PROP_MODE_REPLACE, window,
			wmProtocolsReply->atom, 4, 32, 1, &wmDeleteReply->atom
		);

		xcb_map_window(connection, window);
		xcb_flush(connection);
	}

private:
	xcb_connection_t* connection;
	xcb_screen_t* screen;
	xcb_window_t window;

	xcb_atom_t wmProtocols;
	xcb_atom_t wmDeleteWin;
}

Window::Window(WindowInfo info) : impl(std::make_unique<Impl>()){
	impl->CreateWindow(info);
}

Window::~Window() {
}

void Window::Resize(u32 width, u32 height) {
}

void Window::Title(String title) {
}

WindowStatus Window::ProcessMessages() {
	xcb_generic_event_t* event = xcb_wait_for_event(connection);
	switch(event->response_type & ~0x80) {
		case XCB_CLIENT_MESSAGE: {
			cm = (xcb_client_message_event_t*)event;
			if(cm->data.data32[0] == wmDeleteWin) return WindowStatus::Quit;
		} break;
	}
	free(event);
	return WindowStatus::
}

void Window::Exit(int errorCode) {
	exit(0);
}
