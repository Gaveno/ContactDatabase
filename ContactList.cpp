//
// Created by Gavin on 4/16/2016.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "ContactList.h"
#include "Contacts.h"
#include "ContactExeptions.h"
#include "ContactsExceptions.h"

namespace ContactDatabase {

    ContactList::ContactList() {
        __tree = new AVLTree;
        __lastFile = "NULL";
        __gotomain = false;
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
     * 2) Search Contacts
     * 3) Add Contact
     * 4) Load Contacts
     * 5) Save Contacts
     * 6) Exit
     */
    void ContactList::menuMain() {
        int input = 0;
        while (input != 6) {
            __gotomain = false;
            std::cout << "\n";
            std::cout << "-----------------------\n";
            std::cout << "------ Main Menu ------" << std::endl;
            std::cout << "-----------------------\n";
            std::cout << "1) Display Contacts" << std::endl;
            std::cout << "2) Search Contacts" << std::endl;
            std::cout << "3) Add Contact" << std::endl;
            std::cout << "4) Load Contacts" << std::endl;
            std::cout << "5) Save Contacts" << std::endl;
            std::cout << "6) Exit" << std::endl;
            //cin >> input;
            input = getNumbers(1, 6);

            switch (input) {
                case 1: menuDisplay(*__tree); break;
                case 2: menuSearch(); break;
                case 3: menuAddContact(); break;
                case 4: menuLoad(); break;
                case 5: menuSave(); break;
                //case 6: return;
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
    void ContactList::menuDisplay(AVLTree &tree) {
        int input = 0;
        bool first = true;
        std::vector<ItemType> vec;

        if (tree.size() == 0) {
            std::cout << "\nEmpty contact list!" << std::endl;
            std::cout << "Load a list from a file," << std::endl;
            std::cout << "or add at least one contact\nbefore performing this action!\n\n";
            return;
        }

        while (input != 4 && !__gotomain) {
            std::cout << "\n------ Display Menu ------" << std::endl;
            std::cout << "1) Display all contacts"  << std::endl;
            std::cout << "2) Sort and display all"  << std::endl;
            std::cout << "3) Search and display"    << std::endl;
            if (first) {
                std::cout << "4) Back" << std::endl;
                std::cout << "5) <-- Main Menu" << std::endl;
            }
            else {
                std::cout << "4) Modify Contact" << std::endl;
                std::cout << "5) Back" << std::endl;
                std::cout << "6) <-- Main Menu" << std::endl;
            }

            //cin >> input;
            input = getNumbers(1, 6);

            switch (input) {
                case 1:
                    if (!first) vec.clear();    // Clear previous results
                    displaySorted(tree, vec);         // Sort and display, loading for next menu iteration
                    break;

                case 2: {
                    // Sort and display
                    FieldSearch field;
                    FieldSearch second;

                    std::cout << "------ Sort and Display Menu ------\n";
                    std::cout << "Enter the FIRST field to sort by:\n";
                    for (int i = 0; i < Contacts::NUM_FIELDS; ++i) {
                        if (i % 3 == 0) std::cout << std::endl;

                        string o = to_string(i + 1) + ") " + Contacts::FIELD_NAMES[i];
                        std::cout << padWidth(o, 20);
                    }
                    std::cout << std::endl;

                    field = (FieldSearch) (getNumbers(1, Contacts::NUM_FIELDS) - 1);

                    std::cout << "Enter the SECOND field to sort by:\n";
                    for (int i = 0; i < Contacts::NUM_FIELDS; ++i) {
                        if (i % 3 == 0) std::cout << std::endl;

                        string o = to_string(i + 1) + ") " + Contacts::FIELD_NAMES[i];
                        std::cout << padWidth(o, 20);
                    }
                    std::cout << std::endl;

                    second = (FieldSearch) (getNumbers(1, Contacts::NUM_FIELDS) - 1);

                    // Clear then display with sort fields
                    vec.clear();
                    displaySorted(tree, vec, field, second);
                }
                break;

                case 3: menuSearch(); break;

                case 4: if (first) {
                        return;     // Exit on first iteration
                    }
                    else {  // Modify contact after first iteration
                        unsigned int row;
                        std::cout << "Enter contact row number to modify:\n";
                        //cin >> row;
                        row = getNumbers(1, vec.size());
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
                        else __gotomain = true;
                    break;

                case 6: if (!first) __gotomain = true; break;

                default: break;
            }

            first = false;
        }
    }

    /*
     * Search Contacts Menu
     * Gets a field to search through
     * and a string to search for
     * also asks for the mode of search
     * exact, or contains
     */
    void ContactList::menuSearch() {
        // Make sure list is non-empty
        if (__tree->size() == 0) {
            std::cout << "\nEmpty contact list!" << std::endl;
            std::cout << "Load a list from a file," << std::endl;
            std::cout << "or add at least one contact\nbefore performing this action!\n\n";
            return;
        }

        // Menu options
        enum Option {
            SEARCH=1, STRING, FIELD, MODE, DISPLAY, EDIT, EXIT, MAIN
        };

        // Search arguments
        FieldSearch field = FieldSearch::ALL;
        SearchMode mode = SearchMode::EXACT;
        std::string item = "NULL";

        // Tree with search results
        AVLTree stree(*__tree);
        vector<ItemType> vec;

        // Menu option selected
        unsigned int input = 0;

        while (input != Option::EXIT && !__gotomain) {
            if (__tree->size() == stree.size())
                std::cout << "\n------ Search Menu ------" << std::endl;
            else
                std::cout << "\n------ Sub-Search Menu ------" << std::endl;
            std::cout << Option::SEARCH << ") Search" << std::endl;
            std::cout << Option::STRING << ") Enter a search term" << std::endl;
            std::cout << Option::FIELD << ") Select field to search" << std::endl;
            std::cout << Option::MODE << ") Select search mode" << std::endl;
            std::cout << Option::DISPLAY << ") Display & Sort Menu" << std::endl;
            if (__tree->size() != stree.size())
                std::cout << Option::EDIT << ") Modify Contact" << std::endl;
            std::cout << Option::EXIT << ") Back" << std::endl;
            std::cout << Option::MAIN << ") <-- Main Menu" << std::endl;

            //cin >> input;
            input = getNumbers(Option::SEARCH, Option::MAIN);

            switch (input) {
                case (unsigned int)Option::SEARCH: {
                    AVLTree tmp(stree);
                    stree.clearTree();
                    try {
                        tmp.addTree(stree, item, field, mode);
                    }
                    catch (ContactDatabase::ExEmptyTree &ex) {
                        std::cerr << "Exception thrown: ";
                        ex.print(std::cerr);
                        std::cerr << std::endl;
                    }
                    if (stree.size() > 0) {
                        vec.clear();
                        displaySorted(stree, vec);
                    }
                    else {
                        std::cout << "\n\nSearch produced no results!\n\n";
                        __tree->addTree(stree);
                    }
                }
                break;

                case (unsigned int)Option::STRING: {
                    std::cout << "\nEnter a word or phrase to search for:\n";
                    //getline(cin, item, '\n');
                    item = getWords();
                }
                break;

                case (unsigned int)Option::FIELD: {
                    std::cout << "\nEnter a field to search in:\n";
                    std::cout << "------------------------------------------------------";
                    for (int i = 0; i < Contacts::NUM_FIELDS; ++i) {
                        if (i % 3 == 0) std::cout << std::endl;

                        string o = to_string(i + 1) + ") " + Contacts::FIELD_NAMES[i];
                        std::cout << padWidth(o, 20);
                    }
                    std::cout << (Contacts::NUM_FIELDS + 1) << ") ALL\n";
                    //cin >> input;
                    input = getNumbers(0, Contacts::NUM_FIELDS + 1);
                    if (input == (Contacts::NUM_FIELDS + 1)) {
                        field == FieldSearch::ALL;
                    }
                    else {
                        input--;
                        field = (FieldSearch) input;
                    }
                }
                break;

                case (unsigned int)Option::MODE: {
                    std::cout << "\nEnter a mode to search by:\n";
                    std::cout << "1) Exact\n2) Contains\n";
                    //cin >> input;
                    input = getNumbers(1, 2);
                    input--;
                    switch (input) {
                        case 0: mode = SearchMode::EXACT; break;
                        case 1: mode = SearchMode::CONTAINS; break;
                        default: break;
                    }
                }
                break;

                case (unsigned int)Option::DISPLAY: {
                    menuDisplay(stree);
                }
                break;

                case (unsigned int) Option::EDIT:
                    if (vec.empty()) break;
                {
                    unsigned int row;
                    std::cout << "Enter contact row number to modify:\n";
                    //cin >> row;
                    row = getNumbers(1, vec.size());
                    row--;
                    if (row < vec.size()) {
                        menuModifyContact(vec[row]);
                        //input = 0;
                    }
                    else
                        std::cout << "Error: Row #" << row << " does not exist!" << std::endl;
                }
                break;

                case (unsigned int) Option::MAIN:
                    __gotomain = true; break;

                default: break;
            }
        }
    }

    /*
     * Add Contact Menu
     * Walks the user through creating a new
     * contact.
     */
    void ContactList::menuAddContact() {
        ContactDatabase::Contacts nc;
        menuModifyContact(nc);

    }

    /*
     * Modify Contact Menu
     * Menu to modify contact values
     */
    void ContactList::menuModifyContact(Contacts &cont) {
        Contacts original = cont;
        unsigned int input = 0;
        while (input != (cont.NUM_FIELDS + 2)) {
            // Display menu
            std::cout << "\n------Modify Contact------" << std::endl;

            // Print current state of contact
            cont.printDetailed(std::cout);

            // Display options
            for (unsigned int i = 0; i < cont.NUM_FIELDS + 1; ++i) {
                if (i % 3 == 0) {
                    std::cout << std::endl;
                }

                std::string str = to_string(i + 1) + ") " + cont.FIELD_NAMES[i];
                std::cout << padWidth(str, 20);
            }
            std::cout << padWidth("15) Remove Contact", 20);
            std::cout  << "\n" << (16) << ") Save and Exit" << std::endl;

            // Get selection
            //cin >> input;
            input = getNumbers(1, 17);
            input--;
            //if (input == cont.NUM_FIELDS)
                //return; // Exit if selected

            // If within input range, get entry from user
            if (input < cont.NUM_FIELDS) {
                // Sub menu for new entry
                std::cout << "\n------Current Entry------" << std::endl;
                std::cout << cont.FIELD_NAMES[input] << ": ";
                if (cont.getField(input) == "NULL")
                    std::cout << "<Empty>";
                else
                    std::cout << cont.getField(input);
                std::cout << std::endl;
                std::cout << "Please enter a new entry for field: " << cont.FIELD_NAMES[input] << std::endl;
                string entry;
                //cin >> entry;
                entry = getWords();
                while (entry == "NULL") {
                    std::cout << "Cannot be 'NULL'. Please re-enter:\n";
                    entry = getWords();
                }

                if (entry.size() == 0) entry = "NULL";

                cont.setField(input, entry);
            }
            else {
                if (input == 13) {
                    // Affiliates menu
                    menuListAffiliates(cont);
                }
                else if (input == 14) {
                    // delete contact, make sure!
                    std::cout << "Are you sure you want to delete: ";
                    cont.printNames();
                    std::cout << "?\nType 'YES' exactly as shown to delete this contact\nThis cannot be undone!\n";
                    string entry;
                    //cin >> entry;
                    entry = getWords();
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

        if (cont.getFirstName() != "NULL") {
            __tree->remove(original);
            __tree->insert(cont);
        }
        else {
            std::cout << "\n\nFirst name cannot be 'NULL'\nContact not saved!\n\n";
        }
    }

    /*
         * List Contact's Affiliates Menu
         * Menu to select an affiliate
         */
    void ContactList::menuListAffiliates(Contacts &cont) {
        int input = 0;
        enum Options { ADD=1, MODIFY, DELETE, SAVE };

        while (input != SAVE) {
            std::cout << "\n------ Affiliates ------\n\n";
            for (int i = 0; i < cont.getNumAffiliates(); ++i) {
                std::cout << "#" << (i + 1) << " ";
                std::cout << cont.getAffiliate(i);
            }
            std::cout << std::endl;
            std::cout << ADD << ") Add Affiliate\n";
            std::cout << MODIFY << ") Modify Affiliate\n";
            std::cout << DELETE << ") Remove Affiliate\n";
            std::cout << SAVE << ") Save Affiliates & Exit\n";

            input = getNumbers(ADD, SAVE);

            switch (input) {
                case ADD: {
                    Contacts::Affiliates a(&cont, "NULL", "NULL");
                    menuModifyAffiliate(a);
                    if (a.getFirstName() != "NULL")
                        cont.addAffiliate(a);
                    else
                        std::cout << "\n\nAffiliate must have a first name. Not Added.\n\n";
                }
                break;

                case MODIFY: {
                    std::cout << "\nEnter the row number of the affiliate to modify:\n";
                    int sel = getNumbers(1, cont.getNumAffiliates() + 1);
                    sel--;
                    //Contacts::Affiliates b = cont.getAffiliate(sel);
                    menuModifyAffiliate(cont.getAffiliate(sel));
                    /*if (b != cont.getAffiliate(sel)) {
                        cont.removeAffiliate(b);
                        cont.addAffiliate(cont.getAffiliate(sel));
                    }*/
                }
                break;

                case DELETE: {
                    std::cout << "\nEnter the row number of the affiliate to modify:\n";
                    int sel = getNumbers(1, cont.getNumAffiliates() + 1);
                    sel--;

                    std::cout << "Are you sure you want to permenantly delete this affiliate?\n";
                    std::cout << "This action cannot be done! To continue enter 'YES' exactly as shown:\n";
                    string confirm = getWords();

                    if (confirm == "YES") {
                        cont.removeAffiliate(cont.getAffiliate(sel));
                    }
                }
                break;

                case SAVE: return;

                default: break;
            }
        }
    }

    /*
     * Modify Affiliate Menu
     * Menu to delete, or modify an affiliate of a contact
     */
    Contacts::Affiliates &ContactList::menuModifyAffiliate(Contacts::Affiliates &aff) {
        int input = 0;

        enum Options { FIRST=1, LAST, PHONE, EMAIL, SAVE };

        while (input != SAVE) {
            std::cout << "\n------ Modify Affiliate ------\n\n";

            std::cout << FIRST << ") First Name: ";
            if (aff.getFirstName() == "NULL") std::cout << "<Empty>\n";
            else std::cout << aff.getFirstName() << std::endl;

            std::cout << LAST << ") Last Name: ";
            if (aff.getLastName() == "NULL") std::cout << "<Empty>\n";
            else std::cout << aff.getLastName() << std::endl;

            std::cout << PHONE << ") Phone Number: ";
            if (aff.getMobilePhone() == "NULL") std::cout << "<Empty>\n";
            else std::cout << aff.getMobilePhone() << std::endl;

            std::cout << EMAIL << ") Email: ";
            if (aff.getEmail() == "NULL") std::cout << "<Empty>\n";
            else std::cout << aff.getEmail() << std::endl;

            std::cout << SAVE << ") Save & Exit\n";

            input = getNumbers(FIRST, SAVE);

            string current;
            switch (input) {
                case FIRST: current = aff.getFirstName(); break;
                case LAST: current = aff.getLastName(); break;
                case PHONE: current = aff.getMobilePhone(); break;
                case EMAIL: current = aff.getEmail(); break;
                default: break;
            }

            if (input != SAVE) {
                std::cout << "Current Entry: " << current << std::endl;
                std::cout << "Please enter the replacement entry:\n";
                string entry = getWords();

                switch (input) {
                    case FIRST: aff.setFirstName(entry); break;
                    case LAST: aff.setLastName(entry); break;
                    case PHONE: aff.setNumber(entry); break;
                    case EMAIL: aff.setEmail(entry); break;
                    default: break;
                }
            }
        }

        return aff;
    }

    /*
     * Load Contacts Menu
     * Prompt user for a file to load
     */
    void ContactList::menuLoad() {
        std::string fname = "NULL";
        std::cout << "------Load Menu------" << std::endl;
        std::cout << "Enter the name of a\nfile to load:" << std::endl;

        //cin >> fname;
        fname = getWords();

        // file is loaded
        loadContacts(fname);
    }

    /*
     * Save Contacts Menu
     * Prompts the user for either the same
     * or a new filename to save contacts to
     */
    void ContactList::menuSave() {
        int numOptions = 3;
        std::cout << "------Save Menu------\n";
        if (__lastFile != "NULL") {
            std::cout << "1) Save (same name)\n";
            std::cout << "2) Save as (new name)\n";
            std::cout << "3) Back\n";
        }
        else {
            numOptions = 2;
            std::cout << "1) Save\n";
            std::cout << "2) Back\n";
        }

        int input = 0;
        //cin >> input;
        input = getNumbers(1, numOptions);

        if (__lastFile == "NULL") input++;

        switch (input) {
            case 1: save( ); break;
            case 2: save(1); break;
            default: break;

        }
    }

    void ContactList::loadContacts(std::string fname) {
        std::ifstream file(fname);

        unsigned int contactsread = 0;

        if (file) {
            if (__tree->size() > 0) {
                __tree->clearTree();
            }
            try {
                while (!file.eof()) {
                    ++contactsread;
                    Contacts c;
                    file >> c;
                    __tree->insert(c);
                }
            }
            catch (ExCorruptFile &ex) {
                std::cerr << "\nError in file...\n" << std::endl; //File not loaded." << std::endl;
                std::cerr << contactsread << " contacts read before error.\n";
                ex.print(std::cerr);
                //__tree->clearTree();
            }
            catch (...) {
                std::cerr << "\nError in file...\n" << std::endl; //File not loaded." << std::endl;
                std::cerr << "An unknown error occured.\n\n";
                std::cerr << contactsread << " contacts read before error.\n";
                //__tree->clearTree();
            }
            if (__tree->size() > 0) {
                __lastFile = fname;
            }
        }
        else {
            std::cout << "Error opening file. No contacts loaded.\n\n";
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

    std::vector<ItemType> &ContactList::displaySorted
            (
            AVLTree &tree,
            std::vector<ItemType> &vec,
            FieldSearch field,
            FieldSearch second
            ) {
        tree.addVector(vec);

        SortContacts s(field);

        // Sort based on first name then
        // last name by default
        std::sort(vec.begin(), vec.end(), s);

        // Bubble sort second field
        bool swapped = true;
        while (swapped) {
            swapped = false;
            for (unsigned int i = 1; i < vec.size(); ++i) {
                if (vec[i].getField(field) == vec[i - 1].getField(field)
                        && vec[i].getField(second) < vec[i - 1].getField(second)) {
                    std::iter_swap(vec.begin() + i, vec.begin() + i - 1);
                    swapped = true;
                }
            }
        }

        std::cout << "------ Contact List ------" << std::endl;

        int i = 1;
        for (auto &e : vec) {
            std::cout << "#" << i << " - ";
            e.printNames(field, second);
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
            //cin >> entry;
            entry = getWords();
            entry += ".txt";
            __lastFile = entry;
        }

        std::ofstream file(__lastFile);

        if (file) {
            file << *this;
            std::cout << "\n\n-- Contacts Saved! --\n\n";
        }
        else {
            std::cout << "Error: There was a problem saving to this location.\n";
        }
    }

    string ContactList::getWords() {
        string word;
        getline(cin, word, '\n');
        while (word.size() < 1) {
            getline(cin, word, '\n');
        }

        return word;
    }

    unsigned int ContactList::getNumbers(int from, int to) {
        string word;
        int num = 999999;
        //getline(cin, word, '\n');
        while (word.size() < 1 || num < from || num > to) {
            getline(cin, word, '\n');
            try {
                num = stoi(word);
            }
            catch(...) {
                num = -1;
            }
            if (num < from || num > to) {
                std::cout << "Please enter a number between " << from << " and " << to << ":\n";
            }
        }

        return (unsigned ) num;
    }
}