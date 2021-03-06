// CppAssignmentWebService.cpp : Defines the entry point for the console
// application.
//

#include "stdafx.h"
#include "RequestHandler.h"

using namespace std;
using namespace utility;
using namespace web;
using namespace web::http;

std::unique_ptr<RequestHandler> g_httpHandler;

void on_initialize(const string_t &address) {
  uri_builder uri(address);

  auto addr = uri.to_uri().to_string();
  g_httpHandler = std::unique_ptr<RequestHandler>(new RequestHandler(addr));
  g_httpHandler->open().wait();

  ucout << utility::string_t(U("Listening for requests at: ")) << addr
        << std::endl;

  return;
}

void on_shutdown() {
  g_httpHandler->close().wait();
  return;
}

int wmain(int argc, wchar_t *args[]) {
  utility::string_t port = U("34568");
  if (argc == 2) {
    port = args[1];
  }

  utility::string_t address = U("http://localhost:");
  address.append(port);

  on_initialize(address);
  std::cout << "Press ENTER to exit." << std::endl;

  std::string line;
  std::getline(std::cin, line);

  on_shutdown();
  return 0;
}
