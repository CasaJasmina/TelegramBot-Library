/*
  EchoBot

  This example shows how to program a Telegram Bot
  that echoes your messages using a custom keyboard.

  For a step-by-step tutorial visit:
  https://create.arduino.cc/projecthub/Arduino_Genuino/telegram-bot-library-ced4d4

  Updated 19 May 2016
  by Tommaso Laterza

  This example code is in the public domain.

*/


#include<WiFiSSLClient.h>
#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "xxxx";             // your network SSID (name)
char pass[] = "yyyy";           // your network key


// Initialize Telegram BOT
const char BotToken[] = "xxxx";
const char BotName[] = "yyyy";
const char BotUsername[] = "zzzz";

WiFiSSLClient client;
TelegramBot bot (BotToken, BotName, BotUsername, client);
TelegramKeyboard keyboard_one;

void setup() {

  Serial.begin(115200);
  while (!Serial) {}
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

  // define your row's
  const char* row_one[] = {"true", "false"};
  const char* row_two[] = {"one", "two", "thee", "hello!"};

  // assing a row to one or more keyboards
  // second argument is the length of the row
  keyboard_one.addRow(row_one, 2);
  keyboard_one.addRow(row_two, 4);
  bot.begin();

}

void loop() {

  message m = bot.getUpdates(); // Read new messages
  if ( m.chat_id != 0 ) { // Checks if there are some updates
    Serial.println(m.text);
    bot.sendMessage(m.chat_id, m.text, keyboard_one);  // Reply to the same chat with the same text
  } else {
    Serial.println("no new message");
  }

  delay(2000);
}
