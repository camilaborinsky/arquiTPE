

void divisionbyzero(){
    int a=0;
    int b=1/a;
}

void invalidopcode(){
    char buffer[]="esto no es un opcode";
    void  (* func)(void)=buffer;
    func();
}