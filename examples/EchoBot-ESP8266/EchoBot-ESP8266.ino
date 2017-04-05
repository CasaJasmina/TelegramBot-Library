#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>



// Initialize Wifi connection to the router
const char* ssid     = "xxxx";
const char* password = "yyyy";


// Initialize Telegram BOT
const char BotToken[] = "zzzz";

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);


void setup() {

  Serial.begin(115200);
  while (!Serial);

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
