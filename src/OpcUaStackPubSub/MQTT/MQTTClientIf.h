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
//#include "OpcUaStackPubSub/Network/NetworkSenderIf.h"
//#include "OpcUaStackPubSub/Network/NetworkReceiverIf.h"

namespace OpcUaStackPubSub
{

	class MQTTClientIf
//	: public NetworkSenderIf
	{
	  public:
		typedef boost::shared_ptr<MQTTClientIf> SPtr;

		MQTTClientIf(void);
		virtual ~MQTTClientIf(void);

		// INITIALIZE
		virtual bool init(void);
		virtual bool cleanup(void);
		virtual bool startup(const char* host, int port);
		virtual bool shutdown(void);
		virtual bool mqttClientIfEnabled(void);

		// PUBLISHER
		virtual int sendPublish(int mid, const char* topic, const void* payload,
				int payloadlen, int qos = 0, bool retain = false);

		// SUBSCIRBER
		virtual int createSubscribtion(int mid, const char* topic, int qos = 0);
		virtual int deleteSubscribtion(int mid, const char* topic);

		// CALLBACK HANDLING
		virtual void setCallback(MQTTClientCallback* callback);

//		bool registerReceiverIf(NetworkReceiverIf* networkReceiverIf);
//
//		//
//		// Sender and Receiver interface
//		//
//		virtual bool send(const NetworkMessage& message);

		// class functions
		void clientName(const std::string& clientName);
		std::string& clientName(void);

//	  protected:
//		NetworkReceiverIf* networkReceiverIf_;

	  private:
		std::string clientName_;
	};

}

#endif
