/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include<iostream>
#include <unordered_map>
using namespace std;
#include "rpc_db.hpp"



unsigned long current_session_key = 1;

#define LOGIN_LIST_CAPACITY 10
static LoginCredentials* loggingList;
int loggingListSize = 0;

static unordered_map<string, unsigned long> loggedMap;


bool check_if_logged(char* username) {
	string username_str(username);

	if (loggedMap.find(username_str) == loggedMap.end())
		return false;
	
	return true;
}

LoginCredentials *
login_1_svc(char **argp, struct svc_req *rqstp)
{
	static LoginCredentials  result;
	result.username = (char*)malloc(sizeof(30));
	result.session_key = 0;

	/*
	 * insert server code here
	 */


	cout << "Se conecteaza " << *argp << endl;
	if (check_if_logged(*argp)) {
		cout << "Already logged" << endl;
		return &result;
	} 


	result.username = (char*)malloc(sizeof(30));
	strcpy(result.username, *argp);
	result.session_key = current_session_key++;

	std::string username(result.username);
	loggedMap[username] = result.session_key;

	cout << username << " : " << loggedMap[username] << endl;


	return &result;
}

bool_t *
logout_1_svc(char **argp, struct svc_req *rqstp)
{
	static bool_t  result;
	result = true;

	/*
	 * insert server code here
	 */
	std::string username(*argp);

	loggedMap.erase(username);


	return &result;
}

void *
load_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
store_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
add_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
del_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
update_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
read_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
get_stat_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}

void *
get_stat_all_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return (void *) &result;
}
