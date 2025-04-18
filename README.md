# Generic ADT Framework in C – JerryBoree Daycare

This project implements a generic Abstract Data Type (ADT) framework in C, used to simulate a daycare management system for Jerries (from *Rick and Morty*). It includes dynamic storage, advanced memory handling, and a menu-driven CLI application.

The code demonstrates the use of generic programming in C through the design and integration of reusable data structures like linked lists, hash tables, and multi-value hash tables — all implemented from scratch.

---

## 🧩 Core Features

- **Generic ADT Interfaces** (`void*`-based with user-defined operations)
- **Modular Data Structures**:
  - Linked List
  - Hash Table
  - Multi-Value Hash Table
- **Dynamic Object Management**:
  - Jerries with custom IDs, happiness, origin planets, and characteristics
  - Planets and characteristics managed by configuration files
- **File-Driven Initialization**:
  - Reads structured configuration files to create data models
- **Interactive Simulation**:
  - CLI menu for interacting with Jerries (search, edit, remove, play, etc.)
- **Memory-Safe Design**:
  - Defensive coding practices and clear resource cleanup

---

## 📂 Folder Structure

```
project/
├── src/                    # Core implementation (.c files)
├── include/                # Header files (.h)
├── config/                 # Input files (text-based)
├── Makefile                # Build automation
├── README.md               # This file
```

---

## ⚙️ Building

To compile the project:

```bash
make
```

This will generate the `main` executable.

---

## 🚀 Running the Project

You can run the program with the following syntax:

```bash
./JerryBoree <numberOfPlanets> <configurationFile>
```

Example:

```bash
./JerryBoree 4 config/demo.txt
```

---

## 🛠️ Example Configuration File

```
Planets
Earth,123.1,8392,99.2
Gaia,983.223,8521,2312
Gazorpazorp,85.1,555.5,312
Pluto,3454.21,124.112,985.445

Jerries
23dF21,C-137,Earth,50
	Height:166.2
	LimbsNumber:4
	Weight:80
1q456,C-455,Earth,10
S5d2,V-234,Gaia,99
	Age:50
6e45,B-344,Pluto,34
	LimbsNumber:2
```

---

## 🔁 Example CLI Flow

1. Add a new Jerry  
2. Assign characteristics  
3. Play golf or interact with Fake Beth  
4. Search by characteristic proximity  
5. Automatically suggest sad Jerries  
6. Remove Jerries or traits  
7. Print all known planets or Jerries  
8. Close the system with proper memory cleanup

---

## 📌 Design Highlights

- **ADT-first design**: All logic is decoupled from specific data types
- **Plug-and-play architecture**: ADTs work with any type via function pointers
- **Multi-value map logic**: A hash table that supports multiple values per key
- **Full ownership model**: Functions know whether they should allocate, copy, or destroy data
- **Robust error handling**: Clear status codes for all failure points (`Memory_Problem`, `Invalid_Input`, etc.)

---

## 📜 License

This project is released under the MIT License – feel free to use it, share it, and adapt it freely with attribution.

---

## ✍️ Author

Developed by [Dor Benita](https://github.com/dorbenit) as part of an **Advanced  Programming** course, with an emphasis on low-level design, memory management, and modularity.
