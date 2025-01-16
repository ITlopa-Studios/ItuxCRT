# Ituxalien C Runtime Library
## Documentation
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
If you want use <string.h> file:
```c
#include <unistd.h>
#include <string.h>
int main() { // Main function
    const char *message = "Hello, World!\n";
    write(STDOUT_FILENO, message, strlen(message)); // Print the "Hello, World!" word
    return 0; // Return 0 (success)
} // End main function
```
And read function:
```c
#include <unistd.h>
int main() { // Main function
    char msg[1024];
    read(STDIN_FILENO, msg, sizeof(msg)); // Read word
    return 0; // Return 0 (success)
} // End main function
```
And file functions:
```c
#include <unistd.h>
#include <string.h>
int main() { // Main function
    const char *msg = "Hello, World!\n";
    int file = open("testfile", O_WRONLY | O_CREATE | O_TRUNC, 0644);
    write(file, msg, strlen(msg)); // Print the "Hello, World!" word
    return 0; // Return 0 (success)
} // End main function
```
## Compilation
C files compiles using GCC.
Assembly files compiles using NASM.
