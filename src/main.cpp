#include <iostream>

#include <zmq.hpp>
#include <spdlog/spdlog.h>
#include <httplib.h>

#include <node/node.hpp>

int main()
{
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:<30}", "left aligned");

  spdlog::set_level(spdlog::level::debug); // Set global log level to debug
  spdlog::debug("This message should be displayed..");

  // change log pattern
  spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

  // Compile time log levels
  // define SPDLOG_ACTIVE_LEVEL to desired level
  SPDLOG_TRACE("Some trace message with param {}", 42);
  SPDLOG_DEBUG("Some debug message");

  zmq::context_t ctx;
  zmq::socket_t sock(ctx, zmq::socket_type::sub);
  sock.bind("tcp://127.0.0.1:5050");
  sock.send(zmq::str_buffer("Hello, world"), zmq::send_flags::dontwait);

  using namespace httplib;

  Server svr;

  svr.Get("/hi", [](const Request &req, Response &res)
          { res.set_content("Hello World!", "text/plain"); });

  // Match the request path against a regular expression
  // and extract its captures
  svr.Get(R"(/numbers/(\d+))", [&](const Request &req, Response &res)
          {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain"); });

  // Capture the second segment of the request path as "id" path param
  svr.Get("/users/:id", [&](const Request &req, Response &res)
          {
    auto user_id = req.path_params.at("id");
    res.set_content(user_id, "text/plain"); });

  // Extract values from HTTP headers and URL query params
  svr.Get("/body-header-param", [](const Request &req, Response &res)
          {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
    }
    res.set_content(req.body, "text/plain"); });

  svr.Get("/stop", [&](const Request &req, Response &res)
          { svr.stop(); });

  svr.listen("localhost", 1234);

  return 0;
}