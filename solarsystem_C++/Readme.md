Small Project using OpenGL and GLUT to represent the solar system
Flappy_bird_C: Primitive flappybird on terminal
=========================================

## Description ##

This is a Small Project using OpenGL and GLUT to represent the solar system

## Dependencies ##
* OpenGL
* gcc/Clang
* make

## Installing OpenGL on linux 
```bash
sudo apt-get update
sudo apt-get install freeglut3 freeglut3-dev
```
## Installing OpenGL on MACOS
* Install an IDE. Apple includes Project Builder / Xcode on the Developer CD included
with all OS releases.
* If you are using Mac OS 10.1 to 10.5 download and install the April 2002 version
of Project Builder.
* For all Jaguar revisions (v10.2 to v10.2.8) use the Dec 2002 version of Project
Builder.
* For Panther use Xcode.

### Install OpenGL & GLUT
These are already installed with the OS.
Using OpenGL and GLUT in you source
* Start Project Builder and create a new project of type “C++ Tool”. “Tool” is
Apple’s terminology for GUI-less executable.
* [This step only necessary in 10.2 and earlier] Go to the Target tab and make sure
that no prefix headers are used. The exact location of this varies with the version
of the Project Builder. However this is usually in the section on compiler settings.
* Add the correct Frameworks to your project by selecting Project -> Add
Frameworks and add two frameworks: OpenGL Framework and the GLUT
Framework.
* Replace main.cpp with whatever GLUT code you wish to run (i.e.
drawCircle.cpp from our demo programs) and make sure to include (in addition to
any specialized libaries like math.h) only (glut.h automatically includes gl.h and
glu.h):
```C
#include <GLUT/glut.h>
```
## Compilation and Usage ##
```bash
make
./solarsystem
```
