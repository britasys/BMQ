#pragma once

#ifndef __H_IO__
#define __H_IO__

#include <memory>
#include <deque>
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
        IOutput(const IOutput&) = delete;
        IOutput(IOutput&&) noexcept = delete;
        IOutput& operator = (const IOutput&) = delete;
        IOutput& operator = (IOutput&&) noexcept = delete;

        explicit IOutput(const OUTPUT_INIT& init) : m_init{init} {}

        virtual void send(const std::string& req, std::string& res) = 0;

    protected:
        OUTPUT_INIT m_init{};
    };

    typedef struct _input_init
    {
        unsigned short int uiThreadCount{1};
        std::deque<std::string> endpoints{};
    } INPUT_INIT;

    class IInput
    {
    public:
        IInput() = delete;
        IInput(const IInput&) = delete;
        IInput(IInput&&) noexcept = delete;
        IInput& operator = (const IInput&) = delete;
        IInput& operator = (IInput&&) noexcept = delete;

        explicit IInput(const INPUT_INIT& init) : m_init{init} {}

        void registerOutput(IOutput& output) noexcept { this->m_pOutput = std::make_shared<IOutput>(output); }

        virtual bool run() noexcept = 0;

    protected:
        INPUT_INIT m_init{};
        std::shared_ptr<IOutput> m_pOutput{};
    };
} // !bmq

#endif // !__H_IO__