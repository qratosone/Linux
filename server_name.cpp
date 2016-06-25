#include<iostream>
#include<cstdlib>

using namespace std;
int main(){
  char* server_name=getenv("SERVER_NAME");
  if (!server_name) {
    server_name="server.yours.com";
  }
  cout << "accessing server " << server_name << endl;
  return 0;
}
