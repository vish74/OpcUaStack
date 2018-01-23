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

#ifndef OPCUASTACKPUBSUB_MQTT_NETWORKMQTTPUBLISHER_H_
#define OPCUASTACKPUBSUB_MQTT_NETWORKMQTTPUBLISHER_H_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackPubSub/MQTT/MQTTPublisher.h"
#include "OpcUaStackPubSub/Network/NetworkSenderIf.h"

namespace OpcUaStackPubSub
{

	class DLLEXPORT NetworkMQTTPublisher
	: public MQTTPublisherCallbackIf
	, public NetworkSenderIf
	{
	  public:
		typedef boost::shared_ptr<NetworkMQTTPublisher> SPtr;

		NetworkMQTTPublisher();
		virtual ~NetworkMQTTPublisher();

		// INITIALIZE
		bool startUp(const std::string& host, int port, const std::string& topic, int mid);
		bool shutdown(void);

		// NETWORK SENDER IF
		bool send(const NetworkMessage& message);

		// MQTT PUBLISHER CALLBACK
		void onConnect(int rc);
		void onDisconnect(int rc);
		void onPublish(int mid);

	  private:
		MQTTPublisher mqttPublisher_;
		std::string topic_;
		int mid_;
	};

} /* namespace OpcUaStackPubSub */

#endif /* OPCUASTACKPUBSUB_MQTT_NETWORKMQTTPUBLISHER_H_ */
