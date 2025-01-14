#pragma once

#include "Folder.h"
#include "File.h"
#include <memory>
#include <algorithm>
#include <type_traits>

NodeType Folder::GetType() const { return type; };

bool Folder::CreateContent(const std::string& name, NodeType type) {
	std::vector<std::shared_ptr<Node>>::iterator it = std::find_if(contents.begin(), contents.end(),
		[name](std::shared_ptr<Node>& file) -> bool {return (file->GetName() == name); });
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

std::string Folder::GetPath() {
	return path;
}

void Folder::ShowContents(void (*Display)(std::string folderName, std::vector<std::pair<std::string, NodeType>> data)) {
	std::vector<std::pair<std::string, NodeType>> data;

	for (const std::shared_ptr<Node>& content : contents) {
		data.emplace_back(std::make_pair(content->GetName(), content->GetType()));
	}
	Display(this->folderName, data);

}

void Folder::ShowAll(void (*Display)(std::string name, NodeType nodeType, int level ), int level) {
	Display(folderName, this->type, level);
	for (const std::shared_ptr<Node>& content : contents) {
		if (content->GetType() == NodeType::NodeFile) {
			Display(content->GetName(), NodeType::NodeFile, level + 1);
			continue;
		}
		if (content->GetType() == NodeType::NodeFolder) {
			dynamic_cast<Folder*>(content.get())->ShowAll(Display, level + 1);
		}
	}
}

std::weak_ptr<Folder> Folder::GetSubFolder(std::string folderName) {
	std::vector<std::shared_ptr<Node>>::iterator it = std::find_if(contents.begin(), contents.end(),
		[folderName](std::shared_ptr<Node>& file) -> bool {return (file->GetName() == folderName && file->GetType() == NodeType::NodeFolder); });
	if (it != contents.end()) {
		return std::static_pointer_cast<Folder>(*it);
	}
	return std::weak_ptr<Folder>();
	
}