// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library


#ifndef TelegramBot_h
#define TelegramBot_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Client.h>

#define HOST "api.telegram.org"
#define SSL_PORT 443
#define JSON_BUFF_SIZE 2000

struct message{
  const char* text;
  const char* chat_id;
  const char* sender;
  const char* date;
};

class TelegramBot
{
  public:
    TelegramBot(const char* token, const char* name, const char* username, Client &client);
  	void begin();
    String sendMessage(const char* chat_id, const char* my_text);
    String sendMessage(const char* chat_id, const char* my_text, String markup[], int nrows, int ncolumns, bool one_time_keyboard = true, bool resize_keyboard = true);
    String postMessage(String msg);
    message getUpdates();


  private:
      String readPayload();
      const char* token;
      const char* name;
      const char* username;

      String last_message_recived="";

      Client *client;
};

#endif
