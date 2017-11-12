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

#include "OpcUaStackPubSub/MQTT/MQTTClientIf.h"

namespace OpcUaStackPubSub
{

	MQTTClientIf::MQTTClientIf(void)
	{
	}

	MQTTClientIf::~MQTTClientIf(void)
	{
	}

	bool
	MQTTClientIf::mqttClientIfEnabled(void)
	{
		return false;
	}

	bool
	MQTTClientIf::startup(void)
	{
		return false;
	}

	bool
	MQTTClientIf::init(void)
	{
		return false;
	}

	bool
	MQTTClientIf::cleanup(void)
	{
		return false;
	}

	bool
	MQTTClientIf::shutdown(void)
	{
		return false;
	}

	void
	MQTTClientIf::clientName(const std::string& clientName)
	{
		clientName_ = clientName;
	}

	std::string&
	MQTTClientIf::clientName(void)
	{
		return clientName_;
	}

}