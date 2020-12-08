#ifndef IFTUN_H
#define IFTUN_H

/**
 Créer l'inteface TUN
*/
int tun_alloc(char *dev);

/**
Recopie perpétuellement toutes les données de src dans dst
*/
void writeTun(int src, int dst);

#endif