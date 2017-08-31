/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tencent is pleased to support the open source community by making behaviac available.
//
// Copyright (C) 2015-2017 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at http://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and limitations under the License.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _BEHAVIAC_BEHAVIORTREE_ACTION_H_
#define _BEHAVIAC_BEHAVIORTREE_ACTION_H_

#include "behaviac/common/base.h"
#include "behaviac/behaviortree/behaviortree.h"
#include "behaviac/behaviortree/behaviortree_task.h"
#include "behaviac/agent/agent.h"

namespace behaviac {
    /*! \addtogroup treeNodes Behavior Tree
    * @{
    * \addtogroup Action
    * @{ */

    ///An action is a member function of agent
    /**
    Action node is the bridge between behavior tree and agent member function.
    a member function can be assigned to an action node. function will be
    invoked when Action node ticked. function attached can be up to eight parameters most.
    */
    class BEHAVIAC_API Action : public BehaviorNode {
    public:
        BEHAVIAC_DECLARE_DYNAMIC_TYPE(Action, BehaviorNode);

        Action();
        virtual ~Action();
        virtual void load(int version, const char* agentType, const properties_t& properties);
        EBTStatus Execute(Agent* pAgent);

        EBTStatus Execute(const Agent* pAgent, EBTStatus childSatus);
        static const char* ParseMethodNames(const char* fullName, char* agentIntanceName, char* agentClassName, char* methodName);
    protected:
        virtual bool IsValid(Agent* pAgent, BehaviorTask* pTask) const;

    private:
        virtual BehaviorTask* createTask() const;

    protected:
        behaviac::IInstanceMember*		m_method;
        EBTStatus			    m_resultOption;
        behaviac::IInstanceMember*		m_resultFunctor;

        friend class ActionTask;
    };

    class BEHAVIAC_API ActionTask : public LeafTask {
    public:
        BEHAVIAC_DECLARE_DYNAMIC_TYPE(ActionTask, LeafTask);

        ActionTask();
        virtual ~ActionTask();

    protected:
        virtual void copyto(BehaviorTask* target) const;
        virtual void save(IIONode* node) const;
        virtual void load(IIONode* node);

        virtual bool onenter(Agent* pAgent);
        virtual void onexit(Agent* pAgent, EBTStatus s);
        virtual EBTStatus update(Agent* pAgent, EBTStatus childStatus);
    };
    /*! @} */
    /*! @} */
}

#endif//_BEHAVIAC_BEHAVIORTREE_ACTION_H_