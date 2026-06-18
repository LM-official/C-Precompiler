# Assignment — C Pre-Processor

## Project Description

Develop an application that, given a file containing C code, processes it as follows:

1. **Resolve `#include` directives** — expand the content of the files referenced by each `#include` directive inline;
2. **Check for invalid variable names** — detect identifiers that are not valid (e.g. `x-ray`, `two&four`, `5brothers`);
3. **Remove all comments**;
4. **Produce an output file** containing the modified code — i.e. the input file expanded with includes and stripped of comments;
5. **Produce processing statistics** as described in the Specifications section.

---

## Assumptions

You may assume that:

1. Files included via `#include` are stored in the current working directory (CWD);
2. The input C file consists only of the `main` function body — no other functions are present;
3. All local variables are declared at the beginning of `main` on contiguous lines, and global variables are declared before `main` on contiguous lines;
4. The data types used in variable declarations are correct.

---

## Specifications

### 1. Input

The program accepts three input parameters:

| Short | Long        | Description                              |
|-------|-------------|------------------------------------------|
| `-i`  | `--in`      | Specify the input file                   |
| `-o`  | `--out`     | Specify the output file                  |
| `-v`  | `--verbose` | Enable/disable processing statistics output |

The input file is **mandatory** and can be passed as a positional argument or via `-i`/`--in`. Examples:

```bash
myPreCompiler input.c
myPreCompiler -i input.c
myPreCompiler --in=input.c
```

---

### 2. Output

Two output modes are supported:

- **File output:** use `-o`/`--out` to write the processed code to a file.
- **Stdout output:** if `-o` is omitted, the result is printed to stdout.

Examples:

```bash
myPreCompiler -i input.c -o output.c     # writes processed code to file
myPreCompiler -i input.c                 # prints processed code to stdout
myPreCompiler input.c                    # prints processed code to stdout
myPreCompiler -i input.c > output.c      # stdout redirected to file
```

#### Processing Statistics (enabled with `-v` / `--verbose`)

When verbose mode is active, the program prints to stdout:

- Number of variables checked
- Number of errors detected
- For each error: filename and line number where it was found
- Number of comment lines removed
- Number of files included
- For the input file: size in bytes and number of lines (before processing)
- For each included file: size in bytes and number of lines (before processing)
- Number of lines and size of the output

```bash
myPreCompiler -v -i input.c -o output.c   # prints stats to stdout
myPreCompiler -i input.c -o output.c      # no stats printed
```

> **Optional:** Output statistics to **stderr** instead of stdout, so that the processed code and the statistics can be redirected to two separate files simultaneously.

---

### 3. Error Handling

The application must handle the following errors:

- Invalid command-line options or arguments
- Failure to open the input file or any `#include`-referenced file
- File close errors
- File read errors (e.g. empty or corrupted file)
- File write errors

---

### 4. Program Structure & Memory

- The program must **not** be monolithic — it must be composed of a `main` and several functions implementing core and support functionalities.
- The code must be organized in **at least three files**:
  - One file containing `main`
  - At least one file containing helper functions
  - At least one header file (`.h`)
- **Dynamic memory allocation** should be preferred when choosing data structures.
- At the exam, the code must be compilable from the command line using `gcc`.

---

### 5. Testing

The program must be tested using:

- A pool of test files provided by the instructor (see attached files — more to follow);
- A custom test case developed by the group members.
