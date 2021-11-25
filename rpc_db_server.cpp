/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include<iostream>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <numeric>
#include <bits/stdc++.h>

#include "rpc_db.hpp"
#include "server_utils.hpp"
#include "statistics.hpp"

using namespace std;



LoginCredentials *
login_1_svc(char **argp, struct svc_req *rqstp)
{
	static LoginCredentials  result;
	

	// Initialize result struct
	result.username = new char[30];
	strcpy(result.username, *argp);
	result.session_key = current_session_key;

	// session_key = 0 -> ERROR
	cout << "Connecting: " << *argp << endl;
	if (check_if_logged(&result)) {
		cout << "Already logged" << endl;
		result.session_key = 0;
		return &result;
	} 

	// Keep user as logged (using session_key)
	string username(result.username);
	loggedMap[result.session_key] = result.username;

	// Get next available session_key
	current_session_key++;


	return &result;
}

bool_t *
logout_1_svc(LoginCredentials *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	if (loggedMap.find(argp->session_key) == loggedMap.end()) {
		return (bool_t*) false;
	}

	string username_str(argp->username);

	// Find entry for the current session_key
	auto get_value = loggedMap.find(argp->session_key);

	// Erase the key from the logged map
	if (get_value != loggedMap.end() && loggedMap[argp->session_key] == username_str) {
		loggedMap.erase(argp->session_key);
		database.erase(argp->session_key);
		result = true;
		cout << username_str << " logged out" << endl;
	} else {
		result = false;

	}

	return &result;
}

bool_t *
load_1_svc(LoadParam *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	if (loggedMap.find(argp->session_key) == loggedMap.end()) {
		result = false;
	} else {
		for (int i = 0; i < argp->num; i++) {
			
			vector<float> values (argp->clients_data[i].values, argp->clients_data[i].values + argp->clients_data[i].noValues);
			database[argp->session_key][argp->clients_data[i].dataId] = values;

		}
		
		cout << loggedMap[argp->session_key] << " loaded " << argp->num << " entries " << endl;
		result = true;
	}

	return &result;
}

bool_t *
add_1_svc(SensorDataParam *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	if (loggedMap.find(argp->session_key) == loggedMap.end()) {
		result = false;
	} else {

		auto get_value = database[argp->session_key].find(argp->sensor_data.dataId);

		if (get_value != database[argp->session_key].end()) {
			cout << "dataID already exists" << endl;
			result = false;
		} else {
			insert_to_database(&(argp->sensor_data), argp->session_key);
			print_database(argp->session_key);
			result = true;
		}

	}
	return &result;
}



bool_t *
del_1_svc(IntegerParam *argp, struct svc_req *rqstp)
{	

	static bool_t  result;

	if (loggedMap.find(argp->session_key) == loggedMap.end()) {
		result = false;
	} else {

		auto get_value = database[argp->session_key].find(argp->value);

		if (get_value == database[argp->session_key].end()) {
			cout << "dataID not found" << endl;
			result = false;
		} else {
			database[argp->session_key].erase(argp->value);
			print_database(argp->session_key);
			result = true;
		}

	}

	return &result;

}

bool_t *
update_1_svc(SensorDataParam *argp, struct svc_req *rqstp)
{
	static bool_t  result;


	if (loggedMap.find(argp->session_key) == loggedMap.end()) {
		result = false;
	} else {
		auto get_value = database[argp->session_key].find(argp->sensor_data.dataId);

		if (get_value == database[argp->session_key].end()) {
			cout << "dataID not found" << endl;
			result = false;
		} else {
			database[argp->session_key].erase(get_value);
			insert_to_database(&argp->sensor_data, argp->session_key);
			print_database(argp->session_key);
			result = true;
		}
	}

	return &result;
}

SensorData *
read_1_svc(IntegerParam *argp, struct svc_req *rqstp)
{
	static SensorData  result;
	result.dataId = -1;
	if (loggedMap.find(argp->session_key) == loggedMap.end()) {
		return &result;
	} else {
		auto get_value = database[argp->session_key].find(argp->value);

		if (get_value == database[argp->session_key].end()) {
			cout << "dataID not found" << endl;
			return &result;
		} else {
			result = getSensorData(argp->session_key, argp->value);
		}
	}

	return &result;
}

StoreResult *
read_all_1_svc(u_long *argp, struct svc_req *rqstp)
{
	static StoreResult result;
	
	
	if (loggedMap.find(*argp) == loggedMap.end()) {
		return &result;
	} else {
		int count = 0;
		for (auto & entry : database[*argp]) {
		
			result.clients_data[count].dataId = entry.first;
			result.clients_data[count].noValues = entry.second.size();
			copy(entry.second.begin(), entry.second.end(), result.clients_data[count].values);
			count++;
		}
		result.num = count;
	
	}
 	return &result;
}

Stats *
get_stat_1_svc(IntegerParam *argp, struct svc_req *rqstp)
{
	static Stats  result;
	result.id = -1;

	if (loggedMap.find(argp->session_key) == loggedMap.end()) {
		return &result;
	} else {
		auto get_value = database[argp->session_key].find(argp->value);

		if (get_value == database[argp->session_key].end()) {
			cout << "dataID not found" << endl;
			return &result;
		
		} else {
			result.id = argp->value;
			result.min = getMin(database[argp->session_key][argp->value]);
			result.max = getMax(database[argp->session_key][argp->value]);
			result.mean = getMean(database[argp->session_key][argp->value]);
			result.median = getMedian(database[argp->session_key][argp->value]);
		}
	}

	

	return &result;
}

AllStatsResp *
get_stat_all_1_svc(u_long *argp, struct svc_req *rqstp)
{
	static AllStatsResp  result;

	if (loggedMap.find(*argp) == loggedMap.end()) {
		return (AllStatsResp*)NULL;
	} else {
		int counter = 0;
		for (auto & entry : database[*argp]) {
			result.stats[counter].id = entry.first;
			result.stats[counter].min = getMin(entry.second);
			result.stats[counter].max = getMax(entry.second);
			result.stats[counter].mean = getMean(entry.second);
			result.stats[counter++].median = getMedian(entry.second);
		} 
		result.count = counter;
	}

	return &result;
}

bool_t *
store_1_svc(u_long *argp, struct svc_req *rqstp)
{
	static bool_t result;

	/*
	* NOT USED, keept for RPC compatibility
	*/


	return &result;
}
