//
// Created by Gavin on 5/9/2016.
//

#ifndef FINALPROJECT_SORTCONTACTS_H
#define FINALPROJECT_SORTCONTACTS_H

#include "searchconstants.h"
#include "Contacts.h"

namespace ContactDatabase {
    class SortContacts {
    public:
        SortContacts() : __index(0) { }

        SortContacts(FieldSearch index)
                : __index((unsigned) index) { }

        bool operator()(Contacts &a, Contacts &b) { return (a.getField(__index) < b.getField(__index)); }
        bool operator()(const Contacts &a, const Contacts &b) { return (a.getField(__index) < b.getField(__index)); }
        bool operator()(Contacts &a, const Contacts &b) { return (a.getField(__index) < b.getField(__index)); }
        bool operator()(const Contacts &a, Contacts &b) { return (a.getField(__index) < b.getField(__index)); }

    private:
        unsigned int __index;
    };
}

#endif //FINALPROJECT_SORTCONTACTS_H
