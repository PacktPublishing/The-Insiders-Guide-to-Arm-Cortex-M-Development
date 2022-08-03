# Chapter 4 Example - Hello World on AVH Corstone-300 FVP


To build the application with semihosting support

```console
  cd make/
  make 
```
To run the application with semihosting

```console  
./run.sh
```
  
To build with UART support

```console
cd make_uart
make UART=1
```
  
To run the application with UART

```console
./run.sh -a hello.axf
```

