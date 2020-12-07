#ifndef EXTREMITE_H
#define EXTREMITE_H

/**

*/
int ext_in(char* ipServ, char* port, int fdTun);

/**

*/
int ext_out(int tun);

void echo(int f, char* hote, char* port);

#endif