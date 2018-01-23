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

#ifndef OPCUASTACKPUBSUB_MQTT_MQTTPUBLISHERCALLBACKIF_H_
#define OPCUASTACKPUBSUB_MQTT_MQTTPUBLISHERCALLBACKIF_H_

#include <iostream>

#include "OpcUaStackCore/Base/os.h"

namespace OpcUaStackPubSub
{

	class DLLEXPORT MQTTPublisherCallbackIf
	{
	  public:
		virtual ~MQTTPublisherCallbackIf(void) {};

		virtual void onConnect(int rc) = 0;
		virtual void onDisconnect(int rc) = 0;
		virtual void onPublish(int mid) = 0;
	};

	class DLLEXPORT MQTTPublisherCallbackIfDummy
	: public MQTTPublisherCallbackIf
	{
	  public:
		MQTTPublisherCallbackIfDummy(void);
		virtual ~MQTTPublisherCallbackIfDummy(void);

		void onConnect(int rc);
		void onDisconnect(int rc);
		void onPublish(int mid);
	};

} /* namespace OpcUaStackPubSub */

#endif /* OPCUASTACKPUBSUB_MQTT_MQTTPUBLISHERCALLBACKIF_H_ */
