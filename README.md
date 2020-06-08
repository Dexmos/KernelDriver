# KernelDriver

The goal of this project is to exchange data (like char*, struct...) between Userspace and Linux-Kernel.

## How to try - Linux

Use this command line to compile and create a [device file](https://en.wikipedia.org/wiki/Device_file):
```
make all
```
To test the driver with myTest.c :
```
sudo ./myTest
```
Don't forget to unload the driver and remove the device file using :
```
make fclean
```
