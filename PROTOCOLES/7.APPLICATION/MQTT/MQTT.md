# MQTT

MQTT (Message Queuing Telemetry Transport) est un protocole de messagerie publication-souscription  basé sur le protocole TCP/IP.

![Fonctionnement général](https://www.framboise314.fr/wp-content/uploads/2018/06/principe_MQTT_600px.png)

## MQTT Basic Concepts

In MQTT there are a few basic concepts that you need to understand:

* Publish/Subscribe
* Messages
* Topics
* Broker

## MQTT – Publish/Subscribe

The first concept is the publish and subscribe system. In a publish and subscribe system, a device can publish a message on a topic, or it can be subscribed to a particular topic to receive messages

![Publish/Subscribe](https://gndtovcchome.files.wordpress.com/2020/04/publish-subscribe.png)

* For example Device 1 publishes on a topic.
* Device 2 is subscribed to the same topic as device 1 is publishing in.
* So, device 2 receives the message.

## MQTT – Messages

Messages are the information that you want to exchange between your devices. Whether it’s a command or data.

## MQTT – Topics

Another important concept are the topics. Topics are the way you register interest for incoming messages or how you specify where you want to publish the message.

Topics are represented with strings separated by a forward slash. Each forward slash indicates a topic level. Here’s an example on how you would create a topic for a lamp in your home office:

![Topic levels](https://gndtovcchome.files.wordpress.com/2020/04/5mqtt-topics.jpg)

> Note: topics are case-sensitive, which makes these two topics different:

![two topics different](https://gndtovcchome.files.wordpress.com/2020/04/7case-sensitive-300x188-1.jpg)

If you would like to turn on a lamp in your home office using MQTT you can imagine the following scenario:

![Usage case](https://gndtovcchome.files.wordpress.com/2020/04/publish-subscribe-example.png)

## MQTT – Broker

At last, you also need to be aware of the term broker.
The broker is primarily responsible for receiving all messages, filtering the messages, decide who is interested in them and then publishing the message to all subscribed clients.

![Pinciple](https://gndtovcchome.files.wordpress.com/2020/04/mqtt_broker.png)

There are several brokers you can use. In our home automation projects we use the Mosquitto broker which can be installed in the Raspberry Pi. Alternatively, you can use a cloud MQTT broker.

## Un premier test de MQTT en local

Commencez par connecter vos deux Raspberry Pi en WiFi sur votre Box, et relevez leurs adresses IP (souris sur l’icône réseau ou ifconfig dans un terminal).

Installez d’abord Mosquitto sur les deux Raspberry Pi

```bash
sudo apt-get install -y mosquitto mosquitto-clients
```

Après l’installation, un serveur Mosquitto est démarré automatiquement. Ouvrez un abonné (subscriber) dans le canal “test_channel” en attente de messages sur un des Raspberry Pi. Dans un terminal tapez :

```bash
mosquitto_sub -h localhost -v -t test_channel
```
Mosquitto reste en attente de message sur ce canal.

Afin de transférer simplement les données, nous allons d’abord utiliser le même Raspberry Pi. Cela permet de tester que Mosquitto fonctionne sur ce Raspberry Pi. Ouvrez un nouveau terminal / une nouvelle connexion SSH sur le même Raspberry Pi et tapez :
```bash
mosquitto_pub -h localhost -t test_channel -m "Hello Raspberry Pi"
```
Ici les données partent d’un publisher test_channel, rejoignent le broker et sont envoyées au subscriber. Dans la première fenêtre de terminal (ou dans votre première session SSH) vous devez voir apparaître Hello Raspberry Pi.

## Envoyer des données avec MQTT entre deux Raspberry Pi

![Message échangé entre 2 raspberry Pi](https://www.framboise314.fr/wp-content/uploads/2018/06/mqtt_test02_600px.png)


## Les différents protocoles MQTT existants

paho_mqtt : library Python pour MQTT
zigbee2mqtt : Utiliser le Zigbee avec MQTT