#include "..\\header\\NetworkAnalysis.h"
#include "..\\header\\NetworkBuilder.h"


string suggestUser(int userid, vector<pair<int,vector<int>>> connections) {
    vector<int> userFollowers;
    for (const auto& conn : connections) {
        if (conn.first == userid) {
            userFollowers = conn.second;
            break;
        }
    }

    vector<int> fof;
    for (int follower : userFollowers) {
        for (const auto& conn : connections) {
            if (conn.first == follower) {
                for (int fofUser : conn.second) {
                    if (fofUser != userid && 
                        find(userFollowers.begin(), userFollowers.end(), fofUser) == userFollowers.end()
                        && find(fof.begin(), fof.end(), fofUser) == fof.end()) {
                        fof.push_back(fofUser);
                    }
                }
                break;
            }
        }
    }
    if (fof.empty()) {
        return "No suggestions available";
    }else{
        string suggestion = "Suggested users for user " + to_string(userid) + ": ";
        for (size_t i = 0; i < fof.size(); ++i) {
            suggestion += to_string(fof[i]);
            if (i != fof.size() - 1) {
                suggestion += ", ";
            }
        }
        return suggestion;
    }
}

string mutualUsers(int user1, int user2, vector<pair<int, vector<int>>> connections) {
    vector<int> followers1, followers2;

    
    for (const auto& conn : connections) {
        if (conn.first == user1) {
            followers1 = conn.second;
            break;
        }
    }

    
    for (const auto& conn : connections) {
        if (conn.first == user2) {
            followers2 = conn.second;
            break;
        }
    }

    vector<int> mutual;
    for (int u1 : followers1) {
        if (find(followers2.begin(), followers2.end(), u1) != followers2.end()) {
            mutual.push_back(u1);
        }
    }

    if (mutual.empty()) {
        return "No mutual users between " + to_string(user1) + " and " + to_string(user2);
    } else {
        string result = "Mutual users between " + to_string(user1) +
                        " and " + to_string(user2) + ": ";
        for (size_t i = 0; i < mutual.size(); ++i) {
            result += to_string(mutual[i]);
            if (i != mutual.size() - 1) {
                result += ", ";
            }
        }
        return result;
    }
}