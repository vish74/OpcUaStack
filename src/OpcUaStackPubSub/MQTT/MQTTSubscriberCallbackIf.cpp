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

#include "OpcUaStackPubSub/MQTT/MQTTSubscriberCallbackIf.h"

namespace OpcUaStackPubSub
{

	MQTTSubscriberCallbackIfTest::MQTTSubscriberCallbackIfTest()
	: MQTTSubscriberCallbackIf()
	{
	}

	MQTTSubscriberCallbackIfTest::~MQTTSubscriberCallbackIfTest()
	{
	}

	void
	MQTTSubscriberCallbackIfTest::onConnect(int rc)
	{
		std::cout << "MQTTSubscriberCallbackIfTest::" << "onConnect rc=" << rc << std::endl;
	}

	void
	MQTTSubscriberCallbackIfTest::onDisconnect(int rc)
	{
		std::cout << "MQTTSubscriberCallbackIfTest::" << "onDisconnect rc=" << rc << std::endl;
	}

	void
	MQTTSubscriberCallbackIfTest::onSubscribe(int mid)
	{
		std::cout << "MQTTSubscriberCallbackIfTest::" << "onSubscribe mid=" << mid << std::endl;
	}

	void
	MQTTSubscriberCallbackIfTest::onMessage(int mid, const char* topic, const void* payload,
			int payloadlen, int qos, bool retain)
	{
		std::cout << "MQTTSubscriberCallbackIfTest::" << "onMessage topic=" << topic << " -- len=" << payloadlen << std::endl;
	}

	void
	MQTTSubscriberCallbackIfTest::onUnSubscribe(int mid)
	{
		std::cout << "MQTTSubscriberCallbackIfTest::" << "onUnSubscribe mid=" << mid << std::endl;
	}

} /* namespace OpcUaClientModul */
