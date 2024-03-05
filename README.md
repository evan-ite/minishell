## Minishell 42 project

This project is aimed at creating a shell called "minishell". This shell is designed to provide a command-line interface similar to other Unix-like shells such as Bash. It's capable of interpreting commands, executing programs, handling signals, and implementing various features expected from a shell environment.

---

**Installation:**

1. Clone the repository:
   ```bash
   git@github.com:evan-ite/minishell.git
   ```

2. Navigate to the project directory:
   ```bash
   cd minishell
   ```

3. Compile the project using make:
   ```bash
   make
   ```

---

**Usage:**

Run the game by executing the following command:
```bash
./minishell
```
---

**Rules and Functionality**
- **Prompt Display:**
  The shell displays a prompt when waiting for a new command.
- **History Support:**
  A working history feature is implemented, allowing users to access previously entered commands.
- **Executable Search:**
  The shell searches and launches the correct executable based on the PATH variable or using relative or absolute paths.
- **Global Variable Usage:**
  To ensure robustness, only one global variable is used to indicate a received signal, preventing potential conflicts with signal handlers.
- **Quoting Support:**
  The shell handles single quotes ('), double quotes ("), and escapes () appropriately, preventing unintended interpretation of metacharacters.
- **Redirections:**
  Supports input (<), output (>), and append mode (>>) redirections. Also handles heredoc redirection (<<).
- **Pipes:**
  Implements the pipe (|) character to connect the output of one command to the input of another.
- **Environment Variables:**
  Supports expansion of environment variables ($ followed by a sequence of characters) to their values.
- **Special Variables:**
  Handles $? expansion to the exit status of the most recently executed foreground pipeline.
- **Signal Handling:**
  Behaves similarly to Bash for ctrl-C, ctrl-D, and ctrl-\ signals.
- **Built-in Commands:**
  Implements several built-in commands such as echo, cd, pwd, export, unset, env, and exit.
- **Memory Management:**
  Ensures no memory leaks in the codebase, although readline() function may cause memory leaks, which are left unfixed.

---

**Acknowledgements**
- Marc Rodenbush
- Elise van Iterson, e.vaniterson98@gmail.com
