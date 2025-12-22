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