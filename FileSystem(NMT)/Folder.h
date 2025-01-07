#pragma once

#include <string>
#include <vector>
#include "File.h"
#include <iostream>

class Folder : public Node
{
public:
	Folder(const std::string& folderName) {
		this->folderName = folderName;
	}
	~Folder() = default;

	NodeType Type() const;
	std::string GetName() const;
	bool CreateFile(const std::string& fileName);
	void ShowContents(void (*Display)(std::string folderName, std::vector<std::pair<std::string, NodeType>> data));

private:
	std::string folderName;
	NodeType type = NodeType::NodeFolder;
	std::vector<std::unique_ptr<Node>> contents;
};

namespace Display {
	static void StandarDisplay(std::string folderName, std::vector<std::pair<std::string, NodeType>> data) {
		std::cout << folderName << "/" << std::endl;
		for (const std::pair<std::string, NodeType>& node : data) {
			std::cout << "├──" << node.first << (node.second == NodeType::NodeFolder ? "/" : "") << std::endl;
		}
	}
}