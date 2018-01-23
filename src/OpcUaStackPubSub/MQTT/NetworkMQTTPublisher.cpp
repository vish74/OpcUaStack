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

#include "OpcUaStackPubSub/MQTT/NetworkMQTTPublisher.h"

namespace OpcUaStackPubSub
{

	NetworkMQTTPublisher::NetworkMQTTPublisher()
	: mqttPublisher_()
	, mid_(0)
	, topic_("")
	{
	}

	NetworkMQTTPublisher::~NetworkMQTTPublisher()
	{
	}

	// #######################################################################
	//
	//  INITIALIZE
	//
	// #######################################################################

	bool
	NetworkMQTTPublisher::startUp(const std::string& host, int port,
			const std::string& topic, int mid)
	{
		topic_ = topic;
		mid_ = mid;
		mqttPublisher_.startUp(host, port, this);
		return true;
	}

	bool
	NetworkMQTTPublisher::shutdown(void)
	{
		mqttPublisher_.shutdown();
		return true;
	}

	// #######################################################################
	//
	//  NETWORK SENDER IF
	//
	// #######################################################################

	bool
	NetworkMQTTPublisher::send(const NetworkMessage& message)
	{
		boost::asio::streambuf sb;
		std::ostream os(&sb);

		message.opcUaBinaryEncode(os);

		const char* binaryMessage = boost::asio::buffer_cast<const char*>(sb.data());
		mqttPublisher_.publish(mid_, topic_, binaryMessage, sb.size());
		return true;
	}

	// #######################################################################
	//
	//  MQTT PUBLISHER CALLBACK
	//
	// #######################################################################

	void
	NetworkMQTTPublisher::onConnect(int rc)
	{
	}

	void
	NetworkMQTTPublisher::onDisconnect(int rc)
	{
	}

	void
	NetworkMQTTPublisher::onPublish(int mid)
	{
	}

} /* namespace OpcUaStackPubSub */
