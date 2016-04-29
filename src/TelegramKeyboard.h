// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library


#ifndef TelegramKeyboard_h
#define TelegramKeyboard_h
#include <Arduino.h>

#define ROWS_LIMIT 10

struct button {
    const char* text;
    button* next;
};

class TelegramKeyboard

{
    public:
        TelegramKeyboard();
        void addRow(const char* row[], int length);
        String getButton(int nrow, int button);
        int length();
        int rowSize(int nrow);

    private:
        int nrows = 0;

        button* rows[ROWS_LIMIT];
        int rows_length[ROWS_LIMIT];

};
#endif
