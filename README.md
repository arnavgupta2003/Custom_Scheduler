<H1 align = "center"> Scheduling In Linux </H1>
<p align="Left">
  -> Implementing functions to custom schedule them according to the user. 
  <br> -> Launching three threads, each of which relies on three different
functions, countA(), countB() and countC().
  <br>
  -> Launching three processes, each of which relies on three different
scripts to compile a custom linux kernel.
  <br>
  -> Uses clock_gettime() to get the current time.
</p>

## Q1.1) Thread Scheduling
<p align="Left">
  -> Using Linux's scheduling policies for three threads. 
  <br> -> Launching three threads, each of which relies on three different
functions, countA(), countB() and countC().
  <br>
  -> Each function does the same thing, i.e. counts from 1 – 2^32.
  <br>
  -> Uses clock_gettime() to get the current time.
  <br>
  -> Uses pthread_schedsetparam() to change priority of the threads.
</p>

## `Installation`

```console
# Navigate to src
$> cd src

# run the makefile
$> make -f MakeFile_Thread_1.mak
       OR
$> make
```

## `Results`
`
Available at: /src/Plot_Thread_1.pdf
`

## Q1.2) Process Scheduling
<p align="Left">
  -> Using Linux's scheduling policies for three processes. 
  <br> -> Launching three processes, each of which relies on three different
scripts to compile a custom linux kernel.
  <br>
  -> Uses clock_gettime() to get the current time.
  <br>
  -> Uses sched_setscheduler() to change priority of the processes.
</p>

## `Installation`

```console
# Navigate to src
$> cd src

# run the makefile
$> make -f MakeFile_Process_1_2.mak
       OR
$> make
```
## `Results`
`
Available at: /src/Plot_Process_1_2.pdf
`

<br>

## Q2) Kernel Memory Copy
<p align="Left">
  -> Creating a system call to read data bytes from user space
and write back to user space . 
  <br> -> In other words, this is a version of memcpy() that
relies on the kernel to do the necessary copy operations, which are otherwise usually done directly in the user space.
  -> Uses clock_gettime() to get the current time.
  <br>
  -> Uses __copy_from_user() & __copy_to_user() to read bytes from user space and write back to user space.
</p>

## `Installation`

```console
#Navigate to src
$> cd src

# Compile the Kernel located in /res
$> ./t

# run the diff
$> diff --normal /linux-5.19.8 /linux-5.19.8_Norm
```

<br>

## `diff`

```console
375c375
< 451   common  kernel_2d_memcpy        sys_kernel_2d_memcpy

2789a2790,2799
> SYSCALL_DEFINE4(kernel_2d_memcpy,float *, src,float *,dest,int, row,int,col){
>       float buffer[row][cal];
>       if(__copy_from_user(buffer,src,sizeof(int)* (buffer))){
>               return -EFAULT;
>       }
>       if(__copy_to_user(dest,buffer,sizeof(int)* (buffer))){
>               return -EFAULT;
>       }
>       return 0;
> }


```
## `Results`
`
Available at: /src/DIFF_SYSCALLDEFINE_2.pdf
`
<br><br><br><br>
<br><br><br><br>
<br><br><br><br>
## License

MIT © Arnav Gupta 2022<br/>
Original Creator - [Arnav Gupta](https://github.com/arnavgupta2003)
<br><br>
MIT License

Copyright (c) 2022 Arnav Gupta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
<br>

<p align=center> --- EOF --- </p>
