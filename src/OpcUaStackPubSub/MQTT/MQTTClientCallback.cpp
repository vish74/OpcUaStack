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

#include <OpcUaStackPubSub/MQTT/MQTTClientCallback.h>

namespace OpcUaStackPubSub
{

	// #######################################################################
	//
	//  MQTTClientCallback abstract
	//
	// #######################################################################

	MQTTClientCallback::MQTTClientCallback(void)
	{
	}

	MQTTClientCallback::~MQTTClientCallback(void)
	{
	}

	void
	MQTTClientCallback::onConnect(int rc)
	{
	}

	void
	MQTTClientCallback::onDisconnect(int rc)
	{
	}

	void
	MQTTClientCallback::onPublish(int mid)
	{
	}

	void
	MQTTClientCallback::onSubscribe(int mid)
	{
	}

	void
	MQTTClientCallback::onMessage(int mid, const std::string& topic, const void* payload, int payloadlen, int qos, bool retain)
	{
	}

	void
	MQTTClientCallback::onUnSubscribe(int mid)
	{
	}

	// #######################################################################
	//
	//  MQTTClientCallback dummy test class
	//
	// #######################################################################

	MQTTClientCallbackDummy::MQTTClientCallbackDummy(void)
	: MQTTClientCallback()
	{
	}

	MQTTClientCallbackDummy::~MQTTClientCallbackDummy(void)
	{
	}

	void
	MQTTClientCallbackDummy::onConnect(int rc)
	{
		std::cout << "MQTTClientCallbackTest::" << "onConnect rc" << rc << std::endl;
	}

	void
	MQTTClientCallbackDummy::onDisconnect(int rc)
	{
		std::cout << "MQTTClientCallbackTest::" << "onDisconnect rc" << rc << std::endl;
	}

	void
	MQTTClientCallbackDummy::onPublish(int mid)
	{
		std::cout << "MQTTClientCallbackTest::" << "onPublish mid" << mid << std::endl;
	}

	void
	MQTTClientCallbackDummy::onSubscribe(int mid)
	{
		std::cout << "MQTTClientCallbackTest::" << "onSubscribe mid" << mid << std::endl;
	}

	void
	MQTTClientCallbackDummy::onMessage(int mid, const std::string& topic, const void* payload, int payloadlen, int qos, bool retain)
	{
		std::cout << "MQTTClientCallbackTest::" << "onMessage mid" << mid << " -- topic= " << topic << std::endl;
	}

	void
	MQTTClientCallbackDummy::onUnSubscribe(int mid)
	{
		std::cout << "MQTTClientCallbackTest::" << "onUnSubscribe mid" << mid << std::endl;
	}

} /* namespace OpcUaClientModul */
