
# Title: Exploring the Underlying Implementation of std::async

# Description:

This repository contains C++ code that explores the underlying mechanics of the std::async function, as described by Bartosz Milewski, a renowned computer scientist.

Bartosz Milewski outlined that the std::async function internally works as follows:

It creates a promise.

It gets the future from this promise.

It starts a new thread.

This thread runs a 'thunk' - a simple stub function.

The 'thunk' is a template function that takes the promise, calls the user-defined function inside a try-catch block.
The 'thunk' then either calls set_value with the result or set_exception (in case of an exception) on that promise.
The main thread can then retrieve the result or handle the exception using the future. This process demonstrates how std::async can return values from a worker thread back to the parent thread, or handle any exceptions that were thrown in the worker thread.

The code in this repository provides a conceptual demonstration of this process. It's worth noting that the actual implementation of std::async in the C++ Standard Library might differ and can be more complex due to optimizations and support for various launch policies.

Please note: This code is for educational purposes and may not be suitable for production environments. Always consult the appropriate documentation when working with multithreading and the C++ Standard Library.
