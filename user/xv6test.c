#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/thread.h"

void *myfunc(void) {
    printf("Hello from myfunc\n");
    // sleep(3);
    // int x = 10;
    // x += 10;
    // printf("%d\n", x);
    return 0;
}

void *myfunc2(void *argu) {
    sleep(2);
    int x = *(int*)argu;
    x *= 20;
    printf("%d\n", x);
    return 0;
}

void *myfunc3(void *argu) {
    int x = *(int*)argu;
    x *= 20;
    int *ret = malloc(sizeof(int));
    *ret = x;
    return ret;
}

int main(int argc, char *argv[]) {
    printf("Hello from my test case in xv6\n");
    int tid3;
    // int tid2;
    int tid, tid2;
    int argu = 100;
    pthread_create(&tid, myfunc, 0);
    printf("the tid of my child1 is %d\n", tid);
    pthread_create(&tid2, myfunc2, &argu);
    printf("the tid of my child2 is %d\n", tid2);
    pthread_create(&tid3, myfunc3, &argu);
    sleep(10);
    pthread_join(tid, 0);
    pthread_join(tid2, 0);
    int *ret = 0;
    pthread_join(tid3, &ret);
    printf("The return value is %d\n", *ret);
    free(ret);
    exit(0);
}