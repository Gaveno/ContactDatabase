//
// Created by Gavin on 4/16/2016.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "ContactList.h"
#include "Contacts.h"

namespace ContactDatabase {

    ContactList::ContactList() {
        __tree = new AVLTree;
    }

    ContactList::ContactList(std::string fname) : ContactList() {
        loadContacts(fname);
    }

    ContactList::~ContactList() {
        delete __tree;
    }

    void ContactList::loadContacts(std::string fname) {
        std::ifstream file(fname);

        if (file) {
            while (!file.eof()) {
                Contacts c;
                file >> c;
                __tree->insert(c);
            }
        }
    }

    std::ostream &operator<<(std::ostream &os, const ContactList &cl) {
        std::vector<ItemType> vec;

        cl.__tree->addVector(vec);

        os << "Vector Size: " << vec.size() << std::endl;

        for (auto &e : vec) {
            os << e << "|" << std::endl;
        }

        return os;
    }

    std::istream &operator>>(std::istream &is, ContactList &cl) {
        //int i = 0;
        while (!is.eof()) {
            Contacts c;
            is >> c;
            if (c.getFirstName() != "NULL")
                cl.__tree->insert(c);
            //std::cout << "Tree size: " << cl.__tree->size() << std::endl;
            //std::cout << "Loop Count: " << i << std::endl;
            //++i;
        }

        return is;
    }

}