#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
const int buf_size = 4096;

//  向stream中写入count次msg
void Write( const char * msg, int count, FILE * stream )
{
  for( ; count > 0; --count )
  {
    fprintf( stream, "%s\n", msg );
    fflush( stream );
    sleep (1);
  }
}
void Read(FILE* stream){
  char buf[buf_size];
  while (!feof(stream)&&!ferror(stream)&&fgets(buf,sizeof(buf),stream)!=NULL) {
    fprintf(stdout, "Data recieved \n" );
    fputs(buf,stdout);
  }
}
int main(){
  int fds[2];
  pipe(fds);
  pid_t pid=fork();
  if( pid == 0 )  {	//  子进程
    char buf[buf_size];	//  数据缓冲区，末尾封装两个‘\0’
    std::cout << "child process writing" << std::endl;
    for( int i = 0; i < buf_size-2; i++ )    buf[i] = 'A' + i % 26;
    buf[buf_size-1] = buf[buf_size-2] = '\0';
    close( fds[0] );		//  只写入，关闭管道读取端
    FILE * stream = fdopen( fds[1], "w" );
    Write( buf, 3, stream );
    close( fds[1] );		//  关闭管道写入端
    std::cout << "writing finished " << std::endl;
}
else if( pid > 0 )  {	//  父进程
  close( fds[1] );		//  只读取，关闭管道写入端
  //  将文件描述符转换为FILE *，以方便C/C++标准库函数处理
  std::cout << "father process" << std::endl;
  int child_status;
  wait(&child_status);
  std::cout << "child process finished" << std::endl;
  FILE * stream = fdopen( fds[0], "r" );
  Read( stream );		//  从流中读取数据
  close( fds[0] );		//  关闭管道读取端

}
return 0;
}
