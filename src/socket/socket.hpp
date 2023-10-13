#pragma once

#ifndef __H_SOCKET__
#define __H_SOCKET__

#include <zmq.hpp>

#include <string>
#include <vector>
#include <memory>

namespace bmq
{
    //////////////////////////////////////////////////////////////////
    // BMQ_SOCKET                                                   //
    //////////////////////////////////////////////////////////////////

    typedef struct _bmq_socket_init
    {
        std::string url{};
    } BMQ_SOCKET_INIT, *LP_BMQ_SOCKET_INIT, **LPP_BMQ_SOCKET_INIT;

    typedef struct _bmq_socket
    {
    protected:
        _bmq_socket() = delete;
        _bmq_socket(const _bmq_socket &) = delete;
        _bmq_socket(_bmq_socket &&) noexcept = delete;
        _bmq_socket &operator=(const _bmq_socket &) = delete;
        _bmq_socket &operator=(_bmq_socket &&) noexcept = delete;
        virtual ~_bmq_socket()
        {
            this->pContext->shutdown();
            this->pContext->close();
        }

        explicit _bmq_socket(const BMQ_SOCKET_INIT &init, zmq::socket_type type)
        {
            this->url.assign(init.url);

            this->pContext = std::make_shared<zmq::context_t>();
            this->pSocket = std::make_shared<zmq::socket_t>(*(this->pContext.get()), type);
        }

    protected:
        std::shared_ptr<zmq::context_t> pContext{};
        std::shared_ptr<zmq::socket_t> pSocket{};
        std::string url{};

    public:
        void send(const std::string &data)
        {
            auto l_result = this->pSocket->send(zmq::buffer(data), zmq::send_flags::none);
        }

        void recv(std::string &data)
        {
            std::vector<char> l_data(1024);
            zmq::mutable_buffer mbuf = zmq::buffer(l_data);
            auto l_result = this->pSocket->recv(mbuf, zmq::recv_flags::none);

            data.assign(std::string{(char *)(mbuf.data())});
        }
    } BMQ_SOCKET, *LP_BMQ_SOCKET, **LPP_BMQ_SOCKET;

    //////////////////////////////////////////////////////////////////
    // BMQ_SOCKET_REQ                                               //
    //////////////////////////////////////////////////////////////////

    typedef struct _bmq_socket_req : public _bmq_socket
    {
        ~_bmq_socket_req() { this->pSocket->disconnect(this->url); }
        _bmq_socket_req(const BMQ_SOCKET_INIT &init) : _bmq_socket(init, zmq::socket_type::req)
        {
            this->pSocket->connect(this->url);
        }
    } BMQ_SOCKET_REQ, *LP_BMQ_SOCKET_REQ, **LPP_BMQ_SOCKET_REQ;

    //////////////////////////////////////////////////////////////////
    // BMQ_SOCKET_REP                                               //
    //////////////////////////////////////////////////////////////////

    typedef struct _bmq_socket_rep : public _bmq_socket
    {
        ~_bmq_socket_rep() { this->pSocket->unbind(this->url); }
        _bmq_socket_rep(const BMQ_SOCKET_INIT &init) : _bmq_socket(init, zmq::socket_type::rep)
        {
            this->pSocket->bind(this->url);
        }
    } BMQ_SOCKET_REP, *LPBMQ_SOCKET_REP, **LPP_BMQ_SOCKET_REP;

} // !bmq

#endif // !__H_SOCKET__