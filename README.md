# ScopeExit - C++11 scope guard library
[![Build Status](https://travis-ci.org/SergiusTheBest/ScopeExit.svg?branch=master)](https://travis-ci.org/SergiusTheBest/ScopeExit) [![Build status](https://ci.appveyor.com/api/projects/status/an8btmcolsbuhvs2/branch/master?svg=true)](https://ci.appveyor.com/project/SergiusTheBest/scopeexit/branch/master)

- [Introduction](#introduction)
  - [Features](#features)
  - [Sample](#sample)
- [References](#references)
- [License](#license)
- [Version history](#version-history)

# Introduction
ScopeExit library provides an efficient and convenient way to execute statements when execution flow leaves current scope. It implements a so-called [scope guard idiom](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Scope_Guard) and defines 3 type of guards:

- `SCOPE_EXIT` - statements are always executed on scope exit
- `SCOPE_SUCCESS` - statements are executed on scope exit when no exceptions have been thrown
- `SCOPE_FAILURE` - statements are executed when scope is leaving due to an exception

Using scope guards makes code much cleaner and allows to place resource allocation and clean up code next to each other. They also improve safety because cleanup code is always called independent of which paths are actually taken at runtime.

Scope guards are called in the reverse order they are defined.

## Features
- Easy to use
- Headers only
- Requires C++11 or higher
- No 3rd-party dependencies
- Cross-platform
- Minimal overhead (no std::function or virtual table)
- Clean code
- CMake integration

## Sample
Here is a simple sample that prints htlm code. Scope exit blocks make sure that html tags are properly closed:
```cpp
#include <iostream>
#include <ScopeExit/ScopeExit.h>

using namespace std;

int main()
{
    cout << "<html>" << endl;
    SCOPE_EXIT{ cout << "</html>" << endl; };

    {
        cout << "<head>" << endl;
        SCOPE_EXIT{ cout << "</head>" << endl; };

        cout << "<title>Hello</title>" << endl;
    }

    cout << "<body>" << endl;
    SCOPE_EXIT{ cout << "</body>" << endl; };

    cout << "<h1>Hello World!</h1>" << endl;

    return 0;
}
```

More samples can be found in the [samples](samples) folder.

# References
## Competing C++ scope exit/guard libraries
- [offa/scope-guard](https://github.com/offa/scope-guard)
- [Neargye/scope_guard](https://github.com/Neargye/scope_guard)
- [ricab/scope_guard](https://github.com/ricab/scope_guard)
- [Simple-Look Scope Guard for Visual C++ 2010](https://www.codeproject.com/Articles/124130/Simple-Look-Scope-Guard-for-Visual-C)

## Other resources
- [Scope guards in D Programming Language](https://tour.dlang.org/tour/en/gems/scope-guards)
- [Andrei Alexandrescu “Declarative Control Flow"](https://youtu.be/WjTrfoiB0MQ)

# License
ScopeExit is licensed under the [MIT license](https://choosealicense.com/licenses/mit). You can freely use it in your commercial or opensource software.

# Version history

## Version 1.0.0 (08 Oct 2019)
- Initial public release
