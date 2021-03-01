# libospath

C++ counterpart of Python's os.path module. Provides common pathname manipulations and access to filesystem in your C++ code.

## Integration

- Clone the repository - ```git clone https://github.com/hrishibawane/libospath.git```

### Install library

- Run ```sudo ./install.sh```
- Now, the library can be used from anywhere locally.
- Include the header file ```os_path.hpp``` and compile using ```g++ source_file.cpp -lospath```

### Tests

- ```cd tests/src```
- ```make test```

Note: Make sure to install first before running the tests.
