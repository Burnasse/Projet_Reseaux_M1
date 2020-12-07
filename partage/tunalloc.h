#ifndef TUNALLOC_H
#define TUNALLOC_H

/**
 Créer l'inteface TUN
*/
int tun_alloc(char *dev);

/**
Recopie perpétuellement toutes les données de src dans dst
*/
int writeTun(int src, int dst);

#endif