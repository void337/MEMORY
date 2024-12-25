#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <bitset>
#include <random>
using namespace std;

class Memory {
	struct Page {
		int Number = 0;
		int bytes = 32;
		bool f = 0;
		int R = 0;
		int M = 0;
		bitset<8> count;
		int addr = 0;
		string info;
	};

	struct Page_List {
		int info;
		int virt_addr;
		int addr;
	};

	int lists_quantity;
	vector<Page> OP;
	int OP_syze;
	vector<Page> EM;
	int EM_syze;

	vector<Page_List> catalog;
	int const EMD = -1;

	void Swapping(int& address, int nomer);
	void Request_alg(int b);
public:
	friend void clean();
	Memory();
	void Request();
	void Modify(Page& p);
	void Generation_Request();
	void Generation_Pages();
	void Print_Pages();
	void Read_Page();
	void Change_Page();
};

void clean();












#endif // !HEADER_H