#include<bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    unordered_map<int, vector<int>> graph;

    for(int i = 0; i < N-1; i++){
        int a,b; cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bool calculated[N] = {};

    int primes[60] = {
            2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
            31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
            73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
            127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
            179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
            233, 239, 241, 251, 257, 263, 269, 271, 277, 281
    };
    
    long long int ans[N] = {};
    for(int i = 0; i < N; i++){
        ans[i] = 1;
    }
    
    //The cycle is goin
    int counter = 0;
    int laps = 0; //laps <= counter
    while(counter < N){

        deque<int> myQueue;
        myQueue.push_back(0);
        deque<int> topoOrder;
        int prev[N];
        prev[0] = -1;
        bool vis[N] = {};


        while(!myQueue.empty()){
            int node = myQueue.front();
            myQueue.pop_front();
            vis[node] = true;
            topoOrder.push_front(node);

            for(int i : graph[node]){
                if (vis[i] == true){continue;}
                myQueue.push_back(i);
                prev[i] = node;
            }
        }


        int depth[N] = {};
        int startNode = 0;
        int depthStartNode = -1;
        for(int node : topoOrder){
            if (calculated[node] == true){
                depth[node] = -1;
                continue;
            }

            if (node != 0 && calculated[prev[node]] == false){
                depth[prev[node]] = max(depth[prev[node]],depth[node] + 1);
            }
            
            if (depth[node] > depthStartNode){
                depthStartNode = depth[node];
                startNode = node;
            }
        }
        
        int node = startNode;
        while(1){
            int val = -1;
            int nextNode = -1;
            depth[node] = -1;
            if (calculated[node] == false){
                counter += 1;
                
                if (prev[node] == -1){ans[node] = 1;}else{
                    ans[node] = ans[prev[node]] * primes[laps];
                }
            }
            
            calculated[node] = true;
            for(auto j : graph[node]){
                if (depth[j] > val){
                    val = depth[j];
                    nextNode = j;
                }
            }
            if (nextNode == -1){break;}
            node = nextNode;
        }
        cout << endl;
        /*
        for(int i = 0; i < N; i++){
            cout << depth[i] << " ";
        } cout << endl;*/
        laps++;
    }
    
    for(int i = 0; i < N; i++){
        cout << ans[i] << " ";
    }


    return 0;
}
