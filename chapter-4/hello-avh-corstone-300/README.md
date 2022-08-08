## Hello world example on AVH Corstone-300

To build the application with semihosting

```console
  cd make/
  make 
```
  
To run with semihosting
  
```console
  ./run.sh
```
  
To build the application with UART support

```console
  cd make_uart
  make UART=1
```

To run with UART

```console
  ./run.sh -a hello.axf
```
