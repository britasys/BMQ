#pragma once

#ifndef __H_CNODE_CLIENT__
#define __H_CNODE_CLIENT__

#include "./INode.hpp"

namespace bmq_node
{
    class CNode_client : public INode
    {
    public:
        CNode_client() = delete;
        CNode_client(const CNode_client&) = delete;
        CNode_client(CNode_client&&) = delete;
        CNode_client& operator = (const CNode_client&) = delete;
        CNode_client& operator = (CNode_client&&) = delete;
        virtual ~CNode_client() = default;
    };
} // !bmq_node

#endif //!__H_CNODE_CLIENT__