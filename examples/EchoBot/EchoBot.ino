/*
  EchoBot

  This example shows how to program a Telegram Bot
  that echoes your messages.

  For a step-by-step tutorial visit:
  https://create.arduino.cc/projecthub/Arduino_Genuino/telegram-bot-library-ced4d4

  Updated 29 Nov 2016
  by Tommaso Laterza

  This example code is in the public domain.

*/
#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h>

//The SleepyDog library is needed to reset the board when something goes wrong.
//It is not strictly necessary but makes the bot way more reliable.
#include <Adafruit_SleepyDog.h> 

// Initialize Wifi connection to the router
char ssid[] = "xxxx";             // your network SSID (name)
char pass[] = "yyyy";           // your network key


// Initialize Telegram BOT
const char BotToken[] = "xxxx";

WiFiSSLClient client;
TelegramBot bot (BotToken, client);


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


  bot.begin();
  Watchdog.enable(10000); // set the timer to 10 sec

}

void loop() {
  
    Watchdog.reset(); // if this function is not called within 10 seconds the board will reset itself

    message m = bot.getUpdates(); // Read new messages
    if ( m.chat_id != 0 ){ // Checks if there are some updates
      Serial.println(m.text);
      bot.sendMessage(m.chat_id, m.text);  // Reply to the same chat with the same text
    } else {
      Serial.println("no new message");
    }

}
