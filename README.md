# ContactDatabase
Contact Database Program
Created by: Gavin Atkin

Date Created: 4/16/2016

###Description:
This program manages a contact database. Allowing loading, saving, modifying and creating of new databases. The program supports searching and sorting of the contact lists and a report can be created from the contact list in either txt or csv file formats.

###Overall Software Architecture:
The program consist of three main classes:

1.	AVLTree	- 	The main data structure holding each contact
2.	Contacts	-	Contains each field of the contact as well as functions and procedures to manipulate the information stored.
3.	ContactList	-	All the methods for tying together the AVLTree and Contacts classes. Uses text based menus to interact with the user. See Fig.1.


###Important Procedures:
#####void menuMain();
The main program entry point. Has 6 options. Prompts the user for an integer in the range [1,6].

1.	menuDisplay()		All options for displaying contacts  
2.	menuSearch()		All options for searching contacts  
3.	menuAddContact()	Add a new contact to the current list  
4.	menuLoad()		Load contacts from a file  
5.	menuSave()		Save contacts to the same or a new file  
6.	<program exit>	Exit point for the program

#####void menuDisplay(AVLTree &tree);
All options for displaying the contacts to the console. Can display all contacts with the default sort options, or the user can select which fields to sort by. Allows for primary and secondary sorting.
Display has an option to jump to menuSearch() (see Fig.1)

#####void menuSearch();
All options for searching the database. The user can select to search in all fields, or an individual field. There are two search modes: Exact and Contains. When Exact is selected, the field being searched in must match the users search term exactly in length, order, and characters. Contains will look for an occurrence of that term inside the field.
Search has a menu option to jump to menuDisplay() (see Fig.1)

#####void menuAddContact();
Creates a new contact and opens the menuModifyContact() menu. If the contact has at least a first name entered, the new contact will be added to the current contact list. It will not be saved to a file until menuSave() is navigated and a file is selected.

#####void menuModifyContact(Contacts &cont);
Menu to modify a contacts fields. The user selects which field to modify and then enters the new field entry. Once the user is done they select the option to save and exit. Also allows deleting the contact from the list.
Has an option to jump to menuListAffiliates() to add, delete, and modify the affiliates of the contact.

#####void menuListAffiliates(Contacts &cont);       
Lists out the current affiliates of a contact. Allows the user to select an existing affiliate for modification or deletion, as well as adding new affiliates.
Jumps to menuModifyAffiliate() when an option is selected.

#####Contacts::Affiliates &menuModifyAffiliate(Contacts::Affiliates &aff);
Menu to modify the fields of an affiliate. Once the user has changed the fields to their liking they can save the contact and return to the previous menu, or permanently delete the affiliate from the contact.

#####void menuPrintReport(vector<ItemType> vec);
When the user performs a search or displays the contact list in some way, they will then have the option to jump to this menu. The user can select which fields they would like to include in the report and then choose to save the report as either a csv (comma separated values) or txt (ASCII text document) file.

#####void menuLoad();
Allows the user to load a different contact database then the default loaded. The file must be in the same directory as the program if only typing the file’s name.

#####void menuSave();
The save menu prompts the user to either save to the same file name already in use, or save as a new name creating a new file (or overwriting if it already exists).  

#####void loadContacts(std::string fname);
The legwork of the load menu. This method actually opens and reads in a file to the contacts list. If it reaches a corrupt contact it will stop loading and display a message letting the user know how many contacts were successfully loaded.

#####friend std::ostream &operator<<(std::ostream &os, const ContactList &cl);  
While not actually a method of any class, this friend overloaded operator allows streaming from a contact list into an out stream object. The output format matches the database format for loading contacts.

#####friend std::istream &operator>>(std::istream &is, ContactList &cl);
Another friend function, this one is for loading a contact list from an in stream object. 

#####std::vector<ItemType> &displaySorted(&tree, std::vector<ItemType> &vec,
#####                FieldSearch field = FieldSearch::FIRSTNAME,
#####                FieldSearch second = FieldSearch::LASTNAME);
The main method and algorithm for sorting the contact list. Takes the tree to sort from and copies the contents into a vector. It sorts the first field with the std::sort algorithm and then uses a bubble sort algorithm to sort by the second field. The vector is passed by reference so that it can be used for saving reports with the same sorted order.

#####AVLTree &addTree(AVLTree &tree, std::string item = "NULL",
#####                                     FieldSearch field = FieldSearch::ALL,
#####                                     SearchMode mode = SearchMode::EXACT);
This is the main method for searching. A reference to a secondary tree is passed in and every element from the calling tree matching the field with the passed in mode will be added to the passed in tree.

#####std::vector<ItemType> &addVector(std::vector<ItemType> &vec, std::string item = "NULL",
#####                                     FieldSearch field = FieldSearch::ALL,
#####                                     SearchMode mode = SearchMode::EXACT);
Similarly to addTree(), this method adds every element of the calling tree to the passed in vector matching the search criteria. This is primarily used for sorting purposes.
 
###Input Requirements:
#####Database File:
ASCII text formatted file with each field on a new line. Each contact starts with an ID number that cannot be longer than 9 digits. Field length requirements are [1, N] where N is 30 for email, 25 for any other contact field, and 105 for the total affiliate line length.
#####User Inputs:

**Main menu** – [1, 6] integer or float. Anything after a decimal will be ignored. No words or non-number characters will be accepted.

1.	Display Contacts – Navigates to display sub-menu for sorting and displaying contacts.
2.	Search Contacts – Navigates to search sub-menu for searching and displaying contacts.
3.	Add Contact – Navigates to modify contact sub-menu to modify entries of the new contact.
4.	Load Contacts – Prompts the user for a filename to load from. Any string is accepted. An error message will be displayed if failed to load.
5.	Save Contacts – Save contacts sub-menu to save contact list to a file.
6.	Exit – Quit the program.

**Display Menu** – [1, 7] integer or float. Anything after a decimal will be ignored. No words or non-number characters will be accepted. NOTE: Not every menu option will be available when first entering the menu. Once the contact list has been displayed once, more options become available.

1.	Display all contacts – Displays all contacts in current list (can be sub-list if search was performed) with the default sort options. First name, last name.
2.	Sort and display all – Prompts the user for the first field of the contact to search by then prompts for the second field. Values accepted [1, 13] non-numbers rejected.
3.	Search and display – Navigate to search menu. Does not carry over sort options.
4.	Modify Contact – Prompts the user for a row number (next to contact name) to modify.
5.	Save Report – Navigates to the report sub-menu. Allows saving the currently sorted list to a file.
6.	Back – Goes to the previous menu.
7.	<-- Main Menu – Navigates to the main menu regardless of how many sub-menus the user has entered.

**Search Menu** – [1, 10] integer or float. Anything after a decimal will be ignored. No words or non-number characters will be accepted. NOTE: Not every menu option will be available when first entering the menu. Once the contact list has been searched at least once, more options become available.

1.	Search – Search and display the contact list with the current settings. If no results are found an error is displayed and the search is cleared.
2.	Enter a search term – Prompts the user for a string to search by. Accepted length [1, 30] characters.
3.	Select field to search – Prompts the user for a contact field to search in. Integers [1, 14]. ALL will search every contact field.
4.	Select search mode – Prompts the user for a type of search to perform. Integers [1, 2] Exact, or Contains.
5.	Display & Sort Menu – Navigate to the display menu detailed above. Carries search results over.
6.	Modify Contact – Prompts the user for a row number (next to contact name) to modify.
7.	Clear Search – Clears the search list to allow searching entire list again.
8.	Save Report – Navigates to the report sub-menu. Allows saving the currently sorted list to a file.
9.	Back – Goes to the previous menu.
10.	<-- Main Menu – Navigates to the main menu regardless of how many sub-menus the user has entered.

**Output Report Menu** – [1, 16] integer or float. Anything after a decimal will be ignored. No words or non-number characters will be accepted.

- 1.	– 14. Turn a field on or off. If an ‘X’ is next to the field, it will be included in the report.
- 15. Save Report – Prompts the user for a file type, then a filename to save as. The file can be a text file or comma separated values file. Filename can be any combination of characters (no promises something won’t crash). The appropriate file extension will be appended to the end. Accepted length [1, 25]
- 16. Back – Goes back to the previous menu.

**Modify Contact Menu** – [1, 16] integer or float. Anything after a decimal will be ignored. No words or non-number characters will be accepted. Displays current contact information and lets the user alter any field.

- 1.	– 13. Select a field to modify. Prompts the user for a new entry and returns to this menu. Accepted length [1, N]. For email N = 30, every other field N = 25.
- 14. Affiliates – Opens affiliates menu to add, remove, or modify an affiliate.
- 15. Remove Contact – Permanently delete a contact from the contact list. The user must type “YES” in all caps without quotes to proceed with deletion, otherwise a message will be displayed that the contact was not deleted.
- 16. Save and Exit – Saves the contact and returns to the previous menu.

**Affiliates Menu** – [1, 4] integer or float. Anything after a decimal will be ignored. No words or non-number characters will be accepted. Options for modifying the affiliates of a contact.

1.	Add Affiliate – Add an affiliate to the contact. Opens the modify affiliate menu so the user can enter in values for each field.
2.	Modify Affiliate – Prompts the user for the row number (to the left of the affiliate) to modify. Navigates to the modify affiliate menu. Accepts integers [1, N] (N: total number of affiliates)
3.	Remove Affiliate – Prompts the user for a row number of the affiliate to remove. Accepts integers [1, N] (N: total number of affiliates). The user will have to type “YES” in all caps (without quotes) to continue with deletion. Otherwise a message will be shown that the affiliate was not deleted.
4.	Save Affiliates & Exit – Saves all affiliate information to the parent contact and returns to the modify contact menu.

**Modify Affiliates Menu** – [1, 5] integer or float. Anything after a decimal will be ignored. No words or non-number characters will be accepted. Options for modifying the affiliates of a contact.

1.	First Name – Prompts the user for a new first name. Accepted length [1, 25] characters.
2.	Last Name – Prompts the user for a new last name. Accepted length [1, 25] characters.
3.	Phone Number – Prompts the user for a new phone number. Accepted length [1, 25] characters.
4.	Email – Prompts the user for a new email. Accepted length [1, 30] characters.
5.	Save & Exit – Saves all affiliate entries and returns to the list affiliates menu.

###Output Requirements:
There are three ways the contacts are output.
1)	To the console – The user selects sort options (or uses the default settings) and displays the contacts in rows with an associated row number to the left. The contact fields are displayed in the format: “#<row number> <first name> <middle name> <last name> <additional sort field 1> <additional sort field 2>”. For instance with the default sort settings, a contact could be shown as: “#1 Adob E. Zum” without quotation marks.
2)	To a file as a report – After the contacts have been displayed at least once either by sorting or searching, the menu option Save Report will become available. The Save Report menu will ask the user to select which fields to save to save, and will error if the user does not select any fields at the time of saving the report. The report has two file format options. Standard ASCII Text Document (*.txt) and Comma Separated Values (*.csv). The txt document option will output the contact list with the selected fields with aligned spaces, one contact per row. The csv option will use comma’s to separate each field in the report which allows easy readability in Microsoft Excel. 
3)	To a file as a database – The final option is using the Save menu to save to a file as a contact database list. This format is used to read into the contact database app. Each contact starts with an ID number that will be padded with leading zeroes to have a length of 9 digits, (reading does not require exactly nine digits, but cannot be longer than 9) followed by each field having its own line. The format is:
•	<ID Number>
•	<First Name>
•	<Middle Name>
•	<Last Name>
•	<Company Phone>
•	<Home Phone>
•	<Office Phone>
•	<Email>
•	<Mobile Number>
•	<Street Address>
•	<City>
•	<State>
•	<Zip Code>
•	<Country>
•	<Affiliate 0>
•	<Affiliate 1>
•	… <Affiliate N-1>
•	<Affiliate N>


###Problem Solutions:
One problem I wanted to completely tackle early on was (near) perfect input from the user. I first began with simple cin >> statements, but they can easily be broken by decimal numbers when expecting integers, spaces between words when wanting to get an entire line, etc. I created to helper functions to make input from the user much simpler for all the menus: getWords(int) and getNumbers(int, int). The former will not let the user proceed without entering a string within the designating length (default 25). The latter takes the bounds as inclusive arguments and by using try and catch blocks, tries to convert the input into an integer using stoi and if it fails (because they entered non number characters) it will catch the exception thrown and display an error message to the user reminding them of the bounds they must stay within. If the user enters a decimal it is simply converted to an integer and anything after the decimal place is lost. Using these helper functions I have not found a way to break the program from user input. Additional problems detailed below.
###Data Structure in Program:
The main structure used is an AVLTree located inside AVLTree.h/AVLTree.cpp but the program also uses vectors in a couple places to make certain algorithms smoother.
I considered three databases overall for sub lists, AVLTree, vector, and linked list. For Affiliates I used vector because they do not need ID numbers (making AVLTree sorting pointless) and I’d primarily be accessing them sequentially, but at times there would be random access. For instance, when modifying or adding additional affiliates. I felt a vector was more in line with my use than a linked list.
The second place sub-lists are used is for searching the tree. Knowing that I wanted to allow multiple searches refining the results each time, I felt it would be best to use the same database as the base type to allow a sort of recursion to be possible without much modification. The search menu takes an AVLTree as an argument which allows the first call to pass in the main database, but then the menu can call itself passing in a sub list found in the menu.
And the last sub-list is for sorting and displaying. I went with vector here because it seemed the simplest to manipulate. The menu for display and sorting creates a vector from a tree (which can be a sub-tree from a search) and uses std::sort for the first field to sort by. Since I wanted to allow a secondary sort in case of duplicate fields, I created a bubble sort that could swap values in a vector to order them correctly.

