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
string mostInfluencer(vector<pair<int, vector<int>>> connections) {

    unordered_map<int, int> followerCount;
    for (const auto& conn : connections) 
        followerCount[conn.first] = 0;
        
    for (const auto& conn : connections) {
        for (int follower : conn.second) 
            followerCount[follower]++;
    }
    int maxFollowers = -1;
    int influencerId = -1;
    for (const auto& entry : followerCount) {
        if (entry.second > maxFollowers) {
            maxFollowers = entry.second;
            influencerId = entry.first;
        }
    }
    if (influencerId == -1)
        return "No influencer found";
    else
        return "Most influencer user is " + to_string(influencerId) + " with " + to_string(maxFollowers) + " followers";
}