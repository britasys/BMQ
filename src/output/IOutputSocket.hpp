#pragma once

#ifndef __H_COUTPUTSOCKET__
#define __H_COUTPUTSOCKET__

#include <memory>
#include <string>

#include <IOutput.hpp>

#include <socket/socket.hpp>

namespace bmq
{
    class COutputSocket : public IOutput
    {
    public:
        COutputSocket() = delete;
        COutputSocket(const COutputSocket &) = delete;
        COutputSocket(COutputSocket &&) noexcept = delete;
        COutputSocket &operator=(const COutputSocket &) = delete;
        COutputSocket &operator=(COutputSocket &&) noexcept = delete;

        explicit COutputSocket(const OUTPUT_INIT &init) : IOutput{init} {}

        void send(const std::string &req, std::string &res) {}
    };
} // !bmq

#endif // !__H_COUTPUTSOCKET__