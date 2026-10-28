*This project has been created as part of the 42 curriculum by nicolsan.*

<pre>
█████  █████         █      █████
█        █           █      █    
███      █           █      ████ 
█        █           █          █
█        █    █████  █████  █████
</pre>

> Recreation of the system `ls` command · 42 curriculum project

| Metric | Value |
| --- | --- |
| 🧠 Focus | Directory listing, file metadata, sorting, recursion |
| 🛠️ Stack | C · cc · Makefile · libft |
| 📄 Subject | [en.subject.pdf](en.subject.pdf) · version 4.0 |

---

## 🧭 Description

ft_ls recreates the system `ls` command. It reads directories with `opendir` and `readdir`, collects metadata with `lstat` and prints entries in the order and format of `ls`. The mandatory part supports the options below, alone or combined.

| Option | Effect |
| --- | --- |
| `-l` | Long format: type, permissions, links, owner, group, size, date, name |
| `-R` | Recurse into subdirectories |
| `-a` | Show hidden entries starting with `.` |
| `-r` | Reverse the sort order |
| `-t` | Sort by modification time |

The repository currently holds the structure and the skeletons: parsing, listing, sorting and printing are filled in step by step.

## 🚀 Instructions

Requires `cc` and `make`. Run from this repository:

```sh
make
make clean
make fclean
make re
```

Compilation uses `-Wall -Wextra -Werror`. The build first calls the bundled libft Makefile, then compiles `srcs/` and links against `libft/libft.a`.

## ▶️ Usage

```sh
./ft_ls
./ft_ls -l
./ft_ls -laRrt
```

## 🧪 Checks

The test environment in `tests/` covers hidden entries, symlinks, recursion, permissions, dates and special names. Compare against the system command with the same locale:

```sh
diff <(./ft_ls -l tests) <(LC_ALL=C ls -l tests)
```

## 📚 Resources

- [Project subject](en.subject.pdf).
- Local manual pages: `man 1 ls`, `man 3 opendir`, `man 2 lstat`, `man 3 getpwuid`, `man 3 strftime`.
- AI assistance was used to set up the repository structure, the Makefile and the file skeletons.

## 🗂️ Project Structure

```text
.
├── README.md
├── Makefile
├── includes/
│   └── ft_ls.h
├── srcs/
│   ├── main.c
│   ├── options.c
│   ├── arguments.c
│   ├── directory.c
│   ├── file_info.c
│   ├── output.c
│   ├── sort.c
│   ├── recursive.c
│   ├── errors.c
│   └── memory.c
├── libft/
└── tests/
```
