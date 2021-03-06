#ifndef UTIL_H
#define UTIL_H

#define PANIC() do { kernel_panic(__FILE__,__LINE__) ; } while(0)
#define ASSERT(exp) do { if(!(exp)) PANIC(); } while(0)

void kernel_panic(char* string, int number);
int pow(int x, int y);
int mod(int a, int b);
void int_to_str(char* str ,int n);
#endif
