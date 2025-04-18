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
├── config/                 # Example input files (text-based)
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
./main <expected_number_of_planets> <path_to_configuration_file>
```

Example:

```bash
./main 6 config/demo.txt
```

---

## 🛠️ Sample Configuration Format

```
Planets
Earth,0.0,0.0,0.0
Gazorpazorp,5.0,6.0,7.0

Jerries
Jerry-001,Dimension-C137,Earth,75
    hair:2.0
    iq:88.3
Jerry-002,Dimension-J19,Earth,60
    strength:3.5
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

This project is released under the **MIT License** – feel free to use, share, and extend!

---

## ✍️ Author

Developed by [Dor Benita](https://github.com/dorbenit) as part of a university data structures course, with an emphasis on low-level design, memory management, and modularity.
