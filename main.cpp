/**************************************************************************************************************************************
* Programming Assignment: PA9
* Class: CptS 122, Spring 2026
* Date: April 29, 2026
***************************************************************************************************************************************/
//Main file
#include <iostream>
#include <vector>

#include "CorrectCode.hpp"
#include "BuggyCode.hpp"

int main() {

    // Polymorphism setup:
    // We use a vector of base class pointers (GameObject*)
    // This  will allowed us to store diffrent derived types in one list

    std::vector<GameObject*> items;

    // Add objects to the list
    items.push_back(new CorrectCode());              // +1 points
    items.push_back(new BuggyCode(SYNTAX));          // -1 points
    items.push_back(new BuggyCode(LOGIC));           // -2 points


    for (GameObject* obj : items) {

        // Convert GameObject* → CodeItem*
        CodeItem* code = dynamic_cast<CodeItem*>(obj);

        if (code != nullptr) {

            // Call polymorphic function
            int score = code->onSlice();

            // Print result
            std::cout << "Score change: " << score << std::endl;
        }
    }

    
    for (GameObject* obj : items) {
        delete obj;
    }

    return 0;
}