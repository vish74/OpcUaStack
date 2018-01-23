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

#ifndef __OpcUaStackPubSub_MQTTClient_h__
#define __OpcUaStackPubSub_MQTTClient_h__

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "OpcUaStackCore/Base/os.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackPubSub/MQTT/MQTTClientBase.h"
#include "OpcUaStackPubSub/MQTT/MQTTClientCallback.h"

#define USE_MOSQUITTO_CLIENT

#ifdef USE_MOSQUITTO_CLIENT
#include "mosquitto.h"
#include "mosquittopp.h"
#endif

using namespace OpcUaStackCore;

namespace OpcUaStackPubSub
{

#ifdef USE_MOSQUITTO_CLIENT

	class DLLEXPORT MQTTClient
	: public MQTTClientBase
	, private mosqpp::mosquittopp
	{
	  public:
		typedef boost::shared_ptr<MQTTClient> SPtr;

		MQTTClient(void);
		virtual ~MQTTClient(void);

		// INITIALIZE
		bool init(void);
		bool cleanup(void);
		bool startup(const std::string& host, int port);
		bool shutdown(void);
		bool mqttClientIfEnabled(void);

		// PUBLISHER
		int sendPublish(int mid, const std::string& topic, const void* payload,
				int payloadlen, int qos = 0, bool retain = false);

		// SUBSCIRBER
		int createSubscribtion(int mid, const std::string& topic, int qos = 0);
		int deleteSubscribtion(int mid, const std::string& topic);

		// CALLBACK HANDLING
		void setCallback(MQTTClientCallback* callback);

		// CALLBACKS MQTT
		void on_connect(int rc);
		void on_disconnect(int rc);
		void on_publish(int mid);
		void on_message(const struct mosquitto_message* message);
		void on_subscribe(int mid, int qos_count, const int* granted_qos);
		void on_unsubscribe(int mid);
		void on_log(int level, const char* logStr);
		void on_error();

	  private:
		MQTTClientCallback* callback_;
	};

#endif

	MQTTClientBase::SPtr constructMQTT(void);

}

#endif

