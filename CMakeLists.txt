cmake_minimum_required(VERSION 3.3)
project(FinalProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp AVLNode.cpp AVLTree.cpp itemtype.h Contacts.cpp Contacts.h ContactsExceptions.h ContactList.cpp ContactList.h generator.h ContactExeptions.h searchconstants.h SortContacts.h)
add_executable(FinalProject ${SOURCE_FILES})