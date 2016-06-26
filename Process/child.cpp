#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
int main ()
{
  pid_t child_pid;
  child_pid = fork();
  if( child_pid > 0 ){
    std::cout << "sleeping..." << std::endl;
    sleep( 5 );
  }	//  父进程，速度睡眠六十秒

  else			//  子进程，立即退出
    exit( 0 );
  std::cout << "wake up father process" << std::endl;
  return 0;
}
