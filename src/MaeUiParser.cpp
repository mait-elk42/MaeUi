//
// Created by mait-elk on 3/12/25.
//

#include <MaeUI/MaeUiNode.hpp>
#include <MaeUI/MaeUiParser.hpp>
#include <fstream>
#include <string.h>

MaeUiParser::MaeUiParser() {

}

MaeUiParser::MaeUiParser(const string& maeuiFileName) {
    std::ifstream file(maeuiFileName);
	if (file.is_open()) {
		vector<Token> tokens = _tokenizeScript(_shrinkScript(file));
		for ( const Token &t : tokens ) {
			cout << "$> " << t.type << " <" << t.value << ">" << endl;
		}
		// cout << tokens_head->value << endl;
	}else {
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
				tokens.push_back({WORD, part});
				// cout << "$> " << part << endl;
				part = "";
			}
		} else if ( strchr("[](){},:;", c) && !quoteMode ) {
			if ( !part.empty() ) {
				tokens.push_back({WORD, part});
				// cout << "$> " << part << endl;
				part = "";
			}
			tokens.push_back({SYMBOL, {c}});
			// cout << "$> <" << c << ">" << endl;
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