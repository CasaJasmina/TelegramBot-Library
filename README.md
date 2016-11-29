# TelegramBot Library


A project by [Casa Jasmina](http://casajasmina.arduino.cc/)

## Introductionss

This library allows you to host a Telegram Bot on your Arduino, and interact with telegram bot API.

It works on [Arduino/Genuino MKR1000] (http://www.arduino.cc/en/Main/ArduinoMKR1000), and on [Arduino Zero](https://www.arduino.cc/en/Main/ArduinoBoardZero) with the [WiFi shield 101](https://www.arduino.cc/en/Main/ArduinoWiFiShield101).

## Installing

The downloaded code can be included as a new library into the IDE selecting the menu:

     Sketch / include Library / Add .Zip library

You also have to install the ArduinoJson library written by [Benoît Blanchon](https://github.com/bblanchon).
Available [here](https://github.com/bblanchon/ArduinoJson).


## Getting started

View the last released Telegram API documentation at: https://core.telegram.org/bots/api.

To generate your new Bot, you need an Access Token. Talk to [BotFather](https://telegram.me/botfather) and follow a few simple steps described [here](https://core.telegram.org/bots#botfather).

For full details, see "[Bots: An introduction for developers](https://core.telegram.org/bots)".

## Api Reference
```c++
TelegramBot(const char* token, const char* name, const char* username, Client &client);
```
```c++
String sendMessage(String chat_id, String my_text);
```
```c++
String sendMessage(String chat_id, String my_text, Keyboard keyboard, bool one_time_keyboard = true, bool resize_keyboard = true);
```
```c++
String postMessage(String msg);
```
```c++
message getUpdates();
```

```c++
struct message{
  const char* text;
  const char* chat_id;
  const char* sender;
  const char* date;
};
```

## License

You may copy, distribute and modify the software provided that modifications are described and licensed for free under [LGPL-3](http://www.gnu.org/licenses/lgpl-3.0.html). Derivatives works (including modifications or anything statically linked to the library) can only be redistributed under [LGPL-3](http://www.gnu.org/licenses/lgpl-3.0.html), but applications that use the library don't have to be.
