#include "stdafx.h"
#include "RequestHandler.h"

using namespace web::http::experimental::listener;

const utility::string_t quote_json_key = U("qoute");
const utility::string_t sell_json_key = U("sell");
const utility::string_t buy_json_key = U("buy");
const utility::string_t register_json_key = U("register");
const utility::string_t transaction_json_key = U("transaction");
const utility::string_t portfolio_json_key = U("portfolio");
const utility::string_t error_json_key = U("error");

RequestHandler::RequestHandler(utility::string_t url) : m_listener(url) {
  m_listener.support(
      web::http::methods::GET,
      std::bind(&RequestHandler::handle_get, this, std::placeholders::_1));
  m_listener.support(
      web::http::methods::PUT,
      std::bind(&RequestHandler::handle_put, this, std::placeholders::_1));
  m_listener.support(
      web::http::methods::POST,
      std::bind(&RequestHandler::handle_post, this, std::placeholders::_1));
}

RequestHandler::~RequestHandler() {}

// Handler to process HTTP::GET requests.
// Replies to the request with data.
void RequestHandler::handle_get(web::http::http_request message) {
  auto path = message.relative_uri().path();
  if (0 == path.compare(U("/"))) {
    message.extract_string()
        .then([=](const utility::string_t &location) {
          //			get_data(message, location);
        })
        .then([](pplx::task<void> t) { handle_error(t); });
  } else {
    message.reply(web::http::status_codes::NotFound, U("Path not found"))
        .then([](pplx::task<void> t) { handle_error(t); });
  }
}

// Respond to HTTP::PUT messages
// Post data will contain the postal code or location string.
// Aggregate location data from different services and reply to the POST
// request.
void RequestHandler::handle_put(web::http::http_request message) {
  ucout << message.to_string() << std::endl;
  message.reply(web::http::status_codes::OK, message.to_string());
  return;
}

// Respond to HTTP::POST messages
// Post data will contain the postal code or location string.
// Aggregate location data from different services and reply to the POST
// request.
void RequestHandler::handle_post(web::http::http_request message) {
  auto path = message.relative_uri().path();
  if (0 == path.compare(U("/"))) {
    message.extract_string()
        .then([=](const utility::string_t &location) {
          //			get_data(message, location);
        })
        .then([](pplx::task<void> t) { handle_error(t); });
  } else {
    message.reply(web::http::status_codes::NotFound, U("Path not found"))
        .then([](pplx::task<void> t) { handle_error(t); });
  }
}

void RequestHandler::handle_error(pplx::task<void> &t) {
  try {
    t.get();
  } catch (...) {
    // Ignore the error, Log it if a logger is available
  }
}
