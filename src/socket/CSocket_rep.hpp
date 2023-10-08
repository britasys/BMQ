#pragma once

#ifndef __H_CSOCKET_REP__
#define __H_CSOCKET_REP__

#include "ISocket.hpp"

namespace bmq_socket
{
    class CSocket_rep : public ISocket
    {
    public:
        CSocket_rep() = delete;
        CSocket_rep(const CSocket_rep&) = delete;
        CSocket_rep(CSocket_rep&&) = delete;
        CSocket_rep& operator = (const CSocket_rep&) = delete;
        CSocket_rep& operator = (CSocket_rep&&) = delete;
        virtual ~CSocket_rep() = default;

        explicit CSocket_rep(const std::deque<std::string>& endpoints, const unsigned short int uiThreadCount = 1) : ISocket(endpoints, ZMQ_REP, uiThreadCount) {}
    };
} // !bmq_socket

#endif // !__H_CSOCKET_REP__