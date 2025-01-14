#pragma once

#include <string>
#include <vector>
#include "File.h"

class Folder : public Node, public std::enable_shared_from_this<Folder>
{
public:
	Folder(const std::string& folderName) {
		this->folderName = folderName;
		this->path = "~";
	}
	Folder(const std::string& folderName, std::shared_ptr<Folder> folder, std::string path) {
		this->folderName = folderName;
		this->parentFolder = folder;
		this->path = path + "/" + folderName;
	}
	~Folder() = default;

	NodeType GetType() const;
	std::string GetName() const;
	std::string GetPath() const;
	std::shared_ptr<Folder> GetParent();
	bool CreateContent(const std::string& fileName, NodeType type);
	void ShowContents(void (*Display)(std::string name, NodeType nodeType, int level), int level = 0);
	void ShowAll(void (*Display)(std::string name, NodeType nodeType, int level), int level = 0);
	std::weak_ptr<Folder> GetSubFolder(std::string folderName);
public:
	std::weak_ptr<Folder> parentFolder;
	std::string folderName;
	std::string path;
	NodeType type = NodeType::NodeFolder;
	std::vector<std::shared_ptr<Node>> contents;
};