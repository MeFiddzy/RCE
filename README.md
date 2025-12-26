# RCE (RaylibComponentEngine)

## About

RCE is a small **component-based game framework** built on top of the awesome game development library [raylib](https://www.raylib.com/).

It is written in **C++** and uses **CMake** as its build system.

I started building this engine after making a small game in Unity. I missed **pointers**, disliked the API design, and wanted something closer to the C++ / OOP style I enjoy working with. The result is RCE — a (probably bug-filled) framework focused on:

* Explicit ownership and lifetimes
* Simple and extendable **OOP-based architecture**
* Custom **components** and **scenes**
* Minimal magic, maximum control

The goal is not to compete with full engines, but to provide a **learning-oriented**, hackable framework that stays close to the metal.

---

## Features

* Built on top of **raylib**
* Component-based object system
* Scene management via interfaces
* Simple physics and collision support
* Minimal abstraction overhead
* Cross-platform (Windows / Linux)

---

## Core Concepts

### Scenes

Scenes represent **game states** (menu, level, game over, etc.).

To create a scene, implement the `IScene` interface:

* `onSceneLoad`
* `onSceneTick`
* `onSceneUnload`

Scenes own and manage objects and systems.

---

### Objects

Objects are entities that exist in the world (players, balls, blocks, paddles).

Each object:

* Has a position, size, color, and Z-order
* Can have **multiple components**
* Is stored and managed by the active scene

---

### Components

Components add **behavior** to objects.

Examples:

* Physics (`MiniPhysicsComponent`)
* Hitboxes (`HitboxComponent`)
* Custom gameplay logic

To create a component, inherit from `IObjectComponent` and override `onTick`.

This allows:

* Clean separation of logic
* Easy reuse across objects
* Minimal inheritance chains

---

### Systems

Systems operate at the **scene level**, not per-object.

Examples:

* Block spawning systems
* Enemy wave systems
* Global movement or scrolling logic

Systems are useful when behavior affects **multiple objects at once**.

---

## Creating a Project

1. Clone the repository

```bash
git clone https://github.com/MeFiddzy/RCE.git
```

* Install git:

    * Windows: `winget install Git.Git`
    * Linux: `sudo apt install git`

2. Enter the directory

```bash
cd RCE
```

(Optional) Rename the folder and update the project name in `CMakeLists.txt`.

3. Create a build directory

```bash
mkdir cmake-build-debug
cd cmake-build-debug
```

4. Generate build files

```bash
cmake ..
```

* Install CMake:

    * Windows: `winget install Kitware.CMake`
    * Linux: `sudo apt install cmake`

5. Build the project

```bash
cmake --build .
```

(or on Linux)

```bash
make
```

---

## Examples

The repository includes example games demonstrating:

* Basic object creation
* Physics and collision
* Scene transitions
* Simple gameplay systems

These are the **best place to start** when learning how RCE works.

---

## Known Limitations

* No serialization system (working on it)
* No C compatibility (pure OOP)
* APIs may change frequently
* Limited documentation