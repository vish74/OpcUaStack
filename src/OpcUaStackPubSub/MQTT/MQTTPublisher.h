/*
 Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#ifndef __OpcUaStackPubSub_MQTTPublisher_h__
#define __OpcUaStackPubSub_MQTTPublisher_h__

#include <boost/shared_ptr.hpp>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackPubSub/MQTT/MQTTClient.h"
#include "OpcUaStackPubSub/MQTT/MQTTPublisherCallbackIf.h"

namespace OpcUaStackPubSub
{

	class DLLEXPORT MQTTPublisher
	: public MQTTClientCallback
	{
	  public:
		typedef boost::shared_ptr<MQTTPublisher> SPtr;

		MQTTPublisher();
		virtual ~MQTTPublisher();

		// INITIALIZE
		void startUp(const std::string& host, int port, MQTTPublisherCallbackIf* callback = nullptr);
		void shutdown(void);

		// PUBLSIH
		void publish(int mid, const std::string& topic, const void* payload, int payloadlen);

		// CALLBACKS MQTTClientCallback
		void onConnect(int rc);
		void onDisconnect(int rc);
		void onPublish(int mid);

	  private:
		MQTTClientBase::SPtr mqttClient_;
		MQTTPublisherCallbackIf* callback_;
	};

} /* namespace OpcUaStackPubSub */

#endif /* __OpcUaStackPubSub_MQTTPublisher_h__ */
