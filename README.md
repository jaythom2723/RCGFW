# Rify's C Game Frame Work
Rify's C Game Frame Work (RCGFW) has been developed by Jacob Thomas as a personal project for a future game idea.

The framework will support texture loading, shader loading, gl wrapping, rudimentary entity component system, audio loading, and much more.

RCGFW is still under development and this is the fifth rewrite since initial development started.

The to-do list for the project can be found via `TODO.md` and the TODO list covers all things that have been implemented and features that have yet to be implemented and even ideas for the framework (denoted with '?').

----

RCGFW is entirely written in ISO C99. The following libraries were used to compile this project:
* GLFW - Window & Context Creation
* OpenGL - Rendering
* CGLM - Math Library
* GLAD - OpenGL Extension Loader
* StbImage - Image Loading

# Compiling
Currently, RCGFW only runs on linux and linux-based operating system. A Windows port will be made later during development.

## Linux
### Debian-based Distros
1. You must make sure `make` is installed, you can check if it is installed with `whereis make`. If `whereis make` returns nothing; run the following command:
```
sudo apt-get install make
```
2. Clone the repo into a given directory
```
git clone https://github.com/jaythom2723/RCGFW.git
cd RCGFW
```
3. Create the build directory and run make
```
mkdir build/
make
```

### Arch-based Distros
1. Similar to Debian-based Distros, make sure `make` is installed with `whereis make`. Install `make` if it's not installed.
```
sudo pacman -S make
```
2. Clone the repo into a given directory
```
git clone https://github.com/jaythom2723/RCGFW.git
cd RCGFW
```
3. Create the build directory and run make
```
mkdir build
cd build
```