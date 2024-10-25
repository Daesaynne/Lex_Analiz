#pragma once
#include <iostream>
#include <vector>
#include "token.h"
#include "Hash_table.h"
#include "dfa.h"
#include <string>
#include "matrix.h"
#include <fstream>
#include <iomanip>

using namespace std;



class Lexer
{
private:
	hash_table Tokens;
	void newToken(vector<char>& alphabet, string& s, ofstream& out)
	{
		if (s.size() != 0) {
			//KEYWORDS
			if (dfa(countStates_procedure, alphabet, finalstates_procedure, transFunction_procedure).isAccept(s))
			{
				Token token = Token(s, "KEYWORD");
				Tokens.add(token);
				s.clear();
				return;
			}

			if (dfa(countStates_begin, alphabet, finalStates_begin, transFunction_begin).isAccept(s))
			{
				Token token = Token(s, "KEYWORD");
				Tokens.add(token);
				s.clear();
				return;
			}

			if (dfa(countStates_integer, alphabet, finalstates_integer, transFunction_integer).isAccept(s))
			{
				Token token = Token(s, "KEYWORD");
				Tokens.add(token);
				s.clear();
				return;
			}

			if (dfa(countStates_end, alphabet, finalStates_end, transFunction_end).isAccept(s))
			{
				Token token = Token(s, "KEYWORD");
				Tokens.add(token);
				s.clear();
				return;
			}

			if (dfa(countStates_var_keyword, alphabet, finalStates_var_keyword, transFunction_var_keyword).isAccept(s))
			{
				Token token = Token(s, "KEYWORD");
				Tokens.add(token);
				s.clear();
				return;
			}

			//for, to, do (cond_op)
			if (dfa(countStates_for, alphabet, finalStates_for, transFunction_for).isAccept(s))
			{
				Token token = Token(s, "COND_OP");
				Tokens.add(token);
				s.clear();
				return;
			}
			if (dfa(countStates_to, alphabet, finalStates_to, transFunction_to).isAccept(s))
			{
				Token token = Token(s, "COND_OP");
				Tokens.add(token);
				s.clear();
				return;
			}
			if (dfa(countStates_do, alphabet, finalStates_do, transFunction_do).isAccept(s))
			{
				Token token = Token(s, "COND_OP");
				Tokens.add(token);
				s.clear();
				return;
			}

			//rel_op
			if (dfa(countStates_rel1, alphabet, finalStates_rel1, transFunction_rel1).isAccept(s))
			{
				Token token = Token(s, "REL_OP");
				Tokens.add(token);
				s.clear();
				return;
			}
			if (dfa(countStates_rel2, alphabet, finalStates_rel2, transFunction_rel2).isAccept(s))
			{
				Token token = Token(s, "REL_OP");
				Tokens.add(token);
				s.clear();
				return;
			}

			//var
			if (dfa(countStatesVar, alphabet, finalStatesVar, transFunctionVar).isAccept(s))
			{
				Token token = Token(s, "VAR");
				Tokens.add(token);
				s.clear();
				return;
			}

			//const
			if (dfa(countStatesConst, alphabet, finalStatesConst, transitFunctionConst).isAccept(s))
			{
				Token token = Token(s, "CONST");
				Tokens.add(token);
				s.clear();
				return;
			}
			if (s != ">" && s != "<")
				out << "Не удалось распознать лексему: " << s << '\n';
			s.clear();
		}
	}
public:

	bool trS(char simbl)
	{
		string ALL_ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789;:=,+-)(><\n";
		return (ALL_ALPHABET.find(simbl) != string::npos);
	}

	Lexer(ifstream& in_p)
	{
		vector<char> alphabet;
		char simbl; string str;
		int counter = 0;int costl = 0;
		ofstream out("ERROR.txt");

		for (char c = 'a'; c <= 'z'; c++)
		{
			alphabet.push_back(c);
		}
		for (char c = 'A'; c <= 'Z'; c++)
		{
			alphabet.push_back(c);
		}
		for (char c = '0'; c <= '9'; c++)
		{
			alphabet.push_back(c);
		}
		char symbols[] = { ';', ':', '=', ',', '+', '-', ')', '(', '>', '<' };
		for (char symbol : symbols) {
			alphabet.push_back(symbol);
		}
		
		while (!in_p.eof())
		{
			in_p.get(simbl);
			if (simbl == ';')
			{
				newToken(alphabet, str, out);
				Token token = Token(";", "SEP");
				Tokens.add(token);
			}
			else if (simbl == ',')
			{
				newToken(alphabet, str, out);
				Token token = Token(",", "SEP");
				Tokens.add(token);
			}
			else if (simbl == '(')
			{
				newToken(alphabet, str, out);
				Token token = Token("(", "SEP");
				Tokens.add(token);
			}
			else if (simbl == ')')
			{
				newToken(alphabet, str, out);
				Token token = Token(")", "SEP");
				Tokens.add(token);
			}
			else if (simbl == ' ')
			{
				newToken(alphabet, str, out);
			}
			else if (simbl == '+' || simbl == '-')
			{
				newToken(alphabet, str, out);
				string oper = "";
				oper = oper + simbl;
				Token token = Token(oper, "OPER");
				Tokens.add(token);
			}

			else if (simbl == ':') {
				newToken(alphabet, str, out);
				char nextChar = in_p.peek(); 
				if (nextChar == '=') {
					in_p.get(simbl);
					str += ":="; 
					Token token = Token(str, "REL_OP");
					Tokens.add(token);
					str.clear();
				}
				else {
					Token token = Token(":", "SEP");
					Tokens.add(token);
				}
			}

			else if (simbl == '>' || simbl == '<')
			{
				counter++;
				if (counter == 2)
				{
					str += simbl;
					newToken(alphabet, str, out);
				}
				else
				{
					newToken(alphabet, str, out);
					string oper = "";
					oper = oper + simbl;
					Token token = Token(oper, "REL_OP");
					Tokens.add(token);
					str += simbl;
				}
			}

			else if (!trS(simbl))
			{
				newToken(alphabet, str, out);
				out << "Не удалось распознать лексему: " << simbl << endl;
			}
			else if (simbl == '\n')
			{
				newToken(alphabet, str, out);
			}

			else
				str += simbl;
		}
	}
	hash_table gethashTable()
	{
		return this->Tokens;
	}
};