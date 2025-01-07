#pragma once

#include "Folder.h"
#include "File.h"
#include <memory>
#include <algorithm>

NodeType Folder::Type() const { return type; };

bool Folder::CreateFile(const std::string& fileName) {
	std::vector<std::unique_ptr<Node>>::iterator it = std::find_if(contents.begin(), contents.end(),
		[fileName](std::unique_ptr<Node>& file) -> bool {return (file->GetName() == fileName); });
	if (it != contents.end()) {
		return false;
	}

	contents.emplace_back(std::make_unique<File>(fileName));
	return true;
}

std::string Folder::GetName() const {
	return folderName;
}

void Folder::ShowContents(void (*Display)(std::string folderName, std::vector<std::pair<std::string, NodeType>> data)) {
	std::vector<std::pair<std::string, NodeType>> data;

	for (const std::unique_ptr<Node>& content : contents) {
		data.emplace_back(std::make_pair(content->GetName(), content->Type()));
	}
	Display(this->folderName, data);

}

