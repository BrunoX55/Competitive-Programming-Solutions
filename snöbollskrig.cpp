#include<bits/stdc++.h>
using namespace std;

int main() {
    //Gain input
    int N, L, K; cin >> N >> L >> K;
    
    vector<int> startBaser;
    for(int i = 0; i < L; i++){
        int v; cin >> v;
        startBaser.push_back(v);
    }
    
    unordered_map<int,vector<pair<int,int>>> graph;
    for(int i = 0; i < K; i++){
        int a,b,w; cin >> a >> b >> w;
        graph[a].push_back({w,b});
        graph[b].push_back({w,a});
    }
    
    
    int timeToReach[N];
    unordered_set<int> owner[N];
    int permaOwn[N];
    for(int i = 0; i < N; i++){
        timeToReach[i] = -1;
        permaOwn[i] = -1;
    }
    
    //Make conditions for starter bases to till pq
    //negative weight for min
    //-weight, start, end
    priority_queue<array<int,3>> pq;
    int c = 0;
    for(int i : startBaser){
        owner[i].insert(c);
        permaOwn[i] = c;
        c++;
        for(pair<int,int> edgePairs : graph[i]){
            int w = edgePairs.first;
            int to = edgePairs.second;
            pq.push({-w, i, to});
        }
    }
    
    set<pair<int,int>> war;
    unordered_set<int> newOwners;
    
    
    while(!pq.empty()){
        int w = -pq.top()[0];
        int start = pq.top()[1];
        int end = pq.top()[2];
        pq.pop();
        
        if (owner[end].find(permaOwn[start]) == owner[end].end() && permaOwn[end] == -1){
            owner[end].insert(permaOwn[start]);
            if (newOwners.find(end) == newOwners.end()){
                newOwners.insert(end);
            }
        }else if(permaOwn[end] != -1){
            int a = min(permaOwn[start],permaOwn[end]);
            int b = max(permaOwn[start],permaOwn[end]);
            if (a!=b && war.find({a,b}) == war.end()){
                war.insert({a,b});
            }
        }
        
        if (pq.size()==0 or -pq.top()[0] > w){
            for(int i : newOwners){
                if (owner[i].size() == 1){
                    //Not occupied
                    for(int elm : owner[i]){
                        permaOwn[i] = elm;
                    }
                    
                    for(auto myPair : graph[i]){
                        pq.push({-(w+myPair.first), i, myPair.second});
                    }
                }else{
                    for(int x : owner[i]){
                        for(int y : owner[i]){
                            int a = min(x,y);
                            int b = max(x,y);
                            if (a==b){continue;}
                            if (war.find({a,b}) == war.end()){
                                war.insert({a,b});
                            }
                        }
                    }
                }
            }
            newOwners.clear();
        }
        /*
        for(int i=0; i < N; i++){
                cout << i << " my Own are : ";
                for(int j : owner[i]){
                    cout << j << " ";
                }
                cout << endl;
        }
        
        for(int i=0; i < N; i++){
                cout << i << " PERMA : ";
                cout << permaOwn[i];
                cout << endl;
        }
        cout << "---";*/
    }
    
    vector<pair<int,int>> ans;
    
    for(auto i : war){
        ans.push_back({i.first,i.second});
    }
    sort(ans.begin(),ans.end());
    
    for(pair<int,int> i : ans){
        cout << i.first << " " << i.second << endl;
    }

    return 0;
}
