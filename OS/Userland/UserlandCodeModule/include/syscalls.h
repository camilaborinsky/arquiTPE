void sys_drawCharacter(int x, int y, int px, char letter);
void sys_drawBitmap();
void sys_readErrors(void * error);
void sys_readKeyboard(char * buffer,int count,int * amount);
void sys_setExceptionHandler(int exception, void * func);
void sys_scroll(int xi, int yi, int xf, int yf, int px);
void sys_retrieveReg(void * reg, int * flag);