# First Project in Data Structures
In order to run this code, follow these two steps:
1. Assert that your directory is organized according to the following structure:
```
First Project/
└── src/
    └── main.cpp
└── include/
    └── buffer.h
└── obj/
└── bin/
└── Makefile
```
2.1. Run the following in command prompt on Linux:
```
>>> mkdir bin
>>> mkdir obj
>>> make 
>>>./bin/run.out <TARGET_FILE>
>>> make clean
```
2.2. Or the following in Windows:
```
>>> make 
>>>.\bin\run.out <TARGET_FILE>
>>> make clean
```
Where <TARGET_FILE> stands for the .txt containing the commands for the program.


The /tests directory contain a .cpp file that performs basic structural tests using doctest. These files are not automatically compiled by Make and so in order to run them, compile them manually in the respective folder.
