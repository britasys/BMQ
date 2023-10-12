#pragma once

#ifndef __H_HTTPSERVER__
#define __H_HTTPSERVER__

#include <httplib.h>

#include <memory>
#include <string>

namespace bmq
{
    typedef struct _bmq_http_server_init
    {
        std::string endpoint{};
        unsigned short int port{};
        std::string path{};
    } BMQ_HTTP_SERVER_INIT;

    typedef struct _bmq_http_server
    {
        _bmq_http_server() = delete;
        _bmq_http_server(const _bmq_http_server &) = delete;
        _bmq_http_server(_bmq_http_server &&) noexcept = delete;
        _bmq_http_server &operator=(const _bmq_http_server &) = delete;
        _bmq_http_server &operator=(_bmq_http_server &&) noexcept = delete;
        virtual ~_bmq_http_server() = default;

        explicit _bmq_http_server(const BMQ_HTTP_SERVER_INIT &init) : init{init} {}

        virtual bool listen_sync() const noexcept = 0;
        virtual bool listen_async() const noexcept = 0;

    protected:
        BMQ_HTTP_SERVER_INIT init{};
    } BMQ_HTTP_SERVER, *LP_BMQ_HTTP_SERVER, **LPP_BMQ_HTTP_SERVER;

    typedef struct _bmq_http_server_rest : _bmq_http_server
    {
        _bmq_http_server_rest() = delete;
        _bmq_http_server_rest(const _bmq_http_server_rest &) = delete;
        _bmq_http_server_rest(_bmq_http_server_rest &&) noexcept = delete;
        _bmq_http_server_rest &operator=(const _bmq_http_server_rest &) = delete;
        _bmq_http_server_rest &operator=(_bmq_http_server_rest &&) noexcept = delete;
        virtual ~_bmq_http_server_rest() = default;

        explicit _bmq_http_server_rest(const BMQ_HTTP_SERVER_INIT &init) : _bmq_http_server{init}
        {
            this->pServer->Post(init.path, [&](const auto &req, auto &res)
                                { res.set_content(req.body, "text/plain"); });
        }

        bool listen_sync() const noexcept final
        {
            this->pServer->listen(this->init.endpoint, this->init.port);
            return true;
        }
        bool listen_async() const noexcept final
        {
            return true;
        }

    private:
        std::shared_ptr<httplib::Server> pServer{std::make_shared<httplib::Server>()};
    } BMQ_HTTP_SERVER_REST, *LP_BMQ_HTTP_SERVER_REST, **LPP_BMQ_HTTP_SERVER_REST;
} // !bmq

#endif // !__H_HTTPSERVER__