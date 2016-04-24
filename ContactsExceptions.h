//
// Created by Gavin on 4/16/2016.
//

#ifndef FINALPROJECT_CONTACTSEXCEPTIONS_H
#define FINALPROJECT_CONTACTSEXCEPTIONS_H

#include <string>
#include <iostream>

using namespace std;

namespace ContactDatabase {

    class ExOutOfBounds {
    public:
        ExOutOfBounds(string origin, int index, int expIndex)
                : __origin(origin), __index(index), __expIndex(expIndex) {
            __name = "ExOutOfBounds";
        }

        ostream &print(ostream &os) const {
            os << __name << " : " << __origin << " : ";
            os << "index: " << __index << " max index: " << __expIndex;
            os << endl;
            return os;
        }

        friend ostream &operator<<(ostream &os, const ExOutOfBounds &ex) {
            ex.print(os);
            return os;
        }

    private:
        string __name;
        string __origin;
        int __index;
        int __expIndex;
    };
}

#endif //FINALPROJECT_CONTACTSEXCEPTIONS_H
