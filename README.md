# Vigenere Cipher Decryption
Created for Computer Security Project 1, this program will take a vigenere cipher output and attempt to piece together the key used to encrypt the file that can then be used to decrypt the file (Does not decrypt the file)

## How to use

To use the program, you must first compile it using `make` in the terminal.

```
C:/Vigenere-Cipher-Decryption-master> make
```

From there, the file will be exported as `output.exe` (or just `output` if you're on Linux, assuming it compiles, I think it should)

After getting the .exe file, enter this command to run the program
```
C:/Vigenere-Cipher-Decryption-master> ./output <name-of-file> [characters in vigenere cipher]
```

The program should return the potential key to the vigenere cipher

## Assumptions
1. The first argument given is a vigenere cipher encrypted txt file
2. There is a positive non-zero value for the number of letters in the key (Defaults to one if no value is given, or the given value is less than 1)
3. When using max frequency comparison, the character with the highest frequency will be considered as the letter E.
4. All characters that aren't A-Z (case-insensitive) will be ignored

## Future Updates (hopefully)
* I'd like to remove the input for the number of characters in key and have the program try and figure it out own its own in the future