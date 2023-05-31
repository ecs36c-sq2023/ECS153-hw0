# Homework 0

> Due: 06-09-2023 11:59:59 PM

The goal of this homework is for you to

- setup and get familiarized with the development environment, build tools, and
  homework submission process;
- review C basics by implementing a generic quick sort.
- get familar with C pointers

## Table of Contents

1. [Homework Spec](#homework-spec)
2. [Setup Dev Env & Run/Debug Your Program](#setup-dev-env--rundebug-your-program)
3. [CMakeFiles](#cmakefiles)
4. [Submission](#submission)

## Homework Spec

### Introduction

There are many use cases where the data and the algorithms are separated. 
The algorithm only needs a few guarantees from the data, and that's it. 
Sorting is one example.
Sorting is one of the most important algorithms in computer science. 
To sort an array of objects, all you need to know is how to compare two objects. 

Some programming languages can provide for such needs. For example, `Trait` in Rust and `Interface` in Java. 
Instead of defining data fields, they only contain methods that you can use. 
An algorithm can declare the `Trait` it needs ([Trait Objects](https://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/book/first-edition/trait-objects.html) in Rust). 
Any struct/class that satisfies a `Trait` or `Interface` can then be automatically adapted to this algorithm.

But C doesn't have such design...

Really?
C is a powerful language famous for running the world. 
Many high-level features in OOP can be implemented in C... if you are good enough with pointers. 
If you still don't believe it, just think about how inheritance is implemented in C++: Ah yes, [v-table](https://en.wikipedia.org/wiki/Virtual_method_table)!

All we need is something similar to a v-table. 
Imagine all structs have a bunch of function pointers. 
Then, even if we are facing a bunch of `void *`s, we can still call the functions using offsets. 
These functions can do a lot of things, including comparing the current object (`this` or `self`) with the other.

### File description

In this homework, we will write a quicksort as a warm-up to a lot of things, i.e. algorithms, C, CMake, etc. 
Even better, we would implement sorting with as little knowledge of the type as possible. 
Simply put, the algorithm barely knows what it is sorting! 
Well... it does know how to compare two objects.

You will implement the following:

- Quicksort (`quick_sort.c`)
- Four structs, each has a very different layout, yet all of them can be sorted by the quicksort you wrote.
- A quicksort driver (`main.c`). You will read from the input stream to create the structs, sort them, and print them out.
Here are descriptions of the files:

- `GenericTraits.h`/`GenericTraits.c` provides a bunch of functions that each of the structs needs to implement.
You can think of "Traits" as contracts, they provide a guarantee to your sorting algorithm and driver as to what can be done about the structs.
  - `new`: Generate a new struct based on a string.
  - `dump`: Prints the details of the struct to a file stream. All `dump` should put an extra `\n` when finished.
  - `cmp`: Compares two instances, returns positive number if larger, negative number is smaller, 0 if equal.
  - `drop`: Free the memory allocated to this instance.
- `Int.h`, `Student.h`, `Human.h`, `Rectangle.h` are four structs you need to implement.
  - `Int` is nothing but a wrapper over `int32_t`. `Int` is sorted based on its value. `Int.h` has an example definition.
  - `Human` only have one field `name`, which should be a string. `Human` is sorted based on its name.
  - `Student` inherits from `Human`, it has an extra field called `grade`. 
  - `Rectangle` contains some macro tricks.
- `quick_sort.c`: Where your sorting algorithm stays, you will sort them in decending order.
- `main.c`: The driver to read the file, create objects, call `quick_sort`, and print.
- All the rest C files: The definition of your structs.
- `CMakeLists.txt` will compile the whole project. 

### Input and Output specifications

- The first line of the input contains the name of your struct.
- The second line contains `n`, which is the number of objects in this file.
- The following `n` lines describe the objects, one line each. The specific specification of objects can be found in the following sections.
- The input file ends with an extra `\n`.

### Programming guide

It's not a must, but its recommended that you follow this guide.

Implement `quick_sort.c` first. 
You should sort the array IN PLACE, in descending order. 
Because this algorithm is so basic (also so openly available), you won't get any credit for finishing this. 
We have already given you declarations, telling you that there are `n` objects, each object satisfies `GenericTraits` in `quick_sort.h`.

Then, let's work with a basic `int32_t` wrapper called `Int`. We have provided an example definition of `Int` in `Int.h`, you can use it.
- `new` will convert a line of string to an integer. The input is guaranteed to be valid.
- `dump` should output the hexadecimal format that starts with `0x`.

Once you finished `Int`, let's try to put them together in `main`!
You will read from a file, construct objects from the string you read, call `quick_sort` and print the objects to the file.
You will get 10% if you get everything up till here right.

When you're finished with `Int`, you can move on to the more complicated `Human`. 
`Human` has a `name`, which is a bunch of characters WITHOUT SPACES (' ') OR LINE BREAKS ('\n'). 
The input may contain extra spaces and/or `'\n'` at the end, which you should remove. 
`name` should not be longer than `MAX_LEN - 1`, which is 256 bytes. But there is a trailing `\0` to end the string, that means there are at most 255 characters in the `name`. Anything more than that should be removed.
The input may also contain some words concatenated together by spaces, but you should only use the first word. You can use `strcmp` to compare the strings.
You will get 20% if you finish `Human` correctly, extra 20% if your code is memory safe.
To detect memory safety, we use AddressSanatizer (ASan) to detect memory leaks, double free, and buffer overflows.
You can ask `CMake` to generate a `Makefile` that copmiles your code against ASan by: `cmake -DCMAKE_BUILD_TYPE=asan ..`

`Student` inherits from `Human`.
Each line will have a `name` and `grade` separated by ONE space. `grade` is guaranteed to be an integer.
You should sort `Student` by `grade` first. If the `grades` are equal, compare their `names` using `human`.
When `dump`, you should put the `name` first, then a space ` `, followed by the `grade`.
You will get 10% if you finish `Student` correctly, extra 20% if your code is memory safe.

Finally, you may have realized that much of the code in the previous structs is repeated. 
In `Rectangle`, we attempted to remove this repetition by using macros. Look into `DECLARE_STRUCT` and `DEFINE_STRUCT` in `GenericTraits`. 
Once you understand them, you should be able to declare `Rectangle` in less than 5 lines in `Rectangle`.h, and the implementation of `Rectangle` should be less exhaustive. 
Each line of input contains two integers separated by ONE space, representing `height` and `width`, respectively. It's guaranteed that `height` and `width` will be non-negative.
When using `dump`, you should use the same format as the input. 
`Rectangle`s are sorted based on their area. If two objects have the same area, compare their `heights`. If their `heights` are also the same, compare their `widths`.
Your `Rectangle.h` and `Rectangle.c` will only be graded if `DECLARE_STRUCT` and `DEFINE_STRUCT` are used.
You will get 20% if you finish `Rectangle` using the marcos we provided, and the code has no memory errors.

### Requirements

- For C and header files, you SHOULD NOT modify any code unless you see `/* Your code here ... */` or something similar. Specifically, you SHOULD NOT modify:
  - Any function declarations.
  - Any `#include`, the files have enough `#include` to write the code. Even if `main.c` doesn't include any struct definitions, with smart function pointers you can work that around.
- You may modify `CMakeLists.txt` as you wish.
  - Try not to change compiler settings, but you can modify it for debuggin purposes.
  - You should remove the files you didn't finish to avoid a compiler failure.

### Submitting your Homework

- Run `./generate_submission.sh` to create a zip file `hw0-submission.zip`.
- Transfer `hw0-submission.zip` to your host (if necessary).
  - If you are in VS Code with Dev Container / Remote SSH / WSL2, you can right
    click on `hw0-submission.zip` and click `Download`.
  - If you are using a terminal, you can use `scp` or `sftp`.
- Submit `hw0-submission.zip` on Gradescope.

## Setup Dev Env & Run/Debug Your Program

Use one of the following options to setup your environment.

> ⚠️ If you're a student, **DO NOT FORK** this repository because you cannot
> change the visibility of a forked repo to private. If you plan to use Git for
> version control (which is encouraged), run `rm -rf .git && git init` after
> setting up using one of the options below and push to your **private**
> repository. Any public repository containing part of this homework solution
> will be reported to SJA.

### Option 1: VS Code with Local Dev Container

> This option provides a Graphical User Interface (GUI) for code editing and
> debugging.

> This option does not require internet connection when coding after initial
> setup.

- Install/update the following software on your local OS:

  - [WSL2](https://learn.microsoft.com/en-us/windows/wsl/install) (Required for
    Windows only) (Docker will use WSL2 as backend on Windows)
  - [Docker Desktop](https://www.docker.com/products/docker-desktop/)
    - Make sure you install the correct version based on your hardware
      (especially for Apple-chip powered Macbook and ARM-based Windows PC)
  - [Visual Studio Code](https://code.visualstudio.com/)

- Start Docker Desktop and keep it running in the background.

- Click the following button to setup the environment.

  [![Setup Local Dev Container](https://img.shields.io/static/v1?label=Local%20Dev%20Container&message=Setup&color=blue&logo=visualstudiocode)](https://vscode.dev/redirect?url=vscode://ms-vscode-remote.remote-containers/cloneInVolume?url=https://github.com/ecs36c-sq2023/ECS153-hw0)

- When asked for selecting a Kit to configure CMake, choose **GCC**.

- Click **Run -> Start Debugging** to run the program.

  - project is automatically (re)built (no need to run `make` or `cmake`
    initially or after making code modifications).
  - you can supply command line args in `.vscode/launch.json` through `args`
    array.
  - you may set breakpoints by hovering over the left of each line number and
    click the red dot.

### Option 2: VS Code with CSIF

> This option provides a Graphical User Interface (GUI) for code editing and
> debugging.

> Connecting to CSIF computer may require UC Davis Library VPN.

- Install/update the following software on your local OS:

  - [Visial Studio Code](https://code.visualstudio.com/)
  - [Remote SSH Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-ssh)

- Open **VS Code**

- Click the little green button in the bottom-left corner of the window to open
  **Remote - SSH** extension

- Click **Remote-SSH: Connect to Host...**

- Select **csif** if you configured
  [Passwordless Login to CSIF](https://github.com/HazyFish/ucdavis-csif-passwordless)

  - If not, in the textbox prompted, enter `username@pcXX.cs.ucdavis.edu` (you
    need to replace `username` and `XX`), press **enter**, and then enter your
    password for CSIF

- Wait for VS Code to install VS Code Server on CSIF automatically

  - VS Code Server will be installed in `/home/<username>/.vscode-server` so
    other users don't have access to it
  - Retry if you get any error

- Install **C/C++ Extension Pack** (on Remote Server)

- Open an integrated terminal inside VS Code (**Terminal Menu** -> **New
  Terminal**)

  - Notice that this terminal is already connected to the CSIF

- Run the following command inside the integrated terminal

  `git clone https://github.com/ecs36c-sq2023/ECS153-hw0 ECS153-hw0`

- Run `code ./ECS153-hw0` to open the folder

- When prompted to configure CMake, confirm and choose **GCC** when prompted for
  kit selection.

- Click **Run -> Start Debugging** to run the program.

  - project is automatically (re)built (no need to run `make` or `cmake`
    initially or after making code modifications).
  - you can supply command line args in `.vscode/launch.json` through `args`
    array.
  - you may set breakpoints by hovering over the left of each line number and
    click the red dot.

### Option 3: Terminal with CSIF

> This option works but you will have to use print statements or command-line
> `gdb` for debugging. It is recommended that you try one of the other options
> to have more efficient, developer-friendly way of debugging.

> Connecting to CSIF computer may require UC Davis Library VPN.

- SSH into a CSIF computer

- Run the following commands

  ```bash
  git clone https://github.com/ecs36c-sq2023/ECS153-hw0 ECS153-hw0
  cd ./ECS153-hw0/src
  mkdir build
  cd build
  cmake ..
  make
  ```

- To rebuild after code modification, run `make` in `build` folder.

- To run the program, run `./main [INPUT_FILE] [OUTPUT_FILE]` in `build` folder.

### Other Options

You could use other options such as running it directly on your macOS or WSL2,
but you'll be responsible for having the correct build tools and making sure
your submission works on Gradescope.


## CSIF Docs

Information about using CSIF computers, such as how to remotely login to CSIF
computers from home and how to copy files to/from the CSIF computers using your
personal computer, can be found at
[http://csifdocs.cs.ucdavis.edu/about-us](http://csifdocs.cs.ucdavis.edu/about-us)
csif-general-faq.

# Submission

To submit your homework, you need to run `./generate_submission.sh` to generate a zip file. Make sure that the zip you got contains your code in it.
Then submit it to gradescope.
