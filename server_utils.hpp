#ifndef HEADER_SERVER_UTILS
#define HEADER_SERVER_UTILS

#include<iostream>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <numeric>
#include <bits/stdc++.h>

using namespace std;


// KEY_SESSION, <DATA_ID, DATA_VECTOR>
unordered_map<unsigned long, unordered_map<int, vector<float>>> database;

// Keep a reference for a next availabe session_key; 
unsigned long current_session_key = 1;

// <session_key, user_name>
static unordered_map<unsigned long, string> loggedMap;

bool check_if_logged(LoginCredentials* login_credentials) {
	string username_str(login_credentials->username);
	if (loggedMap.find(login_credentials->session_key) != loggedMap.end() && loggedMap[login_credentials->session_key] == username_str)
		return true;
	
	return false;
}

void print_database(unsigned long session_key) {
	cout << endl;
	cout << "Current database:" << endl;
	for (auto & entry : database[session_key]) {
		cout << entry.first << " " << entry.second.size() << " ";
		for (auto & value : entry.second) {
			cout << value << " ";
		}
		cout<< endl;
	}
	cout<< endl;
}

void insert_to_database(SensorData *argp, unsigned long session_key) {
	vector<float> values(argp->values, argp->values + argp->noValues);
	
	database[session_key][argp->dataId] = values;
}

SensorData getSensorData(unsigned long session_key, int id) {
	SensorData result1;

	result1.dataId = id;
	result1.noValues = database[session_key][id].size();

	
	copy(database[session_key][id].begin(), database[session_key][id].end(), result1.values);
	

	return result1;

}

#endif