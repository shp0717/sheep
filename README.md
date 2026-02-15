# SHEEP

SHEEP is a esoteric programming language designed to be as difficult to understand and write as possible. It is based on the idea of using `SHEEP` as the only valid command.  
The language is Turing complete, meaning that it can theoretically compute anything that a Turing machine can. However, due to its extreme simplicity and lack of syntax, it is not practical for any real-world programming tasks.

## Commands

- `SHEEP`: This is the only valid command in the language. It means bit 1.
- Newline: This means bit 0.
- Other characters: These are not valid commands and will be throw an as errors.

## Hello World Example
A "Hello, World!" program in SHEEP is not a simple string of commands.  
Author said that the "Hello, world!" program in SHEEP is different on each OS, and it is not possible to write a single program that works on all OSes.
Author also did a "Hello, world!" program in SHEEP for MacOS, it is a 446 KB file and it has 280,457 lines.

## Installation
To run SHEEP programs, you need to have a SHEEP compiler. You can download the compiler source code from the [GitHub repository](https://github.com/shp0717/sheep).

## Usage
To compile a SHEEP program, use the following command:
```
sheep compile <source_file.sheep> <output_file>
```
To run a compiled SHEEP program, use the following command:
```
sheep run <source_file.sheep>
```
or:
```
chmod +x <output_file>; ./<output_file>
```
To generate a "Hello, World!" program for a specific OS, use the following command:
```
sheep print "Hello, World!"
```
To parse a C++ program into SHEEP, use the following command:
```
sheep parse <source_file.cpp> <output_file.sheep>
```
You can also use the `sheep decompile` command to decompile a compiled executable back into SHEEP source code:
```
sheep decompile <executable_file> <output_file.sheep>
```

## License
SHEEP has no license, but it is a open-source project, so you can use it and modify it as you wish.
