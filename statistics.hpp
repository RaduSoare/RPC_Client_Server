#ifndef HEADER_STATISTICS
#define HEADER_STATISTICS

#include<iostream>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <numeric>
#include <bits/stdc++.h>

using namespace std;

float getMin(vector<float> data) {
	return *min_element(data.begin(), data.end());
} 

float getMax(vector<float> data) {
	return *max_element(data.begin(), data.end());
} 

float getMean(vector<float> data) {
	return accumulate( data.begin(), data.end(), 0.0 ) / (float)data.size();
} 

float getMedian(vector<float> data) {
	int size = data.size();

	if (size == 0) {
		return 0.f;
	}

	sort(data.begin(), data.end());

	if (size % 2 != 0) {
		return data.at(size / 2);
	} else {
		return (data.at(size / 2) + data.at(size / 2 - 1)) / 2;
	}
} 

#endif