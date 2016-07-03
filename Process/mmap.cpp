#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <wait.h>
#include <iostream>
#include <iomanip>
const int mapped_size = 4096;
const int mapped_count = mapped_size / sizeof(int);
int main( int argc, char * const argv[] )
{
  //  打开文件作为内存映射的对象，确保文件尺寸足够存储1024个整数
  int fd = open( argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
  lseek( fd, mapped_size - 1, SEEK_SET );
  write( fd, "", 1 );
  lseek( fd, 0, SEEK_SET );
  int * base = ( int * )mmap( 0, mapped_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, fd, 0 );
  close( fd );		//  创建映射内存后，关闭文件的文件描述符
  pid_t pid = fork();
  if( pid == (pid_t)0 )	//  子进程写入数据
  {
    //  写入数据0～1023
    std::cout << "child process start" << std::endl;
    for( int i = 0, * p = base; i < mapped_count; *p++ = i++ )
      ;
    munmap( base, mapped_size );
  }
  else if( pid > (pid_t)0 )	// 父进程读取数据
  {
    sleep( 10 );		//  等待10秒
    std::cout << "father process start" << std::endl;
    sleep(3);
    for( int i = 0, *p = base; i < mapped_count; i++, p++ )
      std::cout << std::setw(5) << *p << " ";
    std::cout << std::endl;
    munmap( base, mapped_size );
  }
  return 0;
}
