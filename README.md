# Regex Data Generator (RDG)

RDG is a library with an accompanying executable and Python bindings that
allow users to generate data sets by specifying how data should look using
regular expressions.

# Pre-requisites

To build only the C library, the following packages are required:

* gcc
* CMake
* flex
* bison

In addition, to build the Python bindings, the Python development headers are
required. This was tested with Python 3.7.7. 

# Installation

```bash
mkdir build
cd build
cmake ...
make install
```

# Quickstart

A quick example of how to use librdg:

```c
#include <rdg.h>
...
struct rdg* rdg = rdg_new("test[1-3]");
unsigned char* data = NULL;
size_t size = 0;
while(rdg_generate(&data, &size, data)) {
  ... Do something with data ...
}
rdg_free(rdg);
```

An example of how to do the same thing in Python:

```python
from rdg import RDG
for data in RDG("test[1-3]"):
  ... Do something with data ...
```

# Documentation

Documentation can be found at https://reverentengineer.com/rdg

# License

This software is released under the MIT license. See the file LICENSE for more details.
