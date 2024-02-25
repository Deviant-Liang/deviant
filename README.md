# Deviant

Deviant is a simple and expressive language designed for educating.

## Table of Contents
- [Installation](#installation)
- [Getting Started](#getting-started)
- [Syntax](#syntax)
- [Examples](#examples)
- [License](#license)

## Installation


## Getting Started


## Syntax
Deviant follows a simple and intuitive syntax. Below are some key language constructs:

- Function Declaration:
    ```deviant
    fn function_name(parameters) -> return_type {
        // Function body
    }
    ```
- Variable Declaration:
    ```deviant
    var variable_name = value;
    ```
- Return Statement:
    ```deviant
   ret expression;
    ```

- If-Else Statement:
    ```deviant
    if (condition) {
        // Code block
    } else {
        // Code block
    }
    ```

- Print Statement:
    ```deviant
    print(expression);
    ```

## Examples
Here are some examples demonstrating the usage of Deviant:

- Example 1: Function Definition
    ```deviant
    fn monkey() -> int {
        var x = 12345;
        ret x;
    }
    ```

- Example 2: Main Function
    ```deviant
    // Main function
    fn main() -> int {
        var b = 1;

        if (b) {
            b = 2;
        } else {
            b = 3;
        }

        print(b);

        ret 0;
    }
    ```

## License
Deviant is licensed under the MIT. See the LICENSE file for more details.