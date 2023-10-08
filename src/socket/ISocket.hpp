#pragma once

#ifndef __H_ISOCKET__
#define __H_ISOCKET__

#include <zmq.hpp>

#include <deque>
#include <string>

namespace bmq_socket
{
    typedef struct _socket_init
    {
        unsigned short int uiThredCount{ 1 };
        
    } SOCKET_INIT, * LP_SOCKET_INIT, ** LPP_SOCKET_INIT;

    class ISocket
    {
    public:
        ISocket() = delete;
        ISocket(const ISocket&) = delete;
        ISocket(ISocket&&) = delete;
        ISocket& operator = (const ISocket&) = delete;
        ISocket& operator = (ISocket&&) = delete;
        virtual ~ISocket()
        {            
            for (const auto& endpoint : this->m_endpoints)
            {
                this->m_socket.unbind(endpoint);
                this->m_socket.disconnect(endpoint);
            }
            
            this->m_context.shutdown();
            this->m_context.close();
        }

        explicit ISocket(const std::deque<std::string>& endpoints, const int type, const unsigned short int uiThreadCount = 1)
        {
            this->m_socket = zmq::socket_t(this->m_context, type);

            this->m_endpoints = endpoints;
            for (const auto& endpoint : this->m_endpoints)
                this->m_socket.bind(endpoint);
        }

    private:
        zmq::context_t m_context{};
        zmq::socket_t m_socket{};
        std::deque<std::string> m_endpoints{};
    };
} // !bmq_socket

#endif // !__H_ISOCKET__