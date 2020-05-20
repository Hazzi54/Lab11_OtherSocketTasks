#include "func.h"

int main(int argc, char *argv[]) {
    int sock = socket(AF_LOCAL, SOCK_STREAM, 0);
	if(sock == -1)
		handle_error("socket");
	if(remove(SNAME) == -1 && errno != ENOENT)
		handle_error("remove");
    
	struct sockaddr_un server_addr;
	server_addr.sun_family = AF_LOCAL;
	strncpy(server_addr.sun_path, SNAME, sizeof(server_addr.sun_path) - 1);
	
	if(bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
		handle_error("bind");
		
	if(listen(sock, 5) == -1)
		handle_error("listen");
	
	int new_sock = accept(sock, NULL, NULL), i = 0, j;
	if(new_sock == -1)
		handle_error("accept");
	ssize_t numBytes;
	char buf[BUFSIZE];
	while(i < 10) {
		if(!memset(buf, 0, BUFSIZE))
			handle_error("memset");   
	
	    numBytes = recv(new_sock, buf, BUFSIZE, 0);
	    if(numBytes == -1)
	    	handle_error("recv");
	    printf("%s", buf);
	    	
	    j = 0;
		while(j < numBytes) {
			buf[j] = toupper((unsigned char) buf[j]);
			j++;
		}
		
		if(send(new_sock, buf, numBytes, 0) == -1)
			handle_error("send");
		i++;
	}
	shutdown(new_sock, SHUT_RDWR);
    shutdown(sock, SHUT_RDWR);
    return 0;
}
