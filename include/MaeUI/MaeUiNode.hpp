//
// Created by mait-elk on 3/12/25.
//

#pragma once
#include <MaeUI/Main.hpp>

enum HoldingTypes {
  HTYPE_UNKNOWN,
  HTYPE_SOLO,
  HTYPE_GROUP
};

class MaeUiNode {
  MaeUiNode();
protected:
  HoldingTypes          type;
  MaeUiNode*            parent;
  map<string, string>   properties;
  vector<MaeUiNode>     childList;
public:
  MaeUiNode(HoldingTypes type);
  MaeUiNode(MaeUiNode& parent, HoldingTypes type);
  virtual ~MaeUiNode();

  void addProperty(const string& name, const string& value);

  /**  REMINDER: [[nodiscard]] used to generate warning in compile time when return is unused  **/
  [[nodiscard]] const string getPropertyValue(const string& name) const;

  void removeProperty(const string& name);

  void addChild(MaeUiNode &newChild);

  vector<MaeUiNode> &getChildList();
};


typedef map<string, string>::const_iterator cPropIterator;
typedef map<string, string>::iterator propIterator;

typedef vector<MaeUiNode>::const_iterator cChildIterator;
typedef vector<MaeUiNode>::const_iterator childIterator;