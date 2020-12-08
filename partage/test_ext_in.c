#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iftun.h"
#include "extremite.h"

int main (int argc, char **argv){

	char tunName[100];
	strcpy(tunName, "tun0");

	int tun;
	tun = tun_alloc(tunName);

	system("./configure-tun.sh");

	printf("Configuration terminée\n");
	ext_in("172.16.2.131", "123", tun);

	return 0;
}