#pragma once

#include <string>
#include <memory>
#include "Node.h"

class File : public Node
{
public:
	File(const std::string& fileName) {
		this->fileName = fileName;
	}
	~File() = default;
	std::string GetName() const { return this->fileName; }
	NodeType Type() const { return type; }
private:
	NodeType type = NodeType::NodeFile;
	std::string fileName;
};