#include "FriendList.h"

FriendList GameFriend;

FriendList::FriendList() {
}

FriendList::~FriendList() {
}

void FriendList::addPlayerToList(const std::string& name) {
	GameFriend.List.push_back(name);
}

std::vector<std::string> FriendList::getList() {
	return GameFriend.List;
}

bool FriendList::findPlayer(const std::string& name) {
	for (std::vector<std::string>::iterator it = GameFriend.List.begin(); it != GameFriend.List.end(); ++it) {
		if (it->find(name) != std::string::npos) {
			return true;
		}
	}
	return false;
}

bool FriendList::removePlayer(const std::string& g) {
	for (std::vector<std::string>::iterator it = GameFriend.List.begin(); it != GameFriend.List.end(); ++it) {
		std::string copy = *it;
		std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
		if (copy.find(g) != std::string::npos) {
			GameFriend.List.erase(it);
			return true;
		}
	}
	return false;
}
