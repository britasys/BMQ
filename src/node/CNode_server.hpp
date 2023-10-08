#pragma once

#ifndef __H_CNODE_SERVER__
#define __H_CNODE_SERVER__

#include "./INode.hpp"

namespace bmq_node
{
    class CNode_server : public INode
    {
    public:
        CNode_server() = delete;
        CNode_server(const CNode_server&) = delete;
        CNode_server(CNode_server&&) = delete;
        CNode_server& operator = (const CNode_server&) = delete;
        CNode_server& operator = (CNode_server&&) = delete;
        virtual ~CNode_server() = default;
    };
} // !bmq_node

#endif //!__H_CNODE_SERVER__