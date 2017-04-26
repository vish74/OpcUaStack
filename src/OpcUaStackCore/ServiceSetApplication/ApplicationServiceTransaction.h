/*
   Copyright 2015-2017 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaStackCore_ApplicationServiceTransaction_h__
#define __OpcUaStackCore_ApplicationServiceTransaction_h__

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackCore/ServiceSet/ServiceTransactionTemplate.h"
#include "OpcUaStackCore/ServiceSetApplication/RegisterForwardNodeRequest.h"
#include "OpcUaStackCore/ServiceSetApplication/RegisterForwardResponse.h"
#include "OpcUaStackCore/ServiceSetApplication/RegisterForwardGlobalRequest.h"
#include "OpcUaStackCore/ServiceSetApplication/RegisterForwardGlobalResponse.h"
#include "OpcUaStackCore/ServiceSetApplication/GetNodeReferenceRequest.h"
#include "OpcUaStackCore/ServiceSetApplication/GetNodeReferenceResponse.h"
#include "OpcUaStackCore/ServiceSetApplication/NamespaceInfoRequest.h"
#include "OpcUaStackCore/ServiceSetApplication/NamespaceInfoResponse.h"

namespace OpcUaStackCore
{
	
	typedef ServiceTransactionTemplate<
		RegisterForwardNodeRequest,
		RegisterForwardResponse,
		OpcUaId_RegisterForwardNodeRequest_Encoding_DefaultBinary,
		OpcUaId_RegisterForwardNodeResponse_Encoding_DefaultBinary
	> ServiceTransactionRegisterForward;

	typedef ServiceTransactionTemplate<
		RegisterForwardGlobalRequest,
		RegisterForwardGlobalResponse,
		OpcUaId_RegisterForwardGlobalRequest_Encoding_DefaultBinary,
		OpcUaId_RegisterForwardGlobalResponse_Encoding_DefaultBinary
	> ServiceTransactionRegisterForwardGlobal;

	typedef ServiceTransactionTemplate<
		GetNodeReferenceRequest,
		GetNodeReferenceResponse,
		OpcUaId_GetNodeReferenceRequest_Encoding_DefaultBinary,
		OpcUaId_GetNodeReferenceResponse_Encoding_DefaultBinary
	> ServiceTransactionGetNodeReference;

	typedef ServiceTransactionTemplate<
		NamespaceInfoRequest,
		NamespaceInfoResponse,
		OpcUaId_NamespaceInfoRequest_Encoding_DefaultBinary,
		OpcUaId_NamespaceInfoResponse_Encoding_DefaultBinary
	> ServiceTransactionNamespaceInfo;

}

#endif
