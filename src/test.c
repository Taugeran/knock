#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <ifaddrs.h>
#include <limits.h>
#include <netdb.h>
#include <pcap.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <netinet/if_ether.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct acl_entry {
	uint32_t ip ;
	uint32_t netmask ;

} acl_entry_t;

/*--------------------------------------*/
/* Compute netmask address given prefix */
/*--------------------------------------*/
uint32_t netmask( int prefix ) {

  if ( prefix == 0 )
    return( ~((uint32_t) -1) );
  else
    return( ~((1 << (32 - prefix)) - 1) );

} /* netmask() */

/* Returns a string containing an ACL host statement */
char *generate_door_ip_acl_host( acl_entry_t entry )
{
	char *out = malloc( sizeof( char ) * 30 ) ;
	char template[] = "host %s" ;
	int32_t n ;
  struct in_addr temp = { .s_addr = entry.ip } ;

	n = sprintf( out, template, inet_ntoa( temp ) ) ;
#ifdef __debug__
  printf("%lu characters printed to %s output\n", (unsigned long)n, __func__ );
#endif

  return out;

}

char *generate_door_ip_acl_netblock( acl_entry_t entry )
{
  char *out = malloc( sizeof( char ) * 30 ) ;
  char template[] = "net %s/%s" ;
  int32_t n ;
  struct in_addr _netid = { .s_addr = entry.ip } ;
  struct in_addr _mask = { .s_addr = entry.netmask } ;
}

int main( int argc, char const *argv[] ) {
  char *_ip_ = "192.168.100.4" ;
  char *_nm_ = "255.255.255.255" ;
  char *_cidr_ = "/24" ;
  char *out ;
  int a, b, c ;
  acl_entry_t test = { .ip = inet_addr( _ip_ ), .netmask = inet_addr( _nm_ ) } ;

#ifdef __debug__
    printf( "test.ip = %lu\ntest.netmask = %lu\n",(unsigned long)test.ip, (unsigned long)test.netmask ) ;
#endif


  out = generate_door_ip_acl_host( test ) ;

printf("%s\n", );

  printf("'%s'\n", out );

  return 0 ;
}
