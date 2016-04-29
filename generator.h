//
// Created by Gavin on 4/23/2016.
//

#ifndef FINALPROJECT_GENERATOR_H
#define FINALPROJECT_GENERATOR_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "Contacts.h"

using namespace std;
using namespace ContactDatabase;

const int NAME_FIRST_NUM = 23;
const string NAME_FIRST[] = {
        "Ad", "Ar", "All",
        "B", "C", "D", "Ed",
        "Ell", "F", "G", "J",
        "Gr", "Br", "H", "L",
        "P", "Z", "R", "M", "N",
        "Qu", "Kl", "K"
};
const int NAME_MID_NUM = 10;
const string NAME_MID[] = {
        "a", "e", "i", "o", "u", "y", "ae", "ou", "eou", "or"
};
const int NAME_LAST_NUM = 12;
const string NAME_LAST[] = {
        "m", "r", "lle", "b", "c", "tt", "ttel",
        "rk", "k", "ck", "rd", "tney"
};
const int CITY_TYPE_NUM = 4;
const string CITY_TYPE[] = {
        "Town", "City", "Village", "District"
};

string generateName() {
    string name;
    name += NAME_FIRST[rand() % NAME_FIRST_NUM];
    name += NAME_MID[rand() % NAME_MID_NUM];
    name += NAME_LAST[rand() % NAME_LAST_NUM];

    return name;
}

string generateNumber() {
    string number;
    number += "(";
    number += to_string(rand() % 10);
    number += to_string(rand() % 10);
    number += to_string(rand() % 10);
    number += ") ";
    number += to_string(rand() % 10);
    number += to_string(rand() % 10);
    number += to_string(rand() % 10);
    number += "-";
    number += to_string(rand() % 10);
    number += to_string(rand() % 10);
    number += to_string(rand() % 10);
    number += to_string(rand() % 10);
    return number;
}

ostream &generateContacts(int num, ostream &os) {
    for (int i = 0; i < num; ++i) {
        Contacts c;

        c.setFirstName(generateName());
        c.setMiddleName(generateName());
        c.setLastName(generateName());
        c.setCompanyName(generateName() + " Inc.");
        c.setHomePhone(generateNumber());
        c.setOfficePhone(generateNumber());
        string email;
        email += "genericemail";
        email += to_string(i);
        //email += "@email.com";
        c.setEmail(email);
        string address;
        address += to_string(i * 12);
        address += " W This Pl";
        c.setStreetAddress(address);
        c.setMobilePhone(generateNumber());
        c.setCity(generateName() + " " + CITY_TYPE[rand() % CITY_TYPE_NUM]);
        c.setState("Colorado");
        c.setZipCode(to_string((rand() % 90000) + 10000));
        c.setCountry("United States");

        for (int i = 0; i < (rand() % 10); ++i) {
            if ((rand() % 10) < 5) {
                Contacts::Affiliates a(&c, generateName(), generateName(), generateNumber(), "affilemail@mail.com");
                c.addAffiliate(a);
            }
            else {
                Contacts::Affiliates b(&c, generateName(), generateName());
                c.addAffiliate(b);
            }
        }

        os << c;
        os << "|" << endl;
    }

    return os;
}

#endif //FINALPROJECT_GENERATOR_H
