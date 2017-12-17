#include "unittest.h"

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "OpcUaStackPubSub/MQTT/MQTTClient.h"
#include "OpcUaStackPubSub/MQTT/MQTTPublisher.h"
#include "OpcUaStackPubSub/MQTT/MQTTSubscriber.h"
#include "OpcUaStackPubSub/MQTT/MQTTSubscriberCallbackIf.h"
#include "OpcUaStackPubSub/MQTT/MQTTPublisherCallbackIf.h"

using namespace OpcUaStackPubSub;

#ifdef REAL_SERVER

BOOST_AUTO_TEST_SUITE(MQTTClient_)

BOOST_AUTO_TEST_CASE(MQTTClient_)
{
	std::cout << "MQTTClient_t" << std::endl;
}

BOOST_AUTO_TEST_CASE(MQTTClient_construct)
{
	MQTTClientIf::SPtr mqttClientIf = constructMQTT();

	if (mqttClientIf->mqttClientIfEnabled()) {
		std::cout << "MQTTCLIENT ENABLED" << std::endl;
	}
	else {
		std::cout << "MQTTCLIENT DISABLED" << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(MQTTClient_construct_connect)
{
	std::cout << "MQTTCLIENT CONNECT TEST" << std::endl;

	MQTTClientIf::SPtr mqttClientIf = constructMQTT();

	if (mqttClientIf->mqttClientIfEnabled())
	{
		std::cout << "MQTTCLIENT initialized" << std::endl;
		mqttClientIf->init();

		std::cout << "MQTTCLIENT startup" << std::endl;
		const char* host = "localhost";
		int port = 1883;
		mqttClientIf->startup(host, port);

		std::cout << "MQTTCLIENT shutdown" << std::endl;
		mqttClientIf->shutdown();

		std::cout << "MQTTCLIENT cleanup" << std::endl;
		mqttClientIf->cleanup();
	}

	std::cout << "MQTTCLIENT CONNECT TEST FINISHED" << std::endl;
}

BOOST_AUTO_TEST_CASE(MQTTClient_pub_sub)
{
	std::cout << "MQTTCLIENT PubSub TEST" << std::endl;

	const char* host = "localhost";
	int port = 1883;

	int mid = 1;
	const char* topic = "HELLO_WORLD";
	const void* payload = "123456";
	int payloadlen = 6;

	MQTTSubscriberCallbackIfTest cbSubscriber;
	MQTTPublisherCallbackIfTest cbPublisher;

	MQTTSubscriber subscriber;
	subscriber.startUp(host, port, &cbSubscriber);
	subscriber.subscribe(mid, topic);

	MQTTPublisher publisher;
	publisher.startUp(host, port, &cbPublisher);
	publisher.publish(mid, topic, payload, payloadlen);

//	char c; std::cin >> c; // waiting ... use Conditions...

	publisher.shutdown();

	subscriber.unsubscribe(mid, topic);
	subscriber.shutdown();

	std::cout << "MQTTCLIENT PubSub TEST FINISHED" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()

#endif
