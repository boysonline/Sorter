# Sorter (Console Game)

A high-performance, object-oriented console puzzle game written in C++. The project features a custom grid-based rendering engine, physics/world state collision handling, dynamic object factory patterns, and a robust unit testing suite using the Catch2 framework.

## Tech Stack & Concepts

* **Language:** C++ (C++17 or higher recommended)
* **Testing Framework:** Catch2 (Amalgamated)
* **Architecture Patterns:**
    * **Factory Pattern:** Decouples object generation from runtime world layout (`box_factories`).
    * **Separation of Concerns:** Distinct separation between simulation state (`world`, `state`), entities (`player`, `boxes`, `objects`), and terminal output manipulation (`renderer`).
    * **Unit Testing:** Comprehensive behavioral test coverage verifying coordinate logic, entity interaction, and state transitions independently of terminal rendering.

---

## Project Structure

```text
.
├── .vscode/               # Local IDE task execution and build automation configurations
│   ├── settings.json
│   └── tasks.json
├── build/                 # Compiled binaries target directory
│   ├── Sorter.exe         # Main game execution binary
│   └── UnitTests.exe      # Test runner execution binary
├── src/                   # Application source and header dependencies
│   ├── boxes.cpp / .h     # Interactive container/box entities logic
│   ├── box_factories.cpp  # Creational patterns managing specialized box entities
│   ├── main.cpp           # Game initialization loops and runtime coordination
│   ├── objects.cpp / .h   # Item specifications and auxiliary static/dynamic entities
│   ├── player.cpp / .h    # User mechanics, movement vectors, and action logic
│   ├── renderer.cpp / .h  # Console screen double-buffering / frame output matrix
│   ├── state.h            # Global phase definitions, menus, and level state structures
│   ├── world.cpp / .h     # Coordinate management, grid layout parsing, and rigid collisions
└── test/                  # Test suite suite configurations
    ├── catch_amalgamated.cpp/.hpp # Standalone monolithic distribution of Catch2
    └── tests.cpp          # Behavioral assertion scripts for game components
```

---

## Build and Execution

1. **Prerequisites**
GCC/G++ Compiler with support for C++17 or higher.

make utility or configure manually via the provided VS Code automation scripts inside .vscode/tasks.json.

2. **Compilation**
To build the executable targets manually, execute compilation via terminal commands:

Compile Main Console Game Target:

```Bash
g++ -std=c++17 src/*.cpp -o build/Sorter.exe
```

Compile Behavioral Test Target Suite:

```Bash
g++ -std=c++17 src/boxes.cpp src/box_factories.cpp src/objects.cpp src/player.cpp src/world.cpp test/catch_amalgamated.cpp test/tests.cpp -Isrc -Itest -o build/UnitTests.exe
```

3. **Execution**
Launch Game Simulation:

```Bash
./build/Sorter.exe
```

Run Unit Verification Testing Suite:
```Bash
./build/UnitTests.exe
```
