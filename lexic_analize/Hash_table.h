#pragma once

#include <string>
#include "token.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>

const int INit_Size = 8;

class hash_table {
public:
    Token* table; 
    int size, elementCount;

    void rehash()
    {  
        int reSize = size * 2;

        while (true) {
            bool Prime = true;
            if (reSize <= 1) {
                Prime = false;
            }
            else if (reSize == 2) {
                Prime = true;
            }
            else if (reSize % 2 == 0) {
                Prime = false;
            }
            else {
                for (int i = 3; i <= std::sqrt(reSize); i += 2) {
                    if (reSize % i == 0) {
                        Prime = false;
                        break;
                    }
                }
            }
            if (Prime) {
                break; 
            }
            reSize++;
        }
        Token* newtable = new Token[reSize];
        int oldSize = size;
        for (int i = 0; i < reSize; i++) {
            newtable[i] = Token();
        }
        for (int i = 0; i < oldSize; i++)
        {
            if (table[i].getTokenName() != "") {
                int newHash = hashfunc(table[i].getTokenName(), reSize);
                //разрешение коллизий
                while (newtable[newHash].getTokenName() != "")
                {
                    newHash = (newHash + 1) % reSize;
                }

                newtable[newHash] = table[i];//пермещаем токен
            }
        }

        delete[] table;
        table = newtable;
        size = reSize;

    }

    hash_table() {
        size = INit_Size;
        elementCount = 0;
        table = new Token[INit_Size];
    }


    int hashfunc(string key, int size) {
        int hashValue = 0;
        int prime = 31; // простое число дл€ улучшени€ распределени€ 
        //проходим по каждому символу ключа преобразу€ символ в int и наход€ хеш ключа
        for (char c : key) {
            hashValue = (hashValue * prime + static_cast<int>(c)) % size;
        }
        return hashValue;
    }


    string get(const string& key)
    {
        int hash = hashfunc(key, size);
        int startIndex = hash;
        while (table[hash].getTokenName() != "")
        {
            if (table[hash].getTokenName() == key)
            {
                return table[hash].getTokenType();
            }
            hash = (hash + 1) % size;
            if (hash == startIndex)
            {
                break;
            }
        }
        return "";//возвращаем пустую строку если ключ не найден
    }


    void add(Token& token) {
        //проверка необходимости изменени€ размера (если колличество эллементов >= 75% от размера хэш таблицы вызываем rehash()
        if (elementCount >= size * 0.75) {
            rehash();
        }
        int hash = hashfunc(token.getTokenName(), size);

        if (elementCount < size)
        {
            Token tokenFromIndex = table[hash]; // извлекаем токен, наход€щийс€ по расчитанному хешу 
            if (tokenFromIndex.getTokenName() == token.getTokenName()) // если токен найденный по индексу имеет ту же лексему что и токен который мы добавл€ем то мы ничего не делаем и избегаем дублировани€
            {
                return;
            }
            else {
                while (tokenFromIndex.getTokenName() != "")
                {
                    if (tokenFromIndex.getTokenName() == token.getTokenName())
                    {
                        return;
                    }
                    hash = (hash + 1) % size;
                    tokenFromIndex = table[hash];
                }
                // пока встречаютс€ заполненные токены по индексу идем дальше 
                // если встретилс€ токен с уже существующей лексемой, то мы завершаем метод и ливаем не добавл€€ ничего

                table[hash].setTokenName(token.getTokenName());
                table[hash].setTokenType(token.getTokenType());
                elementCount++;
            }
        }


    }

    void printHashtable() const
    {
        std::ofstream output("output.txt");
        for (int i = 0; i < size; i++)
        {
            if (!table[i].getTokenName().empty())
            {
                output << setw(10) << table[i].getTokenType() << " | " << setw(10) << table[i].getTokenName() << " | " << setw(10) << i << endl;
            }
        }
        output.close();
    }

    ~hash_table()
    {
        delete[] table;
    }

};


