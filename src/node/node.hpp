#pragma once

#ifndef __H_NODE__
#define __H_NODE__

#include <socket/socket.hpp>
#include <http/httpServer.hpp>
#include <http/httpClient.hpp>

#include <memory>
#include <deque>
#include <string>

namespace bmq
{
    template <typename INPUT, typename OUTPUT, typename INPUT_INIT, typename OUTPUT_INIT>
    struct _bmq_node
    {
        _bmq_node() = delete;
        _bmq_node(const _bmq_node &) = delete;
        _bmq_node(_bmq_node &&) noexcept = delete;
        _bmq_node &operator=(const _bmq_node &) = delete;
        _bmq_node &operator=(_bmq_node &&) noexcept = delete;
        virtual ~_bmq_node() = default;

        explicit _bmq_node(const INPUT_INIT &input_init, const OUTPUT_INIT &output_init)
        {
            this->pInput = std::make_shared<INPUT>(input_init);
            this->pOutput = std::make_shared<OUTPUT>(output_init);

            this->pInput.register(this->pOutput);
        }

        void run() const noexcept
        {
            this->pInput->run();
        }

    private:
        std::shared_ptr<INPUT> pInput{};
        std::shared_ptr<OUTPUT> pOutput{};
    };
} // !bmq

#endif //!__H_NODE__