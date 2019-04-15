#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netdb.h>

int main(void)
{
int serverSocket,client_connected,len,start , end,err,sock,i,j;
struct sockaddr_in client_addr,server_addr,sa;
struct hostent *ptrh;
char hostname[100];
//int n=0;
//char message[100],received[100];

serverSocket=socket(AF_INET, SOCK_STREAM, 0);

memset((char*)&server_addr,0,sizeof(server_addr));

server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(10000);

server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

if(bind(serverSocket,
(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1)
printf("Bind Failure\n");
else
printf("Bind Success:<%u>\n", serverSocket);




while(1)
{  
for(;;)
{   
     listen(serverSocket,5);
     len=sizeof(struct sockaddr_in);

    client_connected=accept(serverSocket,
    (struct sockaddr*)&client_addr,&len);
if (-1 != client_connected)
  printf("Connection accepted:<%u>\n", client_connected);
  printf("%s",inet_ntoa(client_addr.sin_addr));

//Get the hostname to scan
if (-1 != client_connected){
	gets(hostname);
	}
    
   printf("Enter hostname or IP : ");
    gets(hostname);
    //Get start port number
    printf("\nEnter start port number : ");
    scanf("%d" , &start);
   
    //Get end port number
    printf("Enter end port number : ");
    scanf("%d" , &end);
    //direct ip address, use it
    if(isdigit(hostname[0]))
    {
        printf("Doing inet_addr...");
        sa.sin_addr.s_addr = inet_addr(hostname);
        printf("Done\n");
    }
    //Resolve hostname to ip address
    else if( (ptrh = gethostbyname(hostname)) != 0)
    {
        printf("Doing gethostbyname...");
        strncpy((char*)&sa.sin_addr , (char*)ptrh->h_addr , sizeof sa.sin_addr);
        printf("Done\n");
    }
    else
    {
        herror(hostname);
        exit(2);
    }
//Start the port scan loop
    printf("Starting the portscan loop : \n");
    for( i = start ; i <= end ; i++)
    {
        //Fill in the port number
        sa.sin_port = htons(i);
        //Create a socket of type internet
        sock = socket(AF_INET , SOCK_STREAM , 0);
       
        //Check whether socket created fine or not
        if(sock < 0)
        {
            perror("\nSocket");
            exit(1);
        }
        //Connect using that socket and sockaddr structure
        err = connect(sock , (struct sockaddr*)&sa , sizeof sa);
       
        //not connected
        if( err < 0 )
        {
            //printf("%s %-5d %s\r" , hostname , i, strerror(errno));
            fflush(stdout);
        }
        //connected
        else
        {
            printf("%-5d open\n",  i);
        }
}
}
close(serverSocket); printf("\nServer Socket Closed !!\n");

return 0;

}
}
