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
public:
  HoldingTypes          type;
  string                name;
  string                value;
  MaeUiNode*            parent;
  map<string, string>   properties;
  vector<MaeUiNode>     childList;

  MaeUiNode();
  /** REMINDER: explicit keyword used to say hey you should call the constructor manually MaeUiNode obj(type) instead of MaeUiNode obj = type **/
  explicit MaeUiNode(HoldingTypes type, const string& name, const string& value);
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