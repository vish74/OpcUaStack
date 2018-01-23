#include "unittest.h"

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#include "OpcUaStackPubSub/DataSetMessage/KeepAliveMessage.h"
#include "OpcUaStackPubSub/Network/NetworkMessage.h"
#include "OpcUaStackCore/Base/Utility.h"
#include "OpcUaStackPubSub/MQTT/MQTTClient.h"
#include "OpcUaStackPubSub/MQTT/MQTTClientBase.h"
#include "OpcUaStackPubSub/MQTT/MQTTPublisher.h"
#include "OpcUaStackPubSub/MQTT/MQTTSubscriber.h"
#include "OpcUaStackPubSub/MQTT/MQTTSubscriberCallbackIf.h"
#include "OpcUaStackPubSub/MQTT/MQTTPublisherCallbackIf.h"
#include "OpcUaStackPubSub/MQTT/NetworkMQTTPublisher.h"
#include "OpcUaStackPubSub/MQTT/NetworkMQTTSubscriber.h"

using namespace OpcUaStackPubSub;

// #############################################################
//
//  ENCODING and DECODING for test with NetworkMessages
//
// #############################################################

#define ENCODE_DECODE(msg, hexString, restoredMsg) {\
	boost::asio::streambuf sb;\
	std::iostream ios(&sb);\
	uint32_t pos;\
                 \
	msg.opcUaBinaryEncode(ios);\
                               \
	OpcUaStackCore::dumpHex(ios);\
	std::stringstream ss;\
	ss	<< hexString;\
                     \
	BOOST_REQUIRE(OpcUaStackCore::compare(ios, ss.str(), pos));\
                                                               \
	restoredMsg.opcUaBinaryDecode(ios);\
} while(0)


#define SHOULD_ENCODE_DECODE(msg, hexString) {\
	NetworkMessage restoredMsg;\
	ENCODE_DECODE(msg, hexString, restoredMsg);\
                                               \
	BOOST_REQUIRE(restoredMsg == msg);\
} while(0)

// #############################################################
//
//  MQTT tests
//
// #############################################################

BOOST_AUTO_TEST_SUITE(MQTTClient_)

BOOST_AUTO_TEST_CASE(MQTTClient_)
{
	std::cout << "MQTTClient_t" << std::endl;
}

// ------------------------------------------------------------
//  Constructor test
// ------------------------------------------------------------

BOOST_AUTO_TEST_CASE(MQTTClient_construct)
{
	std::cout << "MQTTCLIENT CONSTRUCTOR TEST" << std::endl;

	MQTTClientBase::SPtr mqttClient = constructMQTT();
	if ( mqttClient->mqttClientIfEnabled() )
		std::cout << "MQTTCLIENT ENABLED" << std::endl;
	else
		std::cout << "MQTTCLIENT DISABLED" << std::endl;
}

// ------------------------------------------------------------
//  Connection test
// ------------------------------------------------------------

BOOST_AUTO_TEST_CASE(MQTTClient_connect)
{
	std::cout << "MQTTCLIENT CONNECT TEST " << std::endl;

#ifdef MQTT_REAL_SERVER_TEST_1

	MQTTClientBase::SPtr mqttClientIf = constructMQTT();

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

#else

	std::cout << "TEST is not active!" << std::endl;

#endif /* MQTT_REAL_SERVER_TEST_1 */
}

// ------------------------------------------------------------
//  MQTT publisher and subscriber test
// ------------------------------------------------------------

BOOST_AUTO_TEST_CASE(MQTTClient_pub_sub)
{
	std::cout << "MQTTCLIENT PubSub TEST" << std::endl;

#ifdef MQTT_REAL_SERVER_TEST_2

	const std::string host = "localhost";
	int port = 1883;

	int mid = 1;
	const std::string topic = "HELLO_WORLD";
	const void* payload = "123456";
	int payloadlen = 6;

	MQTTSubscriberCallbackIfDummy cbSubscriber;
	MQTTPublisherCallbackIfDummy cbPublisher;

	MQTTSubscriber subscriber;
	subscriber.startUp(host, port, &cbSubscriber);
	subscriber.subscribe(mid, topic);

	MQTTPublisher publisher;
	publisher.startUp(host, port, &cbPublisher);
	publisher.publish(mid, topic, payload, payloadlen);

	std::cout << ">> Press [x] to continue <<" << std::endl;
	char c; std::cin >> c; // TODO waiting ... use Conditions...

	publisher.shutdown();

	subscriber.unsubscribe(mid, topic);
	subscriber.shutdown();

#else

	std::cout << "TEST is not active." << std::endl;

#endif /* MQTT_REAL_SERVER_TEST_2 */
}

// ------------------------------------------------------------
//  MQTT publisher and subscriber with NetworkMessage test
// ------------------------------------------------------------

BOOST_AUTO_TEST_CASE(MQTTClient_network_pub_sub)
{
	std::cout << "MQTTCLIENT Network PubSub TEST" << std::endl;

#ifdef MQTT_REAL_SERVER_TEST_3

	const std::string host = "localhost";
	int port = 1883;

	int mid = 1;
	std::string topic = "HELLO_WORLD";

	NetworkMessage message;
	OpcUaUInt16 writerId = 0x100;
	DataSetMessageArray::SPtr dataSetMessages = constructSPtr<DataSetMessageArray>();
	dataSetMessages->resize(1);
	dataSetMessages->push_back(constructSPtr<KeepAliveMessage>());

	message.dataSetPayloadHeader()->dataSetWriterIds()->resize(1);
	message.dataSetPayloadHeader()->dataSetWriterIds()->push_back(writerId);
	message.dataSetPayload()->count(1);
	message.dataSetPayload()->dataSetMessages(dataSetMessages);

	NetworkMQTTSubscriber networkSubscriber;
	NetworkReceiverIfDummy networkReceiverDummy;
	networkSubscriber.startUp(host, port, topic, mid, &networkReceiverDummy);

	NetworkMQTTPublisher networkPublisher;
	networkPublisher.startUp(host, port, topic, mid);
	networkPublisher.send(message);

	std::cout << ">> Press [x] to continue <<" << std::endl;
	char c; std::cin >> c; // TODO waiting ... use Conditions...

	NetworkMessage receiveMessage = networkReceiverDummy.message_;
	SHOULD_ENCODE_DECODE(receiveMessage, "04 00 01 04 00 84 03 00 00");

	networkPublisher.shutdown();
	networkSubscriber.shutdown();

#else

	std::cout << "TEST is not active." << std::endl;

#endif /* MQTT_REAL_SERVER_TEST_1 */
}

BOOST_AUTO_TEST_SUITE_END()
