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

        /*
         * Main menu
         * 1) Display Contacts
         * 2) Add Contact
         * 3) Exit
         */
        void menuMain();

        /*
         * Display Contacts Menu
         * Gets the key for sorting contacts by
         * then displays them in the console in
         * the format:
         * Row# - Firstname Lastname, Companyname
         */
        void menuDisplay();

        /*
         * Add Contact Menu
         * Walks the user through creating a new
         * contact.
         */
        void menuAddContact();

        /*
         * Modify Contact Menu
         * Menu to modify contact values
         */
        void menuModifyContact(Contacts &cont);

        /*
         * Load Contacts Menu
         * Prompt user for a file to load
         */
        void menuLoad();

        /*
         * Save Contacts Menu
         * Prompts the user for either the same
         * or a new filename to save contacts to
         */
        void menuSave();

        /*
         * Adds all contacts from a file into the tree
         */
        void loadContacts(std::string fname);

        /*
         * Output contact list to stream in database format
         */
        friend std::ostream &operator<<(std::ostream &os, const ContactList &cl);
        /*
         * Adds all contacts from a stream into the tree
         */
        friend std::istream &operator>>(std::istream &is, ContactList &cl);

    protected:
        AVLTree *__tree;
        std::string __lastFile;

        std::vector<ItemType> &displaySorted(std::vector<ItemType> &vec, unsigned int field = 0);
        std::string padWidth(string str, unsigned int w);

        // Save type 0 is __lastFile for filename 1 is for new name
        void save(int type = 0);
    };
}


#endif //FINALPROJECT_CONTACTLIST_H
