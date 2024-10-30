# cppy
Open-source C++ library focused on bringing Python's methods to C++17 and higher

## Installation
### File extraction
You can install cppy by simply extracting files from the `include` folder into your project directory
### CMake
You can also install the library via CMake.
Execute the following commands after cloning the repository and navigating into its root directory in the terminal:

Linux:
```sh
mkdir build
cd build
cmake ..
sudo make install
```
Windows (using MinGW) (Run Powershell as administrator):

```sh
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --target 
```
This will install the library system-wide.
If you want to install the library locally, then change the parameter of `CPPY_LOCAL_INSTALL` to ON in CMakeLists.txt. All of the installed files will be located in `/build/install/`

## Usage
After installing the library you include the header file `cppy.h`:
```c++
#include "cppy.h"
```
If you want to include only a specific method (e.g. print), then use the following syntax: `#include "cppy/function.h"`:
```c++
#include "cppy/print.h"

int main()
{
  cppy::print("Hello World!");
}
```

## Methods
The following methods are currently supported by cppy:
| Method | Description | Status |
| ------ | -------------------- | ------------- |
| abs() | Returns the absolute value of a number. | Already implemented in C/C++ |
| all() | Returns true all elements of the container are true, otherwise it returns false. | Implemented |
| any() | Returns true if atleast one of the element of the container is true, otherwise it returns false. | Implemented |
| ascii() | Returns a string with a printable representation of characters. | Implemented |
| bin() | Converts an integer to a binary string prefixed with "0b". | Implemented |
| boolean() | Returns the bool value of the input. If the input is a container, the function returns false if it's empty, otherwise it return true. | Implemented (renamed due to name conflicts) |
| bytearray() | Returns an array of bytes. | Not implemented |
| bytes() | Returns a sequence of integers in the range 0 <= x <= 255. | Not implemented |
| callable() | Checks if the input is callable. | Implemented |
| chr() | Returns the string representing a character whose Unicode code point is the integer input. | Already implemented in C/C++ ( e.g. `char c = 97;` ) |
| classmethod() | Transforms a method into a class method. | Already implemented in C/C++ ( e.g. SomeClass::SomeFunction() )
| compile() | Returns the specified source as a code object, ready to be executed. | Not implemented |
| complex() | Returns a complex number | Not implemented |
| delattr() | Deletes the named attribute | Not implemented |
| dict() | Creates a new dictionary | Already implemented in C/C++ ( e.g. `std::map<std::string int> map{{"a", 1}, {"b", 2}};` ) |
| dir() | Returns a list of valid attributes for a specified object | Not implemented |
| divmod() | Returns the vector of the inputs' quotient and remainder. | Implemented |
| enumerate() | Adds a counter as the key to the container. | Implemented |
| eval() | Evaluates the expression | Not implemented |
| filter() | Constructs a container from those elements of the input for which function is true. | Implemented |
| floatp() | Returns a floating point number | Implemented (renamed due to name conflicts) |
| format() | Formats the input. | Implemented |
| frozenset() | Returns a constant set | Already implemented in C/C++ (`const std::set`) |
| getattr() | Returns the value of the named attribute of an object | Not implemented |
| hasattr() | Returns true if the input is the name of one of the object's attributes. Returns false otherwise | Not implemented |
| hash() | Returns the hash value of the input. | Implemented |
| hex() | Converts an integer to a lowercase hexadecimal string prefixed with "0x" | Implemented |
| id() | Returns the id of an object | Already implemented in C/C++ (`&`) |
| input() | Reads the input and converts it into a string. | Implemented |
| integer() | Converts the input to an integer. | Implemented (renamed due to name conflicts) |
| isinstance() | Returns true if the object argument is an instance of the argument. Returns false otherwise. | Not implemented |
| issubclass() | Checks if a class is a subclass. | Implemented |
| iter() | Returns an iterable object. | Already implemented in C/C++ ( e.g. `std::vector, std::list` )
| len() | Returns the length of the input. | Implemented |
| list() | Returns a list object | Already implemented in C/C++ ( e.g. `std::list` )
| locals() | Returns an updated dictionary of the current local symbol table. | Not implemented |
| map() | Applies the function to every element of a container. | Implemented |
| max() | Returns the biggest object among all the parsed ones. | Implemented |
| memoryview() | Returns the memory address of the input. | Implemented |
| min() | Returns the smallest object among all the parsed ones. | Implemented |
| next() | Returns the next item in a container. | Not implemented |
| object() | Returns a new empty object | Not implemented (skipped) |
| oct() | Converts an integer to an octal string prefixed with "0o" | Implemented |
| open() | Opens a file | Already implemented in C/C++ ( e.g. `FILE* or <fstream>` )
| ord() | Returns the ASCII value of the input. | Implemented |
| pow() | Returns the base number to the power of another input. | Already implemented in C/C++ |
| print() | Prints objects. Sep, End, File, Flush, if present, must be parsed like structs before objects in any order. | Implemented |
| property() | Returns a property attribute | Not implemented |
| range() | Returns the vector of integers, going from start till stop. | Implemented |
| repr() | Returns a string containing a printable representation of an object. | Not implemented |
| reversed() | Reverses the container. | Implemented |
| round() | Rounds up the input to digit. | Implemented |
| set() | Returns a set object. | Already implemented in C/C++ ( e.g. `std::set` ) |
| setatttr() | Sets the attribute of an object. | Not implemented |
| slice() | Slices the container. | Implemented |
| sorted() | Sorts the container using TimSort. Key and Reverse, if present, must be parsed like structs after the container in any order. | Implemented |
| staticmethod() | Transforms a method int a static method | Already implemented in C/C++ |
| str() | Converts the input into a string. | Implemented |
| sum() | Sums start and the elements of a container and returns the total. The container's elements are normally numbers. | Implemented |
| super() | Returns an object that represents the parent class. | Not implemented |
| tuple() | Returns a tuple object | Already implemented in C/C++ (`std::tuple`) |
| type() | Returns typename of the input. | Implemented |
| vars() | Returns the __dict__ property of an object | Not implemented |
| zip() | Returns a vector of tuples, where the first element in each passed container is paired together, same goes for the second element and so on. | Implemented |

## Uninstallation
Delete the files that were extracted by either CMake or by you. If you've installed the library system-wide, then delete the files located in
Linux:
`/usr/local/include/cppy/` and `/usr/local/include/cppy.h`
Windows:
`C:/Program Files (x86)/cppy/`
