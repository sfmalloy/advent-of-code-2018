**NOTE:** This repository is now archived. Please use [my solutions monorepo](https://github.com/sfmalloy/advent-of-code) to find any future changes.
___

# Advent Of Code 2018

These are my solutions in C++ for Advent of Code 2018.

## Compiling and Running

```
git clone https://github.com/sfmalloy/advent-of-code-2018
cd advent-of-code-2018
make
```

Everything is organized so solution files are seperated from headers and extra source files. To actually run a specific day invoke

```
./advent -d <day_number>
```

This does not use the traditional option parsing bundled with Linux, so it should theoretically be cross platform. However, I have only tested this on Arch Linux with g++ 11.

If you want to use this structure for your own solutions, by all means go ahead! Simply replace the solution files with the template provided in the same directory, and provide your own inputs.

## Using Different Inputs

If you're using this structure for your own solutions and want to download your own inputs you can do so pretty easily! 

First you need to set an environment variable called `AOC_SESSION` which is your personal session cookie you can get from https://adventofcode.com/ from any of the input pages.

After you do that, there is a python script provided to do grab your input and save it to a file. 

On Linux/MacOS you should be able to do
```
./download.py -d <day_num>
```

On Windows you will need to do
```
python3 download.py -d <day_num>
```

The script is designed to only download the input once and then print it. If you run it again it will simply print out the saved file. 

## Writing Your Own Solutions

Each day is broken up into a seperate file, with one function called `solve`. It looks a little different than just a simple `void solve(...)` function however.

```cpp
template <>
void
solution<1>::solve(std::ifstream& input);
```

The template is used to make a unique solve function for day 1, without having a seperate function called `solveDay1` or something like that. This is mainly for organization and abstraction in the `advent.cpp` source file. To change the day number, simply change the number in the template to any number from 1 to 25 (inclusive).

The main runner (`advent.cpp`) is programmed to grab the input from that directory and feed it into a `std::fstream`. For example, if you wanted to read every line of a text file as an int, into a `std::vector`, you could do this:

```cpp
template <>
void
solution<1>::solve(std::ifstream& input)
{
    std::vector<int> nums;
    int curr_num;
    while (input >> curr_num) 
        nums.push_back(curr_num);
}
```

The main goal of this "library" was to take the headache out of reading inputs and timing, and handle all of that in the background so you can focus purely on the solution to the problem.

Ok that's it! If you have any questions about this feel free to reach out!
