//
// Created by Gavin on 4/16/2016.
//

#ifndef FINALPROJECT_CONTACTLIST_H
#define FINALPROJECT_CONTACTLIST_H

#include <iostream>
#include <string>

#include "Contacts.h"
#include "AVLTree.h"

namespace ContactDatabase {
    class ContactList {
    public:
        ContactList();
        ContactList(std::string fname);
        ~ContactList();

        void loadContacts(std::string fname);

        friend std::ostream &operator<<(std::ostream &os, const ContactList &cl);
        friend std::istream &operator>>(std::istream &is, ContactList &cl);

    protected:
        AVLTree *__tree;

    };
}


#endif //FINALPROJECT_CONTACTLIST_H
