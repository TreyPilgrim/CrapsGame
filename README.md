# 🎲 Modular Craps Simulation (C++)

A fully modular, object-oriented simulation of the classic casino game **Craps**, written in C++. Built to support multiple players, diverse bet types, real-time game logic, and extensibility for future AI and embedded systems integration.

---

## 🧠 Features

- 🎯 **28+ Polymorphic Bet Types**  
  Each bet (e.g., Pass Line, Don't Pass, Come, Horn) is implemented as a class extending a shared interface for consistent handling and easy scalability.

- 🌲 **AVL Tree for Bet Management**  
  Custom AVL self-balancing tree handles active bets for each player with guaranteed **O(log n)** lookup time, enabling responsive gameplay even as bet volume increases.

- 💾 **Smart Pointer Architecture**  
  Fully managed memory via `std::shared_ptr`, ensuring safe and automatic cleanup of dynamic objects across the game engine.

- 🛠 **Modular Architecture**  
  Organized by responsibility using subdirectories (e.g., `/bets`, `/players`, `/engine`) with custom `CMakeLists.txt` for modular builds and clear separation of concerns.

- 🤖 **Multiplayer-Ready & AI Scalable**  
  Codebase designed for multiple players with hooks in place for future multithreaded AI player simulation and embedded system compatibility.

---

## 🧱 Tech Stack

- **Language:** C++17
- **Build System:** CMake
- **Memory Management:** STL + Smart Pointers
- **Data Structures:** AVL Tree, Linked Lists
- **OOP Concepts:** Polymorphism, Encapsulation, Inheritance

---

## 👷‍♂️ Project Structure

Modular-Craps-Simulator/
├── CMakeLists.txt
├── /src
│ ├── /bets # All bet types (Pass, Come, Horn, etc.)
│ ├── /engine # Core game logic, bet manager, dice roller
│ ├── /players # Player objects and wallets
│ └── /utils # Logging, input handling, math helpers
├── /include # Public headers
├── /tests # Test cases and stubs (WIP)
└── README.md

---

## 🚀 Getting Started

### ✅ Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- CMake 3.10+

### 🔧 Build Instructions

```bash
# Clone the repo
git clone https://github.com/TreyPilgrim/CrapsGame
cd CrapsGame

# Create a build directory
mkdir build && cd build

# Generate the Makefile with CMake
cmake ..

# Build the project
make

# Run the executable
./CrapsGame
```
