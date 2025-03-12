//
// Created by mait-elk on 3/12/25.
//

#include <MaeUI/MaeUiNode.hpp>

MaeUiNode::MaeUiNode() {  }

MaeUiNode::MaeUiNode(HoldingTypes type) : parent(NULL), type(type) {  }

MaeUiNode::MaeUiNode(MaeUiNode& parent, HoldingTypes type) : parent(&parent), type(type) {  }

MaeUiNode::~MaeUiNode() {   }

void MaeUiNode::addProperty(const string& name, const string& value) {
  properties[name] = value;
}

const string MaeUiNode::getPropertyValue(const string& name) const {
  cPropIterator it = properties.find(name);
  if (it != properties.end())
    return it->second;
  return "";
}

void MaeUiNode::addChild(MaeUiNode& newChild) {
  childList.push_back(newChild);
}

vector<MaeUiNode> &MaeUiNode::getChildList() {
   return childList;
}