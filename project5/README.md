# Program-Analysis-Project 5
1. This tool can detect unused variable assignments and overwritten values in every function
2. The algorithm is in file ./DeadCodeDetector.cpp
3. Test cases are in ./testcases
4. output example:
    [DeadCodeDetector] Function baz
    -> Dead def at line 3:   %3 = fmul double %0, 2.000000e+00, !dbg !17
    -> Dead def at line 2:   %2 = fmul double %0, 3.140000e+00, !dbg !15

run the tool: the tool can be executed in CS6890 VM enviroment
    1. mkdir build 
    2. cd build/
    3. cmake ..
    4. make 
    5.  opt -load-pass-plugin=./ProgramAnalysis.so -passes='program-analysis'  -disable-output ../testcases/1.bc
        opt -load-pass-plugin=./ProgramAnalysis.so -passes='program-analysis'  -disable-output ../testcases/2.bc
        opt -load-pass-plugin=./ProgramAnalysis.so -passes='program-analysis'  -disable-output ../testcases/3.bc

