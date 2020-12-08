#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "iftun.h"

int tun_alloc(char *dev)
{
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("alloc tun");
    exit(-1);
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
   *        IFF_TAP   - TAP device  
   *
   *        IFF_NO_PI - Do not provide packet information  
   */ 
  ifr.ifr_flags = IFF_TUN; 
  if( *dev )
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

void writeTun(int src, int dst) {
  char buffer[1500];
  int nBytes;
 
  nBytes = read(src,buffer,sizeof(buffer));

  if(nBytes < 0) {
    perror("Error during reading");
    return;
  }

  write(dst, buffer, nBytes);

}
