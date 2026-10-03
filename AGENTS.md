# Project guidance

This repository contains two small C command-line tools:

- `hello.c` builds the greeting tool (`hello`).
- `date.c` builds the date and time-zone tool (`date_tool`).

## Build and check

Compile with warnings enabled:

```sh
gcc -std=c11 -Wall -Wextra -Werror hello.c -o hello
gcc -std=c11 -Wall -Wextra -Werror date.c -o date_tool
```

There is no automated test suite. When changing a tool, run its `--help` option and try representative valid input and invalid input. For `date_tool`, verify both local time and a valid IANA time-zone name such as `Asia/Tokyo`. The date tool relies on the system time-zone database, commonly located at `/usr/share/zoneinfo`.

## Project conventions

- Keep the tools small and use standard C/POSIX interfaces already used by the project.
- Preserve the existing command-line behavior and provide clear errors for invalid arguments.
- Update `README.md` when command usage, build instructions, or demo assets change.