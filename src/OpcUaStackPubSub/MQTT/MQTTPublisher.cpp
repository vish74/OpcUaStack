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

#include "OpcUaStackPubSub/MQTT/MQTTPublisher.h"

namespace OpcUaStackPubSub
{

	MQTTPublisher::MQTTPublisher()
	: mqttClient_(nullptr)
	, callback_(nullptr)
	{
	}

	MQTTPublisher::~MQTTPublisher()
	{
	}

	// #######################################################################
	//
	//  Initialization Handling
	//
	// #######################################################################

	void
	MQTTPublisher::startUp(const char* host, int port, MQTTPublisherCallbackIf* callback)
	{
		callback_ = callback;

		mqttClient_ = constructMQTT();
		mqttClient_->setCallback(this);

		mqttClient_->init();
		mqttClient_->startup(host, port);
	}

	void
	MQTTPublisher::shutdown()
	{
		mqttClient_->shutdown();
		mqttClient_->cleanup();

		mqttClient_ = nullptr;
		callback_ = nullptr;
	}

	// #######################################################################
	//
	//  Publish Handling
	//
	// #######################################################################

	void
	MQTTPublisher::publish(int mid, const char* topic, const void* payload, int payloadlen)
	{
		mqttClient_->sendPublish(mid, topic, payload, payloadlen);
	}

	// #######################################################################
	//
	//  Callback Handling
	//
	// #######################################################################

	void
	MQTTPublisher::onConnect(int rc)
	{
		if ( callback_ ) callback_->onConnect(rc);
	}

	void
	MQTTPublisher::onDisconnect(int rc)
	{
		if ( callback_ ) callback_->onDisconnect(rc);
	}

	void
	MQTTPublisher::onPublish(int mid)
	{
		if ( callback_ ) callback_->onPublish(mid);
	}

} /* namespace OpcUaStackPubSub */
