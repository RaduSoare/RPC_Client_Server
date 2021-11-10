/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpc_db.hpp"


void
rpc_db_prog_1(char *host)
{
	CLIENT *clnt;
	LoginCredentials  *result_1;
	char * login_1_arg = (char*)malloc(sizeof(30));
	strcpy(login_1_arg, "radu");
	LoginCredentials  *result_2;
	char * login_2_arg = (char*)malloc(sizeof(30));
	strcpy(login_2_arg, "radu");
	// void  *result_2;
	// char *logout_1_arg;
	// void  *result_3;
	// char *load_1_arg;
	// void  *result_4;
	// char *store_1_arg;
	// void  *result_5;
	// char *add_1_arg;
	// void  *result_6;
	// char *del_1_arg;
	// void  *result_7;
	// char *update_1_arg;
	// void  *result_8;
	// char *read_1_arg;
	// void  *result_9;
	// char *get_stat_1_arg;
	// void  *result_10;
	// char *get_stat_all_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, RPC_DB_PROG, RPC_DB_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = login_1(&login_1_arg, clnt);
	if (result_1 == (LoginCredentials *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("%s %ld asdasdsa\n", result_1->username, result_1->session_key);

	result_2 = login_1(&login_2_arg, clnt);
	// if (result_2 == (LoginCredentials *) NULL) {
	// 	printf("eroare\n");
	// 	clnt_perror (clnt, "call failed");
	// }
	printf("%s %ld asdasdsa\n", result_2->username, result_2->session_key);


	// result_2 = logout_1((void*)&logout_1_arg, clnt);
	// if (result_2 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_3 = load_1((void*)&load_1_arg, clnt);
	// if (result_3 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_4 = store_1((void*)&store_1_arg, clnt);
	// if (result_4 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_5 = add_1((void*)&add_1_arg, clnt);
	// if (result_5 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_6 = del_1((void*)&del_1_arg, clnt);
	// if (result_6 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_7 = update_1((void*)&update_1_arg, clnt);
	// if (result_7 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_8 = read_1((void*)&read_1_arg, clnt);
	// if (result_8 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_9 = get_stat_1((void*)&get_stat_1_arg, clnt);
	// if (result_9 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	// }
	// result_10 = get_stat_all_1((void*)&get_stat_all_1_arg, clnt);
	// if (result_10 == (void *) NULL) {
	// 	clnt_perror (clnt, "call failed");
	//}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	rpc_db_prog_1 (host);
exit (0);
}
