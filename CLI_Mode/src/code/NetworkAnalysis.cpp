#include "..\\header\\NetworkAnalysis.h"
#include "..\\header\\NetworkBuilder.h"


string suggestUser(int userid, vector<pair<int,vector<int>>> connections) {
    unordered_map<int, unordered_set<int>> graph;

    // Build graph
    for (auto &c : connections) {
        graph[c.first] = unordered_set<int>(c.second.begin(), c.second.end());
    }

    if (graph.find(userid) == graph.end())
        return "No suggestions available";

    auto &userFollowers = graph[userid];
    unordered_set<int> suggestions;

    // Friends of friends
    for (int follower : userFollowers) {
        if (graph.find(follower) == graph.end()) continue;

        for (int fof : graph[follower]) {
            if (fof != userid && userFollowers.find(fof) == userFollowers.end()) {
                suggestions.insert(fof);
            }
        }
    }

    if (suggestions.empty())
        return "No suggestions available";

    string result = "Suggested users for user " + to_string(userid) + ": ";
    bool first = true;
    for (int u : suggestions) {
        if (!first) result += ", ";
        result += to_string(u);
        first = false;
    }

    return result;
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
string mostInfluencer(vector<pair<int, vector<int>>> connections, const vector<User>& users){
    unordered_map<int, int> followerCount;
    for (const auto& conn : connections) 
        followerCount[conn.first] = 0;
        
    for (const auto& conn : connections) {
        for (int follower : conn.second) 
            followerCount[follower]++;
    }
    int maxFollowers = -1;
    int influencerId = -1;
    string influencerName = "";
    for (const auto& entry : followerCount) {
        if (entry.second > maxFollowers) {
            maxFollowers = entry.second;
            influencerId = entry.first;
        }
    }
    if (influencerId == -1)
        return "No influencer found";
    else {
        for (const auto& user : users) {
            if (user.getId() == influencerId) {
                influencerName = user.getName();
                break;
            }
        }
    }
    return "Most influencer user is " + influencerName + " with ID: " + to_string(influencerId) +
           " with " + to_string(maxFollowers) + " followers";

        }


pair<int, string> mostActiveUser(
    const vector<pair<int, vector<int>>>& graph,
    const vector<User>& users
)
{
    int mostActiveId = -1;
    int maxOutDegree = -1;

    for (const auto& node : graph) {
        int outDegree = node.second.size();
        if (outDegree > maxOutDegree) {
            maxOutDegree = outDegree;
            mostActiveId = node.first;
        }
    }

    string username = "";
    for (const auto& u : users) {
        if (u.getId() == mostActiveId) {
            username = u.getName();
            break;
        }
    }

    return { mostActiveId, username };
}
