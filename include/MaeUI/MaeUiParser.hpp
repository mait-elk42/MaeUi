//
// Created by mait-elk on 3/12/25.
//

#pragma once
#include <MaeUI/Main.hpp>

enum TOKEN_TYPE {
	NONE,
	WORD,
	SYMBOL
};

class Token {
public:
	TOKEN_TYPE type;
	const string value;
	Token(const TOKEN_TYPE type, const string& value ) : type(type), value(value) {}
	~Token() {}
};

class MaeUiParser {
MaeUiParser();
string _shrinkScript(ifstream& file);
vector<Token>	_tokenizeScript(const string& script);
public:
	MaeUiParser(const string& maeuiFileName);
	~MaeUiParser();
};
