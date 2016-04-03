# Parallel Computing Lab 2: Generating Prime Numbers
By Jason Yao, [github](https://github.com/JasonYao/Parallel-Computing-Lab-2-Generating-Prime-Numbers)

## FOR THE GRADER: 
This README utilises github's markdown, and is a much easier read on the github website listed above.

Link: https://github.com/JasonYao/Parallel-Computing-Lab-2-Generating-Prime-Numbers

For my conclusion, please see [here](CONCLUSION.md)

## Description
This program is designed to generate a list of prime numbers from [2, N], where `N` is
an integer value >= 2.
Both parallel and sequential versions of this code are provided in the source, and can easily be toggled.

## Compilation & Running
### To compile the code and test against an input automatically
To change the input, simply change `nValue="10"` to whatever `N` value you would like to serve as the upper bound.
```sh
./compileAndTest
```

### To compile and run the code manually
```sh
gcc -g -Wall -o -std=c99 <output_file_name> <source_file_name>
./<output_file_name> <N_value_upper_bound> <number_of_threads>
```

e.g. To compile and find prime numbers up to 100 with 10 threads
```sh
gcc -g -Wall -o -std=c99 genprime genprime.c
./genprime 100 10
```

Where:
- `gcc` is the name of the `GNU Compiler Collection` that will compile, 
and link the libraries required for the source code to run.

- `-g` is a flag to produce debugging information

- `-Wall` is a flag to turn on all warnings

- `-o` is to signify the output binary

## Debugging version
If you'd like to run the debugging version of the code irrespective of the other flags, please edit the source file [gs.c](gs.c) and change line **12** from

```sh
bool IS_DEBUG_MODE = false;
```
to
```sh
bool IS_DEBUG_MODE = true;
```
then compile again before running

## Sequential version
If you'd like to run the sequential version of the code instead, please edit the source file [gs.c](gs.c) and change line **13** from

```sh
bool IS_SEQUENTIAL_MODE = false;
```
to
```sh
bool IS_SEQUENTIAL_MODE = true;
```
then compile again before running

## Timed version
If you'd like to run the timed version of this code, irrespective of the other flags, please edit the source file [gs.c](gs.c) and change line **14** from

```sh
bool IS_TIMED_MODE = false;
```
to
```sh
bool IS_TIMED_MODE = true;
```
then compile again before running

## License
This repo is licensed under the terms of the GNU GPL v3, a copy of which may be found [here](LICENSE).
