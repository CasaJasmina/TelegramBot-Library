
// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library


#ifndef TelegramBot_h
#define TelegramBot_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include<Client.h>

#define HOST "api.telegram.org"
#define SSL_PORT 443

struct message{
  String text;
  String chat_id;
  String sender;
  String date;
};

class TelegramBot
{
  public:
    TelegramBot(String token, String name, String username, Client &_client);
  	void begin();
  	void sendMessage(String chat_id, String my_text);
  	message getUpdates();

  private:
      String _token;
      String _name;
      String _username;

      String sendRequest(String command);
      String last_message_recived;

      Client *client;
};

#endif
