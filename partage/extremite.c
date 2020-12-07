#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>

#include "extremite.h"
#include "tunalloc.h"

void sendToTun(int s, int tun){
	char buffer[1500];
	int lenMsg = recv(s, buffer, 1500, 0);
	if(lenMsg < 0) {
		perror("read");
	}
	if(write (tun, buffer, lenMsg) < 0){
		perror("write");
	}
}

int ext_out(int tun){
	
  int s,n; /* descripteurs de socket */
  int len,on; /* utilitaires divers */
  struct addrinfo * resol; /* résolution */
  struct addrinfo indic = {AI_PASSIVE, /* Toute interface */
                           PF_INET6,SOCK_STREAM,0, /* IP mode connecté */
                           0,NULL,NULL,NULL};
  struct sockaddr_in client; /* adresse de socket du client */
  char * port; /* Port pour le service */
  int err; /* code d'erreur */
  
  strcpy(port, "123");;
  err = getaddrinfo(NULL,port,&indic,&resol); 
  if (err<0){
    fprintf(stderr,"Résolution: %s\n",gai_strerror(err));
    exit(2);
  }

  /* Création de la socket, de type TCP / IP */
  if ((s=socket(resol->ai_family,resol->ai_socktype,resol->ai_protocol))<0) {
    perror("allocation de socket");
    exit(3);
  }
  fprintf(stderr,"le n° de la socket est : %i\n",s);

  /* On rend le port réutilisable rapidement /!\ */
  on = 1;
  if (setsockopt(s,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0) {
    perror("option socket");
    exit(4);
  }
  fprintf(stderr,"Option(s) OK!\n");

  /* Association de la socket s à l'adresse obtenue par résolution */
  if (bind(s,resol->ai_addr,sizeof(struct sockaddr_in6))<0) {
    perror("bind");
    exit(5);
  }
  freeaddrinfo(resol); /* /!\ Libération mémoire */
  fprintf(stderr,"bind!\n");

  /* la socket est prête à recevoir */
  if (listen(s,SOMAXCONN)<0) {
    perror("listen");
    exit(6);
  }
  fprintf(stderr,"listen!\n");

  while(1) {
    /* attendre et gérer indéfiniment les connexions entrantes */
    len=sizeof(struct sockaddr_in);
    if( (n=accept(s,(struct sockaddr *)&client,(socklen_t*)&len)) < 0 ) {
      perror("accept");
      exit(7);
    }
    /* Nom réseau du client */
    char hotec[NI_MAXHOST];  char portc[NI_MAXSERV];
    err = getnameinfo((struct sockaddr*)&client,len,hotec,NI_MAXHOST,portc,NI_MAXSERV,0);
    if (err < 0 ){
      fprintf(stderr,"résolution client (%i): %s\n",n,gai_strerror(err));
    }else{ 
      fprintf(stderr,"accept! (%i) ip=%s port=%s\n",n,hotec,portc);
    }
	
	sendToTun(n, tun);
  }
  return EXIT_SUCCESS;
}

int ext_in(char* ipServ, char* port, int tun)
{ 
  char ip[INET_ADDRSTRLEN];
  struct addrinfo *resol; /* struct pour la résolution de nom */
  char * tmpdst; /* chaine pour la notation en IPv6 */
  int s; /* descripteur de socket */

  /* Résolution de l'hôte */
  if ( getaddrinfo(ipServ,port,NULL, &resol) < 0 ){
    perror("résolution adresse");
    exit(2);
  }

	inet_ntop(resol->ai_family, resol, ip, INET_ADDRSTRLEN);

	s = socket(resol->ai_family, resol->ai_socktype, resol->ai_protocol);
  /* Création de la socket, de type TCP / IP */
  /* On ne considère que la première adresse renvoyée par getaddrinfo */
  printf("Essai de connexion à %s /// ip = %s sur le port %s \n", ipServ, ip, port);
  int c = connect(s, resol->ai_addr, sizeof(struct sockaddr_in));
	while( c < 0) {
		sleep(2);
		printf("Essai de connexion à %s /// ip = %s sur le port %s \n", ipServ, ip, port);
		c = connect(s, resol->ai_addr, sizeof(struct sockaddr_in));
	}
  fprintf(stderr,"le n° de la socket est : %i\n",s);

  freeaddrinfo(resol); /* /!\ Libération mémoire */

  while( 1 ) {
    writeTun(tun, s);
  } 
  /* Destruction de la socket */
  close(s);

  fprintf(stderr,"Fin de la session.\n");
  return EXIT_SUCCESS;
}
