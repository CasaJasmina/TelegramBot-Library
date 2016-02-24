
// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library


#include "TelegramBot.h"


TelegramBot::TelegramBot(String token, String name, String username, Client &_client)	{
	client = &_client;

	this->_token=token;
	this->_name=name;
	this->_username=username;
}

void TelegramBot::begin()	{
	last_message_recived="";

	client->connect(HOST, SSL_PORT);
}

/**************************************************************************************************
 * sendRequest- function to achieve connection to api.telegram.org and send command to telegram *                                                                 *
 **************************************************************************************************/

String TelegramBot::sendRequest(String command)  {

	while(!client->connected()){
		Serial.println("trying to connect...");
		client->connect(HOST, SSL_PORT);
		delay (1000);
	}
			//Send your request to api.telegram.org
			String getRequest = "GET /bot"+_token+"/"+command+" HTTP/1.1";
	    client->println(getRequest);
	    client->println("User-Agent: curl/7.37.1");
	    client->println("Host: api.telegram.org");
	    client->println("Accept: */*");
	    client->println();

char c;
String payload="";

	//Read the answer and save it in String payload
	while (client->connected()) {
	payload = client->readStringUntil('\n');
	//Serial.println(payload);
	if (payload == "\r") {
		break;
	 }
  }
payload = client->readStringUntil('\r');

//Serial.println(payload);
return payload;
}


/************************************************************************************
 * GetUpdates - function to receive messages from telegram as a Json and parse them *
 ************************************************************************************/
message TelegramBot::getUpdates()  {
    String command="getUpdates?offset="+last_message_recived;
    String payload=sendRequest(command);       //recieve reply from telegram.org

	message m;

    if (payload!="") {

			DynamicJsonBuffer  jsonBuffer;
			JsonObject & root = jsonBuffer.parseObject(payload);
			String update_id = root["result"][0]["update_id"];

			if(last_message_recived.equals(update_id)){
				String update_id = root["result"][1]["update_id"];

				if(update_id.equals("")){
					Serial.println("no new messages");
				}
				else{
					String _sender = root["result"][1]["message"]["from"]["username"];
					String _text = root["result"][1]["message"]["text"];
					String _chat_id = root["result"][1]["message"]["chat"]["id"];
					String _date = root["result"][1]["message"]["date"];
					m.sender = _sender;
					m.text = _text;
					m.chat_id = _chat_id;
					m.date = _date;
					last_message_recived=update_id;

				}
			}else{
				String _sender = root["result"][0]["message"]["from"]["username"];
				String _text = root["result"][0]["message"]["text"];
				String _chat_id = root["result"][0]["message"]["chat"]["id"];
				String _date = root["result"][0]["message"]["date"];
				m.sender = _sender;
				m.text = _text;
				m.chat_id = _chat_id;
				m.date = _date;
				last_message_recived=update_id;
			}

			if(!root.success()) {
			  Serial.println("parseArray() failed");
			}
		}

		return m;
	}

/***********************************************************************
 * SendMessage - function to send message to telegram                  *
 ***********************************************************************/

void TelegramBot::sendMessage(String chat_id, String my_text)  {
        String command="sendMessage?chat_id="+chat_id+"&text="+my_text+"&reply_markup=";
        String payload=sendRequest(command);
		 }
