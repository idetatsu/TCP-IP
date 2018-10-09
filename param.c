#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include "sock.h"
#include "ether.h"
#include "param.h"

extern PARAM Param;

static char *ParamFname = NULL;

int SetDefaultParams()
{
  Param.MTU = DEFAULT_MTU;
  Param.IpTTL = DEFAULT_IP_TTL;

  return(0);
}

int ReadParam(char *fname)
{
  FILE *fp;
  char buf[1024];
  char *ptr, *saveptr;

  ParamFname = fname;

  if((fp=fopen(fname, "r")) == NULL) {
    printf("Could not read %s\n", fname);
    return(-1);
  }

  while(1) {
    fgets(buf, sizeof(buf), fp);
    if(feof(fp)) {
      break;
    }

    // strtok_r: Splits a string into tokens;
    ptr = strtok_r(buf, "=", &saveptr);
    if(ptr != NULL) {
      if(strcmp(ptr, "IP-TTL") == 0) {
        if((ptr = strtok_r(NULL, "\r\n", &saveptr)) != NULL) {
          Param.IpTTL = atoi(ptr);
        }
      }else if(strcmp(ptr, "MTU") == 0) {
        if((ptr = strtok_r(NULL, "\r\n", &saveptr)) != NULL) {
          Param.MTU = atoi(ptr);
        }
      }
    }
  }
}

