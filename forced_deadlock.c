/* #include "philo.h"

typedef struct s_thread
{
	pthread_mutex_t lock1;
	pthread_mutex_t lock2;
	int count;
}	t_thread;


void *count_locks1(void *data)
{
	t_thread *info;
	pthread_t tid;

	info = (t_thread *)data;
	tid = pthread_self();

	printf("Thread 1 wants Lock1\n");
	pthread_mutex_lock(&info->lock1);
	printf("Thread 1 has Lock1\n");

	printf("Thread 1 wants Lock2\n");
	pthread_mutex_lock(&info->lock2);
	printf("Thread 1 has Lock2\n");

	info->count = info->count + 1;

	printf("Thread 1 wants to Unlock2\n");
	pthread_mutex_unlock(&info->lock2);
	printf("Thread 1 has been Unlocked2\n");

	printf("Thread 1 wants Unlock1\n");
	pthread_mutex_unlock(&info->lock1);
	printf("Thread 1 has been Unlock1\n");

	return (NULL);

}

void *count_locks2(void *data)
{
	t_thread *info;
	pthread_t tid;

	info = (t_thread *)data;

	tid = pthread_self();

	printf("Thread 2 wants Lock2\n");
	pthread_mutex_lock(&info->lock2);
	printf("Thread 2 has Lock2\n");

	printf("Thread 2 wants Lock1\n");
	pthread_mutex_lock(&info->lock1);
	printf("Thread 2 has Lock1\n");

	info->count = info->count + 1;

	printf("Thread 2 wants to Unlock1\n");
	pthread_mutex_unlock(&info->lock1);
	printf("Thread 2 has been Unlocked1\n");

	printf("Thread 2 wants Unlock2\n");
	pthread_mutex_unlock(&info->lock2);
	printf("Thread 2 has been Unlock2\n");

	return (NULL);

}


int main()
{
	t_thread info;
	pthread_t tid1;
	pthread_t tid2;

	pthread_mutex_init(&info.lock1, NULL);
	pthread_mutex_init(&info.lock2, NULL);
	info.count = 0;

	pthread_create(&tid1, NULL, count_locks1, &info);
	pthread_create(&tid2, NULL, count_locks2, &info);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	printf("Count = %d", info.count);

	pthread_mutex_destroy(&info.lock1);
	pthread_mutex_destroy(&info.lock2);

	return (0);



} */