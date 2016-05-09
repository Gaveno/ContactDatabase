FLAGS = -Wall -g -std=c++11

SOURCES = main.cpp SortContacts.h Contacts.h ContactList.h AVLNode.h AVLTree.h itemtype.h generator.h searchconstants.h AVLNode.cpp AVLTree.cpp ContactList.cpp Contacts.cpp

CXX=g++

all:
	$(CXX) $(FLAGS) $(SOURCES) -o prog.out

