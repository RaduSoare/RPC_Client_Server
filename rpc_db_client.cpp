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
#define READ_ALL_CMD "read_all"
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

LoadParam load_data_from_disk_new(string filepath, unsigned long session_key) {
	
	string line;
	fstream fs;

	fs.open(filepath, std::ios_base::in | std::ios::app);
	int count = 0;
	LoadParam load_arg;

	while(getline(fs, line)) {

		SensorData current_data;
		std::istringstream iss(line);
		float i;
		iss >> current_data.dataId;
		iss >> current_data.noValues;
		
		int index = 0;
		while (iss >> i) {             
			current_data.values[index++] = i;
		}
		//memDB.push_back(current_data);
		load_arg.clients_data[count] = current_data;
		count++;

	}

	fs.close();

	load_arg.num = count;
	load_arg.session_key = session_key;

	return load_arg;

	//show_data_from_mem();
}

void store_data_to_disk_new(StoreResult* read_all_result, string filepath) {

	

	ofstream ofs (filepath, std::ofstream::in | std::ofstream::trunc);

	for (int i = 0; i < read_all_result->num; i++) {

		ofs << read_all_result->clients_data[i].dataId << " " << read_all_result->clients_data[i].noValues << " ";

		for (int j = 0; j < read_all_result->clients_data[i].noValues; j++) {
			ofs << read_all_result->clients_data[i].values[j] << " ";
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

	
	ifstream infile(argv[2]);

	while (getline(infile, input_command))
	{
		
		//getline(std::cin, input_command);

		std::istringstream iss(input_command);
		cout << input_command << endl;

		string cmd;

		// Extract the command
		iss >> cmd;



		if (cmd == LOGIN_CMD) {

			// Get username from login command
			string username;
			iss >> username;
			fstream fs;
			
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
					fs.open(filepath, fstream::in | fstream::out | fstream::app);
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
				//delete login_result;
			}

		} else if (input_command == LOAD_CMD) {
			

			LoadParam load_arg = load_data_from_disk_new(filepath, login_result->session_key);

			bool_t  *load_result = load_1(&load_arg, clnt);
			if (*load_result == false) {
				clnt_perror (clnt, "call failed");
				continue;
				
			}

			cout << "Load done clnt" << endl;




		} else if (input_command == STORE_CMD) {

			StoreResult* read_all_result = read_all_1(&(login_result->session_key), clnt);
			if (read_all_result == (StoreResult *) NULL) {
				cout << "aici nu" << endl;
				clnt_perror (clnt, "call failed");
			}

			
			store_data_to_disk_new(read_all_result, filepath);

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

			IntegerParam*  read_arg = new IntegerParam;
			read_arg->session_key = login_result->session_key;
			iss >> read_arg->value;

			
			SensorData  *read_result = read_1(read_arg, clnt);
			if (read_result == NULL) {
				clnt_perror (clnt, "call failed");
				continue;
			}

			cout << read_result->dataId << " " << read_result->noValues << endl;
			for (int i = 0; i < read_result->noValues; i++) {
				cout << read_result->values[i] << " ";
			}

		} else if (cmd == READ_ALL_CMD) {
			
			StoreResult* read_all_result = read_all_1(&(login_result->session_key), clnt);
			if (read_all_result == (StoreResult *) NULL) {
				cout << "aici nu" << endl;
				clnt_perror (clnt, "call failed");
			}
			
			for (int i = 0; i < read_all_result->num; i++) {
				cout << read_all_result->clients_data[i].dataId << " " << read_all_result->clients_data[i].noValues << " ";
				for (int j = 0; j < read_all_result->clients_data[i].noValues; j++) {
					cout << read_all_result->clients_data[i].values[j] << " ";
				}
				cout<< endl;
			}
		} else if (cmd == GET_STAT_CMD) {

			IntegerParam  get_stat_arg;
			get_stat_arg.session_key = login_result->session_key;
			iss >> get_stat_arg.value;


			Stats  *result_10 = get_stat_1(&get_stat_arg, clnt);
			if (result_10 == (Stats *) NULL) {
				clnt_perror (clnt, "call failed");
			};
			
			cout << result_10->min << endl;
			cout << result_10->max << endl;
			cout << result_10->mean << endl;
			cout << result_10->median << endl;
		
		} else if (cmd == GET_STAT_ALL_CMD) {
			
			
			AllStatsResp  *result_get_stat_all = get_stat_all_1(&login_result->session_key, clnt);
			if (result_get_stat_all == (AllStatsResp *) NULL) {
				clnt_perror (clnt, "call failed");
			}
			for (int i = 0; i < result_get_stat_all->count; i++) {
				cout << result_get_stat_all->stats[i].id << " " << result_get_stat_all->stats[i].min << " " << result_get_stat_all->stats[i].max << " " << result_get_stat_all->stats[i].mean << " " << result_get_stat_all->stats[i].median << endl;
			}

		}
	}
	



#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


// de facut functie de destroy care elibereaza memoria si la values