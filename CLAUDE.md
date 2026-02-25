# netc

A lightweight C HTTP client that reads a request from a file, sends it over TCP, and parses the response using the Node.js http-parser library.

## Build & run

```bash
make              # build (outputs ./net on Linux/macOS, net.exe on Windows)
make test         # build and run all 21 unit tests
make clean        # remove all build artifacts
```

Windows (MinGW/MSYS2):
```bash
make              # automatically links -lws2_32
```

## Architecture

```
main.c            entry point — connect, send, parse, print
strutils.c/h      string utilities: replace(), push_str()
net.c/h           cross-platform TCP socket abstraction
netfile.c/h       file I/O: reads request.net, writes response.net
rparse.c/h        http-parser callback implementations, populates http_t struct
http-parser/      embedded Node.js HTTP parser (C library, git submodule)
test/             unit test suite
```

## Platform support

- Linux (x86-64)
- macOS ARM64 (Apple Silicon)
- Windows (MinGW/MSYS2, Winsock2)

Platform detection is done at compile time via `_WIN32` and `uname -s` in the Makefile.
The socket type is `net_socket_t` (POSIX `int` or Windows `SOCKET`).

## Tests

Tests live in `test/` and use the minimal framework in `test/test_framework.h` — no external dependencies.

| Suite | File | Tests |
|-------|------|-------|
| String utils | `test/test_strutils.c` | 7 |
| File I/O | `test/test_netfile.c` | 4 |
| HTTP parser callbacks | `test/test_rparse.c` | 7 |
| Socket lifecycle | `test/test_net.c` | 3 |

`test/test_rparse.c` feeds synthetic HTTP response strings directly to `http_parser_execute()` — no network required.

CI runs on every push via GitHub Actions (`.github/workflows/ci.yml`) against `ubuntu-latest` and `macos-latest`.

## Runtime files

The binary reads/writes two files in the working directory:

- `request.net` — HTTP request to send (must exist before running)
- `response.net` — raw HTTP response written after each run

Both are gitignored.

## Known limitations

- Server address and port are hardcoded to `127.0.0.1:80` in `main.c`
- Response buffer is capped at `MAX_REQ_SIZE` (8192 bytes) in `net.h`
- `http_t` supports a maximum of 256 response headers
