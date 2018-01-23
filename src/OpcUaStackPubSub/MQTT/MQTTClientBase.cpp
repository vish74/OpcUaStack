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

#include "OpcUaStackPubSub/MQTT/MQTTClientBase.h"

namespace OpcUaStackPubSub
{
	// #######################################################################
	//
	//  MQTTClientBase dummy
	//
	// #######################################################################

	MQTTClientBase::MQTTClientBase(void)
	: clientName_("")
	{
	}

	MQTTClientBase::~MQTTClientBase(void)
	{
	}

	bool
	MQTTClientBase::mqttClientIfEnabled(void)
	{
		return false;
	}

	bool
	MQTTClientBase::startup(const std::string& host, int port)
	{
		std::cout << "startup abstarct" << std::endl;
		return false;
	}

	bool
	MQTTClientBase::init(void)
	{
		return false;
	}

	bool
	MQTTClientBase::cleanup(void)
	{
		return false;
	}

	bool
	MQTTClientBase::shutdown(void)
	{
		return false;
	}

	int
	MQTTClientBase::sendPublish(int mid, const std::string& topic, const void* payload,
			int payloadlen, int qos, bool retain)
	{
		return 0;
	}

	int
	MQTTClientBase::createSubscribtion(int mid, const std::string& topic, int qos)
	{
		return 0;
	}

	int
	MQTTClientBase::deleteSubscribtion(int mid, const std::string& topic)
	{
		return 0;
	}

	void
	MQTTClientBase::setCallback(MQTTClientCallback* callback)
	{
	}

	void
	MQTTClientBase::clientName(const std::string& clientName)
	{
		clientName_ = clientName;
	}

	std::string&
	MQTTClientBase::clientName(void)
	{
		return clientName_;
	}
}
