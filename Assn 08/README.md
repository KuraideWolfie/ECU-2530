# ECU-2530

## Assignment 08
### Assignment Description
This assignment incorporated the Huffman algorithm, being split into two parts: huffman, and unhuffman. The first portion was about executing the Huffman algorithm to generate a Huffman code for a file, and unhuffman was required to decompose that code to rebuild the original file. A couple of files were provided to manipulate binary data, and the reutilization of priority queues mandated. (The instructor provided for us, as well, a tree structure definition to use.) The console output of huffman was the frequencies of all characters in the file, as well as the constructed Huffman code. The console output of unhuffman needed to only be the reconstructed code from the input file.
### Source Files
huffman.cpp unhuffman.cpp binary.h binary1.cpp pqueue.cpp pqueue.h trace.cpp trace.h tree.h
### Compilation, Testing, and Known Issues
```
Windows:
Compile:
g++ -Wall -Werror -o huffman.exe huffman.cpp binary.h binary1.cpp pqueue.cpp pqueue.h trace.cpp trace.h tree.h
g++ -Wall -Werror -o unhuffman.exe unhuffman.cpp binary.h binary1.cpp pqueue.cpp pqueue.h trace.cpp trace.h tree.h
Testing:
huffman -t “./data/input.txt” “./data/output.cmp”
unhuffman -t “./data/output.cmp” “./data/decrypt.txt”

Linux:
g++ -Wall -Werror -o huffman huffman.cpp binary.h binary1.cpp pqueue.cpp pqueue.h trace.cpp trace.h tree.h
g++ -Wall -Werror -o unhuffman unhuffman.cpp binary.h binary1.cpp pqueue.cpp pqueue.h trace.cpp trace.h tree.h
Testing:
./huffman -t “./data/input.txt” “./data/output.cmp”
./unhuffman -t “./data/output.cmp” “./data/decrypt.txt”
```
Notes:
- Special characters, such as tabs and spaces, are represented by words, such as “TAB,” “SPACE,” and “NEWLN.” Other characters that are special or unrepresented by physical characters have their character code printed instead.
- The toggle `-t` prints trace/debug statements, which includes the frequency counts of the source text file provided as a parameter to the program.
- The arguments of huffman are an input, regular text file, and then an output file where the Huffman code and compressed text is stored in binary. The arguments of unhuffman are the generated, compressed text file, and then where to store the uncompressed results. After passing a text file through huffman and then unhuffman, the contents should be exactly the same.
