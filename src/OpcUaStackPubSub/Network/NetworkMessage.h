/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaStackPubSub_NetworkMessage_h__
#define __OpcUaStackPubSub_NetworkMessage_h__

#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackPubSub
{

	class DLLEXPORT NetworkMessageHeader
	{
	  public:
		NetworkMessageHeader(void);
		~NetworkMessageHeader(void);
	};


	class DLLEXPORT ExtendedNetworkMessageHeader
	{
	  public:
		ExtendedNetworkMessageHeader(void);
		~ExtendedNetworkMessageHeader(void);
	};


	class DLLEXPORT SecurityHeader
	{
	  public:
		SecurityHeader(void);
		~SecurityHeader(void);
	};


	class DLLEXPORT NetworkMessage
	{
	  public:
		NetworkMessage(void);
		~NetworkMessage(void);
	};

}

#endif