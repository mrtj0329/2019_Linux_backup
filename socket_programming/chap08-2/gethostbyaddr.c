#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include <sys/socket.h>
#include <netdb.h>

void error_handling(char* msg);

int main(int argc, char* argv[]) {
	int i;
	struct hostent* host;
	struct sockaddr_in addr;
	
	if (argc != 2) {
		printf("Usage: %s <IP> \n", argv[0]);
		exit(1);
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(argv[1]); // input ip address
	
	host = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET); // IPv4 (4 bytes)
	if (!host) {
		error_handling("gethost... error!");
	}

	printf("Canonical Name: %s \n", host->h_name);
	
	for (i = 0; host->h_aliases[i]; ++i) {
		printf("Aliases Name %d: %s \n", (i + 1), host->h_aliases[i]);
	}

	printf("Address Type: %s \n",
		(host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");

	printf("Address Length: %d \n", host->h_length);

	for (i = 0; host->h_addr_list[i]; ++i) {
		printf("IP Address %d: %s \n", (i + 1),
			inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
	}

	return 0;
}

void error_handling(char* msg) {
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
