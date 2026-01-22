# Longana

**ACADEMIC INTEGRITY WARNING**
> This repository contains code developed for a university course. It is uploaded for portfolio and archival purposes only.
> **Current Students:** Do not copy or reference this code for your own assignments. Doing so may violate your university's academic integrity policy.

### Overview
This project involves developing a **Longana Dominoes** game engine in C++.
The program simulates a tournament between a **Human** player and a **Computer** opponent, enforcing complex placement rules and managing game state across multiple rounds.

### Project Goal
To design and implement:
- A **polymorphic game engine** that manages turn-based logic for different player types.
- A **computer** that analyzes the board state to make optimal moves or assist the human player.
- A **serialization system** to save and resume tournaments from text files.

### Technologies
- **Language:** C++

## Requirements
#### Game Engine
- Must implement the full rules of **Longana** (a variant of Dominoes).
- Must manage specific game mechanics:
  - **Engine Rotation:** Rounds start with specific doubles (6-6, 5-5, etc.) in descending order.
  - **Placement Logic:** Enforce specific placement rules for Left (Human) vs. Right (Computer) sides, including "Cross-wise" doubles.
  - **Turn Management:** Handle drawing from the boneyard, passing turns, and detecting round winners based on pip counts.

#### System Architecture
- Must utilize **Object-Oriented Design** with at least 7 distinct classes:
  - **`Layout`**: Manages the board state using a Double-Ended Queue (`std::deque`).
  - **`Player` (Base Class)**: Abstract class defining the interface for moves.
  - **`Human` / `Computer`**: Polymorphic derived classes implementing input validation and AI strategy.
  - **`Hand`, `Stock`, `Round`, `Tournament`**: Classes for state management.
- Must implement **Serialization**:
  - Ability to suspend the game after any move.
  - Save the exact state (Hands, Board, Scores, Boneyard) to a text file.
  - Resume the game by parsing the file and reconstructing the objects.
 
#### User Interface (ASCII)
- Must provide a clear command-line interface.
- **Help Mode**: The computer must be able to suggest the "Best Move" for the human player upon request.
- **Visuals**: Display the layout clearly, marking **L** (Left) and **R** (Right) endpoints.

---

## Game Rules Summary
* **Objective:** Reach the Tournament Score by winning rounds (lowest pip count remaining).
* **Setup:** 28 tiles (Double-six set). 8 tiles per player.
* **Placement:**
    * **Doubles:** Can be played on *either* the Left or Right side.
    * **Non-Doubles:** Can normally only be played on *your* designated side.
    * **Exception:** If the opponent **Passed**, you may play on *either* side.
