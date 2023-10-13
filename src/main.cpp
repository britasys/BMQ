#include <argh.h>
#include <node/node.hpp>

int main(int argc, char *argv[])
{
  argh::parser cmdl(argc, argv);

  unsigned short int l_uiPort{};
  cmdl({"-p", "--port"}) >> l_uiPort;

  std::string l_strEndpoint{};
  cmdl({"-e", "--endpoint"}) >> l_strEndpoint;

  std::string l_strThreadCount{};
  cmdl({"-t", "--thread"}) >> l_strThreadCount;

  if (cmdl[{"-c", "--client"}])
  {
    bmq::BMQ_NODE_INIT l_init{
        "192.168.1.102",
        5050,
        "/data",
        "ipc://test"};
    bmq::BMQ_NODE_CLIENT l_node{l_init};
    l_node.run();
  }

  if (cmdl[{"-s", "--server"}])
  {
    bmq::BMQ_NODE_INIT l_init{
        "jsonplaceholder.typicode.com",
        80,
        "/posts",
        "ipc://test"};
    bmq::BMQ_NODE_SERVER l_node{l_init};
    l_node.run();
  }

  return 0;
}