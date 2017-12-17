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

#ifndef __OpcUaStackPubSub_MQTTSubscriber_h__
#define __OpcUaStackPubSub_MQTTSubscriber_h__

#include <boost/shared_ptr.hpp>

#include "OpcUaStackPubSub/MQTT/MQTTClient.h"
#include "OpcUaStackPubSub/MQTT/MQTTSubscriberCallbackIf.h"

namespace OpcUaStackPubSub
{

	class MQTTSubscriber
	: public MQTTClientCallback
	{
	  public:
		typedef boost::shared_ptr<MQTTSubscriber> SPtr;

		MQTTSubscriber();
		virtual ~MQTTSubscriber();

		// INITIALIZE
		void startUp(const char* host, int port, MQTTSubscriberCallbackIf* callback);
		void shutdown(void);

		// SUBSCRIPTION
		void subscribe(int mid, const char* topic);
		void unsubscribe(int mid, const char* topic);

		// CALLBACKS MQTTClientCallback
		void onConnect(int rc);
		void onDisconnect(int rc);
		void onSubscribe(int mid);
		void onMessage(int mid, const char* topic, const void* payload,
				int payloadlen, int qos, bool retain);
		void onUnSubscribe(int mid);

	  private:
		MQTTClientIf::SPtr mqttClient_;
		MQTTSubscriberCallbackIf* callback_;
	};

} /* namespace OpcUaStackPubSub */

#endif /* __OpcUaStackPubSub_MQTTSubscriber_h__ */
