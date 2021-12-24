# eventpp

A simple event library for c++.

## Building

You can build the library normally:

```bash
mkdir build
cd build
cmake ..
make
```

The resulting library will be outputted as `build/libeventpp.*`

..Or, you can include it in an existing CMake project:

```
add_dependency(... eventpp)

...

target_link_libraries(... eventpp)
```

## Testing

You can compile and run the tests:

```bash
mkdir build
cd build
cmake -DBUILD_TESTS=1 ..
make
# run the tests
./test/eventpp-test
```


## Example

```cpp
#include <iostream>
#include <eventpp.hpp>

enum EVENTS {
    MY_EVENT
};

class Listener : public epp::observer {
public:
    Thing(epp::emitter& em)
        : epp::observer(em) {
        // hook into MY_EVENT
        hook(MY_EVENT, [this](data d) {
            x = d.get<int>("val");
        });
    }
    
    int x = 0;
}

int main() {
    // create the manager
    epp::emitter em;
    // create a Thing instance
    Thing t(em);
    
    std::cout << t.x << std::endl; // x = 0
    
    //! Raise an event, using data with the key "val" set to 9. 
    em.emit(MY_EVENT, data({{ "val", 9 }}));
    
    std::cout << t.x << std::endl; // x = 9!
    
    return 0;
}
