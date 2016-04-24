//
// Created by Gavin on 4/16/2016.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "ContactList.h"
#include "Contacts.h"

namespace ContactDatabase {

    ContactList::ContactList() {
        __tree = new AVLTree;
        __lastFile = "NULL";
    }

    ContactList::ContactList(std::string fname) : ContactList() {
        __lastFile = "NULL";
        loadContacts(fname);
    }

    ContactList::~ContactList() {
        delete __tree;
    }

    /*
     * Main menu
     * 1) Display Contacts
     * 2) Add Contact
     * 3) Load Contacts
     * 4) Save Contacts
     * 5) Exit
     */
    void ContactList::menuMain() {
        int input = 0;
        while (input != 5) {
            std::cout << "\n------Main Menu------" << std::endl;
            std::cout << "1) Display Contacts" << std::endl;
            std::cout << "2) Add Contact" << std::endl;
            std::cout << "3) Load Contacts" << std::endl;
            std::cout << "4) Save Contacts" << std::endl;
            std::cout << "5) Exit" << std::endl;
            cin >> input;

            switch (input) {
                case 1: menuDisplay(); break;
                case 2: menuAddContact(); break;
                case 3: menuLoad(); break;
                case 4: menuSave(); break;
                case 5: return;
                default: break;
            }
        }
    }

    /*
     * Display Contacts Menu
     * Gets the key for sorting contacts by
     * then displays them in the console in
     * the format:
     * Row# - Firstname Lastname, Companyname
     */
    void ContactList::menuDisplay() {
        int input = 0;
        bool first = true;
        std::vector<ItemType> vec;

        if (__tree->size() == 0) {
            std::cout << "\nEmpty contact list!" << std::endl;
            std::cout << "Load a list from a file," << std::endl;
            std::cout << "or add at least one contact\nbefore performing this action!\n\n";
            return;
        }

        while (input != 4) {
            std::cout << "\n------Display Menu------" << std::endl;
            std::cout << "1) Display all contacts"  << std::endl;
            std::cout << "2) Sort and display all"  << std::endl;
            std::cout << "3) Search and display"    << std::endl;
            if (first) {
                std::cout << "4) <- Main Menu" << std::endl;
            }
            else {
                std::cout << "4) Modify Contact" << std::endl;
                std::cout << "5) <- Main Menu" << std::endl;
            }

            cin >> input;

            switch (input) {
                case 1:
                    if (!first) vec.clear();    // Clear previous results
                    displaySorted(vec);         // Sort and display, loading for next menu iteration
                    break;

                case 4: if (first) {
                        return;     // Exit on first iteration
                    }
                    else {  // Modify contact after first iteration
                        unsigned int row;
                        std::cout << "Enter contact row number to modify:\n";
                        cin >> row;
                        row--;
                        if (row < vec.size()) {
                            menuModifyContact(vec[row]);
                            input = 0;
                        }
                        else
                            std::cout << "Error: Row #" << row << " does not exist!" << std::endl;
                    }
                    break;

                case 5: if (!first) return; // Exit after first menu iteration
                    break;

                default: break;
            }

            first = false;
        }
    }

    /*
     * Add Contact Menu
     * Walks the user through creating a new
     * contact.
     */
    void ContactList::menuAddContact() {

    }

    /*
     * Modify Contact Menu
     * Menu to modify contact values
     */
    void ContactList::menuModifyContact(Contacts &cont) {
        Contacts original = cont;
        unsigned int input = 0;
        while (input != cont.NUM_FIELDS) {
            // Display menu
            std::cout << "\n------Modify Contact------" << std::endl;

            // Print current state of contact
            cont.printDetailed(std::cout);

            // Display options
            for (unsigned int i = 0; i < cont.NUM_FIELDS; ++i) {
                if (i % 3 == 0) {
                    std::cout << std::endl;
                }

                std::string str = to_string(i + 1) + ") " + cont.FIELD_NAMES[i];
                std::cout << padWidth(str, 20);
            }
            std::cout << padWidth("14) Remove Contact", 20);
            std::cout  << "\n" << (15) << ") <- Main Menu" << std::endl;

            // Get selection
            cin >> input;
            input--;
            //if (input == cont.NUM_FIELDS)
                //return; // Exit if selected

            // If within input range, get entry from user
            if (input < cont.NUM_FIELDS) {
                // Sub menu for new entry
                std::cout << "\n------Current Entry------" << std::endl;
                std::cout << cont.FIELD_NAMES[input] << ": " << cont.getField(input) << std::endl;
                std::cout << "Please enter a new entry for field: " << cont.FIELD_NAMES[input] << std::endl;
                string entry;
                cin >> entry;

                if (entry.size() == 0) entry = "NULL";

                cont.setField(input, entry);
            }
            else {
                if (input == 13) {
                    // delete contact, make sure!
                    std::cout << "Are you sure you want to delete: ";
                    cont.printNames();
                    std::cout << "?\nType 'YES' exactly as shown to delete this contact\nThis cannot be undone!\n";
                    string entry;
                    cin >> entry;
                    if (entry == "YES") {
                        __tree->remove(cont);
                        std::cout << "! Contact Deleted !" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "! Contact NOT Deleted !" << std::endl;
                    }
                }
            }
        }

        __tree->remove(original);
        __tree->insert(cont);
    }

    /*
     * Load Contacts Menu
     * Prompt user for a file to load
     */
    void ContactList::menuLoad() {
        std::string fname = "NULL";
        bool loaded = false;
        while (!loaded) {
            std::cout << "------Load Menu------" << std::endl;
            std::cout << "Enter the name of a\nfile to load:" << std::endl;

            cin >> fname;

            std::ifstream file(fname);
            if (file) {
                // file is loaded
                file >> *this;
                loaded = true;
            }
            else {
                std::cout << "Error: Failed to open file '" << fname << "'" << std::endl;
                return;
            }
        }
    }

    /*
     * Save Contacts Menu
     * Prompts the user for either the same
     * or a new filename to save contacts to
     */
    void ContactList::menuSave() {
        std::cout << "------Save Menu------\n";
        if (__lastFile != "NULL") {
            std::cout << "1) Save (same name)\n";
            std::cout << "2) Save as (new name)\n";
            std::cout << "3) <- Main Menu\n";
        }
        else {
            std::cout << "1) Save as (new name)\n";
            std::cout << "2) <- Main Menu\n";
        }

        int input = 0;
        cin >> input;

        if (__lastFile == "NULL") input++;

        switch (input) {
            case 1: save( ); break;
            case 2: save(1); break;
            default: return;

        }
    }

    void ContactList::loadContacts(std::string fname) {
        std::ifstream file(fname);

        if (file) {
            if (__tree->size() > 0) {
                __tree->clearTree();
            }
            while (!file.eof()) {
                Contacts c;
                file >> c;
                __tree->insert(c);
            }
            if (__tree->size() > 0) {
                __lastFile = fname;
            }
        }
    }

    std::ostream &operator<<(std::ostream &os, const ContactList &cl) {
        std::vector<ItemType> vec;

        cl.__tree->addVector(vec);
        std::sort(vec.begin(), vec.end());

        //os << "Vector Size: " << vec.size() << std::endl;

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

    std::vector<ItemType> &ContactList::displaySorted(std::vector<ItemType> &vec, unsigned int field) {
        __tree->addVector(vec);

        SortContacts s(field);

        // Sort based on first name by default
        std::sort(vec.begin(), vec.end(), s);

        int i = 1;
        for (auto &e : vec) {
            std::cout << "#" << i << " - ";
            e.printNames();
            std::cout << std::endl;
            ++i;
        }

        return vec;
    }

    std::string ContactList::padWidth(string str, unsigned int w) {
        std::string temp;
        temp = str;
        for (int i = str.size(); i < w; ++i) {
            temp += " ";
        }

        return temp;
    }

    void ContactList::save(int type) {
        if (type == 1 || __lastFile == "NULL") {
            std::string entry;
            std::cout << "Enter a filename to save the contact list as: (.txt will be appended to the end)\n";
            cin >> entry;
            entry += ".txt";
            __lastFile = entry;
        }

        std::ofstream file(__lastFile);

        if (file) {
            file << *this;
        }
        else {
            std::cout << "Error: There was a problem saving to this location.\n";
        }
    }

}