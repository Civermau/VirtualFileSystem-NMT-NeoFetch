#pragma once

#include "Folder.h"
#include "File.h"
#include <memory>
#include <algorithm>
#include <type_traits>

NodeType Folder::GetType() const { return type; };

bool Folder::CreateContent(const std::string& name, NodeType type) {
	std::vector<std::shared_ptr<Node>>::iterator it = std::find_if(contents.begin(), contents.end(),
		[&name](std::shared_ptr<Node>& file) -> bool {return (file->GetName() == name); });
	if (it != contents.end()) {
		return false;
	}
	if (type == NodeType::NodeFile) {
		contents.emplace_back(std::make_shared<File>(name));
	}
	if (type == NodeType::NodeFolder) {
		contents.emplace_back(std::make_shared<Folder>(name, shared_from_this(), path));
	}
	return true;
}

std::string Folder::GetName() const {
	return folderName;
}

std::shared_ptr<Folder> Folder::GetParent() {
	if (parentFolder.expired()) {
		return shared_from_this();
	}
	return parentFolder.lock();
}

std::string Folder::GetPath() const {
	return path;
}

void Folder::ShowContents(void (*Display)(std::string name, NodeType nodeType, int level), int level) {
	Display(folderName, this->type, level);
	for (const std::shared_ptr<Node>& content : contents) {
		Display(content->GetName(), content->GetType(), level + 1);
	}
}

void Folder::ShowAll(void (*Display)(std::string name, NodeType nodeType, int level), int level) {
	Display(folderName, this->type, level);
	for (const std::shared_ptr<Node> content : contents) {
		int currentLevel = level + 1;
		if (content->GetType() == NodeType::NodeFile) {
			Display(content->GetName(), NodeType::NodeFile, currentLevel);
		}
		else if (content->GetType() == NodeType::NodeFolder) {
			if (auto folder = std::dynamic_pointer_cast<Folder>(content)) {
				folder->ShowAll(Display, currentLevel);
			}
		}
	}
}

std::weak_ptr<Folder> Folder::GetSubFolder(std::string folderName) {
	//auto type instead
	std::vector<std::shared_ptr<Node>>::iterator it = std::find_if(contents.begin(), contents.end(),
		[&folderName](std::shared_ptr<Node>& file) -> bool {return (file->GetName() == folderName && file->GetType() == NodeType::NodeFolder); });
	if (it != contents.end()) {
		return std::static_pointer_cast<Folder>(*it);
	}
	return std::weak_ptr<Folder>();
	
}

bool Folder::DeleteContent(std::string name) {
	//auto type instead
	std::vector<std::shared_ptr<Node>>::iterator it = std::find_if(contents.begin(), contents.end(),
		[&name](std::shared_ptr<Node>& file) -> bool {return (file->GetName() == name); });
	if (it == contents.end()) {
		return false;
	}
	contents.erase(it);
	return true;

}