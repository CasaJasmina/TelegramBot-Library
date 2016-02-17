
// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library


#ifndef TelegramBot_h
#define TelegramBot_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include<WiFiSSLClient.h>
#include<Client.h>

struct message{
  String text;
  String chat_id;
  String sender;
  String date;
};

class TelegramBot
{
  public:
    TelegramBot(Client &_client);
  	void begin(String, String, String);
  	void sendMessage(String chat_id, String my_text);
  	message getUpdates();
    String _token;
    String _name;
    String _username;
  private:
    String sendRequest(String command);
    String last_message_recived;
    Client *client;
    const char *host="api.telegram.org";
    const int httpsPort = 443;

};

#endif
