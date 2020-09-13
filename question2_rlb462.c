#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

struct arguments
{
   int thread_id;
   int *counter;
   pthread_mutex_t mutex;
};

void *do_work( void *arg )
{
   struct arguments *argu = (struct arguments *) arg;
   int *counter = argu->counter;
   int id = argu->thread_id;
   pthread_mutex_t mutex = argu->mutex;

   if( id % 2 == 0)
   {
      pthread_mutex_lock(&mutex);
      counter = counter - 1;
      pthread_mutex_unlock(&mutex);
   }
   else
   {
      pthread_mutex_lock(&mutex);
      counter = counter + 1;
      pthread_mutex_unlock(&mutex);
   }

   return NULL;
}

int main()
{
   pthread_t thread_array[10];
   struct arguments *ids[10];
   int counter = 0; 
   pthread_mutex_t mutex;

   pthread_mutex_init( &mutex, NULL );

   for( int index = 0; index < 10; index++)
   {
      ids[index] = ( struct arguments *) calloc( 1, sizeof (struct arguments ));
      ids[index]->thread_id = index;
      ids[index]->counter = &counter;
      ids[index]->mutex = mutex;
      
      pthread_create(&thread_array[index], NULL, do_work, (void *)ids[index]);
   }

   for( int index = 0; index < 0; index++)
   {
      pthread_join( thread_array[index], NULL );
   }

   printf("Counter final value: %d\n", counter);

   return 0;
}
