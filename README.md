# Advent of Code 2023 Solutions

This repository contains my personal solutions for the [Advent of Code 2023](https://adventofcode.com/2023) challenges, implemented in C++. The solutions are designed to be efficient and readable.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installation

**Prerequisites:**
- A C++ compiler (e.g., MSVC, Clang)
- [CMake](https://cmake.org/)
- [Make](https://www.gnu.org/software/make/)

To set up the project, start by cloning the repository with all submodules:
```bash
git clone --recurse-submodules https://github.com/tomlegodais/aoc-2023.git
cd aoc-2023
```

After cloning, initiate and install the required packages via vcpkg:
```bash
./vcpkg/bootstrap-vcpkg.sh
./vcpkg/vcpkg install
```

Build the project using `make`. For a debug build, simply run `make debug` or `make` (as it defaults to debug). For a release build, use `make release`.

Finally, create a `.session` file in the root directory and add your Advent of Code session cookie value to it. This value can be retrieved from the Cookies section in the Application tab of your browser's developer tools while on `https://adventofcode.com`.

## Usage
To run the application, use the `make` command in your terminal.

Run the application with the debug profile (make sure it's already built):
```bash
make run
```

For building and running in debug mode in one step:
```bash
make debug run
```

To run the application with the release profile:
```bash
make release run
```

Note: It's important to build the project in the desired profile (debug or release) before executing these run commands.

## Contributing
Contributions to this project are welcome! To contribute, please follow these steps:

1. Fork the repository.
2. Make your changes or improvements in your forked version.
3. Create a pull request with a clear description of your changes.

Your pull requests will be reviewed, and once approved, they will be merged into the main project. This is a great way to contribute to the improvement and evolution of the solutions provided in this repository.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.