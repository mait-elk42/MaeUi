//
// Created by mait-elk on 3/12/25.
//

#include <MaeUI/MaeUiNode.hpp>
#include <MaeUI/MaeUiParser.hpp>
#include <fstream>
#include <string.h>

MaeUiParser::MaeUiParser() {

}

MaeUiNode MaeUiParser::_parse_node(vector<Token>::iterator &it, const vector<Token>::iterator &end) {
	MaeUiNode node;
	if ( it != end ) {
		if ( it->type == TTYPE_KEYWORD && it->value == "layout" ) {

		}
	}
	return node;
}

MaeUiParser::MaeUiParser(const string& maeuiFileName) {
    std::ifstream file(maeuiFileName);
	if (file.is_open()) {
		vector<Token> tokens = _tokenizeScript(_shrinkScript(file));
		MaeUiNode *node = nullptr;


		for ( int i = 0; i < tokens.size(); i++) {
			cout << tokens[i].type << "=" << tokens[i].value << endl;
		}
		/** 	Token& t = tokens[i];
		//
		// 	if ( t.type == TTYPE_KEYWORD ) {
		// 		if ( t.value == "layout" )
		// 			node = new MaeUiNode(HTYPE_GROUP, tokens[i +1].value, t.value);
		// 		if ( t.value == "text" || t.value == "button" )
		// 			node = new MaeUiNode(HTYPE_SOLO, tokens[i +1].value, t.value);
		// 	}
		//
		// 	if ( t.type == TTYPE_OPEN_PROP ) {
		// 		if ( node == nullptr ) {
		// 			throw runtime_error("unknown view add these props to him");
		// 		}
		// 		while ( i < tokens.size() && t.type != TTYPE_CLOSE_PROP ) {
		// 			while ( i < tokens.size() && tokens[i].type != TTYPE_COMMA && tokens[i].type != TTYPE_CLOSE_PROP ) i++;
		//
		// 			const Token& prop_key = tokens[i - 3];
		// 			const Token& prop_val = tokens[i -1];
		//
		// 			if ( prop_key.type != TTYPE_VALUE || prop_val.type != TTYPE_VALUE ) {
		// 				throw runtime_error("error occurred in property key or value :>");
		// 			}
		//
		// 			node->addProperty(prop_key.value, prop_val.value);
		//
		// 			cout << prop_key.value << "=" << prop_val.value << "-> for " << node->name << endl;
		// 			i++;
		//
		// 			if ( tokens[i -1].type == TTYPE_CLOSE_PROP )
		// 				break;
		// 		}
		// 		delete node;
		// 		node = nullptr;
		// 	}
		// 	i++;
		// }
		**/

		// cout << tokens_head->value << endl;
	} else {
		throw runtime_error("File: '" + maeuiFileName + "' is not exist or permission denied");
	}
}

string MaeUiParser::_shrinkScript(ifstream& file) {
	string fileContent;
	string line;
	while (getline(file, line)) {
		if (line.empty())
			continue;
		if ( file.peek() != EOF )
			line += '\n';
		const string cleanLine;
		bool inSpaceMode = false;
		bool inCommentMode = false;
		const size_t start = line.find_first_not_of(' ');
		const size_t end = line.find_last_not_of(' ');

		if (start == string::npos || end == string::npos) {
			line = "";
		} else {
			line = line.substr(start, end - start + 1);
		}

		for ( int i = 0; i < line.length(); i++) {
			if ( line[i] == '@' ) {
				inCommentMode = (inCommentMode == false);
				continue;
			}

			if ( inCommentMode )
				continue;

			if ( isspace(line[i]) ) line[i] = ' ';

			if ( isspace(line[i]) ) {
				if ( inSpaceMode == false ) {
					inSpaceMode = true;
					fileContent.append({line[i]});
				}
			}else {
				inSpaceMode = false;
				fileContent.append({line[i]});
			}
		}
		fileContent += cleanLine;
	}
	file.close();
	return fileContent;
}

vector<Token>	MaeUiParser::_tokenizeScript(const string& script) {
	vector<Token> tokens;
	cout << script << endl;
	char quoteMode = 0;
	string part = "";
	for (const char c : script) {
		if ( c == ' ' && !quoteMode ) {
			if ( !part.empty() ) {
				if ( keywords.find(part) != keywords.end() )
					tokens.emplace_back(TTYPE_KEYWORD, part);
				else
					tokens.emplace_back(TTYPE_VALUE, part);
				part = "";
			}
		} else if ( strchr("<>[](){},:;", c) && !quoteMode ) {
			if ( !part.empty() ) {
				if ( keywords.find(part) != keywords.end() )
					tokens.emplace_back(TTYPE_KEYWORD, part);
				else
					tokens.emplace_back(TTYPE_VALUE, part);
				part = "";
			}
			switch ( c ) {
				case '(':
					tokens.push_back({TTYPE_OPEN_PROP, {c}});
				break;
				case ')':
					tokens.push_back({TTYPE_CLOSE_PROP, {c}});
				break;
				case ',':
					tokens.push_back({TTYPE_COMMA, {c}});
				break;
				case '<':
					tokens.push_back({TTYPE_OPEN_TAG, {c}});
				break;
				case '>':
					tokens.push_back({TTYPE_CLOSE_TAG, {c}});
				break;
				default:
					tokens.push_back({TTYPE_SYM, {c}});
					break;
			}
		} else {
			if ( strchr("\"\'", c) ) {
				if ( quoteMode == c )
					quoteMode = 0;
				else
					quoteMode = c;
			}
			part.append({c});
		}
	}
	return tokens;
}

MaeUiParser::~MaeUiParser() {

}