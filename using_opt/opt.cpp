#include<iostream>
#include<cstdlib>
#include<getopt.h>
using namespace std;
const char* program_name;
void OutputInfo(ostream& os,int exit_code){
  os<<"Usage: "<<program_name<<" options [filename]" <<endl;
  os << " -h --help: Display this usage information." << endl;
  os << " -o --output filename: Write output to file." << endl;
  os << " -v --verbose: Print verbose messages." << endl;
  exit( exit_code );
}
int main(int argc,char* argv[]){
  //  全部短选项的合并字符串，“:”表示带有附加参数
  const char* const short_opts="ho:v";
  const struct option long_opts[]={
    {"help",0,NULL,'h'},
    {"output",1,NULL,'o'},//1表示有附加参数
    {"verbose",0,NULL,'v'},
    {NULL,0,NULL,0}//最后要封装一个空选项
  };
  //  参数指定的输出文件名
  const char* output_filename=NULL;
  //  是否显示复杂信息
  int verbose=0;
  program_name=argv[0];
  int opt=getopt_long(argc,argv,short_opts,long_opts,NULL);
  while (opt!=-1) {
    switch (opt) {
      case 'h'://-h或者-help
        OutputInfo( cout, 0 );
      case 'o'://-o
        output_filename=optarg; break;
      case 'v':
        verbose=1; break;
      case '?'://无效参数
        OutputInfo(cerr,1);
      default://未知错误
        abort();
    }
    opt=getopt_long(argc,argv,short_opts,long_opts,NULL);
  }
  return 0;
}
