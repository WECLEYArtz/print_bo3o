// hexBuff[0|x|0|7|f| | | | | | | | | | |f]
//	             ^                       ^
//	  small N%16 ^              big N%16 ^

#include <unistd.h>

size_t print_mem_hex(intptr_t ptr, char *hexMap, size_t hexSz){
	if (ptr/16)
		hexSz = print_mem_hex(ptr/16, hexMap, hexSz+1);
	if(hexSz != 0)
	{
		write(1,"0000000000000000",16 - hexSz);
		hexSz=0;
	}
	write(1, &hexMap[ptr%16],1);
	return hexSz;
}

void print_str_hex(char *straddr, char *hexMap, unsigned int size){
	if (size > 16)//work with 16 bytes a time from size
		size = 16;
	size_t prints=size;
	while(prints > 0)
	{
		if(prints > 0 && prints--)
		{
			write(1," ",1);
			write(1,&hexMap[(*straddr/16)%16],1);
			write(1,&hexMap[*straddr++%16],1);
		}
		else
			write(1,"   ",3);
		if(prints > 0 && prints--)
		{
			write(1,&hexMap[(*straddr/16)%16],1);
			write(1,&hexMap[*straddr++%16],1);
		}
		else
			write(1,"  ",2);
	}
	while(prints++ != (8-((size)+(size%2))/2))// it replaces two slots
									 // at the same time.
									 //(size%2) is 1 if placeholder printed
		write(1,"     ",5);
	write(1," ",1);
}

unsigned int print_str_pntbl(char *straddr, unsigned int size){
	size_t prints = 0;
	while(size !=0 && prints++ < 16 && size--)
		if( 32 <= *straddr && *straddr <= 126 )
			write(1,straddr++,1);
		else if(1 && straddr++)// sociopathic shortening
			write(1,".",1);

	return size;
}

void *ft_print_memory(void *addr, unsigned int size){
	char hexMap[]= "0123456789abcdef";

	while(size != 0){
		//	COLUMN 1
		print_mem_hex((intptr_t)addr, hexMap, 0);
		write(1, ":",2);//cant addi it in recursion
		//	COLUMN 2
		print_str_hex((char *)addr, hexMap, size); 
		//	COLUMN 3
		size = print_str_pntbl((char *)addr, size);//return how much left
												   //from the size
												   //after printing 16 bytes

		addr += 0x10;//done with 16 byte, next
		write(1, "\n",1);
	}

	return addr;
}

int main(void){
	char str[] = 
	"Bon\n\n\n\t\0jour les amin testing this shit, hope it explodes\
	like seriously thisnt be done in less than half the pool period";
	// (fails with the stupid useless \200)
		ft_print_memory((void *)str, sizeof(str));
}
