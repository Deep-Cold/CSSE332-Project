#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user/thread.h"

void *myfunc(void) {
    printf("Hello from myfunc\n");
    sleep(3);
    int x = 10;
    x += 10;
    printf("%d\n", x);
    return 0;
}

void *myfunc2(void *argu) {
    sleep(2);
    int x = *(int*)argu;
    x *= 20;
    printf("%d\n", x);
    return 0;
}

void *getf(void *argu) {
    int x = *(int*)argu;
   // printf("The value of x is %d\n", x);
    if(x <= 1) {
        int *ret = malloc(sizeof(int));
        *ret = 1;
        return ret;
    }
    int argu1 = x - 1, argu2 = x - 2;
    int *ret1 = (int*)getf(&argu1);
    int *ret2 = (int*)getf(&argu2);
    int *ret = malloc(sizeof(int));
    *ret = *ret1 + *ret2;
    free(ret1);
    free(ret2);
    return ret;
}

void *getg(void *argu) {
    int x = *(int*)argu;
   // printf("The value of x is %d\n", x);
    if(x <= 1) {
        int *ret = malloc(sizeof(int));
        *ret = 1;
        return ret;
    }
    int ch1, ch2;
    int argu1 = x - 1, argu2 = x - 2;
    pthread_create(&ch1, getg, &argu1);
    //printf("pid of child1 is %d\n", ch1);
    pthread_create(&ch2, getg, &argu2);
    //printf("pid of child2 is %d\n", ch2);
    int *ret1, *ret2;
    pthread_join(ch1, &ret1);
    pthread_join(ch2, &ret2);
    int *ret = malloc(sizeof(int));
    *ret = *ret1 + *ret2;
    free(ret1);
    free(ret2);
    return ret;
}

void *myfunc3(void *argu) {
    int x = *(int*)argu;
    sleep(2);
    x *= 20;
    int *ret = malloc(sizeof(int));
    *ret = x;
    return ret;
}

void *myfunc4(void) {
    sleep(2);
    int tid[10], argu[10];
    sleep(20);
    for(int i = 0; i < 7; i++) {
        argu[i] = i;
        pthread_create(&tid[i], getg, &argu[i]);
    }
    for(int i = 0; i < 7; i++) {
        int *ret = 0;
        pthread_join(tid[i], &ret);
        printf("The return value is %d\n", *ret);
        free(ret);
    }
    return 0;
}

int *p = (int*)(0xdeadbeef);

void *thread_t1(void *arg)
{
  p = (int*)sbrk(4096);
  p[0] = 3;
  p[1] = 2;
  return 0;
}

void *thread_t2(void *arg)
{
  sleep(50);

  if(p == (int*)(0xdeadbeef)) {
    printf("Memory not found!\n");
  }

  if(p[0] == 3 && p[1] == 2) {
    printf("Test passes!\n");
  } else {
    printf("The information is wrong!\n");
  }
  return 0;
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

    int tid4;
    pthread_create(&tid4, myfunc4, 0);
    printf("the tid of my child4 is %d\n", tid4);
    pthread_join(tid4, 0);

    int pt1, pt2;
    pthread_create(&pt1, thread_t1, 0);
    pthread_create(&pt2, thread_t2, 0);
    pthread_join(pt1, 0);
    pthread_join(pt2, 0);
    exit(0);
}