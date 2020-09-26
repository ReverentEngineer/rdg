# librdg

librdg is a library for generating data sets by specifying how the data should
look using regular expressions. It includes a C++ wrapper and Python bindings
for use with your favorite language. Well, as long as your favorite language 
is C, C++, or Python.

# Interfaces

* [librdg](@ref librdg)
* [librdg++](@ref librdg-cpp)

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

The equivalent functionality in librdg++:

```
#include <rdg.hh>
...
RDG generator("test[1-3");
for (int i = 0; i < rdg.permutations(); i++) {
  std::string permutation = rdg.generate();
}
```

And the same thing in Python:

```python
from rdg import RDG
for data in RDG("test[1-3]"):
  ... Do something with data ...
```


