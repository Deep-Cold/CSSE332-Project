#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/thread.h"

void *myfunc(void *argu) {
    int x = *(int*)argu;
    x += 10;
    return 0;
}

void *myfunc2(void *argu) {
    int x = *(int*)argu;
    x *= 20;
    return 0;
}

int main(int argc, char *argv[]) {
    printf("Hello from my test case in xv6\n");
    int tid, tid2;
    int argu = 100;
    thread_create(&tid, myfunc, &argu);
    thread_create(&tid2, myfunc2, &argu);
    thread_join(&tid, 0);
    thread_join(&tid2, 0);
    exit(0);
}