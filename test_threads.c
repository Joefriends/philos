/* #include <pthread.h>
#include <stdio.h>
#include <unistd.h>


typedef struct s_thread
{
	int count;
	pthread_mutex_t mute;
}	t_thread;

void *thread_function(void *data)
{
	t_thread *info;
	int i;
	pthread_t tid;

	tid = pthread_self();

	i = 0;
	info = (t_thread *)data;

	pthread_mutex_lock(&info->mute);
	printf("Thread [%ld] count starts at %d\n", tid, info->count);
	pthread_mutex_unlock(&info->mute);

	while (i < 100000)
	{
		pthread_mutex_lock(&info->mute);
		i++;
		info->count++;
		pthread_mutex_unlock(&info->mute);
	}

	pthread_mutex_lock(&info->mute);
	printf("Final count for Thread [%ld] is %d\n", tid, info->count);
	pthread_mutex_unlock(&info->mute);
	return (NULL);

}
int main()
{
	pthread_t tid1;
	pthread_t tid2;

	t_thread info;

	pthread_mutex_init(&info.mute, NULL);
	info.count = 0;

	pthread_create(&tid1, NULL, thread_function, &info);
	printf("Created Thread 1 [%ld]\n", tid1);

	pthread_create(&tid2, NULL, thread_function, &info);
	printf("Created Thread 2 [%ld]\n", tid2);

	
	pthread_join(tid1, NULL);
	printf("Joined Thread 1 [%ld]\n" ,tid1);

	
	pthread_join(tid2, NULL);
	printf("Joined Thread 2 [%ld]\n" ,tid2);

	pthread_mutex_destroy(&info.mute);


	return (0);

	
} */