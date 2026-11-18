# Everybody Codes 2026

My solutions to the [Everybody Codes](https://everybody.codes) 2026 event, a set of programming puzzles ("quests") released over the course of the event.

Each quest lives in its own directory (`q1/`, `q2/`, ...) and is built as a library. A single `lotw` executable links them all together and picks which quest to run from the command line.

## Requirements

- CMake 3.28 or newer
- A C++20 compiler (the build is currently set to `clang++`)
- Ninja (optional, but recommended)

## Building

From the repository root:

```bash
cmake -S . -B build -G Ninja   # configure (only needed once, or after changing CMake files)
cmake --build build            # build
```

Drop `-G Ninja` to use Make instead. Add `-v` to the build command to see the full compiler commands.

## Running

Run from the repository root, since input files are loaded by paths relative to it (for example `q1/pinecones.txt`):

```bash
./build/lotw 1        # run quest 1
./build/lotw q1       # same thing
./build/lotw quest1   # same thing
./build/lotw -a       # run every quest
```

## Project layout

```
.
├── CMakeLists.txt    # top-level build; adds each quest directory and links it into lotw
├── main.cpp          # argument parsing and quest dispatch
└── qN/
    ├── CMakeLists.txt  # builds the questN library
    ├── quest.hpp       # the quest's public interface (qN::quest())
    ├── quest.cpp       # the solution
    ├── README.md       # notes on the approach
    └── *.txt           # puzzle input
```

## Adding a new quest

1. Create `qN/` with a `CMakeLists.txt` that defines a library named `questN`.
2. Add `add_subdirectory(qN)` to the top-level `CMakeLists.txt` and add `questN` to `target_link_libraries`.
3. Add a `QuestType` value and a dispatch case in `main.cpp`.
