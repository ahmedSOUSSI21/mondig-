#include <stdio.h> 
#include <string.h> 
#include <sys/types.h> 
#include <netdb.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 

int main(int argc, char * argv[]){
	if(argc != 2 ){
		printf(" donnez un domaine à résoudre \n");
		return 1;
	}
	struct addrinfo hints = {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM};
	struct addrinfo *ai, *cur;
	int stat;
	char addr_str[256];
	if((stat = getaddrinfo(argv[1],NULL, &hints, &ai))!=0){
		printf("%s\n",gai_strerror(stat));
		return 1;
	}
	cur = ai;
	while(cur!= NULL){
		//identification de l'adresse courante 
		if(cur->ai_family == AF_INET){ //IPV4
			struct sockaddr_in *ipv4 = (struct sockaddr_in *) cur->ai_addr;
			printf("A: %s\n",inet_ntop(cur->ai_family,&(ipv4->sin_addr),addr_str,cur->ai_addrlen));
		}
		else{ //IPV6
			struct sockaddr_in6 * ipv6 = (struct sockaddr_in6 *) cur->ai_addr;
			printf("AAAA: %s\n",inet_ntop(cur->ai_family,&(ipv6->sin6_addr),addr_str,cur->ai_addrlen));
		}
		cur=cur->ai_next;
	}
	
	
	freeaddrinfo(ai);
	return 0;
}
