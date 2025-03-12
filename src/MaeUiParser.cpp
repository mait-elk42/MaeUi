//
// Created by mait-elk on 3/12/25.
//

#include <MaeUI/MaeUiNode.hpp>
#include <MaeUI/MaeUiParser.hpp>
#include <fstream>

MaeUiParser::MaeUiParser() {

}

MaeUiParser::MaeUiParser(const string& maeuiFileName) {
  	string fileContent;
    std::ifstream file(maeuiFileName);
	    if (file.is_open()) {
	      cout << "file" << maeuiFileName << endl;
	      string line;
	      while (getline(file, line)) {
                if (line.empty())
                  continue;
	      		if ( file.peek() != EOF )
	      			line += '\n';
                string cleanLine;
	      		for ( int i = 0; i < line.length();) {
	      			if ( isspace(line[i]) && line[i] != '\n' ) line[i] = ' ';
	      			cout << line[i];
	      			// cleanLine.append({line[i]});
	      			// if ( line[i] == ' ' )
	      			// 	while ( i < line.length() && line[i] == ' ' ) { i++; }
	      			// else
	      			// 	i++;
	      		}
                fileContent += cleanLine;
	      }
          cout << fileContent << endl;
    }
}

MaeUiParser::~MaeUiParser() {

}