#pragma once

#ifndef __H_CSOCKET_REQ__
#define __H_CSOCKET_REQ__

#include "ISocket.hpp"

namespace bmq_socket
{
    class CSocket_req : public ISocket
    {
    public:
        CSocket_req() = delete;
        CSocket_req(const CSocket_req&) = delete;
        CSocket_req(CSocket_req&&) = delete;
        CSocket_req& operator = (const CSocket_req&) = delete;
        CSocket_req& operator = (CSocket_req&&) = delete;
        virtual ~CSocket_req() = default;

        explicit CSocket_req(const std::deque<std::string>& endpoints, const unsigned short int uiThreadCount = 1) : ISocket(endpoints, ZMQ_REQ, uiThreadCount) {}
    };
} // !bmq_socket

#endif // !__H_CSOCKET_REQ__