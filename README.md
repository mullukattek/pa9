Code Ninja Game PA 9 (CptS 122)

Game Description
Code Ninja is a fast-paced, educational arcade game inspired by classic slicing mechanics. 
In this game, the player takes on the role of a “code ninja” whose mission is to eliminate bugs and improve code quality by slicing correct programming snippets while avoiding errors.
Code fragments appear and move across the screen, similar to a fruit-slicing game. Each fragment represents either:
      Correct code ( proper syntax or logic)
      Buggy code ( syntax errors, logical mistakes)
The player uses mouse movements to “slice” through the code:
      Slicing correct code earns points 
      Slicing buggy code results in penalties such as losing  score
      
As the game progresses, the difficulty increases with faster-moving objects and more complex code snippets, challenging the player’s reaction time and programming knowledge.


How to Play:
Launch the game.
Use your mouse cursor to slice through code fragments that appear on the screen.
Identify whether each snippet is:
    Correct Code (valid syntax/logic)
    Buggy Code (contains errors)
Slice wisely:
  Slice correct code to earn points
  Avoid slicing buggy code to prevent penalties

Bonus Feature:
The bonus feature in this project is multiplayer network play.
Two players can connect and play the game together using socket communication.

Creators: 
Jacob Langer (lab section 8), Vincent Rampp (lab section 12), Kristina Mullukatte (lab section 7), Raahina Sheik Syed Ali (lab section 7) 


Features:
      Mouse-Based Slicing: Slice objects using mouse movement
      Educational Gameplay: Identify correct vs incorrect code
      Scoring System:
            Correct Code → +1
            Syntax Error → -1
            Logic Error → -2
      Difficulty Progression System:
            Easy → Medium → Hard (based on score)
      Dynamic Difficulty Scaling:
            Faster objects over time
            Increased spawn rate
            More buggy code appears
      Graphical Interface using SFML
      Object-Oriented Design:
            Inheritance & polymorphism
      Main Menu System (Play / Exit / Instructions)



Technologies Used:
C++
SFML (Simple and Fast Multimedia Library)
Object-Oriented Programming (OOP)
      Inheritance
      Polymorphism

Generative AI Usage
Used for:
      Debugging
      Code suggestions
      Documentation (README file)
      Bonus - Socket Implementation
      How to use WINSOCK for Bonus 
      
       
