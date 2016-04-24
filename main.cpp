#include <iostream>
#include <string>
#include <fstream>
#include "ContactList.h"
#include "Contacts.h"
#include "generator.h"

using namespace std;
using namespace ContactDatabase;

int main() {

    ContactList cl("contacts.txt");
    cl.menuMain();

    return 0;
}
