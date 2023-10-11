#pragma once

#ifndef __H_SOCKET__
#define __H_SOCKET__

#include <zmq.hpp>

#include <string>
#include <deque>
#include <vector>

namespace bmq
{
    //////////////////////////////////////////////////////////////////
    // BMQ_SOCKET                                                   //
    //////////////////////////////////////////////////////////////////

    typedef struct _bmq_socket_init
    {
        unsigned short int uiThreadCount{1};
        std::deque<std::string> endpoints{};
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
            for (const auto &endpoint : this->endpoints)
            {
                this->socket.unbind(endpoint);
                this->socket.disconnect(endpoint);
            }

            // this->m_context.shutdown();
            // this->m_context.close();
        }

        explicit _bmq_socket(const BMQ_SOCKET_INIT &init, zmq::socket_type type)
        {
            this->socket = zmq::socket_t(context, type);

            this->endpoints = endpoints;
            for (const auto &endpoint : this->endpoints)
                this->socket.bind(endpoint);
        }

        void send(const std::string& data)
        {
            auto l_result = this->socket.send(zmq::buffer(data), zmq::send_flags::none);
        }

        void recv(std::string& data)
        {
            std::vector<char> l_data(1024);
            zmq::mutable_buffer mbuf = zmq::buffer(l_data);
            auto l_result = this->socket.recv(mbuf, zmq::recv_flags::none);

            data.assign(std::string{ (char*)(mbuf.data()) });
        }

    private:
        static zmq::context_t context;
        zmq::socket_t socket{};
        std::deque<std::string> endpoints{};
    } BMQ_SOCKET, *LP_BMQ_SOCKET, **LPP_BMQ_SOCKET;

    //////////////////////////////////////////////////////////////////
    // BMQ_SOCKET_REQ                                               //
    //////////////////////////////////////////////////////////////////

    typedef struct _bmq_socket_req : public _bmq_socket
    {
        _bmq_socket_req(const BMQ_SOCKET_INIT &init) : _bmq_socket(init, zmq::socket_type::req) {}
    } BMQ_SOCKET_REQ, *LP_BMQ_SOCKET_REQ, **LPP_BMQ_SOCKET_REQ;

    //////////////////////////////////////////////////////////////////
    // BMQ_SOCKET_REP                                               //
    //////////////////////////////////////////////////////////////////

    typedef struct _bmq_socket_rep : public _bmq_socket
    {
        _bmq_socket_rep(const BMQ_SOCKET_INIT &init) : _bmq_socket(init, zmq::socket_type::rep) {}
    } BMQ_SOCKET_REP, *LPBMQ_SOCKET_REP, **LPP_BMQ_SOCKET_REP;

} // !bmq

#endif // !__H_SOCKET__