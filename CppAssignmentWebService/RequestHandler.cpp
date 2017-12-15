#include "stdafx.h"
#include "RequestHandler.h"


RequestHandler::RequestHandler()
{
}

RequestHandler::RequestHandler(utility::string_t url):m_listener(url)
{
	m_listener.support(methods::GET, std::bind(&RequestHandler::handle_get, this, std::placeholders::_1));
	m_listener.support(methods::PUT, std::bind(&RequestHandler::handle_put, this, std::placeholders::_1));
	m_listener.support(methods::POST, std::bind(&RequestHandler::handle_post, this, std::placeholders::_1));
}


RequestHandler::~RequestHandler()
{
}

void RequestHandler::handle_get(http_request message)
{
	ucout << message.to_string() << std::endl;
	message.reply(status_codes::OK, message.to_string());
	return;
}

void RequestHandler::handle_put(http_request message)
{
	ucout << message.to_string() << std::endl;
	message.reply(status_codes::OK, message.to_string());
	return;
}

void RequestHandler::handle_post(http_request message)
{
	ucout << message.to_string() << std::endl;
	message.reply(status_codes::OK, message.to_string());
	return;
}

void RequestHandler::handle_error(pplx::task<void>& t)
{
	try
	{
		t.get();
	}
	catch (...)
	{
		// Ignore the error, Log it if a logger is available
	}
}
