#define DEFAULT_MTU       (ETHERMTU) // =1500
#define DEFAULT_IP_TTL    (64)
#define DEFAULT_PING_SIZE (64)

#define DUMMY_WAIT_MS     (100)
#define RETRY_COUNT       (3)

typedef struct {
  char           *device;
  u_int8_t       mymac[6];
  struct in_addr myip;
  u_int8_t       vmac[6];
  struct in_addr vip;
  struct in_addr vmask;
  int IpTTL;
}PARAM;

int SetDefaultParams();
int ReadParam(char *fname);
int isTargetIPAddr(struct in_addr* addr);
int isSameSubnet(struct in_addr* addr);

