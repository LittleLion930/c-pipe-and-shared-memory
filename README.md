# c-pipe-and-shared-memory

# Inter-Process Communication with Pipes

Demonstrates bidirectional message passing between parent and child processes using UNIX pipes.

## Features
- **Unidirectional pipe**: Initial implementation with one-way communication[^1]
- **Bidirectional communication**: Enhanced version using two pipes for parent↔child messaging
- **Process synchronization**: Proper `wait()` usage to prevent race conditions
