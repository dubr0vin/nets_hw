#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <netdb.h>

using namespace std;

#define HEADES_SIZE 28

bool check_mtu(string host, int mtu) {
  stringstream ss;
  ss << "ping -M do -s " << mtu << " " << host;
#ifdef _WIN32 // Works for bith 32 and 64 bit
  ss << " -n 1";
#else
  ss << " -c 1";
#endif
  return system(ss.str().c_str()) == 0;
}

bool is_host_correct(string host) {
    auto ptr = gethostbyname(host.c_str());
    return ptr != NULL;
}

bool host_available(string host) {
  stringstream ss;
  ss << "ping " << host;
#ifdef _WIN32 // Works for bith 32 and 64 bit
  ss << " -n 1";
#else
  ss << " -c 1";
#endif
  return system(ss.str().c_str()) == 0;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "Usage: find_mtu HOSTNAME\n";
    return 1;
  }
  string host = argv[1];
  if (!is_host_correct(host)) {
    cout << "Incorrect host\n";
  }
  if (!host_available(host)){
    cout << "Host is unavailable or icmp is blocked\n";
    return 1;
  }
  int l = 0;
  int r = 100000;
  while (r - l > 1) {
    int m = (r + l) / 2;
    if (check_mtu(host, m)) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << "MTU is " << l + HEADES_SIZE << endl;
}