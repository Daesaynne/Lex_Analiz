#include <iostream>
#include <fstream>
#include <vector>
#include "dfa.h"
#include "Hash_table.h"
#include "token.h"
#include "lexer.h"
using namespace std;


int main() {
	ifstream input_file("input.txt"); 
	Lexer Try(input_file);
	Try.gethashTable().printHashtable();
	return 0;
}