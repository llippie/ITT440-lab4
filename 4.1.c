#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
 int sockd;
 struct sockaddr_in server;
 char *message,server_reply[2000];

 sockd = socket(AF_INET,SOCK_STREAM,0);
 if(sockd == -1)
 {
  printf("Create socket fail.\n");
 }
 server.sin_addr.s_addr = inet_addr("192.168.56.101");
 server.sin_family = AF_INET;
 server.sin_port = htons(8888);

 if(connect(sockd,(struct sockaddr *)&server,sizeof(server))<0)
 {
  printf("Connect error.\n");
  return 0;
 }
 puts("Connected\n");
 message = "connect\n";
 if(send(sockd,message,strlen(message),0)<0)
 {
  printf("Send failed.\n");
  return 1;
 }
 puts("Data sent\n");
 if(recv(sockd,server_reply,200,0)<0)
 {
  puts("Receive fail\n");
 }
 puts("Reply received.\n");
 puts(server_reply);

 close(sockd);
 return 0;
}
