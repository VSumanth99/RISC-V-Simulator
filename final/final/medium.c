// This is our minimal startup code (usually in _start)
asm("li sp, 0x100000"); // SP set to 1 MB
asm("jal main");        // call main
asm("mv a1, a0");       // save return value in a1
asm("li a0, 10");       // prepare ecall exit
asm("ecall");           // now your simlator should stop


int main(void) 
{
	int len = 20;
	int arr[len];
	int sum = 0;
	for (int i = 0; i < len; i++)
		arr[i] = i;
	for (int j = len-1; j>0; --j)
		sum += arr[j];
	return sum;
}
