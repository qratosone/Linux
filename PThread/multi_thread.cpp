#include <pthread.h>
#include <cmath>
#include <iostream>

void *  IsPrime( void * n )
{
  unsigned int  p = reinterpret_cast<unsigned int>( n );
  unsigned int  i = 3u, t = (unsigned int)sqrt( p ) + 1u;
  if( p == 2u )
    return reinterpret_cast<void *>( true );
  if( p % 2u == 0u )
    return reinterpret_cast<void *>( false );
  while( i <= t )
  {
    if( p % i == 0u )
      return reinterpret_cast<void *>( false );
    i += 2u;
  }
  return reinterpret_cast<void *>( true );
}
int  main()
{
  pthread_t  tids[8];
  bool  primalities[8];
  int i;
  for( i = 0; i < 8; i++ )
    pthread_create( &tids[i], NULL, &IsPrime, reinterpret_cast<void *>( i+2 ) );
  for( i = 0; i < 8; i++ )
    pthread_join( tids[i], reinterpret_cast<void **>( &primalities[i] ) );
  for( i = 0; i < 8; i++ )
    std::cout << primalities[i] << " ";
  std::cout << std::endl;
  return 0;
}
