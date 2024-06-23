/* udp_socket_client.c
 * The Linux Channel
 * Author: Kiran Kankipati
 * Updated: 01-Feb-2017
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXBUF 1024

int main()
{ int sockfd, len, i;
  unsigned char buf[MAXBUF];
  struct sockaddr_in udp_server_addr;
  socklen_t addr_size;

  sockfd = socket(PF_INET, SOCK_DGRAM, 0); // create a UDP socket
  if(sockfd<=0) { printf("socket error !\n"); return 0; }

  /* configure settings to communicate with remote UDP server */
  udp_server_addr.sin_family = AF_INET;
  udp_server_addr.sin_port = htons(6800); // server port
  udp_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // local-host
  memset(udp_server_addr.sin_zero, '\0', sizeof udp_server_addr.sin_zero);  
  addr_size = sizeof udp_server_addr;

  memset(buf, 0xab, MAXBUF); // set the entire buffer with 0xab (i.e 1010 1011 binary)

  sendto(sockfd, buf, MAXBUF, 0, (struct sockaddr *)&udp_server_addr, addr_size); //send the data to server
  
  len = recvfrom(sockfd, buf, MAXBUF, 0, NULL, NULL); // receive data from server
  
  printf("Received from server: %d bytes\n", len); for(i=0;i<len;i++) { printf("%02x ", buf[i]); } printf("\n"); //print received data dump

  close(sockfd); //close socket file-descriptor
  
  return 0;
}
