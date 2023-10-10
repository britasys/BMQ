#pragma once

#ifndef __H_HTTPCLIENT__
#define __H_HTTPCLIENT__

#include <httplib.h>

#include <string>
#include <memory>

namespace bmq
{
    typedef struct _bmq_http_client_init
    {
        std::string url{};
    } BMQ_HTTP_CLIENT_INIT;

    typedef struct _bmq_http_client
    {
        _bmq_http_client() = delete;
        _bmq_http_client(const _bmq_http_client &) = delete;
        _bmq_http_client(_bmq_http_client &&) noexcept = delete;
        _bmq_http_client &operator=(const _bmq_http_client &) = delete;
        _bmq_http_client &operator=(_bmq_http_client &&) noexcept = delete;
        virtual ~_bmq_http_client() = default;

        explicit _bmq_http_client(const BMQ_HTTP_CLIENT_INIT &init) : init{init} {}

        virtual bool send_sync(const std::string &) const noexcept = 0;
        virtual bool send_async(const std::string &) const noexcept = 0;

    protected:
        BMQ_HTTP_CLIENT_INIT init{};
    } BMQ_HTTP_CLIENT, *LP_BMQ_HTTP_CLIENT, **LPP_BMQ_HTTP_CLIENT;

    typedef struct _bmq_http_client_rest : _bmq_http_client
    {
        _bmq_http_client_rest() = delete;
        _bmq_http_client_rest(const _bmq_http_client_rest &) = delete;
        _bmq_http_client_rest(_bmq_http_client_rest &&) noexcept = delete;
        _bmq_http_client_rest &operator=(const _bmq_http_client_rest &) = delete;
        _bmq_http_client_rest &operator=(_bmq_http_client_rest &&) noexcept = delete;
        virtual ~_bmq_http_client_rest() = default;

        explicit _bmq_http_client_rest(const BMQ_HTTP_CLIENT_INIT &init) : _bmq_http_client{init}
        {
            this->pClient = std::make_shared<httplib::Client>(init.url);
        }

        bool send_sync(const std::string &message) const noexcept final
        {
            this->pClient->Post(this->init.url, message, "text/plain");
            return true;
        }
        bool send_async(const std::string &) const noexcept final
        {
            return true;
        }

    private:
        std::shared_ptr<httplib::Client> pClient{};
    } BMQ_HTTP_CLIENT_REST, *LP_BMQ_HTTP_CLIENT_REST, **LPP_BMQ_HTTP_CLIENT_REST;
} // !bmq

#endif // !__H_HTTPCLIENT__