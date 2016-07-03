#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
int main()
{
  struct shmid_ds  shmbuf;
  int seg_size;
  const int shared_size = 0x6400;
  //  分配共享内存段
  int seg_id = shmget( IPC_PRIVATE, shared_size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR );
  //  连接共享内存段
  char * shared_mem = ( char * )shmat( seg_id, 0, 0 );
  printf( "Shared memory attached at %p\n", shared_mem );
  //  获取段尺寸信息
  shmctl( seg_id, IPC_STAT, &shmbuf );
  seg_size = shmbuf.shm_segsz;
  printf( "Segment size: %d\n", seg_size );
  //  向共享内存区段写入字符串
  sprintf( shared_mem, "Hello, world." );
  //  拆卸共享内存区段
  shmdt( shared_mem );
  //  在不同的地址处重新连接共享内存区段
  shared_mem = ( char * )shmat( seg_id, ( void * )0x5000000, 0 );
  printf( "Shared memory reattached at %p\n", shared_mem );
  //  获取共享内存区段中的信息并打印
  printf( "%s\n", shared_mem );
  //  拆卸共享内存区段
  shmdt( shared_mem );
  //  释放共享内存区段，与semctl类似
  shmctl( seg_id, IPC_RMID, 0 );
  return 0;
}
