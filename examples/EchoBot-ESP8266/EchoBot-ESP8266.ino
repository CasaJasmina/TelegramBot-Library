/*
  EchoBot on ESP8266

  This example shows how to program a Telegram Bot
  that echoes your messages.

  For a step-by-step tutorial visit:
  https://create.arduino.cc/projecthub/Arduino_Genuino/telegram-bot-library-ced4d4

  Updated 13 February 2018
  by Tommaso Laterza

  This example code is in the public domain.

*/

#include "arduino_secrets.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>

// Initialize Wifi connection to the router
const char* ssid  = SECRET_SSID;
const char* password = SECRET_PASS;


// Initialize Telegram BOT
const char BotToken[] = SECRET_BOT_TOKEN;

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);


void setup() {

  Serial.begin(115200);
  while (!Serial); // Wait for the Serial monitor to be opened

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");


  bot.begin();

}

void loop() {
 
    message m = bot.getUpdates(); // Read new messages
    if ( m.chat_id != 0 ){ // Checks if there are some updates
      Serial.println(m.text);
      bot.sendMessage(m.chat_id, m.text);  // Reply to the same chat with the same text
    } else {
      Serial.println("no new message");
    }

}
