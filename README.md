# RCE (RaylibComponentEngine)
## About
This engine is built on top of the existing awesome game making library [raylib](https://www.raylib.com/). <br>
This framework uses CMake build system. <br>
I started building this library because I created a small game in unity, but I missed pointers and I didn't like the API, so I decided to build this (probably bug filled) framework, with the goal of making it as generic as I can, with people being able to create components and scenes using some simple `IScenes` and `IObjectComponent` interfaces (maybe) using the wonderful ideology of OOP.
## Creating a project (Using CMake and Ninja)
To create a project using RCE follow this steps:
1. Installing the programs:
  - Windows: `winget install Git.Get`, `winget install Kitware.CMake`, `winget install Ninja-build.Ninja`
  - Linux: `sudo apt update`, `sudo apt install git`, `sudo apt install cmake`, `apt install ninja-build`
2. Clone the repo with `git clone https://github.com/MeFiddzy/RCE.git`  
3. CD into the RCE dir `cd RCE` and (optional) rename he folder to your project name and the cmake project from `CMakeLists.txt`
4. Create a `build` directory (`mkdir build`), go into it (`cd build`) and run `cmake -G "Ninja" ..` 
5. Build the project `ninja`
