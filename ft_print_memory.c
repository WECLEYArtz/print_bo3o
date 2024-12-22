// Coucou\ntu vas bien ?
// Coucou\0atu vas bien ?
// hexbuff[ | | | | | | | | | | | | | | | ]

#include <unistd.h>

size_t print_mem_hex(intptr_t ptr, char *hexMap, size_t hezSz){
	if (ptr/16)
		hezSz = print_mem_hex(ptr/16, hexMap, hezSz+1);
	if(hezSz != 0)
	{
		write(1,"0000000000000000",16 - hezSz);
		hezSz=0;
	}
	write(1, &hexMap[ptr%16],1);
	return hezSz;
}
void *ft_print_memory(void *addr){
	char hexMap[]= "0123456789abcdef";
	intptr_t intaddr = (intptr_t)addr; 


	print_mem_hex(intaddr, hexMap, 0);

	write(1,"\n",1);

	return addr;
}

int main(void){
	char c= 'c';
	void *addr = &c;
	ft_print_memory(addr);
}

// int main(){
// 	ft_putstr_non_printable("Coucou\n\t\atu vas bien ?");
// }
