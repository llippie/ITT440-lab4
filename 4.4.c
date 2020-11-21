#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main()
{
 struct sockaddr_in server;
 int sockd;
 char message[100],reply[100];
 if((sockd = socket(AF_INET,SOCK_STREAM,0))==-1)
 {
  printf("Failed to create socket\n");
  return 1;
 }
 server.sin_addr.s_addr = inet_addr("192.168.56.101");
 server.sin_family = AF_INET;
 server.sin_port = htons(8888);
 if(connect(sockd,(struct sockaddr *)&server,sizeof(server))<0)
 {
  puts("Connect failed\n");
  return 1;
 }
 printf("You:");
 fgets(message,100,stdin);
 if(send(sockd,message,100,0)<0)
 {
  puts("Send failed\n");
  return 1;
 }
 puts("Sent");
 if(recv(sockd,reply,100,0)<0)
 {
  puts("Receive failed");
 }
 printf("server: %s",reply);
 close(sockd);
 return 0;
}
