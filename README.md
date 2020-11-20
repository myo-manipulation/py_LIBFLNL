# libFLNL
C++ Fast Light Network Library for simple real-time data exchange

### Features:
- Exhange of a fixed number of double values and simple characters commands between a server and a client
- No buffering: only last received values are available
- Fixed predefined frame size  
- Simple data integrity check
- Based on BSD sockets
- Windows and Unix

### Warning
The library assumes the same representation of double types on both sides. A simple bytes size is performed at runtime and it will work just fine on most modern compiler.

### Requirements
The library uses pthread.
