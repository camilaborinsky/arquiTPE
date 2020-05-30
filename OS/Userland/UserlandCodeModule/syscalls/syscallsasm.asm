GLOBAL sys_drawCharacter


sys_drawCharacter: ;int x, int y, int px, char letter
    push rbp
    mov rbp,rsp
    mov rax, 1
    int 80h
    mov rsp,rbp
    pop rbp
    ret

sys_readKeyboard:  ;char* buffer, int count
	push rbp
	mov rbp, rsp
	mov rax, 2
	int 80h
	mov rsp, rbp
	pop rbp
	ret

sys_drawBitmap:  ;int x, int y, char * bitmap
	push rbp
	mov rbp, rsp
	mov rax, 3
	int 80h
	mov rsp, rbp
	pop rbp
	ret	


sys_cpuTemp:  ;double * temp
	push rbp
	mov rbp, rsp
	mov rax, 4
	int 80h
	mov rsp, rbp
	pop rbp
	ret




