/*
    EventTypeClass: AuditConditionCommentEventType

    Generated Source Code - please do not change this source code

    EventTypeCodeGenerator Version:
        OpcUaStackCore - 3.0.1

    Autor: Kai Huebl (kai@huebl-sgh.de)
*/

#include "OpcUaStackCore/StandardEventType/AuditConditionCommentEventType.h"

namespace OpcUaStackCore
{
    
    AuditConditionCommentEventType::AuditConditionCommentEventType(void)
    : AuditConditionEventType()
    , eventVariables_()
    {
        eventVariables_.registerEventVariable("EventId", OpcUaBuildInType_OpcUaByteString);
        eventVariables_.registerEventVariable("Comment", OpcUaBuildInType_OpcUaLocalizedText);
    
        eventVariables_.eventType(OpcUaNodeId((OpcUaUInt32)2829));
        eventVariables_.namespaceIndex(0);
        eventVariables_.browseName(OpcUaQualifiedName("AuditConditionCommentEventType"));
        eventVariables_.namespaceUri("");
    }
    
    AuditConditionCommentEventType::~AuditConditionCommentEventType(void)
    {
    }
    
    OpcUaVariant::SPtr 
    AuditConditionCommentEventType::eventId(void)
    {
    	OpcUaVariant::SPtr value;
    	eventVariables_.getValue("eventId", value);
    	return value;
    }
    
    OpcUaVariant::SPtr 
    AuditConditionCommentEventType::comment(void)
    {
    	OpcUaVariant::SPtr value;
    	eventVariables_.getValue("comment", value);
    	return value;
    }
    
    bool 
    AuditConditionCommentEventType::eventId(OpcUaVariant::SPtr& eventId)
    {
    	return eventVariables_.setValue("EventId", eventId);
    }
    
    bool 
    AuditConditionCommentEventType::comment(OpcUaVariant::SPtr& comment)
    {
    	return eventVariables_.setValue("Comment", comment);
    }
    
    void
    AuditConditionCommentEventType::mapNamespaceUri(void)
    {
        uint32_t namespaceIndex;
        AuditConditionEventType::mapNamespaceUri();
    
        OpcUaVariant::SPtr eventTypeVariable = constructSPtr<OpcUaVariant>();
        eventTypeVariable->setValue(eventVariables_.eventType());
    
        setNamespaceIndex(eventVariables_.namespaceUri(), namespaceIndex, eventVariables_.browseName(), eventTypeVariable);
    
        eventType(eventTypeVariable);
        eventVariables_.eventType(eventTypeVariable);
        eventVariables_.namespaceIndex(namespaceIndex);
    }

    OpcUaVariant::SPtr
    AuditConditionCommentEventType::get(
    	OpcUaNodeId& eventType,
    	std::list<OpcUaQualifiedName::SPtr>& browseNameList,
    	EventResult::Code& resultCode
    )
    {
        resultCode = EventResult::Success;

        // check whether eventType and typeNodeId are identical
        if (eventType == eventVariables_.eventType()) {
    	    return eventVariables_.get(browseNameList, resultCode);
        }

        // the start item was not found. We delegate the search to the base class
        OpcUaVariant::SPtr variant;
        variant = AuditConditionEventType::get(eventType, browseNameList, resultCode);
        if (resultCode != EventResult::Success || browseNameList.empty()) {
    	    return variant;
        }

        return eventVariables_.get(browseNameList, resultCode);
    }

}