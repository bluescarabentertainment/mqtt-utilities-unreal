// Fill out your copyright notice in the Description page of Project Settings.


#include "MqttClientBridge.h"


#if PLATFORM_WINDOWS
#include "Windows/MqttClient.h"
#endif

#if PLATFORM_MAC
#include "Mac/MqttClient.h"
#endif

#if PLATFORM_IOS
#include "IOS/MqttClient.h"
#endif

#if PLATFORM_ANDROID
#include "Android/MqttClient.h"
#endif

#if PLATFORM_LINUX
#include "Linux/MqttClient.h"
#endif

void UMqttClientBridge::Init(const FMqttClientConfig& Config)
{
	ClientImpl = NewObject<UMqttClient>();
	ClientImpl->Init(Config);
}

void UMqttClientBridge::Connect(FMqttConnectionData ConnectionData, const FOnConnectDelegate& OnConnectCallback)
{
	ClientImpl->Connect(ConnectionData, OnConnectCallback);
}

void UMqttClientBridge::Disconnect(const FOnDisconnectDelegate& OnDisconnectCallback)
{
	ClientImpl->Disconnect(OnDisconnectCallback);
}

void UMqttClientBridge::Subscribe(FString Topic, int Qos)
{
	ClientImpl->Subscribe(Topic, Qos);
}

void UMqttClientBridge::Unsubscribe(FString Topic)
{
	ClientImpl->Unsubscribe(Topic);
}

void UMqttClientBridge::Publish(FMqttMessage Message)
{
	ClientImpl->Publish(Message);
}

void UMqttClientBridge::SetOnPublishHandler(const FOnPublishDelegate& OnPublishCallback)
{
	ClientImpl->SetOnPublishHandler(OnPublishCallback);
}

void UMqttClientBridge::SetOnMessageHandler(const FOnMessageDelegate& OnMessageCallback)
{
	ClientImpl->SetOnMessageHandler(OnMessageCallback);
}

void UMqttClientBridge::SetOnSubscribeHandler(const FOnSubscribeDelegate& OnSubscribeCallback)
{
	ClientImpl->SetOnSubscribeHandler(OnSubscribeCallback);
}

void UMqttClientBridge::SetOnUnsubscribeHandler(const FOnUnsubscribeDelegate& OnUnsubscribeCallback)
{
	ClientImpl->SetOnUnsubscribeHandler(OnUnsubscribeCallback);
}

void UMqttClientBridge::SetOnErrorHandler(const FOnMqttErrorDelegate& OnErrorCallback)
{
	ClientImpl->SetOnErrorHandler(OnErrorCallback);
}
