/*
  Custom_Keyboard

  This example shows how to program a Telegram Bot
  with a custom keyboard that echoes your messages.

*/


#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "xxxx";             // your network SSID (name)
char pass[] = "yyyy";           // your network key


// Initialize Telegram BOT
const char BotToken[] = "****";
const char BotName[] = "****";
const char BotUsername[] = "****";


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

  // define your rows
  const char* row_one[] = {"true", "false"};
  const char* row_two[] = {"one", "two", "three", "hello!"};

  // assign a row to one or more keyboards
  // second argument is the number of buttons of that row
  keyboard_one.addRow(row_one, 2);
  keyboard_one.addRow(row_two, 4);
  bot.begin();

}

void loop() {

  // Checks if there are some updates
  message m = bot.getUpdates();
  
  
  if ( m.chat_id != 0 ) { // if message received
    Serial.println(m.text);
    // Reply to the same chat with the same text
    // last two argument: one_time_keyboard & resize_keyboard
    bot.sendMessage(m.chat_id, m.text, keyboard_one, false, true);
  } else {
    Serial.println("no new message");
  }

}
