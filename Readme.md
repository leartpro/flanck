# FLANCK LIBRARY

Beinhaltet Lexer, Parser und Interpreter der Sprache Flanck.
Des Weiteren wird die Wrapperklasse Stack exportiert.

## CONFIGURATION

1. create a folder called `libs` in your project root
2. checkout the `libs` folder and run
    ```sh
      git clone https://github.com/leartpro/flanck.git -b libary
    ```
3. configure your CMakeLists.txt
    ```cmake
        add_subdirectory(libs/flanck)
        target_link_libraries(${PROJECT_NAME}
            flanck
            # Add any other libs you want to use here
        )
    ```
   flanck does not need further includes
4. to use flanck in your code:
   ```c++
      #include "flanck/flanck.h"
   ```



