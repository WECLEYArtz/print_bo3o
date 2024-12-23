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
	if (size > 16)
		size = 16;
	size_t prints=size ;
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
		write(1,"     ",5);
	write(1," ",1);
}
// 000007ffd62cd1af0:^@=426f=6e6r=6f75=7220=6c65=7320=616d=696e Bonjour les amin.$
// 000007ffd62cd1ae0:^@=426f=6e6a=6f75=7220=6c65=7320=616d=69YZ-XZYZ Bonjour les ami.$
// 000007ffd62cd1ade:^@=42YZ-XZYZ-XZYZ-XZYZ-XZYZ-XZYZ-XZYZ-XZYZ-XZYZ B.
unsigned int print_str_pntbl(char *straddr, unsigned int size){
	size_t prints = 0;
	while(size !=0 && prints++ < 16 && size--)
		if( 32 <= *straddr && *straddr <= 126 )
			write(1,straddr++,1);
		else
		{
			write(1,".",1);
			straddr++;
		}

	return size;
}

void *ft_print_memory(void *addr, unsigned int size){
	char hexMap[]= "0123456789abcdef";

	// intptr_t intaddr = (intptr_t)addr; 
	// char *straddr = (char *)addr;
	while(size != 0){
		//	COLUMN 1
		print_mem_hex((intptr_t)addr, hexMap, 0);//Func 1
		write(1, ":",2);
		//	COLUMN 2
		print_str_hex((char *)addr, hexMap, size);//Func 2 
		//	COLUMN 3
		size = print_str_pntbl((char *)addr, size);//Func 3

		//if (size > 16)//protect size_t from overflow
		//			  //even tho i better use int
		//	size -=16;
		addr += 0x10;
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

// int main(){
// 	ft_putstr_non_printable("Coucou\n\t\atu vas bien ?");
// }
