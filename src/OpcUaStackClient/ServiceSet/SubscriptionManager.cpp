/*
   Copyright 2015 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/ServiceSet/DataChangeNotification.h"
#include "OpcUaStackClient/ServiceSet/SubscriptionManager.h"

using namespace OpcUaStackCore;

namespace OpcUaStackClient
{

	SubscriptionManager::SubscriptionManager(void)
	: SubscriptionService()
	, subscriptionServiceIf_(NULL)
	, subscriptionManagerIf_(NULL)
	, subscriptionSet_()
	, subscriptionSetPendingDelete_()
	, publishCount_(5)
	, actPublishCount_(0)
	{
		subscriptionServicePublishIf(this);
	}

	SubscriptionManager::~SubscriptionManager(void)
	{
	}

	void
	SubscriptionManager::publishCount(uint32_t publishCount)
	{
		publishCount_ = publishCount;
	}

	uint32_t
	SubscriptionManager::publishCount(void)
	{
		return publishCount_;
	}

	void
	SubscriptionManager::subscriptionManagerIf(SubscriptionManagerIf* subscriptionManagerIf)
	{
		subscriptionManagerIf_ = subscriptionManagerIf;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// send
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	SubscriptionManager::sendSync(ServiceTransactionCreateSubscription::SPtr& serviceTransactionCreateSubscription)
	{
		SubscriptionService::sendSync(serviceTransactionCreateSubscription);
	}
	void
	SubscriptionManager:: send(ServiceTransactionCreateSubscription::SPtr& serviceTransactionCreateSubscription)
	{
		SubscriptionService::send(serviceTransactionCreateSubscription);
	}

	void
	SubscriptionManager:: sendSync(ServiceTransactionModifySubscription::SPtr& serviceTransactionModifySubscription)
	{
		SubscriptionService::sendSync(serviceTransactionModifySubscription);
	}

	void
	SubscriptionManager:: send(ServiceTransactionModifySubscription::SPtr& serviceTransactionModifySubscription)
	{
		SubscriptionService::send(serviceTransactionModifySubscription);
	}

	void
	SubscriptionManager:: sendSync(ServiceTransactionTransferSubscriptions::SPtr& serviceTransactionTransferSubscriptions)
	{
		SubscriptionService::sendSync(serviceTransactionTransferSubscriptions);
	}

	void
	SubscriptionManager:: send(ServiceTransactionTransferSubscriptions::SPtr& serviceTransactionTransferSubscriptions)
	{
		SubscriptionService::send(serviceTransactionTransferSubscriptions);
	}

	void
	SubscriptionManager::sendSync(ServiceTransactionDeleteSubscriptions::SPtr& serviceTransactionDeleteSubscriptions)
	{
		sendDeleteSubscriptions(serviceTransactionDeleteSubscriptions);
		SubscriptionService::sendSync(serviceTransactionDeleteSubscriptions);
	}

	void
	SubscriptionManager::send(ServiceTransactionDeleteSubscriptions::SPtr& serviceTransactionDeleteSubscriptions)
	{
		sendDeleteSubscriptions(serviceTransactionDeleteSubscriptions);
		SubscriptionService::send(serviceTransactionDeleteSubscriptions);
	}

	void
	SubscriptionManager:: sendSync(ServiceTransactionSetPublishingMode::SPtr& serviceTransactionSetPublishingMode)
	{
		SubscriptionService::sendSync(serviceTransactionSetPublishingMode);
	}

	void
	SubscriptionManager:: send(ServiceTransactionSetPublishingMode::SPtr& serviceTransactionSetPublishingMode)
	{
		SubscriptionService::send(serviceTransactionSetPublishingMode);
	}

	void
	SubscriptionManager:: sendSync(ServiceTransactionPublish::SPtr& serviceTransactionPublish)
	{
		SubscriptionService::sendSync(serviceTransactionPublish);
	}

	void
	SubscriptionManager:: send(ServiceTransactionPublish::SPtr& serviceTransactionPublish)
	{
		SubscriptionService::send(serviceTransactionPublish);
	}

	void
	SubscriptionManager:: sendSync(ServiceTransactionRepublish::SPtr& serviceTransactionRepublish)
	{
		SubscriptionService::sendSync(serviceTransactionRepublish);
	}

	void
	SubscriptionManager:: send(ServiceTransactionRepublish::SPtr& serviceTransactionRepublish)
	{
		SubscriptionService::send(serviceTransactionRepublish);
	}


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// Component
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	SubscriptionManager::receive(Message::SPtr message)
	{
		ServiceTransaction::SPtr serviceTransaction = boost::static_pointer_cast<ServiceTransaction>(message);
		switch (serviceTransaction->nodeTypeResponse().nodeId<uint32_t>())
		{
			case OpcUaId_CreateSubscriptionResponse_Encoding_DefaultBinary:
			{
				subscriptionServiceCreateSubscriptionResponse(
					boost::static_pointer_cast<ServiceTransactionCreateSubscription>(serviceTransaction)
				);
				break;
			}

			case OpcUaId_DeleteSubscriptionsResponse_Encoding_DefaultBinary:
			{
				subscriptionServiceDeleteSubscriptionsResponse(
					boost::static_pointer_cast<ServiceTransactionDeleteSubscriptions>(serviceTransaction)
				);
				break;
			}

			case OpcUaId_PublishResponse_Encoding_DefaultBinary:
			{
				subscriptionServicePublishResponse(
					boost::static_pointer_cast<ServiceTransactionPublish>(serviceTransaction)
				);
				return;
			}
		}

		SubscriptionService::receive(message);
	}

    void
    SubscriptionManager::subscriptionServiceCreateSubscriptionResponse(ServiceTransactionCreateSubscription::SPtr serviceTransactionCreateSubscription)
    {
    	if (serviceTransactionCreateSubscription->statusCode() == Success) {
    		CreateSubscriptionResponse::SPtr res = serviceTransactionCreateSubscription->response();
    		createSubscription(res->subscriptionId());
    	}
    }

    void
    SubscriptionManager::sendDeleteSubscriptions(ServiceTransactionDeleteSubscriptions::SPtr& serviceTransactionDeleteSubscriptions)
    {
    	DeleteSubscriptionsRequest::SPtr req = serviceTransactionDeleteSubscriptions->request();
    	for (uint32_t pos=0; pos<req->subscriptionIds()->size(); pos++) {
    		uint32_t subscriptionId;
    		req->subscriptionIds()->get(pos, subscriptionId);
    		deleteSubscriptionRequest(subscriptionId);
    	}
    }

    void
    SubscriptionManager::subscriptionServiceDeleteSubscriptionsResponse(ServiceTransactionDeleteSubscriptions::SPtr serviceTransactionDeleteSubscriptions)
    {
    	if (serviceTransactionDeleteSubscriptions->statusCode() != Success) {
        	DeleteSubscriptionsRequest::SPtr req = serviceTransactionDeleteSubscriptions->request();
        	for (uint32_t pos=0; pos<req->subscriptionIds()->size(); pos++) {
        		uint32_t subscriptionId;
        		req->subscriptionIds()->get(pos, subscriptionId);
        		subscriptionSet_.insert(subscriptionId);
        	}
        	return;
    	}

        DeleteSubscriptionsRequest::SPtr req = serviceTransactionDeleteSubscriptions->request();
        for (uint32_t pos=0; pos<req->subscriptionIds()->size(); pos++) {
            uint32_t subscriptionId;
            req->subscriptionIds()->get(pos, subscriptionId);
            deleteSubscriptionResponse(subscriptionId);
        }
    }

    void
    SubscriptionManager::subscriptionServiceSetPublishingModeResponse(ServiceTransactionSetPublishingMode::SPtr serviceTransactionSetPublishingMode)
    {
    }

    void
    SubscriptionManager::subscriptionServicePublishResponse(ServiceTransactionPublish::SPtr serviceTransactionPublish)
    {
    	actPublishCount_--;

    	// check transaction status code
    	if (serviceTransactionPublish->statusCode() != Success) {
    		Log(Error, "subscription publish response error")
    			.parameter("StatsCode", OpcUaStatusCodeMap::shortString(serviceTransactionPublish->statusCode()));
    		sendPublishRequests();
    		return;
    	}

    	PublishResponse::SPtr res = serviceTransactionPublish->response();
    	receivePublishResponse(res);
    }

    void
    SubscriptionManager::subscriptionServiceRepublishResponse(ServiceTransactionRepublish::SPtr serviceTransactionRepublish)
    {
    }

    // --------------------------------------------------------------
    // --------------------------------------------------------------
    //
    // management of subscription
    //
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    void
    SubscriptionManager::createSubscription(uint32_t subscriptionId)
    {
    	SubscriptionSet::iterator it;
    	it = subscriptionSet_.find(subscriptionId);
    	if (it != subscriptionSet_.end()) {
    		Log(Error, "subscription create subscription response, because subscription already exist")
    			.parameter("SubscriptionId", subscriptionId);
    		return;
    	}

    	subscriptionSet_.insert(subscriptionId);
   		if (subscriptionManagerIf_ != NULL) {
    		subscriptionManagerIf_->subscriptionStateUpdate(SS_Open, subscriptionId);
    	}

    	if (subscriptionSet_.size() != 1) return;

    	sendPublishRequests();
    }

    void
    SubscriptionManager::deleteSubscriptionRequest(uint32_t subscriptionId)
    {
    	SubscriptionSet::iterator it;
    	it = subscriptionSet_.find(subscriptionId);
    	if (it == subscriptionSet_.end()) {
    	    Log(Error, "subscription delete subscription response error, because subscription not exist")
    	    	.parameter("SubscriptionId", subscriptionId);
    	    return;
    	}
    	subscriptionSet_.erase(it);
    }

    void
    SubscriptionManager::deleteSubscriptionResponse(uint32_t subscriptionId)
    {
   		if (subscriptionManagerIf_ != NULL) {
    		subscriptionManagerIf_->subscriptionStateUpdate(SS_Close, subscriptionId);
    	}
    }

    void
    SubscriptionManager::sendPublishRequests(void)
    {
    	while (actPublishCount_ < publishCount_) {
    		ServiceTransactionPublish::SPtr trx = ServiceTransactionPublish::construct();
    		trx->requestTimeout(60000); // FIXME:
    		SubscriptionService::send(trx);

    		actPublishCount_++;
    	}
    }

    void
    SubscriptionManager::receivePublishResponse(const PublishResponse::SPtr& publishResponse)
    {
    	uint32_t count = publishResponse->notificationMessage()->notificationData()->size();
    	for (uint32_t idx=0; idx<count; idx++) {
    		ExtensibleParameter::SPtr notify;
    		publishResponse->notificationMessage()->notificationData()->get(idx, notify);

    		switch (notify->parameterTypeId().nodeId<uint32_t>())
    		{
    			case OpcUaId_DataChangeNotification_Encoding_DefaultBinary:
    				dataChangeNotification(notify);
    				break;
    			default:
    				Log(Error, "subscription publish response error, because notification type in publish response unknown")
    				    .parameter("NotificationTypeId", notify->parameterTypeId().toString());
    				break;
    		}
    	}

    	sendPublishRequests();
    }

    void
    SubscriptionManager::dataChangeNotification(const ExtensibleParameter::SPtr& extensibleParameter)
    {
    	DataChangeNotification::SPtr dataChange;
    	dataChange = extensibleParameter->parameter<DataChangeNotification>();

    	uint32_t count = dataChange->monitoredItems()->size();
    	for (uint32_t idx=0; idx<count; idx++) {
    		MonitoredItemNotification::SPtr monitoredItem;
    		dataChange->monitoredItems()->get(idx, monitoredItem);

    		if (subscriptionManagerIf_ != NULL) {
    			subscriptionManagerIf_->dataChangeNotification(monitoredItem);
    		}
    	}
    }
}
