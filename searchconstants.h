//
// Created by Gavin on 4/29/2016.
//

#ifndef FINALPROJECT_SEARCHCONSTANTS_H
#define FINALPROJECT_SEARCHCONSTANTS_H

// Search field options
enum FieldSearch {
    FIRSTNAME=0, MIDDLENAME, LASTNAME,
    COMPANYNAME, HOMEPHONE, OFFICEPHONE,
    EMAIL, MOBILENUMBER, STREETADDRESS,
    CITY, STATE, ZIPCODE, COUNTRY,
    AFFILIATES, ALL
};

enum SearchMode {
    EXACT=0, CONTAINS
};

#endif //FINALPROJECT_SEARCHCONSTANTS_H