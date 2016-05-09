//
// Created by Gavin on 4/16/2016.
//

#ifndef FINALPROJECT_CONTACTS_H
#define FINALPROJECT_CONTACTS_H

#include <string>
#include <vector>
#include <iostream>
#include "searchconstants.h"

using std::string;

namespace ContactDatabase {
    class Contacts {
    public:
        // Constants
        static const int NUM_FIELDS = 13;

        static const string FIELD_NAMES[];

        //----------------------------------------- Affiliates -----------------------------------------//
        class Affiliates {
        public:
            //  Constructors
            Affiliates(Contacts *owner, string firstname, string lastname,
                       string number = "NULL", string email = "NULL") {
                __firstName = firstname;
                __lastName = lastname;
                __mobileNumber = number;
                __email = email;
                __owner = owner;
            }

            //  Setters
            void setFirstName(string firstname) { __firstName = firstname; }
            void setLastName(string lastname) { __lastName = lastname; }
            void setNumber(string number) { __mobileNumber = __owner->convertNumber(number); }
            void setEmail(string email) { __email = email; }

            //  Accessors
            const string &getFirstName() const { return __firstName; }
            const string &getLastName() const { return __lastName; }
            const string &getMobilePhone() const { return __mobileNumber; }
            const string &getEmail() const { return __email; }
            const string &getCompanyName() const { return __owner->getCompanyName(); }
            const string &getHomePhone() const { return __owner->getHomePhone(); }
            const string &getOfficePhone() const { return __owner->getOfficePhone(); }
            const string &getMiddleName() const { return __owner->getMiddleName(); }
            const string &getStreetAddress() const { return __owner->getStreetAddress(); }
            const string &getState() const { return __owner->getState(); }
            const string &getZipCode() const { return __owner->getZipCode(); }
            const string &getCountry() const { return __owner->getCountry(); }
            const Contacts *getOwner() const { return __owner; }
            string print() const {
                string os;
                os = __firstName;
                os += " ";
                os += __lastName;
                if (__mobileNumber != "NULL") {
                    os += " ";
                    os += __mobileNumber;
                }
                if (__email != "NULL") {
                    os += " ";
                    os += __email;
                }
                return os;
            }

            //  Friend functions
            friend std::ostream &operator<<(std::ostream &os, const Affiliates &aff);
            friend bool operator==(const Affiliates &lhs, const Affiliates &rhs) {
                return (lhs.__firstName == rhs.__firstName && lhs.__lastName == rhs.__lastName &&
                lhs.__email == rhs.__email && lhs.__mobileNumber == rhs.__mobileNumber);
            }
            friend bool operator!=(const Affiliates &lhs, const Affiliates &rhs) { return !(lhs == rhs); }

        private:
            string __firstName;
            string __lastName;
            string __mobileNumber;
            string __email;
            Contacts *__owner;
        };
        //----------------------------------------- Affiliates -----------------------------------------//

        Contacts();
        Contacts(string firstname);
        Contacts(string firstname, string middlename, string lastname);

        // Helpers
        string &convertNumber(string &number);
        string &convertEmail(string &email);

        //  Setters
        std::istream &loadFromStream(std::istream &is);
        void setField(unsigned int index, string entry);
        void setID(unsigned int id) { __id = id; }
        void setFirstName(string name) { __firstName = name; }
        void setLastName(string name) { __lastName = name; }
        void setMiddleName(string name) { __middleName = name; }
        void setCompanyName(string name) { __companyName = name; }
        void setHomePhone(string number);
        void setOfficePhone(string number);
        void setMobilePhone(string number);
        void setEmail(string email);
        void setStreetAddress(string address) { __streetAddress = address; }
        void setCity(string city) { __city = city; }
        void setState(string state) { __state = state; }
        void setZipCode(string zipcode) { __zipCode = zipcode; }
        void setCountry(string country) { __country = country; }
        void addAffiliate(const Affiliates &aff);
        void removeAffiliate(Affiliates &aff);

        //  Accessors - Constant
        std::ostream &printDetailed(std::ostream &os) const;
        const string &getField(unsigned int index) const;
        const unsigned int getID() const { return __id; }
        const string &getFirstName() const { return __firstName; }
        const string &getMiddleName() const { return __middleName; }
        const string &getLastName() const { return __lastName; }
        const string &getCompanyName() const { return __companyName; }
        const string &getHomePhone() const { return __homePhone; }
        const string &getOfficePhone() const { return __officePhone; }
        const string &getMobilePhone() const { return __mobileNumber; }
        const string &getEmail() const { return __email; }
        const string &getStreetAddress() const { return __streetAddress; }
        const string &getCity() const { return __city; }
        const string &getState() const { return __state; }
        const string &getZipCode() const { return __zipCode; }
        const string &getCountry() const { return __country; }
        unsigned int getNumAffiliates() const { return __affiliates.size(); }
        const Affiliates &getAffiliate(unsigned int index) const;
        const string &operator[](unsigned int index) const;
        void printNames(FieldSearch f1 = FieldSearch::FIRSTNAME, FieldSearch f2 = FieldSearch::LASTNAME) const;
        bool searchFor(string &item, FieldSearch field = FieldSearch::ALL, SearchMode mode = SearchMode::EXACT) const;

        //  Accessors - Non-Constant
        string &getField(unsigned int index);
        string &getFirstName() { return __firstName; }
        string &getMiddleName() { return __middleName; }
        string &getLastName() { return __lastName; }
        string &getCompanyName() { return __companyName; }
        string &getHomePhone() { return __homePhone; }
        string &getOfficePhone() { return __officePhone; }
        string &getMobilePhone() { return __mobileNumber; }
        string &getEmail() { return __email; }
        string &getStreetAddress() { return __streetAddress; }
        string &getCity() { return __city; }
        string &getState() { return __state; }
        string &getZipCode() { return __zipCode; }
        string &getCountry() { return __country; }
        Affiliates &getAffiliate(unsigned int index);
        string &operator[](unsigned int index);

        // Friend functions
        friend std::ostream &operator<<(std::ostream &os, const Contacts &contact);
        friend std::istream &operator>>(std::istream &is, Contacts &contact);
        friend bool operator<(const Contacts& lhs, const Contacts& rhs) { return (lhs.getID() < rhs.getID()); }
        friend bool operator>=(const Contacts& lhs, const Contacts& rhs) { return (lhs.getID() >= rhs.getID()); }
        friend bool operator>(const Contacts& lhs, const Contacts& rhs) { return (lhs.getID() > rhs.getID()); }
        friend bool operator<=(const Contacts& lhs, const Contacts& rhs) { return (lhs.getID() <= rhs.getID()); }
        friend bool operator==(const Contacts& lhs, const Contacts& rhs) { return (lhs.getID() == rhs.getID()); }
        friend bool operator!=(const Contacts& lhs, const Contacts& rhs) { return !(lhs == rhs); }


    private:
        // Variables
        static unsigned int __idGen;
        unsigned int __id;
        string __firstName;
        string __middleName;
        string __lastName;
        string __companyName;
        string __homePhone;
        string __officePhone;
        string __email;
        string __mobileNumber;
        string __streetAddress;
        string __city;
        string __state;
        string __zipCode;
        string __country;

        // Vector list of affiliates
        std::vector<Affiliates> __affiliates;

        // Private functions
        string getWordN(string str, unsigned int n, char c = ' ', unsigned int pos = 0);
        int getNumChars(string str, char c);
    };

    /*class SortContacts {
    public:
        SortContacts() : __index(0) { }
        SortContacts(FieldSearch index)
                : __index((unsigned) index) { }

        bool operator()(Contacts &a, Contacts &b) { return (a.getField(__index) < b.getField(__index)); }

    private:
        unsigned int __index;
    };*/
}


#endif //FINALPROJECT_CONTACTS_H
