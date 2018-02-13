// Copyright Casa Jasmina 2016
// LGPL License
//
// TelegramBot library
// https://github.com/CasaJasmina/TelegramBot-Library

#include "TelegramKeyboard.h"

TelegramKeyboard::TelegramKeyboard(){
}

void TelegramKeyboard::addRow(const char* row[], int length){
    button* first = new button();
    first->next = NULL;

    rows_length[nrows] = length;

    for (int i = length-1 ; i >= 0; i--) {
        button* temp;
        temp = new button;
        temp->text = row[i];
        temp->next = first;
        first = temp;
    }

    rows[nrows] = first;
    nrows++;
}

String TelegramKeyboard::getButton(int nrow, int nbutton){
    if (nrow < 1 || nbutton < 1) {
        return "error";
    }

    button* first;
    first  = rows[nrow-1];

    for (int i = 0; i < nbutton-1 ; i++){
        first = first->next;
    }

    if (first == NULL) {
        return "overflow";
    }

    return first->text;
}

int TelegramKeyboard::length(){
    return nrows;
}

int TelegramKeyboard::rowSize(int nrow){
    return rows_length[nrow - 1];
}
