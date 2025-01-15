# Ituxalien C Runtime Library
## how to use
Example:
```c
#include <stdio.h> // include <stdio.h> from ItuxCRT
int main() { // Main function
    printf("Hello, World!\n"); // Print the "Hello, World!" word
    return 0; // Return 0 (success)
} // End main function
```
And <unistd.h> file:
```c
#include <unistd.h>
int main() { // Main function
    write(STDOUT_FILENO, "Hello, World!\n", 14); // Print the "Hello, World!" word
    return 0; // Return 0 (success)
} // End main function
```
