#pragma once

#include "stdafx.h"


class RequestHandler {
public:
  RequestHandler() {}
  RequestHandler(utility::string_t url);
  ~RequestHandler();

  pplx::task<void> open() { return m_listener.open(); }
  pplx::task<void> close() { return m_listener.close(); }

  void handle_get(web::http::http_request message);
  void handle_put(web::http::http_request message);
  void handle_post(web::http::http_request message);

private:
  static void handle_error(pplx::task<void> &t);

  static const utility::string_t quote_json_key;
  static const utility::string_t sell_json_key;
  static const utility::string_t buy_json_key;
  static const utility::string_t register_json_key;
  static const utility::string_t transaction_json_key;
  static const utility::string_t portfolio_json_key;
  static const utility::string_t error_json_key;

  // key: Resource
  // Value: JSON response data to be sent to clients
  // We are caching the data for multiple requests.
  std::map<utility::string_t, web::json::value> m_data;

  // Http listener
  web::http::experimental::listener::http_listener m_listener;
};
