OnlyOnce
========

Copyright (c) 2015 Cornerstone Solutions Pty Ltd.

Licensed under the BSD license as per `LICENSE.md`


Summary
-------

OnlyOnce is a small library that can prevent a program from being run multiple
times simultaneously.

At this time, OnlyOnce has been written to work in C++ on Linux. It may run on
other POSIX compliant systems.

This library is still in a prerelease state, and changes may break code which
includes it.


Basic Use
---------

OnlyOnce has been tested being compiled as part of the source of a C++ 
application with `g++`.

OnlyOnce requires that C++11 standard be enabled by your compiler.

### Example of Basic Use

#### main.cpp

```c++
#include <iostream>
#include "OnlyOnce.h"

int main()
{
    if (helpers::LockMeUp("MyApp"))
    {
        // The program is not already running, so do what the program
        // needs to do here
        helpers::LockMeUp("MyApp");
    }
    else
    {
        // Close, because the program is already running
        std::cout << "Program not started - already running\n";
    }
}
```

#### makefile
```make
all:
	g++ -std=c++11 main.cpp OnlyOnce.cpp cw TestOnce
```

Version History
---------------

### 0.1 (2015-14-10)

Initial release
