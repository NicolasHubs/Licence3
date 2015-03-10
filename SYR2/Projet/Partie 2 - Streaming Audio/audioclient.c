/*
	SYR2 - Projet - Partie 2
	ANDRIAMILANTO Tompoariniaina
	BOUCHERIE Thomas
*/

#include <clientserver.h>


/**
 * The main program
 *
 * Parameters:
 *	 - int argc  => The number of arguments passed
 *	 - char** args  => The arguments list
 *
 * Return:
 *	 - int  => The result of the execution
 */
int main(int argc, char** args) {

	// If there aren't the correct number of arguments
	if (argc != 3) { perror("Three arguments expected. Run with audioclient [server_host_name] [file_name]"); return 1; }

	// Check the parameters
	if (args[1] == NULL) { perror("The first argument is NULL. Run with audioclient [server_host_name] [file_name]"); return 1; }
	if (args[2] == NULL) { perror("The second argument is NULL. Run with audioclient [server_host_name] [file_name]"); return 1; }



	/* 	################################################## Name Resolution ################################################## */
	// Structure for the name resolution
	struct hostent* name_resolution;

	// Resolve the ip address here
	name_resolution = gethostbyname(args[1]);

	// If error
	if (name_resolution == NULL) { perror("Error during the name resolution"); return 1; }

	// Get the ip address (first of the list)
	struct in_addr* ip_addr = (struct in_addr*)name_resolution->h_addr_list[0];



	/* 	################################################## Socket creation and bind ################################################## */
	// Create the client socket
	int client_socket = socket(AF_INET, SOCK_DGRAM, 0);

	// If error
	if (client_socket == -1) { perror("Error during the creation of the client socket"); return 1; }

	// The structure containing the port number
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(SERVER_PORT);
	addr.sin_addr = *ip_addr;

	// Bind the port
	if (bind(client_socket, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1) { perror("Error during the client socket's bind"); return 1; }



	/* 	################################################## Sending the packet ################################################## */
	// The structure for informations about the destination (will be filled)
	struct sockaddr_in destination;

	// Its length (for the pointer)
	socklen_t destination_length = (socklen_t)sizeof(struct sockaddr);

	// Send a packet
	int packet_send = sendto(client_socket, args[2], BUFFER_SIZE, 0, (struct sockaddr *)&destination, destination_length);

	// If error
	if (packet_send == -1) { perror("Error during the receiving of the packet"); return 1; }

	// Then close it in the end
	if (close(client_socket) == -1) { perror("Error during the closing of the client socket"); return 1; }

	// If everything's was ok (but the server is normally just waiting for clients)
	return 0;
}