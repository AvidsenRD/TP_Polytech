/**
* \file api_mqtt.c
* \brief Handle mqtt connection of different objects
*/
#include "../inc/api_mqtt.h"
#include "../../gpio/inc/api_led.h"
#include "../../gpio/inc/api_servo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTClient.h"
#include "MQTTAsync.h"

volatile MQTTClient_deliveryToken deliveredtoken;

Object light = {NULL, "IDmaison0", "IDmaison0/us1", "IDmaison0/s1", "NULL", "NULL", "light/light_2ch", NULL, NULL};
/**
* \fn void delivered (void *context, MQTTClient_deliveryToken dt)
* \brief Callback for the deliverance of a message
* \param *context Additional info that can be given
* \param dt token of deliverance
*/
void delivered(void *context, MQTTClient_deliveryToken dt)
{
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

/**
* \fn int msgarrvd (void *context, char *topicName, int topicLen, MQTTClient_message *message)
* \brief Callback for the reception of a message
* \param *context Additional info that can be given
* \param *topicName name of the topic received
* \param topicLen topic length
* \param *message data received
* \return 1
*/
int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{
    int i;
    char *payloadptr;
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = message->payload;
    for (i = 0; i < message->payloadlen;i++)
    {
        printf("%x\n",message->payload);
    }
    putchar('\n');

    if(!strcmp(topicName, light.topic1Rx))
    {
        set_state_led(light.obj1, *payloadptr);
    }
    
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

/**
* \fn void connlost (void *context, char *cause)
* \brief Callback for the disconnection
* \param *context Additional info that can be given
* \param *cause reason of the disconnection
*/
void connlost(void *context, char *cause)
{
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

/**
* \fn int connectObject (Object *obj)
* \brief Connect an object to the server
* \param *obj Object to connect
* \return State of the connection
*/
int connectObject(Object *obj)
{
    int rc;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    conn_opts.username = obj->username;
    conn_opts.password = "PASSWORD";
    MQTTClient_create(&(obj->client), ADDRESS, obj->clientID,
                      MQTTCLIENT_PERSISTENCE_NONE, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_setCallbacks(obj->client, NULL, connlost, msgarrvd, delivered);

    if ((rc = MQTTClient_connect(obj->client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d, %s\n", rc, MQTTClient_strerror(rc));
        return rc;
    }
    printf("Connection %s\n", MQTTClient_strerror(rc));

    if(strcmp("NULL", obj->topic1Rx))
    {
        rc = MQTTClient_subscribe(obj->client, obj->topic1Rx, 1);
        printf("Subscribing to %s, %s\n", obj->topic1Rx, MQTTClient_strerror(rc));
    }
    if(strcmp("NULL", obj->topic2Rx))
    {
        rc = MQTTClient_subscribe(obj->client, obj->topic2Rx, 1);
        printf("Subscribing to %s, %s\n", obj->topic2Rx, MQTTClient_strerror(rc));
    }
    return rc;
}
/**
* \fn int sendMessage (Object *obj, char * msg, int size)
* \brief Send a message to the server
* \param *obj Sender object
* \param *msg Message to send
* \param size Size of the message to send
*/
int sendMessage(Object *obj, char * msg, int size)
{
    int rc;
    MQTTClient_deliveryToken token;

    MQTTClient_message pubmsg = MQTTClient_message_initializer;

    pubmsg.payload = msg;
    pubmsg.payloadlen = size;
    pubmsg.qos = 1;
    pubmsg.retained = 0;

    rc = MQTTClient_publishMessage(obj->client, obj->topic1Tx, &pubmsg, &token);
    printf("Envoi message, %s\n", MQTTClient_strerror(rc));
    rc = MQTTClient_waitForCompletion(obj->client, token, 5000);
    printf("Message with delivery token %d delivered, %s\n", token, MQTTClient_strerror(rc));
    return rc;
}