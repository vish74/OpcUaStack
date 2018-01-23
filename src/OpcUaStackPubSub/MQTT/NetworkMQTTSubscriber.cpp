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

#include "OpcUaStackPubSub/MQTT/NetworkMQTTSubscriber.h"

namespace OpcUaStackPubSub
{

	NetworkMQTTSubscriber::NetworkMQTTSubscriber()
	: mqttSubscriber_()
	, networkReceiver_(nullptr)
	, topic_("")
	, mid_(0)
	{
	}

	NetworkMQTTSubscriber::~NetworkMQTTSubscriber()
	{
	}

	// #######################################################################
	//
	//  INITIALIZE
	//
	// #######################################################################

	bool
	NetworkMQTTSubscriber::startUp(const std::string& host, int port,
			const std::string& topic, int mid, NetworkReceiverIf* networkReceiver)
	{
		topic_ = topic;
		mid_ = mid;
		networkReceiver_ = networkReceiver;
		mqttSubscriber_.startUp(host, port, this);
		return true;
	}

	bool
	NetworkMQTTSubscriber::shutdown(void)
	{
		mqttSubscriber_.unsubscribe(mid_, topic_);
		mqttSubscriber_.shutdown();
		networkReceiver_ = nullptr;
		return true;
	}

	// #######################################################################
	//
	//  MQTT SUBSCRIBER CALLBACK
	//
	// #######################################################################

	void
	NetworkMQTTSubscriber::onConnect(int rc)
	{
		mqttSubscriber_.subscribe(mid_, topic_);
	}

	void
	NetworkMQTTSubscriber::onSubscribe(int mid)
	{
	}

	void
	NetworkMQTTSubscriber::onMessage(int mid, const std::string& topic, const void* payload,
			int payloadlen, int qos, bool retain)
	{
		const char* binaryMessage = reinterpret_cast<const char *>(payload);

		boost::asio::streambuf sb;
		std::iostream ios(&sb);

		ios.write(binaryMessage, payloadlen);

		NetworkMessage message;
		message.opcUaBinaryDecode(ios);
		networkReceiver_->receive(message);
	}

	void
	NetworkMQTTSubscriber::onUnSubscribe(int mid)
	{
	}

	void
	NetworkMQTTSubscriber::onDisconnect(int rc)
	{
	}

	// #######################################################################
	// #######################################################################
	//
	//  NETWORK RECEIVER DUMMY CLASS
	//
	// #######################################################################
	// #######################################################################

	NetworkReceiverIfDummy::NetworkReceiverIfDummy()
	{
	}

	NetworkReceiverIfDummy::~NetworkReceiverIfDummy()
	{
	}

	bool
	NetworkReceiverIfDummy::receive(const NetworkMessage& message)
	{
		message_ = message;
		return true;
	}

} /* namespace OpcUaStackPubSub */
