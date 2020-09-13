#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct arguments
{
   int thread_id;
   int *counter;
   pthread_cond_t condition;
   pthread_mutex_t mutex;
};

void *do_work( void *arg )
{
   struct arguments *argu = (struct arguments *) arg;
   int counter = *argu->counter;
   int id = argu->thread_id;
   pthread_mutex_t mutex = argu->mutex;
   pthread_cond_t condition = argu->condition;

   if( id == 0)
   {
      pthread_mutex_lock(&mutex);
      while( counter == 0 )
      {
         pthread_cond_wait( &condition, &mutex );
      }
      counter = counter + 1;
      printf( "Counter: %d\n", counter );
      pthread_mutex_unlock(&mutex);
   }
   else if( id == 1)
   {
      pthread_mutex_lock(&mutex);
      counter = counter - 1;
      printf( "Counter: %d\n", counter );
      pthread_cond_signal( &condition );
      pthread_mutex_unlock(&mutex);
   }

   return NULL;
}

int main()
{

   pthread_t thread_0, thread_1;
   struct arguments *arg_0, *arg_1;
   int counter = 0; 
   pthread_cond_t condition;
   pthread_mutex_t mutex;

   pthread_mutex_init( &mutex, NULL );
   pthread_cond_init(&condition, NULL );

   arg_0 = (struct arguments *) calloc(1, sizeof(struct arguments));
   arg_0->thread_id = 0;
   arg_0->counter = &counter;
   arg_0->condition = condition;
   arg_0->mutex = mutex;

   arg_1 = (struct arguments *) calloc(1, sizeof(struct arguments));
   arg_1->thread_id = 1;
   arg_1->counter = &counter;
   arg_1->condition = condition;
   arg_1->mutex = mutex;

   pthread_create(&thread_0, NULL, do_work, (void *)arg_0);
   pthread_create(&thread_1, NULL, do_work, (void *)arg_1);

   pthread_join(thread_0, NULL);
   pthread_join(thread_1, NULL);

   return 0;
}










































