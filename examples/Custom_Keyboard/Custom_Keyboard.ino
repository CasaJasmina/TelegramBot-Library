/*
 * This example shows how program  
 * a Telegram bot that turns on 
 * and off the on-board LED,
 * and how to implement 
 * a custom keyboard for your bot
 * 
 * For a step by step tutorial visit
 * https://create.arduino.cc/projecthub/Arduino_Genuino/telegram-bot-library-ced4d4
 * 
 * This example code is in the public domain.
 * 
 * created 8 April 2016
 * by Tommaso Laterza
 * 
*/

#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h>
#include <ArduinoJson.h> 

// Initialize Wifi connection to the router
char ssid[] = "network";             // your network SSID (name)
char pass[] = "password";           // your network key


// Initialize Telegram BOT
const char* BotToken = "****";
const char* BotName = "****";
const char* BotUsername = "****";

WiFiSSLClient client;
TelegramBot bot (BotToken, BotName, BotUsername, client);

const int ledPin =  6; // use this if you are using a mkr1000 board
//const int ledPin =  13; // uncomment this if you are using other Arduino/Genuino boards
bool started = false;

void setup() {

  Serial.begin(115200);
 // while (!Serial) {} // uncomment this for debug
  delay(3000);


  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");

  bot.begin();
  pinMode(ledPin, OUTPUT);

}

void loop() {
  
  // use a String array to make a list of buttons 
  String ButtonsLayout[] = { "On", "Off" };
  
  message m = bot.getUpdates(); // Read new messages
  
  if ( m.text.equals("Start")) { // check for a Start message 
    started = true;

    // m.chat_id = a unique number for every chat 
    // the message you want to send in String format
    // the list of buttons you want to be displayed on you bot
    // number of rows of your button 
    // number of columns of your buttons
    // one_time_keyboard
    
    bot.sendMessage(m.chat_id,"Started", ButtonsLayout , 1, 2, false);
  }



  if ( m.text.equals("On") && started == true) {
    digitalWrite(ledPin, HIGH);
    bot.sendMessage(m.chat_id,"Led On!", ButtonsLayout , 1, 2, false);
  }
  else if ( m.text.equals("Off") && started == true) {
    digitalWrite(ledPin, LOW);
    bot.sendMessage(m.chat_id,"Led Off!", ButtonsLayout , 1, 2, false);
  }


}
