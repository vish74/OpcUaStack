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

#include "OpcUaStackPubSub/MQTT/MQTTSubscriber.h"

namespace OpcUaStackPubSub
{

	MQTTSubscriber::MQTTSubscriber()
	: mqttClient_(nullptr)
	, callback_(nullptr)
	{
	}

	MQTTSubscriber::~MQTTSubscriber()
	{
	}

	// #######################################################################
	//
	//  Initialization Handling
	//
	// #######################################################################

	void
	MQTTSubscriber::startUp(const std::string& host, int port, MQTTSubscriberCallbackIf* callback)
	{
		callback_ = callback;

		mqttClient_ = constructMQTT();
		mqttClient_->setCallback(this);

		mqttClient_->init();
		mqttClient_->startup(host, port);
	}

	void
	MQTTSubscriber::shutdown(void)
	{
		mqttClient_->shutdown();
		mqttClient_->cleanup();

		mqttClient_ = nullptr;
		callback_ = nullptr;
	}

	// #######################################################################
	//
	//  Subscriber Handling
	//
	// #######################################################################

	void
	MQTTSubscriber::subscribe(int mid, const std::string& topic)
	{
		mqttClient_->createSubscribtion(mid, topic);
	}

	void
	MQTTSubscriber::unsubscribe(int mid, const std::string& topic)
	{
		mqttClient_->deleteSubscribtion(mid, topic);
	}

	// #######################################################################
	//
	//  Callback Handling
	//
	// #######################################################################

	void
	MQTTSubscriber::onConnect(int rc)
	{
		callback_->onConnect(rc);
	}

	void
	MQTTSubscriber::onDisconnect(int rc)
	{
		callback_->onDisconnect(rc);
	}

	void
	MQTTSubscriber::onSubscribe(int mid)
	{
		callback_->onSubscribe(mid);
	}

	void
	MQTTSubscriber::onMessage(int mid, const std::string& topic, const void* payload, int payloadlen,
			int qos, bool retain)
	{
		callback_->onMessage(mid, topic, payload, payloadlen, qos, retain);
	}

	void
	MQTTSubscriber::onUnSubscribe(int mid)
	{
		callback_->onUnSubscribe(mid);
	}

} /* namespace OpcUaStackPubSub */
