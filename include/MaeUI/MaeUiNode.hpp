//
// Created by mait-elk on 3/12/25.
//

#pragma once
#include <MaeUI/Main.hpp>

/** REMINDER: explicit keyword used to say hey you should call the constructor manually MaeUiNode obj(type) instead of MaeUiNode obj = type **/
/**  REMINDER: [[nodiscard]] used to generate warning in compile time when return is unused  **/

class MaeUiNode {
public:
  string                type;
  string                tag;
  string                id;
  map<string, string>   properties;
  MaeUiNode*            parent;
  vector<MaeUiNode>     childList;


  MaeUiNode();
  MaeUiNode(const string& type, const string& tag, const string& id);
  MaeUiNode(MaeUiNode& parent, const string& type);
  virtual ~MaeUiNode();

  void addProperty(const string& name, const string& value);

  [[nodiscard]] const string getPropertyValue(const string& name) const;

  void removeProperty(const string& name);

  void addChild(MaeUiNode &newChild);

  vector<MaeUiNode> &getChildList();
};


typedef map<string, string>::const_iterator cPropIterator;
typedef map<string, string>::iterator propIterator;

typedef vector<MaeUiNode>::const_iterator cChildIterator;
typedef vector<MaeUiNode>::const_iterator childIterator;