#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int spawn(char* program,char** args);
int main(int argc, char const *argv[]) {
  char* args[]={"ls","-l","/",NULL};
  spawn("ls",args);
  int child_status;
  wait(&child_status);//等待子进程结束
  if (WIFEXITED(child_status)) {
    std::cout << "abort normally" << std::endl;
  }
  else {
    std::cout << "abort abnormally" << std::endl;
  }
  cout <<"Done!"<<endl;
  return 0;
}
int spawn( char * program, char ** args )
{
  pid_t child_pid = fork();	//  复制进程
  if( child_pid != 0 )		//  此为父进程
    return child_pid;
  else				//  此为子进程
  {
    execvp( program, args );	//  执行程序，按路径查找
    //  只有发生错误时，该函数才返回
    std::cerr << "Error occurred when executing execvp.\n";
    abort ();
  }
}
