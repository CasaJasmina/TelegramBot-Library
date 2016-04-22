/*
  EchoBot

  This example shows how to program a Telegram Bot
  that echoes your messages.

 */


#include<WiFiSSLClient.h>
#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "xxxx";             // your network SSID (name)
char pass[] = "yyyy";           // your network key


// Initialize Telegram BOT
const String BotToken = "xxxx";
const String BotName = "yyyy";
const String BotUsername = "zzzz";


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
  keyboard.addRow(x, 2);
  keyboard.addRow(y, 4);

  bot.begin();

}

void loop() {

  message m = bot.getUpdates(); // Read new messages
  bot.sendMessage(m.chat_id, m.text, keyboard_one);  // Reply to the same chat with the same text
}
