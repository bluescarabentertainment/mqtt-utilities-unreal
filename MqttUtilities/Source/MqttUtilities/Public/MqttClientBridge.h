// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interface/MqttClientInterface.h"
#include "UObject/Object.h"
#include "MqttClientBridge.generated.h"

/**
 * 
 */
UCLASS()
class MQTTUTILITIES_API UMqttClientBridge : public UObject, public IMqttClientInterface
{
	GENERATED_BODY()
public:
	void Init(const FMqttClientConfig &Config);
	/**
	 * Connect to MQTT broker
	 * @param ConnectionData - structure with data required to connect to MQTT broker (host url, port, client id etc.)
	 * @param OnConnectCallback - callback function handler triggered after client successfully established connection with MQTT broker 
	 */
	virtual void Connect(FMqttConnectionData ConnectionData, const FOnConnectDelegate& OnConnectCallback) override;

	/**
	 * Disconnect from MQTT broker
	 * @param OnDisconnectCallback - callback function handler triggered after client was disconnected from MQTT broker
	 */
	virtual void Disconnect(const FOnDisconnectDelegate& OnDisconnectCallback) override;

	/**
	 * Subscribe to topic
	 * @param Topic - name of the topic
	 * @param Qos - level of quality of service
	 */
	virtual void Subscribe(FString Topic, int Qos) override;

	/**
	 * Unsubscribe from topic
	 * @param Topic - name of the topic
	 */
	virtual void Unsubscribe(FString Topic) override;

	/**
	 * Publish message
	 * @param Message - structure with message data (topic, QoS, payload etc.)
	 */
	virtual void Publish(FMqttMessage Message) override;

	/**
	 * Set handler for message publishing event
	 * @param OnPublishCallback - callback function handler triggered after client message was published to MQTT broker
	 */
	virtual void SetOnPublishHandler(const FOnPublishDelegate& OnPublishCallback) override;

	/**
	 * Set handler for message receiving event
	 * @param OnMessageCallback - callback function handler triggered after client received message from MQTT broker
	 */
	virtual void SetOnMessageHandler(const FOnMessageDelegate& OnMessageCallback) override;

	/**
	 * Set handler for subscription event
	 * @param OnSubscribeCallback - callback function handler triggered after client subscribed to topic exposed by MQTT broker
	 */
	virtual void SetOnSubscribeHandler(const FOnSubscribeDelegate& OnSubscribeCallback) override;

	/**
	 * Set handler for unsubscription event
	 * @param OnUnsubscribeCallback - callback function handler triggered after client unsubscribed from topic exposed by MQTT broker
	 */
	virtual void SetOnUnsubscribeHandler(const FOnUnsubscribeDelegate& OnUnsubscribeCallback) override;

	/**
	 * Set handler for error event
	 * @param OnErrorCallback - callback function handler triggered after any MQTT-related error occured
	 */
	virtual void SetOnErrorHandler(const FOnMqttErrorDelegate& OnErrorCallback) override;

private:
	UPROPERTY()
	class UMqttClientBase *ClientImpl = nullptr;
};
