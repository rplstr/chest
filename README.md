# chest

Single-header C99 testing framework for unit tests.


## Usage

1. Copy `chest.h` into your project.
2. Include the header in your source:
   ```c
   #include "chest.h"
   ```
3. Write tests:
   ```c
   TEST(addition) {
       assertcmp(c, EQ, 2 + 3, 5);
   }
   ```
4. Register and run tests:
   ```c
   RUN_ALL(
       ADDTEST(c, addition);
       // ADDTEST(c, another_test);
   );
   ```


## License

This project is licensed under the 0BSD license. See [LICENSE](LICENSE) for full text.
