/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpc_db.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

bool is_logged = false;



#define LOGIN_CMD "login"
#define LOGOUT_CMD "logout"
#define LOAD_CMD "load"
#define STORE_CMD "store"
#define ADD_CMD "add"
#define DEL_CMD "del"
#define UPDATE_CMD "update"
#define READ_CMD "read"
#define GET_STAT_CMD "get_stat"
#define GET_STAT_ALL_CMD "get_stat_all"

vector<SensorData*> memDB;


void show_data_from_mem() {

	
	for (auto & elem : memDB) {
		cout << elem->dataId << " " << elem->noValues << " ";
		for (int i = 0; i < elem->noValues; i++) {
			cout << elem->values[i] << " ";
		}
		cout << endl;
	}
			
}

void load_data_from_disk(string filepath) {
	
	string line;
	fstream fs;

	fs.open(filepath, std::ios_base::in | std::ios::app);

	while(getline(fs, line)) {

		SensorData* current_data = new SensorData;
		std::istringstream iss(line);
		float i;
		iss >> current_data->dataId;
		iss >> current_data->noValues;
		
		int index = 0;
		while (iss >> i) {             
			current_data->values[index++] = i;
		}
		memDB.push_back(current_data);
	}

	fs.close();

	show_data_from_mem();
}

void store_data_to_disk(string filepath) {

	cout << memDB.size() << endl;

	ofstream ofs (filepath, std::ofstream::in | std::ofstream::trunc);

	for (auto & elem : memDB) {
		ofs << elem->dataId << " ";
		ofs << elem->noValues << " ";
		for (int i = 0; i < elem->noValues; i++) {
			ofs << elem->values[i] << " ";
		}
		ofs << endl;
	}

	ofs.close();
}



int main (int argc, char *argv[]) 
{
	CLIENT *clnt;
	

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}

#ifndef	DEBUG
	clnt = clnt_create (argv[1], RPC_DB_PROG, RPC_DB_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (argv[1]);
		exit (1);
	}
#endif	/* DEBUG */

	string input_command;
	string filepath;
	LoginCredentials  *login_result;
	char * login_arg = (char*)malloc(sizeof(30));

	
	

	while (true)
	{
		getline(std::cin, input_command);

		std::istringstream iss(input_command);
		string cmd;

		// Extract the command
		iss >> cmd;

		if (cmd == LOGIN_CMD) {

			// Get username from login command
			string username;
			iss >> username;
			
			//Check for correct command
			if (username.empty() ) {
				cout << "Invalid username" << endl;
				continue;
			}

			strcpy(login_arg, username.c_str());

			if (is_logged == true) {
				cout << "Already logged" << endl;
				continue;
			} else {

				login_result = login_1(&login_arg, clnt);
				// If session_key is 0, it means that there was a problem
				if (login_result->session_key == 0) {
					clnt_perror (clnt, "call failed");
				} else {
					cout << "Logged in: " << login_result->username << endl;
					// Compute the path to the database on the disk
					filepath = username + ".rpcdb";
					is_logged = true;
				}

			}
		} else if (input_command == LOGOUT_CMD) {
			if (is_logged == false) {
				cout << "You are not logged in" << endl;
				continue;
			}
			bool_t  *logout_result;
			logout_result = logout_1(login_result, clnt);
			if (*logout_result == false) {
				clnt_perror (clnt, "call failed");
			} else {
				cout << "Logged out" << endl;
				memDB.clear();
				is_logged = false;
				delete login_result;
			}

		} else if (input_command == LOAD_CMD) {
			
			bool_t  *load_result = load_1(&(login_result->session_key), clnt);
			if (*load_result == false) {
				clnt_perror (clnt, "call failed");
				
			}
			memDB.clear();
			load_data_from_disk(filepath);

		} else if (input_command == STORE_CMD) {
			bool_t  *store_result = store_1(&(login_result->session_key), clnt);
			if (*store_result == false) {
				clnt_perror (clnt, "call failed");
				
			}

			SensorData* current_data = new SensorData;
			current_data->dataId = 99;
			current_data->noValues = 1;
			//current_data->values = new float[current_data->noValues];
			current_data->values[0] = 90;

			memDB.push_back(current_data);
			
			store_data_to_disk(filepath);
		} else if (cmd == ADD_CMD) {
			// De guardat pentru input prost
			
			if (is_logged == false) {
				cout << "You are not logged in" << endl;
				continue;
			}

			SensorDataParam* sensor_data_param = new SensorDataParam;

			sensor_data_param->session_key = login_result->session_key;

			iss >> sensor_data_param->sensor_data.dataId;
			iss >> sensor_data_param->sensor_data.noValues;
			
			for (int i = 0; i < sensor_data_param->sensor_data.noValues; i++) {
				iss >> sensor_data_param->sensor_data.values[i];
			}

			bool_t  *add_result = add_1(sensor_data_param, clnt);
			if (*add_result == false) {
				clnt_perror (clnt, "call failed");
				continue;
			}
			

		} else if (cmd == UPDATE_CMD) {
			SensorDataParam* sensor_data_param = new SensorDataParam;

			sensor_data_param->session_key = login_result->session_key;

			iss >> sensor_data_param->sensor_data.dataId;
			iss >> sensor_data_param->sensor_data.noValues;
			
			for (int i = 0; i < sensor_data_param->sensor_data.noValues; i++) {
				iss >> sensor_data_param->sensor_data.values[i];
			}

			bool_t  *update_result= update_1(sensor_data_param, clnt);
			if (*update_result == false) {
				clnt_perror (clnt, "call failed");
				continue;
			}

		} else if (cmd == DEL_CMD) { 
			
			IntegerParam*  del_arg = new IntegerParam;
			del_arg->session_key = login_result->session_key;
			iss >> del_arg->value;

			bool_t  *del_result = del_1(del_arg, clnt);
			if (*del_result == false) {
				clnt_perror (clnt, "call failed");
				continue;
			} 
		} else if (cmd == READ_CMD) {

			int  read_arg;
			iss >> read_arg;

			bool_t  *read_result = read_1(&read_arg, clnt);
			if (*read_result == false) {
				clnt_perror (clnt, "call failed");
				continue;
			}


		}
	}
	



#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


// de facut functie de destroy care elibereaza memoria si la values