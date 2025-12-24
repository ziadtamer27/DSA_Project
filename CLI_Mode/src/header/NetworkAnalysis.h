#include <bits/stdc++.h>
using namespace std;
string suggestUser(int userid, vector<pair<int,vector<int>>> connections);
string mutualUsers(int user1, int user2, vector<pair<int, vector<int>>> connections);
string mostInfluencer(vector<pair<int, vector<int>>> connections, const vector<User>& users);
pair<int, string> mostActiveUser(const vector<pair<int, vector<int>>>& graph, const vector<User>& users);