#include <bits/stdc++.h>
using namespace std;


int main() {
    long int N; cin >> N;
    vector<pair<long int,long int>> torn;
    for(long int i = 0; i < N; i++){
        long int a,b;cin >> a >> b;
        torn.push_back({a,b});
    }
    
    sort(torn.begin(), torn.end());
    reverse(torn.begin(),torn.end());
    
    //Latest height
    set<long int> bst;
    bst.insert(0);
    //Latest height ;;; highestHeight
    map<long int,long int> bestVals;
    bestVals[0] = 0;
    
    vector<pair<long int,long int>> toUpdate;
    for(int i = 0; i < N; i++){
        long int num = torn[i].second;

        long int elm = *--bst.upper_bound(num);
        long int val = bestVals[elm];
        
        toUpdate.push_back({num, val + num});
        if(i == N-1 || torn[i+1].first < torn[i].first){
            for(auto p : toUpdate){
                if (bestVals.find(p.first) == bestVals.end()){
                    bestVals[p.first] = -1;
                }
                bestVals[p.first] = max(bestVals[p.first],p.second);
                bst.insert(p.first);
                
                while(bst.upper_bound(p.first) != bst.end() && bestVals[*bst.upper_bound(p.first)] <= bestVals[p.first]){
                    bestVals.erase(bestVals.find(*bst.upper_bound(p.first)));
                    bst.erase(bst.upper_bound(p.first));
                }
            }
            toUpdate.clear();
        }
        /*
        for (const auto &value : bestVals) {
            cout << value.first << " " <<value.second << " || ";
        }cout << "ENDED" << endl;*/
    }

    long int ans = 0;
    for (const auto &value : bestVals) {
        ans = max(ans,value.second);
        //cout << value.first << " " <<value.second << " || ";
    }//cout << "ENDED" << endl;
    cout << ans;
    
    return 0;
}
