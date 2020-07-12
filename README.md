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
#include "eventpp/manager.hpp"

enum EVENTS {
    MY_EVENT
};

class Thing {
public:
    Thing(eventpp::manager& mgr) {
        // subscribe to MY_EVENT
        mgr.subscribe(tok, MY_EVENT, [this](const eventpp::data& d) {
            // retrieve the integer stored in key "val".
            this->x = d.get<int>("val");
        });
    }
    
    int x = 0;
private:
    // Required for subscribing to events.
    eventpp::token tok;
}

int main() {
    // create the manager
    eventpp::manager mgr;
    // create a Thing instance
    Thing t(mgr);
    
    std::cout << t.x << std::endl; // x = 0
    
    //! Raise an event, using data with the key "val" set to 9. 
    mgr.raise(MY_EVENT, data().set("val", 9));
    
    std::cout << t.x << std::endl; // x = 9!
    
    return 0;
}
```