#pragma once

#ifndef __H_INODE__
#define __H_INODE__

#include "../socket/CSocket_rep.hpp"
#include "../socket/CSocket_req.hpp"

#include <zmq.hpp>

#include <string>
#include <memory>

namespace bmq_node
{
    class INode
    {
    public:
        INode() = delete;
        INode(const INode&) = delete;
        INode(INode&&) = delete;
        INode& operator = (const INode&) = delete;
        INode& operator = (INode&&) = delete;
        virtual ~INode() = default;
    };
} // !bmq_node

#endif //!__H_INODE__