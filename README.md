# RCE (RaylibComponentEngine)
## About
This engine is built on top of the existing awesome game making library [raylib](https://www.raylib.com/). <br>
This framework uses CMake build system. <br>
I started building this library because I created a small game in unity, but I missed pointers and I didn't like the API, so I decided to build this (probably bug filled) framework, with the goal of making it as generic as I can, with people being able to create components and scenes using some simple `IScenes` and `IObjectComponent` interfaces (maybe) using the wonderful ideology of OOP.
## Creating a project
To create a project using RCE follow this steps:
1. Clone the repo with `git clone https://github.com/MeFiddzy/RCE.git` (to install git use `winget install Git.Get` on windows or linux `sudo apt install git`)
2. CD into the RCE dir `cd RCE` and (optional) rename he folder to your project name and the cmake project from `CMakeLists.txt`
3. Create a `cmake-build-debug` directory (`mkdir cmake-build-debug`), go into it (`cd cmake-build-debug`) and run `cmake ..` (to install cmake use `winget install Kitware.CMake` on windows or `sudo apt install cmake` on linux)
4. Build the project using make (`make`) or cmake (`cmake --build .`)
