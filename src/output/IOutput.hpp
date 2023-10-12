#pragma once

#ifndef __H_IOUTPUT__
#define __H_IOUTPUT__

#include <memory>
#include <string>

namespace bmq
{
    typedef struct _output_init
    {
        std::string url{};
    } OUTPUT_INIT;

    class IOutput
    {
    public:
        IOutput() = delete;
        IOutput(const IOutput &) = delete;
        IOutput(IOutput &&) noexcept = delete;
        IOutput &operator=(const IOutput &) = delete;
        IOutput &operator=(IOutput &&) noexcept = delete;

        explicit IOutput(const OUTPUT_INIT &init) : m_init{init} {}

        virtual void send(const std::string &req, std::string &res) = 0;

    protected:
        OUTPUT_INIT m_init{};
    };
} // !bmq

#endif // !__H_IOUTPUT__