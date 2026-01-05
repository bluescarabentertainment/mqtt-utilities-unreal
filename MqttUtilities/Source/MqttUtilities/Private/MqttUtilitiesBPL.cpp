// Copyright (c) 2019 Nineva Studios

#include "MqttUtilitiesBPL.h"

#if PLATFORM_WINDOWS
#include "Windows/MqttClient.h"
#elif PLATFORM_MAC
#include "Mac/MqttClient.h"
#elif PLATFORM_IOS
#include "IOS/MqttClient.h"
#elif PLATFORM_ANDROID
#include "Android/MqttClient.h"
#elif PLATFORM_LINUX
#include "Linux/MqttClient.h"
#endif

TScriptInterface<IMqttClientInterface> UMqttUtilitiesBPL::CreateMqttClient(FMqttClientConfig config)
{
	UE_LOG(LogTemp, Log, TEXT("MQTT => Creating MQTT client..."));

	UMqttClient* MqttClient = NewObject<UMqttClient>();
	MqttClient->Init(config);
	TScriptInterface<IMqttClientInterface> MqttClientInterface;
	MqttClientInterface.SetObject(MqttClient);
	MqttClientInterface.SetInterface(Cast<IMqttClientInterface>(MqttClient));
	return MqttClientInterface;
}
