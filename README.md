# Phases of Compiler

## A Simple Implementation of Compiler Phases

This project demonstrates a basic implementation of several phases of a compiler: lexical analysis, syntax analysis, and translation from infix to postfix notation.

### Introduction

This project showcases a simplified version of a compiler that processes an input expression, validates its syntax, constructs a parse tree, and converts the expression from infix to postfix notation. The implementation covers:

- Lexical Analysis: Tokenizing the input.
- Syntax Analysis: Validating and parsing the expression into a parse tree.
- Infix to Postfix Conversion: Translating infix expressions to postfix notation.

### Demonstration

![Compiler Phases](https://yourimageurl.com/diagram.png)

### Installation and Usage Instructions (For End-Users)

1. **Clone the repository:**

```bash
git clone https://github.com/yourusername/Phases-of-Compiler.git
cd Phases-of-Compiler
```

2. **Compile the code:**

```bash
g++ -o compiler compiler.cpp lexical_analyzer.cpp syntax_analyzer.cpp
```

3. **Run the compiler:**

```bash
./compiler
```

4. **Enter an expression when prompted.**

### Installation and Usage Instructions (For Contributors)

1. **Clone the repository:**

```bash
git clone https://github.com/yourusername/Phases-of-Compiler.git
cd Phases-of-Compiler
```

2. **Set up your development environment:**

Ensure you have `g++` installed. You can install it using:

- For Debian-based systems:

  ```bash
  sudo apt-get install g++
  ```

- For Red Hat-based systems:

  ```bash
  sudo yum install g++
  ```

3. **Compile the code:**

```bash
g++ -o compiler compiler.cpp lexical_analyzer.cpp syntax_analyzer.cpp
```

4. **Run the compiler:**

```bash
./compiler
```

5. **Make your changes and create a pull request.**

### Contributor Expectations

- Fork the repository and clone it to your local machine.
- Create a new branch for your feature or bugfix.
- Make your changes and commit them with descriptive messages.
- Push your changes to your fork and create a pull request.
- Ensure your code follows the project's style guidelines.
- Include tests for any new functionality.

Feel free to contribute to this project. Happy coding!
