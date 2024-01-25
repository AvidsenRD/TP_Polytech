/**
* \file api_mqtt.h
* \brief header file to handle mqtt connection of different objects
*/
#ifndef API_MQTT_H
#define API_MQTT_H

#include "MQTTClient.h"

#define ADDRESS "mqtt://donkey.athemium.com:1883"
/**
* \struct Object api_mqtt.h
* \brief Structure to handle a mqtt connection of an object
* \param client MQTT client to be connected
* \param clientID ID of the object
* \param topic1Rx first reception topic
* \param topic1Tx first sending topic
* \param topic2Rx second reception topic
* \param topic2Tx second sending topic
* \param username object_type/object_reference
* \param *obj1 first object to handle
* \param *obj2 second object to handle
*/
typedef struct Objects
{
    MQTTClient client;
    char clientID[25];
    char topic1Rx[25];
    char topic1Tx[25];
    char topic2Rx[25];
    char topic2Tx[25];
    char username[40];
    void *obj1;
    void *obj2;
} Object;



void delivered(void *context, MQTTClient_deliveryToken dt);

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);

void connlost(void *context, char *cause);

int connectObject(Object *obj);

int sendMessage(Object *obj, char * msg, int size);

#endif