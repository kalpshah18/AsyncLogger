# ConcurrentLogger

A high-performance asynchronous logging library written in modern C++. The logger is designed using a producer-consumer architecture where multiple application threads enqueue log messages into a thread-safe blocking queue while a dedicated background thread performs all disk I/O.

This design minimizes contention between worker threads and eliminates the need for every thread to compete for file access.

---

## Features

* Thread-safe asynchronous logging
* Producer-consumer architecture
* Generic `BlockingQueue<T>` implementation
* Dedicated background writer thread
* Multiple log levels
* Automatic timestamps
* Thread ID logging
* Source file and line number metadata
* FIFO ordering of log messages
* Automatic cleanup through RAII
* Cross-platform C++17 implementation

---

## Architecture

```
                Worker Thread 1
                       │
                LOG_INFO(...)
                       │
                Worker Thread 2
                       │
                LOG_ERROR(...)
                       │
                Worker Thread N
                       │
        --------------------------------
        |        Logger Interface       |
        --------------------------------
                       │
                       ▼
            Thread-safe Blocking Queue
      (mutex + condition_variable)
                       │
                       ▼
           Dedicated Background Thread
                       │
                       ▼
               LogFormatter
                       │
                       ▼
               application.log
```

Only the background thread performs file writes, allowing application threads to continue executing with minimal blocking.

---

## Project Structure

```
ConcurrentLogger
│
├── include
│   ├── BlockingQueue.hpp
│   ├── BlockingQueue.tpp
│   ├── Logger.hpp
│   ├── LogFormatter.hpp
│   └── LogMessage.hpp
│
├── src
│   ├── Logger.cpp
│   └── LogFormatter.cpp
│
├── examples
│   └── main.cpp
│
├── benchmarks
│
└── CMakeLists.txt
```

---

## Logging API

```cpp
LOG_TRACE("Trace message");

LOG_DEBUG("Debug message");

LOG_INFO("Server started");

LOG_WARN("Disk usage high");

LOG_ERROR("Database connection failed");

LOG_FATAL("Unexpected failure");
```

Each macro automatically captures

* timestamp
* thread ID
* source file
* source line number

without additional user code.

---

## Example Output

```
2026-06-26 18:34:21.531 [INFO] [TID 12044] main.cpp:15 Server started

2026-06-26 18:34:22.014 [WARN] [TID 12051] Server.cpp:81 High memory usage

2026-06-26 18:34:23.188 [ERROR] [TID 12044] Socket.cpp:54 Failed to bind socket
```

---

## Building

Clone the repository

```bash
git clone https://github.com/kalpshah18/AsyncLogger.git
```

Configure

```bash
cmake -S . -B build
```

Build

```bash
cmake --build build
```

Run the example

```bash
./build/ConcurrentLogger
```

---

## Design Decisions

### Asynchronous Logging

Instead of allowing every thread to write directly to the log file, worker threads only enqueue log messages.

This prevents contention on the output file and significantly reduces time spent waiting on disk I/O.

---

### Producer-Consumer Model

The logger follows the classic producer-consumer design pattern.

* Producers are application threads generating log messages.
* The consumer is a dedicated logging thread responsible for writing messages to disk.

Communication is performed through a generic thread-safe blocking queue.

---

### Blocking Queue

The queue is implemented using

* `std::mutex`
* `std::condition_variable`
* `std::queue`

It supports

* concurrent producers
* a blocking consumer
* graceful shutdown

The queue implementation is generic and reusable in other concurrent systems such as thread pools or task schedulers.

---

### RAII

The logger automatically

* starts its background thread during construction
* joins the worker thread during destruction
* flushes pending log messages
* closes the output file safely

No manual resource management is required by the user.

---

## Technologies

* C++17
* STL
* Multithreading
* Mutexes
* Condition Variables
* Producer-Consumer Pattern
* RAII
* CMake

---

## Future Improvements

* Batched disk writes
* Lock-free queue implementation
* Multiple output sinks (console, file, network)
* Configurable formatting
* JSON log output
* Log rotation
* Runtime log level filtering
* Configurable flush intervals
* Performance benchmarking suite
* Unit tests