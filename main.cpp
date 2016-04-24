#include <iostream>
#include <string>
#include <fstream>
#include "ContactList.h"
#include "Contacts.h"
#include "generator.h"

using namespace std;
using namespace ContactDatabase;

int main() {

    fstream file;
    file.open("contacts.txt");
    ContactList cl;


    if (file) {
        file >> cl;
    }

    file.close();

    cout << cl;

    return 0;
}
