<div align="center">
  <a href="https://github.com/umutsogukpinar/pipeX">
    <img src="https://github.com/ayogun/42-project-badges/blob/main/badges/pipexm.png" alt="PIPEX Logo" width="200">
  </a>

  <h1>PIPEX</h1>
  
  <p>
    <b>"Simulating the logic of Unix pipes in C."</b>
  </p>

  <p>
    <a href="https://github.com/umutsogukpinar/pipeX">
      <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" alt="C Language">
    </a>
    <a href="#">
      <img src="https://img.shields.io/badge/Score-125%2F100-success?style=for-the-badge" alt="Score">
    </a>
  </p>

</div>

---

## <a id="about"></a>🧐 About

**PIPEX** is a core **42 School** project that reimplements the fundamental behavior of Unix shell pipes (`|`) in **pure C**.

The main objective of this project is to gain a deep understanding of low-level Unix mechanisms, including:

- Inter-process communication (IPC) using pipes  
- Process creation with `fork()`  
- File descriptor redirection via `dup2()`  
- Command execution through `execve()`  

Rather than relying on the shell, PIPEX manually reproduces what happens internally when commands are chained together.

The program simulates the following shell behavior:

```bash
< file1 cmd1 | cmd2 > file2
```



## 🔧 How It Works <a id="how-it-works"></a>

PIPEX creates multiple child processes and connects them using Unix pipes.  
Each command runs in its own process, and file descriptors are redirected
so that standard input and output point to the correct sources.

```text
[ CHILD PROCESS ]                 [ CHILD PROCESS ]
     cmd1                              cmd2
   (producer)                       (consumer)
        |        +----------------+      |
        |        |                |      |
        +------> |     PIPE       | ---->+
                 |                |
                 +----------------+
        ▲                                |
        |                                ▼
     [ infile ]                      [ outfile ]
```

## 🧠 Project Structure

The project is structured to keep responsibilities clearly separated, making the codebase easier to understand and maintain.

```text
.
├── includes
│   ├── pipex.h          # Core data structures and prototypes
│   └── feedback.h       # Error and feedback utilities
│
├── libs
│   ├── gnl              # Get Next Line implementation
│   └── libft            # Custom C standard library
│
├── srcs
│   ├── main.c           # Program entry point
│   ├── init.c           # Structure and environment setup
│   ├── child.c          # Forked process logic
│   ├── execute.c        # Command resolution & execution
│   ├── execute_child.c  # Child-specific execution helpers
│   ├── fd.c             # File descriptor & pipe management
│   ├── free.c           # Memory cleanup and safe exit
│   └── utils.c          # General helper functions
│
├── Makefile             # Build rules
└── README.md            # Project documentation
```

## 🚀 Usage <a id="usage"></a>

### Compilation

```bash
make
```
#### Bonus 
```bash
make bonus
```

### Mandatory Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

Equivalent to:

```bash
< file1 cmd1 | cmd2 > file2
```

---

### Example

```bash
./pipex infile "grep hello" "wc -l" outfile
```

Equivalent shell command:

```bash
< infile grep hello | wc -l > outfile
```

---

### Bonus — Multiple Pipes

```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2
```

Equivalent to:

```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdN > file2
```

---

### Example

```bash
./pipex infile "cat" "grep error" "wc -l" outfile
```

Equivalent shell command:

```bash
< infile cat | grep error | wc -l > outfile
```

---

### Bonus — Here_doc

```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```

Equivalent to:

```bash
cmd1 << LIMITER | cmd2 >> file
```

---

### Example

```bash
./pipex here_doc EOF "cat" "wc -l" outfile
```

Equivalent shell command:

```bash
cat << EOF | wc -l >> outfile
```
