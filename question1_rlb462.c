#include <stdio.h>
#include <pthread.h>

enum id { id_0, id_1, id_2 };

void *do_work( void *arg )
{
   int id_num = (int)arg;

   printf( "Thread: %d\n", id_num );
}

int main()
{
   pthread_t thread_0, thread_1, thread_2;

   pthread_create( &thread_0, NULL, do_work, (void *)id_0 );
   pthread_create( &thread_1, NULL, do_work, (void *)id_1 );
   pthread_create( &thread_2, NULL, do_work, (void *)id_2 );

   pthread_join( thread_0, NULL );
   pthread_join( thread_1, NULL );
   pthread_join( thread_2, NULL );

   return 0;
}
