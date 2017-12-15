#pragma once

#include "stdafx.h"

using namespace web::http;
using namespace web::http::experimental::listener;

class RequestHandler
{
public:
	RequestHandler();
	RequestHandler(utility::string_t url);
	~RequestHandler();

	pplx::task<void>open() { return m_listener.open(); }
	pplx::task<void>close() { return m_listener.close(); }

private:
	void handle_get(http_request message);
	void handle_put(http_request message);
	void handle_post(http_request message);
	void handle_error(pplx::task<void>& t);
	http_listener m_listener;

};

