# Bitify
Bitify is a simple program to create binary or hexadecimal text from the commandline input.

## Usage
bitify [options] The text to convert to binary
Options:
 -x - converts text to hex instead
 -s - adds space between each letter
 -h - shows this help menu
=== Examples ===
bitify cool prog
01100011011011110110111101101100001000000111000001110010011011110110011100100000
---------
bitify -x cool prog
636F6F6C2070726F6720
---------
bitify -x -s cool prog
63 6F 6F 6C 20 70 72 6F 67 20 
== Examples end ==
