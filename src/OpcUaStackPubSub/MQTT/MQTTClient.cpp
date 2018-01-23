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

#include "OpcUaStackPubSub/MQTT/MQTTClient.h"

namespace OpcUaStackPubSub
{

#ifdef USE_MOSQUITTO_CLIENT

	MQTTClient::MQTTClient(void)
	: MQTTClientBase()
	, mosquittopp()
	, callback_(nullptr)
	{
	}

	MQTTClient::~MQTTClient(void)
	{
	}

	// #######################################################################
	//
	//  De/Initialization Handling
	//
	// #######################################################################

	bool
	MQTTClient::init(void)
	{
		mosquitto_lib_init();
		return true;
	}

	bool
	MQTTClient::cleanup(void)
	{
		mosquitto_lib_cleanup();
		callback_ = nullptr;
		return true;
	}

	// #######################################################################
	//
	//  Startup and Shutdown Handling
	//
	// #######################################################################

	bool
	MQTTClient::startup(const std::string& host, int port)
	{
		connect_async(host.c_str(), port);
		loop_start();
		return true;
	}

	bool
	MQTTClient::shutdown(void)
	{
		loop_stop(true);
		disconnect();
		return true;
	}

	// #######################################################################
	//
	//  Publish Handling
	//
	// #######################################################################

	int
	MQTTClient::sendPublish(int mid, const std::string& topic, const void* payload,
			int payloadlen, int qos, bool retain)
	{
		return publish(&mid, topic.c_str(), payloadlen, payload, qos, retain);
	}

	// #######################################################################
	//
	//  Subscriber Handling
	//
	// #######################################################################

	int
	MQTTClient::createSubscribtion(int mid, const std::string& topic, int qos)
	{
		return subscribe(&mid, topic.c_str(), qos);
	}

	int
	MQTTClient::deleteSubscribtion(int mid, const std::string& topic)
	{
		return unsubscribe(&mid, topic.c_str());
	}

	// #######################################################################
	//
	//  Callback Handling
	//
	// #######################################################################

	void
	MQTTClient::setCallback(MQTTClientCallback* callback)
	{
		callback_ = callback;
	}

	void
	MQTTClient::on_connect(int rc)
	{
		if ( callback_ ) callback_->onConnect(rc);
	}

	void
	MQTTClient::on_disconnect(int rc)
	{
		if ( callback_ ) callback_->onDisconnect(rc);
	}

	void
	MQTTClient::on_publish(int mid)
	{
		if ( callback_ ) callback_->onPublish(mid);
	}

	void
	MQTTClient::on_message(const struct mosquitto_message* message)
	{
		if ( callback_ ) callback_->onMessage(message->mid, message->topic,
				message->payload, message->payloadlen,
				message->qos, message->retain);
	}

	void
	MQTTClient::on_subscribe(int mid, int qos_count, const int* granted_qos)
	{
		if ( callback_ ) callback_->onSubscribe(mid);
	}

	void
	MQTTClient::on_unsubscribe(int mid)
	{
		if ( callback_ ) callback_->onUnSubscribe(mid);
	}

	void
	MQTTClient::on_log(int level, const char* logStr)
	{
		std::cout << "MQTTClient::" << "on_log " << level << " -- " << logStr << std::endl;
	}

	void
	MQTTClient::on_error()
	{
		std::cout << "MQTTClient::" << "on_error" << std::endl;
	}

	// #######################################################################
	//
	//  Helper Functions
	//
	// #######################################################################

	bool
	MQTTClient::mqttClientIfEnabled(void)
	{
		return true;
	}

	MQTTClientBase::SPtr constructMQTT(void)
	{
		return constructSPtr<MQTTClient>();
	}

#else

	MQTTClientBase::SPtr constructMQTT(void)
	{
		return constructSPtr<MQTTClientBase>();
	}

#endif

}
