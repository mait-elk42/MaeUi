//
// Created by mait-elk on 3/12/25.
//

#pragma once
#include <MaeUI/Main.hpp>
#include <MaeUI/MaeUiNode.hpp>

const unordered_set<string> keywords = {
	"viewgroup",
	"view"
};

enum TOKEN_TYPE {
	TTYPE_KEYWORD,
	TTYPE_VALUE,
	TTYPE_OPEN_PROP,
	TTYPE_CLOSE_PROP,
	TTYPE_COMMA,
	TTYPE_OPEN_TAG,
	TTYPE_CLOSE_TAG,
	TTYPE_SYM
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
string			_shrinkScript(ifstream& file);
vector<Token>	_tokenizeScript(const string& script);
MaeUiNode		_parse_node(vector<Token>::iterator &it, const vector<Token>::iterator &end);
public:
	MaeUiParser(const string& maeuiFileName);
	~MaeUiParser();
};
