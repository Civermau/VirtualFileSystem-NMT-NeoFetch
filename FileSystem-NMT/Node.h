#pragma once

#include <string>

enum NodeType {
	NodeFile,
	NodeFolder
};

class Node {
public:
	virtual NodeType GetType() const = 0;
	virtual std::string GetName() const = 0;
	virtual ~Node() = default;
};