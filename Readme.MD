# Rat in a Maze

**Rat in a Maze** – An autonomous warehouse robot simulator integrating **PathWeaver**, a modular pathfinding engine that supports multiple adaptive algorithms for optimized navigation.  

---

## Overview

This project is a **modular system** that simulates pathfinding in a maze-like environment. It is designed with **extensibility** in mind, leveraging **Singleton** and **Builder** design patterns for its core components.  

The system focuses on:
-  **Path generation**
-  **Congestion control**
-  **Deadlock removal**
-  **Environment simulation (Maze)**

---

## Architecture (Low-Level Design)

### Main Components

#### **RatInMazeSim**
- Entry point of the simulation.  
- Calls the **UNIT** module to initiate processing.  

#### **UNIT**
- Acts as the **mediator** between modules.  
- Delegates work to:
  - **PathWeaver Engine**
  - **Deadlock Removal**
  - **Maze**

#### **PathWeaver Engine** *(Strategy design pattern)*
- Responsible for **path generation**.  
- Can call:
  - **Congestion Control**
  - **Maze**

#### **Congestion Control**
- Ensures **optimal pathfinding under high traffic**.  
- Can call:
  - **Maze**

#### **Maze**
- Represents the **simulation environment**.  
- Can be called by:
  - **UNIT**
  - **PathWeaver Engine**
  - **Congestion Control**
  - **Deadlock Removal**

#### **Deadlock Removal** *(Singleton)*
- Handles **deadlock scenarios**.  
- Can call:
  - **Maze**

---

## Workflow

- RatInMazeSim -> UNIT

- UNIT delegates to:

    - PathWeaver Engine -> Congestion Control -> Maze

    - Deadlock Removal -> Maze

    - Maze directly when required


## Build and Run

### Build
```bash
g++ -std=c++17 \
    -I./src/Maze \
    -I./src/Unit \
    -I./src/PathWeaver \
    -I./src/CongestionControl \
    -I./src/DeadlockHandling \
    -o RatInAMaze RatInAMaze.cpp -pthread

./RatInAMaze
```

## Result

![robot in action](https://github.com/Mac16661/RatInAMaze/blob/main/RobotInAction.png?raw=true)

