# avr microcontroller

## Requirement

* CMake
* avr-gcc

## Run
1. Using `cu` command to open serial console.
```
$ sudo cu -s 38400 -l /dev/<avr board device>
```
2. Rewrite `SOURCE_FILES` of `CMakeLists.txt`.
```
set(SOURCE_FILES some/of/source.c)
add_avr_executable(work ${SOURCE_FILES})
```
3. Run `install` script in Project root directory.
```
$ ./install
```
4. Enjoy!!!!!!
