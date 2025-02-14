# Minishell

## As Beautiful as a Shell

Minishell is a simple shell implementation written in C, inspired by Bash. This project was created as part of our studies at Hive Helsinki to gain a deeper understanding of processes, file descriptors, and shell behavior.

## Features

- Custom interactive prompt
- Command execution using absolute, relative paths, and `PATH` resolution
- Environment variable expansion (`$VAR`)
- Input/output redirections (`<`, `>`, `<<`, `>>`)
- Pipelines (`|`) to chain multiple commands
- Built-in commands:
  - `echo` (with `-n` option)
  - `cd` (relative/absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Handling of `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` signals
- Command history with `readline`

## Installation

Clone the repository and compile the project:

```sh
git clone https://github.com/yourusername/minishell.git
cd minishell
make
```

Run the shell:

```sh
./minishell
```

## Demo Video

Check out the project in action:

![Example video](assets/minishell.webm)


## Usage

Once inside Minishell, you can execute commands just like in Bash:

```sh
$ echo "Hello, world!"
Hello, world!
$ ls -l | grep minishell
$ export MYVAR=42
$ echo $MYVAR
42
$ exit
```

## Technical Details

- Uses `fork()` and `execve()` for process handling
- `pipe()` for command chaining
- `dup2()` for redirections
- `readline()` for user input
- Minimal use of global variables for signal handling

## Authors

- **Your Name** - [GitHub](https://github.com/yourusername)
- **Teammate's Name** - [GitHub](https://github.com/theirusername)

## License

This project is for educational purposes and does not have a specific license. Feel free to explore and learn from it!

---

For any issues or suggestions, feel free to open an issue or contribute to the project!
