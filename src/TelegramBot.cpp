
// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library

#include "TelegramBot.h"

TelegramBot::TelegramBot(const char* token, const char* name, const char* username, Client &client)	{
	this->client = &client;
	this->token=token;
	this->name=name;
	this->username=username;
}

void TelegramBot::begin()	{
	while(!client->connected()){
		Serial.println("trying to connect...");
		client->connect(HOST, SSL_PORT);
		delay (1000);
	}
}

/************************************************************************************
 * GetUpdates - function to receive messages from telegram as a Json and parse them *
 ************************************************************************************/
message TelegramBot::getUpdates()  {
		while(!client->connected()){
			begin();
		}

		//Send your request to api.telegram.org
		String getRequest = "GET /bot"+String(token)+"/getUpdates?offset="+last_message_recived+" HTTP/1.1";
		client->println(getRequest);
		client->println("User-Agent: curl/7.37.1");
		client->println("Host: api.telegram.org");
		client->println("Accept: */*");
		client->println();

		String payload = readPayload();

		message m;
	    if (payload!="") {
			StaticJsonBuffer<JSON_BUFF_SIZE> jsonBuffer;
			JsonObject & root = jsonBuffer.parseObject(payload);
			String update_id = root["result"][0]["update_id"];

			if(last_message_recived.equals(update_id)){
				String update_id = root["result"][1]["update_id"];

				if(update_id.equals("")){
					Serial.println("no new messages");
				}else{
					String sender = root["result"][1]["message"]["from"]["username"];
					String text = root["result"][1]["message"]["text"];
					String chat_id = root["result"][1]["message"]["chat"]["id"];
					String date = root["result"][1]["message"]["date"];
					m.sender = sender;
					m.text = text;
					m.chat_id = chat_id;
					m.date = date;
					last_message_recived=update_id;
				}
			}else{
				String sender = root["result"][0]["message"]["from"]["username"];
				String text = root["result"][0]["message"]["text"];
				String chat_id = root["result"][0]["message"]["chat"]["id"];
				String date = root["result"][0]["message"]["date"];
				m.sender = sender;
				m.text = text;
				m.chat_id = chat_id;
				m.date = date;
				last_message_recived=update_id;
			}

			if(!root.success()) {
			  Serial.println("error to parse payload from telegram.org");
			}
		}
		return m;
	}

// send message function
// send a simple text message to a telegram char
String TelegramBot::sendMessage(String chat_id, String text)  {
		while(!client->connected()){
			begin();
		}

		StaticJsonBuffer<JSON_BUFF_SIZE> jsonBuffer;
		JsonObject& buff = jsonBuffer.createObject();
		buff["chat_id"] = chat_id;
		buff["text"] = text;

		String msg;
		buff.printTo(msg);
		return postMessage(msg);
	}

// send a message to a telegram chat with a reply markup
String TelegramBot::sendMessage(String chat_id, String my_text, String markup[], int nrows, int ncolumns, bool one_time_keyboard)  {
		StaticJsonBuffer<JSON_BUFF_SIZE> jsonBuffer;
		JsonObject& mkp = jsonBuffer.createObject();
		mkp["chat_id"] = chat_id;
		mkp["text"] = my_text;

		JsonObject& reply_markup = mkp.createNestedObject("reply_markup");
		JsonArray& keyboard = reply_markup.createNestedArray("keyboard");

		for (int a = 0 ; a < nrows ; a++){
			JsonArray& row = keyboard.createNestedArray();
				for( int b = 0 ; b < ncolumns ; b++){
					row.add(markup[b+(ncolumns*a)]);
				}
		}

		reply_markup.set<bool>("one_time_keyboard", one_time_keyboard);
		reply_markup.set<bool>("resize_keyboard", true);

		String msg;
		mkp.printTo(msg);
		return postMessage(msg);
}

// gets the telegram json string
// posts the message to telegram
// returns the payload
String TelegramBot::postMessage(String msg) {
		 while(!client->connected()){
			 begin();
		 }

		client->println("POST /bot"+String(token)+"/sendMessage"+" HTTP/1.1");
		client->println("Host: api.telegram.org");
	    client->println("Content-Type: application/json");
	    client->println("Connection: close");
	    client->print("Content-Length: ");
	    client->println(msg.length());
	    client->println();
	    client->println(msg);

		return readPayload();
}

// reads the payload coming from telegram server
// returns the payload string
String TelegramBot::readPayload(){
	char c;
	String payload="";
		//Read the answer and save it in String payload
		while (client->connected()) {
		payload = client->readStringUntil('\n');
		if (payload == "\r") {
			break;
		 }
	  }
	payload = client->readStringUntil('\r');
	return payload;
}
