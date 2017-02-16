// Official
// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library

#include "TelegramBot.h"

TelegramBot::TelegramBot(const char* token, Client &client)	{
	this->client = &client;
	this->token=token;
}


void TelegramBot::begin()	{
	if(!client->connected()){
		client->connect(HOST, SSL_PORT);
	}
}

/************************************************************************************
 * GetUpdates - function to receive messages from telegram as a Json and parse them *
 ************************************************************************************/
message TelegramBot::getUpdates()  {
		begin();

		//Send your request to api.telegram.org
		String getRequest = "GET /bot"+String(token)+"/getUpdates?limit=1&offset="+String(last_message_recived)+" HTTP/1.1";
		client->println(getRequest);
		client->println("User-Agent: curl/7.37.1");
		client->println("Host: api.telegram.org");
		client->println("Accept: */*");
		client->println();

		String payload = readPayload();
	    if (payload != "") {
			message m;
			StaticJsonBuffer<JSON_BUFF_SIZE> jsonBuffer;
			JsonObject & root = jsonBuffer.parseObject(payload);



			if(root.success()){

				int update_id = root["result"][0]["update_id"];
				update_id = update_id+1;

				if(last_message_recived != update_id ){
					String sender = root["result"][0]["message"]["from"]["username"];
					String text = root["result"][0]["message"]["text"];
					String chat_id = root["result"][0]["message"]["chat"]["id"];
					String date = root["result"][0]["message"]["date"];

					m.sender = sender;
					m.text = text;
					m.chat_id = chat_id;
					m.date = date;
					last_message_recived=update_id;
					return m;
				}else{
					m.chat_id = "";
					return m;
				}
			}
			else{
				Serial.println("");
				Serial.println("Message too long, skipped.");
				Serial.println("");
				int update_id_first_digit=0;
				int update_id_last_digit=0;
				for(int a =0; a<3; a++){
					update_id_first_digit= payload.indexOf(':',update_id_first_digit+1);
				}
				for(int a =0; a<2; a++){
					update_id_last_digit= payload.indexOf(',',update_id_last_digit+1);
				}
			last_message_recived = payload.substring(update_id_first_digit+1,update_id_last_digit).toInt() +1;
			}
		}
	}

// send message function
// send a simple text message to a telegram char
String TelegramBot::sendMessage(String chat_id, String text)  {
	if(chat_id!="0" && chat_id!=""){
		StaticJsonBuffer<JSON_BUFF_SIZE> jsonBuffer;
		JsonObject& buff = jsonBuffer.createObject();
		buff["chat_id"] = chat_id;
		buff["text"] = text;

		String msg;
		buff.printTo(msg);
		return postMessage(msg);
	} else {
		Serial.println("Chat_id not defined");
	}
}

// send a message to a telegram chat with a reply markup
String TelegramBot::sendMessage(String chat_id, String text, TelegramKeyboard &keyboard_markup, bool one_time_keyboard, bool resize_keyboard)  {
		StaticJsonBuffer<JSON_BUFF_SIZE> jsonBuffer;
		JsonObject& buff = jsonBuffer.createObject();
		buff["chat_id"] = chat_id;
		buff["text"] = text;

		JsonObject& reply_markup = buff.createNestedObject("reply_markup");
		JsonArray& keyboard = reply_markup.createNestedArray("keyboard");

		for (int a = 1 ; a <= keyboard_markup.length() ; a++){
			JsonArray& row = keyboard.createNestedArray();
				for( int b = 1; b <= keyboard_markup.rowSize(a) ; b++){
					row.add(keyboard_markup.getButton(a,b));
				}
		}

		reply_markup.set<bool>("one_time_keyboard", one_time_keyboard);
		reply_markup.set<bool>("resize_keyboard", resize_keyboard);
		reply_markup.set<bool>("selective", false);

		String msg;
		buff.printTo(msg);
		// Serial.println(msg);
		return postMessage(msg);
}

// gets the telegram json string
// posts the message to telegram
// returns the payload
String TelegramBot::postMessage(String msg) {
		begin();

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
	// Serial.println(payload);
	return payload;
}
