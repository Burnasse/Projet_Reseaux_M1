#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tunalloc.h"

int main (int argc, char** argv){
  char tunName[100];
  strcpy(tunName, "tun0");
  int tun = tun_alloc(tunName);
  
  if(tun < 0){
    printf("Error tun_alloc \n");
    return 1;
  }

  system("./configure-tun.sh");

  printf("Configuration terminée\n");

//src = tun & dst = 1
  while(1) {
    writeTun(tun, 1);
  }

  return 0;
}