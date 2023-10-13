#pragma once

#ifndef __H_NODE__
#define __H_NODE__

#include <log.hpp>

#include <socket/socket.hpp>
#include <httplib.h>

#include <memory>
#include <unordered_map>
#include <string>

namespace bmq
{
    //////////////////////////////////////////////////////////////////
    // NMQ_NODE                                                     //
    //////////////////////////////////////////////////////////////////

    typedef struct _bmq_node_init
    {
        std::string endpoint{};
        unsigned short int endpoint_port{};
        std::string endpoint_path{};
        std::string url{};
    } BMQ_NODE_INIT;

    typedef struct _bmq_node
    {
        _bmq_node() = delete;
        _bmq_node(const _bmq_node &) = delete;
        _bmq_node(_bmq_node &&) noexcept = delete;
        _bmq_node &operator=(const _bmq_node &) = delete;
        _bmq_node &operator=(_bmq_node &&) noexcept = delete;
        virtual ~_bmq_node() = default;

        explicit _bmq_node(const BMQ_NODE_INIT &init) : init{init} {}

        virtual void run() noexcept = 0;

    protected:
        BMQ_NODE_INIT init{};
    } NMQ_NODE;

    typedef struct _bmq_node_client : public _bmq_node
    {
        _bmq_node_client() = delete;
        _bmq_node_client(const _bmq_node_client &) = delete;
        _bmq_node_client(_bmq_node_client &&) noexcept = delete;
        _bmq_node_client &operator=(const _bmq_node_client &) = delete;
        _bmq_node_client &operator=(_bmq_node_client &&) noexcept = delete;
        virtual ~_bmq_node_client() = default;

        explicit _bmq_node_client(const BMQ_NODE_INIT &init) : _bmq_node(init)
        {
            BMQ_SOCKET_INIT l_init_socket{init.url};
            this->pSocket_req = std::make_shared<BMQ_SOCKET_REQ>(l_init_socket);

            this->pServer_rest = std::make_shared<httplib::Server>();
            this->pServer_rest->Get("/hi", [this](const httplib::Request &req, httplib::Response &res)
                                    { res.set_content("Hello World!", "text/plain"); });

            this->pServer_rest->Get("/stop", [&](const httplib::Request &req, httplib::Response &res)
                                    { this->pServer_rest->stop(); });

            this->pServer_rest->Post(init.endpoint_path, [this](const httplib::Request &req, httplib::Response &res)
                                     {
                                        INFO("Message recieved - {}", req.body);
                                        std::string l_res_socket{};
                                        this->pSocket_req->send(req.body);
                                        this->pSocket_req->recv(l_res_socket);
                                        res.set_content(l_res_socket, "text/plain"); });
        }

        void run() noexcept final
        {
            INFO("Node is running...");
            this->pServer_rest->listen(this->init.endpoint, this->init.endpoint_port);
        }

    private:
        std::shared_ptr<httplib::Server> pServer_rest{};
        std::shared_ptr<BMQ_SOCKET_REQ> pSocket_req{};
    } BMQ_NODE_CLIENT;

    typedef struct _bmq_node_server : public _bmq_node
    {
        _bmq_node_server() = delete;
        _bmq_node_server(const _bmq_node_server &) = delete;
        _bmq_node_server(_bmq_node_client &&) noexcept = delete;
        _bmq_node_server &operator=(const _bmq_node_server &) = delete;
        _bmq_node_server &operator=(_bmq_node_server &&) noexcept = delete;
        virtual ~_bmq_node_server() = default;

        explicit _bmq_node_server(const BMQ_NODE_INIT &init) : _bmq_node(init)
        {
            this->pClient_rest = std::make_shared<httplib::Client>(init.endpoint, init.endpoint_port);

            BMQ_SOCKET_INIT l_init_socket{init.url};
            this->pSocket_rep = std::make_shared<BMQ_SOCKET_REP>(l_init_socket);
        }

        void run() noexcept final
        {
            INFO("Node is running...");

            while (true)
            {
                std::string message{};
                this->pSocket_rep->recv(message);
                INFO("Message recieved - {}", message);

                // auto l_result = this->pClient_rest->Post(this->init.endpoint_path, message.c_str(), message.size(), "text/plain");
                auto l_result = this->pClient_rest->Post(this->init.endpoint_path);
                if (l_result)
                {
                    if (200 == l_result->status)
                        this->pSocket_rep->send(l_result->body);
                    else
                        this->pSocket_rep->send(std::to_string(l_result->status));
                }
                else
                {
                    auto err = l_result.error();
                    this->pSocket_rep->send(httplib::to_string(err));
                }
            }
        }

    private:
        std::shared_ptr<httplib::Client> pClient_rest{};
        std::shared_ptr<BMQ_SOCKET_REP> pSocket_rep{};
    } BMQ_NODE_SERVER;
} // !bmq

#endif //!__H_NODE__