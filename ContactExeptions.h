//
// Created by Gavin on 4/24/2016.
//

#ifndef FINALPROJECT_CONTACTEXEPTIONS_H
#define FINALPROJECT_CONTACTEXEPTIONS_H

#include <string>
#include <iostream>

#include "itemtype.h"

namespace ContactDatabase {

    class ExEmptyTree {
    public:
        ExEmptyTree() { __name = "ExEmptyTree"; }

        std::ostream &print(std::ostream &os) {
            os << __name << std::endl;
            return os;
        }

        std::ostream &operator<<(std::ostream &os) {
            print(os);
            return os;
        }

    private:
        std::string __name;
    };

    class ExItemNotFound {
    public:
        ExItemNotFound(const ItemType &item) {
            __name = "ExItemNotFound";
            __item = item;
        }

        std::ostream &print(std::ostream &os) {
            os << __name << ": " << __item << std::endl;
            return os;
        }

        std::ostream &operator<<(std::ostream &os) {
            print(os);
            return os;
        }

    private:
        std::string __name;
        ItemType __item;
    };
}

#endif //FINALPROJECT_CONTACTEXEPTIONS_H
