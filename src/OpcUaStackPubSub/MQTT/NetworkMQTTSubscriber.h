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

#ifndef OPCUASTACKPUBSUB_MQTT_NETWORKMQTTSUBSCRIBER_H_
#define OPCUASTACKPUBSUB_MQTT_NETWORKMQTTSUBSCRIBER_H_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackPubSub/MQTT/MQTTSubscriber.h"
#include "OpcUaStackPubSub/Network/NetworkReceiverIf.h"

namespace OpcUaStackPubSub
{

	class DLLEXPORT NetworkMQTTSubscriber
	: public MQTTSubscriberCallbackIf
	{
	  public:
		typedef boost::shared_ptr<NetworkMQTTSubscriber> SPtr;

		NetworkMQTTSubscriber(void);
		virtual ~NetworkMQTTSubscriber(void);

		// INITIALIZE
		bool startUp(const std::string& host, int port, const std::string& topic, int mid,
				NetworkReceiverIf* networkReceiver);
		bool shutdown(void);

		// CALLBACK MQTT IF
		void onConnect(int rc);
		void onDisconnect(int rc);
		void onSubscribe(int mid);
		void onMessage(int mid, const std::string& topic, const void* payload,
				int payloadlen, int qos, bool retain);
		void onUnSubscribe(int mid);

	  private:
		MQTTSubscriber mqttSubscriber_;
		NetworkReceiverIf* networkReceiver_;
		std::string topic_;
		int mid_;
	};

	class DLLEXPORT NetworkReceiverIfDummy
	: public NetworkReceiverIf
	{
	  public:
		NetworkReceiverIfDummy(void);
		virtual ~NetworkReceiverIfDummy(void);

		bool receive(const NetworkMessage& message);

		NetworkMessage message_;
	};

} /* namespace OpcUaStackPubSub */

#endif /* OPCUASTACKPUBSUB_MQTT_NETWORKMQTTSUBSCRIBER_H_ */
