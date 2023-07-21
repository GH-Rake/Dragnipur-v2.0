# Dragnipur-v2.0 AssaultCube Internal Aimbot/ESP/MultiHack

his repository contains a collection of hacks for the game AssaultCube, including an Aimbot and ESP (Extra Sensory Perception). The codebase is written in C++ and is designed to provide an unfair advantage to the user in the game.

![Screenshot_3.png](https://bitbucket.org/repo/B4pn7b/images/799256167-Screenshot_3.png)

## What does this do?

This is an internal hack with these features:
-   Aimbot
-   OpenGL ESP
-   Item ESP
-   No Recoil
-   Teleport
-   Flag Hack
-   Teleporting Mass Murder

## Why?

This is my first internal project that works online.  I learned most of everything I know from making this. ESP code is terrible.

## Usage

Compile.  Put glut32.dll into AssaultCube\bin_win32
Inject DLL into ac_client.exe
Pwn at your leisure

## TODO

Remove GLUT
Recompile with loader.
Rewrite entire project using my current framework and make an extensive youtube tutorial series with it.


## Development History

I finished my first External Aimbot for this game in 02/2015 and I finished this one in 12/2015 and have made small minor alterations to it over time.

###

[Assault Cube Internal Multihack Thread](http://guidedhacking.com/showthread.php?7479)
[Assault Cube Internal Multihack Video](https://youtu.be/skwSUTK1MTw)

File Structure
--------------

Here's a brief overview of the main files in the repository and their purpose:

-   `aimbot.cpp` and `aimbot.h`: These files contain the implementation of the aimbot feature.
-   `esp.cpp` and `esp.h`: These files contain the implementation of the ESP feature.
-   `main.cpp`: This is the entry point of the program.
-   `mem.cpp` and `mem.h`: These files handle memory-related operations.
-   `menu.cpp` and `menu.h`: These files manage the in-game menu that allows toggling different features.
-   `openGLHacks.cpp` and `openGLHacks.h`: These files contain OpenGL related hacks.
-   `reversals.cpp` and `reversals.h`: These files handle the reversal of game functions.
-   `glDraw.cpp` and `glDraw.h`, `gltext.cpp` and `gltext.h`: These files handle the drawing of elements on the game screen.
-   `geom.cpp` and `geom.h`: These files handle geometric calculations.
-   `MyRect.cpp` and `myRect.h`: These files define a custom rectangle class used in the program.
-   `DragnipurV2.0.sln`, `DragnipurV2.0.vcxproj`, `DragnipurV2.0.vcxproj.filters`: These are Visual Studio solution and project files.
-   `lib/OpenGL32.Lib`: This is a library file for OpenGL.

### Official GH Courses

-   [The Game Hacking Bible](https://guidedhacking.com/ghb) - a massive 70 chapter Game Hacking Course
-   [Computer Science 420](https://guidedhacking.com/threads/squally-cs420-game-hacking-course.14191/) - an eight chapter lecture on CS, Data Types & Assembly
-   [Binary Exploit Development](https://guidedhacking.com/forums/binary-exploit-development-course.551/) - a 9 chapter series on exploit dev from a certified OSED
-   [Game Hacking Shenanigans](https://guidedhacking.com/forums/game-hacking-shenanigans/) - a twenty lesson Cheat Engine hacking course
-   [Python Game Hacking Course](https://guidedhacking.com/threads/python-game-hacking-tutorial-1-1-introduction.18695/) - 7 chapter external & internal python hack lesson
-   [Python App Reverse Engineering](https://guidedhacking.com/threads/python-game-hacking-tutorial-2-1-introduction.19199/) - Learn to reverse python apps in 5 lessons
-   [Web Browser Game Hacking](https://guidedhacking.com/threads/web-browser-game-hacking-intro-part-1.17726/) - Hack javascript games with this 4 chapter course
-   [Roblox Exploiting Course](https://guidedhacking.com/forums/roblox-exploit-scripting-course-res100.521/) - 7 Premium Lessons on Hacking Roblox
-   [Java Reverse Engineering Course](https://guidedhacking.com/forums/java-reverse-engineering-course-jre100.538/) - 5 chapter beginner guide
-   [Java Game Hacking Course](https://guidedhacking.com/forums/java-game-hacking-course-jgh100.553/) - 6 Chapter Beginner Guide

Prerequisites
-------------

To use this codebase, you need to have a basic understanding of the following:

1.  C++: The codebase is written in C++, so you need to understand C++ syntax and concepts.

2.  Game Hacking: The codebase is designed to modify the behavior of a game, so understanding how game hacking works, including concepts like memory manipulation and reverse engineering, is beneficial.

3.  OpenGL: Some parts of the codebase use OpenGL for rendering, so understanding how OpenGL works is helpful.

4.  Visual Studio: The codebase includes Visual Studio solution and project files, so you need to know how to use Visual Studio to build and run the project.

Usage
-----

To use this codebase, follow these steps:

1.  Clone the repository to your local machine.
2.  Open the `DragnipurV2.0.sln` file in Visual Studio.
3.  Build the solution.
4.  Run the resulting executable while AssaultCube is running


Frequently Asked Questions
--------------------------

1.  Adapting the Codebase for Other Games

    *Question*: Can I use this codebase to hack other games?

    *Answer*: This codebase is specifically tailored for AssaultCube. While some of the concepts might be transferable, adapting it to another game would require significant effort. Each game is unique and necessitates a distinct approach to hacking.

2.  Risk of Getting Banned

    *Question*: Will I get banned for using this?

    *Answer*: Utilizing game hacks always carries the risk of being banned. Game developers are continuously working to detect and ban players who employ hacks to ensure fair gameplay. Therefore, use this codebase at your own risk.

Learning About Game Hacking

Question: Can I use this codebase to learn about game hacking?

Answer: Absolutely, this codebase can serve as a valuable resource for learning about game hacking. It demonstrates several key concepts, such as memory manipulation and OpenGL rendering.

Glossary
--------

1.  Aimbot: A software tool used in first-person shooting games that allows the player to automatically aim at the enemy players. It gives the player an unfair advantage as it requires no skill to aim and shoot the enemies.

2.  ESP (Extra Sensory Perception): In gaming terms, ESP stands for Extra Sensory Perception. This feature allows the player to perceive details that would be otherwise hidden in the game. For example, it can reveal enemy locations, their health status, and other critical information.

3.  OpenGL: OpenGL (Open Graphics Library) is a cross-language, cross-platform application programming interface (API) for rendering 2D and 3D vector graphics. The API is typically used to interact with a graphics processing unit (GPU), to achieve hardware-accelerated rendering.

4.  Memory Manipulation: In the context of game hacking, memory manipulation is the practice of altering a game's memory to change certain aspects of the game. This can include things like player health, ammo count, position, and more.

5.  Reverse Engineering: Reverse engineering is the process of understanding how something works by examining its components and their interactions. In game hacking, this often involves understanding how the game code works in order to exploit it.

6.  Visual Studio: Visual Studio is an integrated development environment (IDE) from Microsoft. It is used to develop computer programs, as well as websites, web apps, web services, and mobile apps. Visual Studio uses Microsoft software development platforms such as Windows API, Windows Forms, Windows Presentation Foundation, Windows Store, and Microsoft Silverlight.
