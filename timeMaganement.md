
The features we implemented is shown in table below:

| Features                                                                               | Guanxi Lu | Haocheng Fan |
|----------------------------------------------------------------------------------------|:---------:|:------------:|
| **Basic Features**                                                                     |                          |
| A file containing just a single function with no arguments                             |     ✓     |              |
| Variables of int type                                                                  |     ✓     |              |
| Local variables                                                                        |           |      ✓       |
| Arithmetic and logical expressions                                                     |     ✓     |              |
| If-then-else statements                                                                |     ✓     |              |
| While loops                                                                            |     ✓     |              |
| **Intermediate Features**                                                              |                          |
| Files containing multiple functions that call each other                               |           |      ✓       |
| Functions that take up to 8 parameters                                                 |           |      ✓       |
| For loops                                                                              |     ✓     |              |
| Arrays declared globally (i.e. outside of any function in your file)                   |           |      ✓       |
| Arrays declared locally (i.e. inside a function)                                       |           |      ✓       |
| Array initialization                                                                   |           |      ✓       |
| Reading and writing elements of an array                                               |           |      ✓       |
| Recursive function calls                                                               |           |      ✓       |
| The enum keyword                                                                       |     ✗     |      ✗       |
| Switch statements                                                                      |     ✓     |              |
| The break and continue keywords                                                        |           |      ✓       |
| Ternary operator (x ? y : z)                                                           |     ✓     |      ✓       |
| **Advanced Features**                                                                  |                          |
| Variables of double, float, char, unsigned, structs, and pointer types                 |     ✓     |              |
| Calling externally-defined functions                                                   |           |      ✓       |
| Functions that take more than 8 parameters                                             |           |      ✓       |
| Mutually recursive function calls                                                      |           |      ✓       |
| Locally scoped variable declarations                                                   |     ✓     |      ✓       |
| The typedef keyword                                                                    |     ✗     |      ✗       |
| The sizeof(...) function                                                               |     ✓     |              |
| Taking the address of a variable using the & operator                                  |           |      ✓       |
| Dereferencing a pointer-variable using the * operator                                  |           |      ✓       |
| Pointer arithmetic                                                                     |     ✓     |      ✓       |
| Character literals, including escape sequences like \n                                 |     ✓     |              |
| Strings (as NULL-terminated character arrays)                                          |           |      ✓       |
| Declaration and use of structs                                                         |     ✗     |      ✗       |


Mile Stone:

- **26/02** - [Built the repository.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/f7c89e178bdb6c28aa2cb116e1f277e063182cf7)
- **03/03** - [Completed the first version of context, parser, and lexer.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/bda3f228be1d555d0ddc47f34347db06f1a23e62)
- **04/03** - [Implemented binary operations for basic arithmetic.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/50e53805623bb755b627b9d91bf80ba0afa29229)
- **10/03** - [Implemented local variable support.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/881003868ee8c6c9230019bdbe51e51d17c83520)
- **11/03** - [Completed 3 tests successfully.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/fa95ca6c9fcc377ba8a7c236dae77785954cff6a)
- **12/03** - [Implemented relational and equality operations.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/b58213de9349920f66b204d4e961978c2929acd6)
- **13/03** - [Completed 13 tests, modified binary operations, unsigned types, and compound statements.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/d5c79c0207e1baf65bd99457c6c8891ce94edf6c)
- **14/03** - [Completed 24 tests, implemented selection statements and other logical operations.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/b00076ec13b7bd5afb775f5cacb85402ff5ada95)
- **15/03** - [Completed 38 tests, implemented function calls, unary operations, and iteration statements.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/81184b0026a245632c7d1bf5279430da42aaf405)
- **16/03** - [Completed 52 tests, implemented sizeof and types, modified function call logic.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/b566211c567d69a976b99a9ca4dba33930216692)
- **17/03** - [Completed 55 tests, implemented arrays, and fixed unary operation bugs.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/08446a16b75945a10a7d9be33d8b08f378a487fd)
- **18/03** - [Completed 60 tests, implemented floating-point support, fixed memory leaks, segmentation faults, and other bugs.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/dd2540a4c91c16b1c11bf8b43d718be147a2355f)
- **19/03** - [Completed 70 tests, fixed a bug in a for loop used to allocate registers in compound statements.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/8a2e2ea678b0a6e4641434fd696718a41a79afbb)
- **20/03** - [Completed 73 tests, modified code format, implemented break, continue, and ternary operations, modified function calls, and arithmetic bugs.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/59f5c47627bf4889b9de3882c30b4e24883dd3d9)
- **21/03** - [Completed 76 tests, implemented switch statements, modified parser, function definitions, and context management.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/83123eeb7c67779bb0f8b4b4a6c247196a987652)
- **22/03** - [Complete 78 test, add the 8 parameter feature, Modified float code and register allocation, added comments.](https://github.com/LangProc/langproc-2023-cw-CRV_Compiler/commit/c552123a619df160f5fbf33bcf0e8d9ae1e59b35)

Week-by-week View

- **first week(26/02-03/03)**
  1. Get basic understanding of the compiler project
  2. Review material on slide that relates to this project
  3. Try to finish work for other module(e.g. control report) in order to give time for compiler
     
  About 2 hours each day

- **second week(04/03-10/03)**
  1. work together to finish the basic features
  2. modify the context with help from TA and online resources
  3. start adding higher level features
 
  About 4 hours each day

- **third week(11/03-17/03)**
  1. work on medium and high level features
  2. join the code on the two branches of us each day
  3. debugging and testing with the .sh file
     
  whole day in library, almost everyday until 1 a.m.

- **fourth week(18/03-22/03)**
  1. continue to add features as much as we can
  2. improve the coding layout and add comments
  3. do the finial testing to avoid error like memory leakage
  4. check all the test case we done work well
 
  whole day in library, until 10 p.m.

  Detailed Time Taken for Each Milestone

| Features                                                     |                   Time                    | Estimation | Note                      |
| ------------------------------------------------------------ | :---------------------------------------: | :--------: | ------------------------- |
| **Basic Features**                                           |                                           |         |                           |
| A file containing just a single function with no arguments   |                   6 hrs                   |     👌      |                           |
| Variables of int type                                        |                   2 hrs                   |     👌      |                           |
| Local variables                                              |            Very long (20 hrs)             |     👎      |                           |
| Arithmetic and logical expressions                           |                   4 hrs                   |     👍      |                           |
| If-then-else statements                                      |                   1 hrs                   |     👍      |                           |
| While loops                                                  |                   1 hrs                   |     👍      |                           |
| **Intermediate Features**                                    |                                           |            |                           |
| Files containing multiple functions that call each other     |                   4 hrs                   |     👌      |                           |
| Functions that take up to 8 parameters                       |                   2 hrs                   |     👌      |                           |
| For loops                                                    |                   1 hrs                   |     👍      |                           |
| Arrays declared globally (i.e. outside of any function in your file) |          10 hrs (Array in total)          |     👎      |                           |
| Arrays declared locally (i.e. inside a function)             |          10 hrs (Array in total)          |     👎      |                           |
| Array initialization                                         |          10 hrs (Array in total)          |     👎      |                           |
| Reading and writing elements of an array                     |          10 hrs (Array in total)          |     👎      |                           |
| Recursive function calls                                     |                   4 hrs                   |     👌      |                           |
| The enum keyword                                             |                     \                     |     \      | Reduced from deliverables |
| Switch statements                                            |        2 hrs (more time in debug)         |     👎      |                           |
| The break and continue keywords                              |                   1 hrs                   |     👌      |                           |
| Ternary operator (x ? y : z)                                 |                   3 hrs                   |     👎      |                           |
| **Advanced Features**                                        |                                           |            |                           |
| Variables of double, float, char, unsigned, structs, and pointer types |                   6 hrs                   |     👎      |                           |
| Calling externally-defined functions                         |                   6 hrs                   |     👌      |                           |
| Functions that take more than 8 parameters                   |                   3 hrs                   |     👌      |                           |
| Mutually recursive function calls                            |                   2 hrs                   |     👌      |                           |
| Locally scoped variable declarations                         |                   2 hrs                   |     👌      |                           |
| The typedef keyword                                          |                     \                     |     \      | Reduced from deliverables |
| The sizeof(...) function                                     |                   3 hrs                   |     👍      |                           |
| Taking the address of a variable using the & operator        |         10 hrs (pointer in total)         |     👍      |                           |
| Dereferencing a pointer-variable using the * operator        |         10 hrs (pointer in total)         |     👍      |                           |
| Pointer arithmetic                                           |         10 hrs (pointer in total)         |     👍      |                           |
| Character literals, including escape sequences like \n       |          8 hrs (String in total)          |     👌      |                           |
| Strings (as NULL-terminated character arrays)                |          8 hrs (String in total)          |     👌      |                           |
| Declaration and use of structs                               |                     \                     |     \      | Reduced from deliverables |
| **Lexer**                                                    |          Inherited from template          |            |                           |
| **Parser**                                                   | Completed after each feature is completed |            |                           |




