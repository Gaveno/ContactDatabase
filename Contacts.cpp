//
// Created by Gavin on 4/16/2016.
//

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Contacts.h"
#include "ContactsExceptions.h"

using std::string;
using std::endl;

namespace ContactDatabase {

    unsigned int Contacts::__idGen = 0;
    const string Contacts::FIELD_NAMES[] = {
            "First Name", "Middle Name", "Last Name",
            "Company Name", "Home Phone", "Office Phone",
            "Email", "Mobile Number", "Street Address",
            "City", "State", "Zip Code", "Country",
            "Affiliates"
    };

    Contacts::Contacts() {
        __id = ++__idGen;
        __firstName = "NULL";
        __middleName = "NULL";
        __lastName = "NULL";
        __companyName = "NULL";
        __homePhone = "NULL";
        __officePhone = "NULL";
        __email = "NULL";
        __mobileNumber = "NULL";
        __streetAddress = "NULL";
        __city = "NULL";
        __state = "NULL";
        __zipCode = "NULL";
        __country = "NULL";
    }

    Contacts::Contacts(string firstname) : Contacts() {
        __firstName = firstname;
    }

    Contacts::Contacts(string firstname, string middlename, string lastname) : Contacts() {
        __firstName = firstname;
        __middleName = middlename;
        __lastName = lastname;
    }

    //  Setters
    void Contacts::setField(unsigned int index, string entry) {
        if (index >= NUM_FIELDS) throw ExOutOfBounds("Contacts", index, NUM_FIELDS);

        switch (index) {
            case 0: __firstName = entry; break;
            case 1: __middleName = entry; break;
            case 2: __lastName = entry; break;
            case 3: __companyName = entry; break;
            case 4: __homePhone = entry; break;
            case 5: __officePhone = entry; break;
            case 6: __email = entry; break;
            case 7: __mobileNumber = entry; break;
            case 8: __streetAddress = entry; break;
            case 9: __city = entry; break;
            case 10: __state = entry; break;
            case 11: __zipCode = entry; break;
            case 12: __country = entry; break;
            default: break;
        }
    }

    void Contacts::setHomePhone(string number) {
        __homePhone = convertNumber(number);
    }

    void Contacts::setOfficePhone(string number) {
        __officePhone = convertNumber(number);
    }

    void Contacts::setMobilePhone(string number) {
        __mobileNumber = convertNumber(number);
    }

    void Contacts::setEmail(string email) {
        __email = convertEmail(email);
    }

    void Contacts::addAffiliate(const Contacts::Affiliates &aff) {
        __affiliates.push_back(aff);
    }

    //  Getters - Const
    std::ostream &Contacts::printDetailed(std::ostream &os) const {
        // Print out contact information
        for (unsigned int i = 0; i < NUM_FIELDS; ++i) {
            os << FIELD_NAMES[i] << ": " << getField(i) << "\n";
        }

        // Print out affiliate information is exists
        for (auto it = __affiliates.begin(); it != __affiliates.end(); ++it) {
            os << *it;
        }

        return os;
    }

    const Contacts::Affiliates &Contacts::getAffiliate(unsigned int index) const {
        if (index >= __affiliates.size()) throw ExOutOfBounds("Affiliates", index, __affiliates.size());

        return __affiliates[index];
    }

    const string &Contacts::getField(unsigned int index) const {
        if (index > 13) throw ExOutOfBounds("Contacts", index, 13);

        switch (index) {
            case 0: return __firstName;
            case 1: return __middleName;
            case 2: return __lastName;
            case 3: return __companyName;
            case 4: return __homePhone;
            case 5: return __officePhone;
            case 6: return __email;
            case 7: return __mobileNumber;
            case 8: return __streetAddress;
            case 9: return __city;
            case 10: return __state;
            case 11: return __zipCode;
            case 12: return __country;
            default: return __country;
        }
    }

    const string &Contacts::operator[](unsigned int index) const {
        if (index > 13) throw ExOutOfBounds("Contacts", index, 13);

        switch (index) {
            case 0: return __firstName;
            case 1: return __middleName;
            case 2: return __lastName;
            case 3: return __companyName;
            case 4: return __homePhone;
            case 5: return __officePhone;
            case 6: return __email;
            case 7: return __mobileNumber;
            case 8: return __streetAddress;
            case 9: return __city;
            case 10: return __state;
            case 11: return __zipCode;
            case 12: return __country;
            default: return __country;
        }
    }

    void Contacts::printNames() const {
        std::cout << getFirstName() << " " << getLastName() << ", " << getCompanyName();
    }

    //  Getters - Non-Const
    Contacts::Affiliates &Contacts::getAffiliate(unsigned int index) {
        if (index >= __affiliates.size()) throw ExOutOfBounds("Affiliates", index, __affiliates.size());

        return __affiliates[index];
    }

    string &Contacts::getField(unsigned int index) {
        if (index > 13) throw ExOutOfBounds("Contacts", index, 13);

        switch (index) {
            case 0: return __firstName;
            case 1: return __middleName;
            case 2: return __lastName;
            case 3: return __companyName;
            case 4: return __homePhone;
            case 5: return __officePhone;
            case 6: return __email;
            case 7: return __mobileNumber;
            case 8: return __streetAddress;
            case 9: return __city;
            case 10: return __state;
            case 11: return __zipCode;
            case 12: return __country;
            default: return __country;
        }
    }
    string &Contacts::operator[](unsigned int index) {
        if (index > 13) throw ExOutOfBounds("Contacts", index, 13);

        switch (index) {
            case 0: return __firstName;
            case 1: return __middleName;
            case 2: return __lastName;
            case 3: return __companyName;
            case 4: return __homePhone;
            case 5: return __officePhone;
            case 6: return __email;
            case 7: return __mobileNumber;
            case 8: return __streetAddress;
            case 9: return __city;
            case 10: return __state;
            case 11: return __zipCode;
            case 12: return __country;
            default: return __country;
        }
    }

    // Friend functions
    std::ostream& operator<<(std::ostream &os, const Contacts::Affiliates &aff) {
        os << aff.getFirstName() << " " << aff.getLastName();
        if (aff.getMobilePhone() != "NULL")
            os << ", " << aff.getMobilePhone();
        if (aff.getEmail() != "NULL")
            os << ", " << aff.getEmail();
        os << ";" << endl;

        return os;
    }

    std::ostream &operator<<(std::ostream &os, const Contacts &contact) {
        for (unsigned int i = 0; i < (9 - std::to_string(contact.getID()).size()); ++i)
            os << "0";
        os << contact.getID() << endl;
        os << contact.getFirstName() << endl;
        os << contact.getMiddleName() << endl;
        os << contact.getLastName() << endl;
        os << contact.getCompanyName() << endl;
        os << contact.getHomePhone() << endl;
        os << contact.getOfficePhone() << endl;
        os << contact.getEmail() << endl;
        os << contact.getMobilePhone() << endl;
        os << contact.getStreetAddress() << endl;
        os << contact.getCity() << endl;
        os << contact.getState() << endl;
        os << contact.getZipCode() << endl;
        os << contact.getCountry() << endl;
        for (auto it = contact.__affiliates.begin(); it != contact.__affiliates.end(); ++it) {
            os << *it;
        }
        return os;
    }

    std::istream &operator>>(std::istream &is, Contacts &contact) {
        contact.loadFromStream(is);

        return is;
    }

    //  Private functions
    string &Contacts::convertNumber(string &number) {
        // converts phone number into
        // (123) 123-3210
        // 12345678901234
        // format
        string newNumber = "(";
        for (unsigned int i = 0; i < number.size(); ++i) {
            if (number[i] >= '0' && number[i] <= '9') {
                newNumber += number[i];
            }
            if (newNumber.size() == 4) {
                newNumber += ") ";
            }
            if (newNumber.size() == 9) {
                newNumber += "-";
            }
        }

        number = newNumber;
        return number;
    }

    string &Contacts::convertEmail(string &email) {
        // Appends @email.com
        // to the end if it's not present already
        string newemail;
        bool contains = false;
        for (int i = 0; i < email.size(); ++i) {
            if (email[i] == '@') contains = true; break;
        }
        if (!contains) {
            newemail = email + "@email.com";
        }

        email = newemail;
        return email;
    }

    std::istream &Contacts::loadFromStream(std::istream &is) {
        string line;
        getline(is, line);

        //if (is.eof()) std::cout << "Warning... Empty contact file." << std::endl;
        //if (line.size() != 9) std::cout << "Warning... Corrupt contact file." << std::endl;

        while (!is.eof() && line[0] != '|' && line.size() == 9 && line[0] != ' ') {
            setID((unsigned) std::stoi(line));
            for (unsigned int i = 0; i < Contacts::NUM_FIELDS; ++i) {
                getline(is, line);
                getField(i) = line;
            }

            //Affiliates
            getline(is, line);
            while (line[0] != '|' && !is.eof()) {
                if (getNumChars(line, ',')) {
                    // Has email and phone number
                    string  a_fn, a_ln, a_pn, a_em;

                    a_fn = getWordN(line, 0);
                    line = line.substr(a_fn.size() + 1);
                    a_ln = getWordN(line, 0);
                    a_ln = a_ln.substr(0, a_ln.size() - 1);
                    line = line.substr(a_ln.size() + 2);
                    a_pn = getWordN(line, 0, ',');
                    line = line.substr(a_pn.size() + 2);
                    a_em = getWordN(line, 0, ';');

                    Contacts::Affiliates a(this, a_fn, a_ln, a_pn, a_em);
                    addAffiliate(a);
                } else {
                    // Does not have email or phone number
                    string a_fn, a_ln;

                    a_fn = getWordN(line, 0);
                    line = line.substr(a_fn.size() + 1);
                    a_ln = getWordN(line, 0);
                    a_ln = a_ln.substr(0, a_ln.size() - 1);

                    Contacts::Affiliates a(this, a_fn, a_ln);
                    addAffiliate(a);
                }

                getline(is, line);
            }

            //getline(is, line);
        }

        return is;
    }

    string Contacts::getWordN(string str, unsigned int n, char c, unsigned int pos) {
        unsigned int cn = 0;
        string tempstring;

        for (unsigned int i = pos; i < str.size(); ++i) {
            if (str[i] == c) cn++;
            else {
                if (n == cn) {
                    tempstring += str[i];
                }
            }
        }

        return tempstring;
    }

    int Contacts::getNumChars(string str, char c) {
        int n = 0;
        for (int i = 0 ; i < str.size(); i++) {
            if (str[i] == c) n++;
        }

        return n;
    }
}