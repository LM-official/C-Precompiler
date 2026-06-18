<div align="center">

# ⚙️ C Precompiler

**A preprocessor for the C language, written in pure C with no external dependencies.**
It resolves includes, strips comments, compacts the source
and produces a detailed report on identifier validity.

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square)
![Build](https://img.shields.io/badge/Build-Make-orange?style=flat-square)
![Dependencies](https://img.shields.io/badge/Dependencies-none-4c1?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-lightgrey?style=flat-square)

</div>

---

## 📖 What it does

Reads a C source file and produces a pre-processed version of it. In particular:

- **🔗 Recursive `#include` resolution** — quoted directives (`#include "file.h"`) are expanded inline, even when nested. Angle-bracket includes (`#include <stdio.h>`) — typical of the standard library — are left intact.
- **🛡️ Multiple-inclusion guard** — a file that has already been included is not expanded a second time.
- **✂️ Comment removal** — strips both line comments (`//`) and block comments (`/* ... */`).
- **📏 Compaction** — removes the lines left empty after comment removal.
- **🔍 Identifier checking** — analyzes variable declarations and verifies that identifiers follow the C language rules, pinpointing the exact position of the first illegal character.
- **📊 Statistics** — with the verbose option it prints a tree report with bytes, lines, removed comments and the validation result of every variable.

> 🗣️ The pre-processed output is written to **stdout** (or to a file with `-o`), while the statistics are printed to **stderr**: the two streams are therefore separable and can be redirected independently.

---

## 🗂️ Project structure

```
.
├── README.md
├── assignment.md		# the project assignment
├── LICENSE
├── Makefile            # build, run, test and clean targets
├── src/
│   ├── main.c          # entry point: orchestrates the pipeline and frees resources
│   ├── functions.h     # data structures and function declarations (documented)
│   └── functions.c     # implementation of all the functions
└── tests/
    ├── test1.c / .h    # test case: variables, comments, nested includes
    ├── test2.c / .h    # test case: pointer arithmetic, angle-bracket includes
    └── test2.1.h       # empty included file (inclusion chain)
	│
	...
```

---

## ⚙️ Building

The project has no dependencies: a C compiler and `make` are enough.

| Command | Action |
| :------ | :----- |
| `make` | 🔨 Builds the `./cpre` executable |
| `make run` | ▶️ Builds and runs a demo on `test1.c` |
| `make test` | 🧪 Builds and runs the demo on all the test files |
| `make clean` | 🧹 Removes every generated file (build artifacts + runtime output) |

Alternatively, manual compilation:

```sh
gcc -Wall -o cpre src/main.c src/functions.c
```

To wipe every generated file — build artifacts (`cpre`, `src/*.o`) and runtime output (`o.txt`, `output.c`, `*.out`) — restoring the project to its source-only state:

```sh
make clean
```

---

## 🚀 Usage

```
cpre (-i FILE | --in=FILE) [-o FILE | --out=FILE] [-v | --verbose]
```

| Option | Description |
| :----- | :---------- |
| `-i FILE`, `--in=FILE` | Input file to pre-process. **Mandatory.** |
| `-o FILE`, `--out=FILE` | Output file. If omitted, the result is written to `stdout`. |
| `-v`, `--verbose` | Prints the processing statistics to `stderr`. |

Examples (run from inside `tests/`, see the note below):

```sh
cd tests

# Output to screen
../cpre --in=test1.c

# Output to file, statistics to screen
../cpre -i test1.c -o output.c -v

# Output only (statistics discarded)
../cpre --in=test1.c -v 2>/dev/null > output.c

# Statistics only (output discarded)
../cpre --in=test1.c -v 2>&1 >/dev/null
```

> ⚠️ **A note on paths.** Quoted includes are resolved relative to the *current working directory*, not to the location of the file that contains them. That is why the test files must be processed from inside the `tests/` folder (the `make run` and `make test` targets do this automatically).

---

## 🧪 Example

Given `test2.c`, which declares some pointers with invalid identifiers (`nptr^1`, `nptr^2`) and includes `test2.h`:

**Statistics** (`stderr`):

```
STATISTICS:
1 included files:
	└── test2.c:
		├── 546 bytes
		├── 37 lines kept
		└── 13 comment lines removed

Output: 271 bytes, 13 lines

6 variables checked

3 valid variables:
	└── test2.c:
		├── line 5, n
		├── line 6, nptr
		└── line 7, addrcopy

3 errors detected:
	└── test2.c:
		├── line 6, nptr^1
		│	        ^~
		├── line 6, nptr^2
		│	        ^~
		└── line 33, 0
			     ^
```

The `^~~~` cursor points exactly at the first invalid character of the reported identifier.

---

## 🔬 How it works

Processing is a four-stage pipeline, orchestrated by [`main.c`](src/main.c):

1. **`file_include`** — opens the input file, removes its comments, checks its variables (in verbose mode) and recursively resolves every `#include "..."`, concatenating the text of the child files into the parent. It progressively updates the statistics.
2. **`file_compacter`** — removes from the resulting text every line left without content.
3. **`print_output`** — writes the result to a file or to `stdout`.
4. **`print_statistics`** — if requested, prints the tree report to `stderr`.

---

## ✅ Identifier validation rules

An identifier is considered **valid** when it satisfies all the C language rules (`check_variable` in [`functions.c`](src/functions.c)):

- the first character is a letter or an underscore (`_`);
- the following characters are letters, digits or underscores;
- it does not match a reserved C keyword;
- it is not longer than 31 characters.

On error, the index of the **first** illegal character is stored, then used to position the cursor (`^~~`) in the report.

---

## 🧱 Architecture

The main data structures are defined in [`functions.h`](src/functions.h):

| Struct | Role |
| :----- | :--- |
| `Mods` | Command-line options (input, output, verbose). |
| `Stats` | Root of the statistics: dynamic array of analyzed files. |
| `File` | Statistics of a single file: name, bytes, lines, comments, variables. |
| `Var` | A variable: name, line, index of the first error (`-1` if valid). |
| `List_var` | Dynamic list of variables extracted from a single instruction. |

The functions are grouped by responsibility (statistics, error handling, string utilities, basic file I/O, advanced processing, variable analysis) and each one is documented in Doxygen style in the header.

---

## ⚠️ Notes & limitations

- Only quoted includes (`"..."`) are expanded; angle-bracket ones (`<...>`) are intentionally preserved.
- Identifier checking runs only in verbose mode (`-v`).
- The declaration parser is heuristic and meant for educational purposes: it covers the test-file cases but not the whole C grammar.

---

## 👥 Authors

C Precompiler was designed and built by:

- **[LM-official](https://github.com/LM-official)**
- **[Pierba](https://github.com/Pierba)**
- **[ItsSpicci](https://github.com/loremicci)**

---

## 📄 License

Released under the MIT License. See [LICENSE](LICENSE).