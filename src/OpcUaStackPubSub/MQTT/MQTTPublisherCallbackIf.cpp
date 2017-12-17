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

#include "OpcUaStackPubSub/MQTT/MQTTPublisherCallbackIf.h"

namespace OpcUaStackPubSub
{

	MQTTPublisherCallbackIfTest::MQTTPublisherCallbackIfTest(void)
	: MQTTPublisherCallbackIf()
	{
	}

	MQTTPublisherCallbackIfTest::~MQTTPublisherCallbackIfTest(void)
	{
	}

	void
	MQTTPublisherCallbackIfTest::onConnect(int rc)
	{
		std::cout << "MQTTPublisherCallbackIfTest::" << "onConnect rc=" << rc << std::endl;
	}

	void
	MQTTPublisherCallbackIfTest::onDisconnect(int rc)
	{
		std::cout << "MQTTPublisherCallbackIfTest::" << "onDisconnect rc=" << rc << std::endl;
	}

	void
	MQTTPublisherCallbackIfTest::onPublish(int mid)
	{
		std::cout << "MQTTPublisherCallbackIfTest::" << "onPublish mid=" << mid << std::endl;
	}

} /* namespace OpcUaStackPubSub */
