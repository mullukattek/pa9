     
CptS 122 – Programming Assignment 9
Spring 2026

Project Title: Code Ninja

Creators: 
Jacob Langer (lab section 8), Vincent Rampp (lab section 12), Kristina Mullukatte (lab section 7), Raahina Sheik Syed Ali (lab section 7) 


---

PROJECT DESCRIPTION:

Code Ninja is a fast-paced, educational arcade game inspired by classic slicing mechanics. 
In this game, the player takes on the role of a “code ninja” whose mission is to eliminate bugs and improve code quality by slicing correct programming snippets while avoiding errors.
Code fragments appear and move across the screen, similar to a fruit-slicing game. Each fragment represents either:
      Correct code ( proper syntax or logic)
      Buggy code ( syntax errors, logical mistakes)
The player uses mouse movements to “slice” through the code:
      Slicing correct code earns points 
      Slicing buggy code results in penalties such as losing  score
      
As the game progresses, the difficulty increases with faster-moving objects and more complex code snippets, challenging the player’s reaction time and programming knowledge.

---

Technologies Used:
* C++
* SFML (Simple and Fast Multimedia Library)
* Object-Oriented Programming (OOP)

---

HOW TO RUN THE PROGRAM:

1. Ensure SFML is installed and properly configured.
2. Open the project in Visual Studio (or preferred IDE).
3. Build the solution.
4. Run the program (main.cpp).

---

HOW TO PLAY:
* Launch the game.
* Use your mouse cursor to slice through code fragments that appear on the screen.
* Identify whether each snippet is:
    •Correct Code (valid syntax/logic)
    •Buggy Code (contains errors)
* Slice wisely:
  •Slice correct code to earn points
  •Avoid slicing buggy code to prevent penalties

* Bonus Feature:
•The bonus feature in this project is multiplayer network play.
•Two players can connect and play the game together using socket communication.

---
Scoring:

* Slice Correct Code → +1 point
* Slice Syntax Error Code → -1 point
* Slice Logic Error Code → -2 points

Goal:

* Maximize score by slicing correct code and avoiding buggy code.

---

FEATURES IMPLEMENTED:

* Graphical game using SFML

* Object-oriented design with inheritance and polymorphism

* Real-time object spawning and movement

* Mouse-based collision detection (slicing mechanic)

* Scoring system with positive and negative points

* Difficulty progression system:
  • Easy (0–5 points): Easy code only
  • Medium (6–15 points): Easy + Medium code
  • Hard (15+ points): Medium + Hard code

* Dynamic difficulty scaling:
  • Increasing object speed over time
  • Decreasing spawn interval
  • Increased number of buggy code objects

---

CLASS DESIGN (INHERITANCE):

GameObject (base class)
→ CodeItem
→ CorrectCode
→ BuggyCode

* GameObject handles position, movement, and rendering
* CodeItem adds slicing behavior
* CorrectCode returns +1 score
* BuggyCode returns -1 or -2 based on error type

---

GENERATIVE AI USAGE:
* Debugging assistance
* Code suggestions for BONUS
* README and documentation formatting
---
Video Link: 
https://youtu.be/NpoIJl8PgNw
