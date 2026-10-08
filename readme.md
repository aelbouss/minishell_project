# minishell — As beautiful as a shell can be 🐚

Ask any 42 student which project gave them trust issues with edge cases, and 9 times out of 10, the answer is **minishell**.

Before building this, the terminal felt like a black box: you type something, hit Enter, and things just work. Minishell is about opening that box and writing our own mini version of Bash completely from scratch in C. 

This project was built as a team effort with my friend and peer. Together, we spent countless hours whiteboarding parsers, tracking down zombie processes at 2 AM, and arguing over how Bash handles nested quotes.

No shortcuts. Just reading raw user input, breaking down syntax, juggling processes, handling signals, and making sure not a single byte of memory or open file descriptor leaks along the way.

---

### What it actually does

You launch `./minishell`, and it drops you into an interactive prompt with history support that behaves just like a real shell:

* **Runs system commands:** Anything living in your `$PATH` (like `ls`, `grep`, `cat`, `awk`) or direct binary paths (`./my_script`, `/bin/ps`).
* **Built-in commands:** Written from scratch so they run directly in the parent process without unnecessary forks:
  * `echo` (with the `-n` flag)
  * `cd` (moving around directories with relative, absolute, or empty paths)
  * `pwd` (prints current working directory)
  * `export` (setting and updating environment variables)
  * `unset` (removing environment variables)
  * `env` (listing active environment variables)
  * `exit` (clean exit with proper numeric exit codes)
* **Pipes (`|`):** Connects commands seamlessly so output passes directly down the line without writing temporary files to disk.
* **Redirections:**
  * `<` read input from a file
  * `>` redirect output to a file (overwrite)
  * `>>` redirect output to a file (append)
  * `<<` (heredoc) interactive multi-line input until a custom delimiter keyword is typed
* **Environment variables:** Expands `$VAR` and `$?` (the exit status of the most recently finished foreground command).
* **Quotes management:** Handles `'single quotes'` (literal string, zero expansion) and `"double quotes"` (preserves whitespace, allows `$` expansion).
* **Signals:** Replicates Bash behavior for `Ctrl-C` (new prompt line), `Ctrl-D` (clean EOF exit), and `Ctrl-\` (ignored on prompt, terminates running child).

---

### How it works (The journey of a command)

Every time you type a command and hit Enter, the input goes through a four-stage pipeline:

1. **Lexing (Tokenizing):** Splits the raw input string into manageable tokens (words, pipes, redirects, quotes) while preserving context on which characters were quoted.
2. **Parsing & Syntax Checking:** Validates the grammar (catching syntax errors like unclosed quotes or floating pipes like `ls | | grep a`), expands environment variables, and packs everything into structured command nodes.
3. **Execution:** Forks child processes, creates and routes pipe channels using `pipe()` and `dup2()`, resolves binary locations through the `$PATH`, and launches commands with `execve()`.
4. **Cleanup & Exit Codes:** Waits on all child processes with `waitpid()`, collects termination statuses, and updates `$?` so the prompt knows whether the last command succeeded or failed.

---

### The real headaches (and lessons learned)

* **Dividing and conquering:** Building something this interconnected with a friend meant we had to agree on strict data structures before writing a single line of logic. If the parser's output struct changed, execution broke instantly. Good communication was half the grade.
* **Quote madness:** Things like `echo "'$USER'"` vs `echo '"$USER"'` sound simple on paper, but writing a tokenizer that gets every combination right without breaking spaces is an absolute rite of passage.
* **Signal duality:** When the shell is idle waiting for input, `Ctrl-C` should just give you a fresh empty prompt. But when a command like `cat` is running, `Ctrl-C` needs to interrupt the child process instead. Switching signal handlers back and forth without race conditions took serious patience.
* **Heredocs & Delimiters:** Gathering input until a delimiter is matched, expanding variables inside it *only* when the delimiter wasn't quoted, and keeping everything temporary in memory.
* **Leaks and zombies:** In an infinite loop shell, a single unfreed string or unclosed file descriptor will eventually crash the session. Valgrind was practically a third team member on this project.

---

### Quick Start

**1. Prerequisites:**
You need a C compiler (`gcc` or `clang`), `make`, and the `readline` library:

```bash
# On Debian/Ubuntu
sudo apt-get install libreadline-dev

# On macOS (via Homebrew)
brew install readline