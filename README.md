# Share Memory
This project helps you to walk through the usage and the difference between 2 popular share memory acquisition: Posix and System V

With each kind of Shared Memory, I have implemented to demonstrate how to create and present you the content shared among processes. All you need is to run the `Creator` first and `Consumer` afterward

## Build And Run
Go to the specific folder for example PosixShare, run command
```
cmake -B build && cd build && make install -j8 DESTDIR=./ && cd ./usr/local/bin
```
You'll see 2 binaries "Consumer and Creator". Execute them in order I told you before


