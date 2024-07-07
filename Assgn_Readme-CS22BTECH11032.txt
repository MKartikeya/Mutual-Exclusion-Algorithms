------------PROGRAMMING ASSIGNMENT-3----------------
--------------KARTIKEYA MANDAPATI-------------------
-----------------CS22BTECH11032---------------------

FILES: The zip consists of the following files:
        1)Assgn3Src-CS22BTECH11032_tas.cpp
        2)Assgn3Src-CS22BTECH11032_cas.cpp
        3)Assgn3Src-CS22BTECH11032_bcas.cpp
        4)Assgn3Src-CS22BTECH11032_atomic.cpp
        5)Assgn3Readme-CS22BTECH11032.txt
        6)Assgn3Report-CS22BTECH11032.pdf
Additional input.txt file.

INPUT:  The input must be given in input.txt file. It must contain:
        1)N (Size)
        2)K (The number of threads)
        3)rowInc (The number of cores)
        4) The input n*n matrix in row major form.
        These must be separated by a space.
    NOTE: The values must be power 2 for better utilization of threads. ELse the work division would not be uniform.
COMPILATION:    g++ Assgn2Src-CS22BTECH11032_{method}.cpp
                ./a.out

OUTPUT: 
    Respective Output files tasOut.txt
                            casOut.txt
                            bcasOut.txt
                            atomicOut.txt