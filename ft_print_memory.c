// Coucou\ntu vas bien ?
// Coucou\0atu vas bien ?
// hexbuff[ | | | | | | | | | | | | | | | ]

#include <unistd.h>
#include <stdio.h>

char *get_mem_hex(intptr_t ptr, char *hexMap, char *hexBuff){
	if (ptr/16)
		hexBuff = get_mem_hex(ptr/16, hexMap, hexBuff-1);
	*hexBuff = hexMap[ptr%16];
	return (hexBuff+1);
}

void *ft_print_memory(void *addr, unsigned int size){
	char hexMap[]= "0123456789abcdef";
	char hexBuff[17];

	intptr_t intaddr = (intptr_t)addr; 
	get_mem_hex(intaddr, hexMap, hexBuff+15);
	size_t i = 0;

	while(!hexBuff[i])
		hexBuff[i++] = '0';
	hexBuff[15] = 0;

	return addr;
}
int main(void){
}

// int main(){
// 	ft_putstr_non_printable("Coucou\n\t\atu vas bien ?");
// }
