#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE4(kernel_2d_memcpy,float *, src,float *,dest,int, row,int,col){
	float * buffer=(float*)kmalloc(row*col*sizeof(float),GFP_KERNEL);
	if(__copy_from_user(buffer,src, sizeof(buffer))){
		return -EFAULT;
	}
	if(__copy_to_user(dest,buffer,sizeof(buffer))){
		return -EFAULT;
	}
	return 0;
}
