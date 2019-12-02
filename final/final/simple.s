	.text
	li x1, 1
	li x2, 2
	li x3,0xff000000
	srai x3, x3, 8
	li x4, 0xffff0003
	xor x3, x3, x4
	li x4,0x000000ff
	slli x4,x4,3
	addi x4,x4,0x7
	xori x4, x4, 0x04
	xori x4, x4, 0x007ff
	addi a0,x0,10
	ecall


