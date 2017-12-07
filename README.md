# avr microcontroller

## Requirement
* x64 architecture Linux or macOS
* make
* avr-gcc

## Run
- Using `cu` command to open serial console.

        $ sudo cu -s 38400 -l /dev/<avr board device>

- Run `make` command in project root directory.

        $ make

- When if training source build.

        # build training/week1/work1.c file.
        $ make W=1 E=1

- When direct writing into AVR Board.

        $ make dl

- Enjoy!!!!!!
