struct func_wrapper{
    void* (*func)(void *);
    void *arg;
};

void user_thread_wrapper(void *arg) {
    struct func_wrapper *argu = (struct func_wrapper*) arg;
    void *ret = argu->func(argu->arg);
    thread_exit(ret);
}

int pthread_create(int* tid, void* func, void* arg) {
    struct func_wrapper *fc = malloc(sizeof(struct func_wrapper));
    void*(*cast_ptr)(void *) = (void*(*)()) func;
    fc->func = cast_ptr, fc->arg = arg;
    int ret = thread_create(tid, &user_thread_wrapper, fc);
    free(fc);
    return ret;
}

int pthread_join(int tid, void* ret) {
    return thread_join(tid, ret);
}