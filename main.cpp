#include <iostream>
#include <string>
#include <fstream>
#include "ContactList.h"
#include "Contacts.h"
#include "generator.h"

using namespace std;
using namespace ContactDatabase;

int main() {

    // Contact generation
    /*ofstream fout ("contacts.txt");
    generateContacts(200, fout);
    fout.close();*/

    ContactList cl("contacts.txt");
    cl.menuMain();

    return 0;
}
