#include "func.h"

int main(int argc, char *argv[]) {
	int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(sock == -1)
		handle_error("socket");
	if(remove(CNAME) == -1 && errno != ENOENT)
		handle_error("remove");
    
	struct sockaddr_un server_addr, client_addr;
	server_addr.sun_family = AF_LOCAL;
	client_addr.sun_family = AF_LOCAL;
	strncpy(server_addr.sun_path, SNAME, sizeof(server_addr.sun_path) - 1);
	strncpy(client_addr.sun_path, CNAME, sizeof(server_addr.sun_path) - 1);
	
	if(bind(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
		handle_error("bind");
	
	if(connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		handle_error("connect");

	char buf[BUFSIZE], buf2[BUFSIZE];
	int i = 0;
	puts("Enter messages:");
	while(i < 10) {
		if(!memset(buf, 0, BUFSIZE))
			handle_error("memset");
		if(!memset(buf2, 0, BUFSIZE))
			handle_error("memset");
			
		fgets(buf, BUFSIZE, stdin);
			
		if(send(sock, buf, BUFSIZE, 0) == -1)
			handle_error("send");
		if(recv(sock, buf2, BUFSIZE, 0) == -1)
			handle_error("recv");
		printf("%s", buf2);
		i++;
	}
	shutdown(sock, SHUT_RDWR);
	return 0;
}
