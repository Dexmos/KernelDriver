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
 ### Must read to make it work
 
 You **may** have to change the MAJOR variable from Makefile to compile and make it work. 
 
<p align="center">
  <img width="850" height="240" src="https://github.com/Dexmos/KernelDriver/blob/master/img/MakfileVar.png">
</p>
<p align="center">
  Makefile variables.
</p>

You can find your MAJOR number at the first compilation using *make all* :
<p align="center">
  <img width="1000" height="200" src="https://github.com/Dexmos/KernelDriver/blob/master/img/MakeFileOutput.png">
</p>
