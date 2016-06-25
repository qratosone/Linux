#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
  cout << "Program name is " << argv[0] << endl;
  if (argc>1) {
    cout << "the following argunemts: "<< endl;
    for (int i = 1; i < argc; i++) {
      cout<<argv[i]<<endl;
    }
  }
  else{
    cout << "with no argument" << endl;
  }
  return 0;
}
