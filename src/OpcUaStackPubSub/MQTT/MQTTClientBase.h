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

#ifndef __OpcUaStackPubSub_MQTTClientBase_h__
#define __OpcUaStackPubSub_MQTTClientBase_h__

#include <boost/shared_ptr.hpp>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackPubSub/MQTT/MQTTClientCallback.h"

namespace OpcUaStackPubSub
{

	class DLLEXPORT MQTTClientBase
	{
	  public:
		typedef boost::shared_ptr<MQTTClientBase> SPtr;

		MQTTClientBase(void);
		virtual ~MQTTClientBase(void);

		// INITIALIZE
		virtual bool init(void);
		virtual bool cleanup(void);
		virtual bool startup(const std::string& host, int port);
		virtual bool shutdown(void);
		virtual bool mqttClientIfEnabled(void);

		// PUBLISHER
		virtual int sendPublish(int mid, const std::string& topic, const void* payload,
				int payloadlen, int qos = 0, bool retain = false);

		// SUBSCIRBER
		virtual int createSubscribtion(int mid, const std::string& topic, int qos = 0);
		virtual int deleteSubscribtion(int mid, const std::string& topic);

		// CALLBACK HANDLING
		virtual void setCallback(MQTTClientCallback* callback);

		// class functions
		void clientName(const std::string& clientName);
		std::string& clientName(void);

	  private:
		std::string clientName_;
	};

}

#endif
