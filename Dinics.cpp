/* 

DINIC'S ALGORITHM : CSES - DOWNLOAD SPEED

*/

#include <bits/stdc++.h>
using namespace std;
 
#define F first
#define S second
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) (int)(x).size()
#define each(x, a) for (auto& x : a)
#define fastio ios::sync_with_stdio(false); cin.tie(0);
#define LINF 1e18
#define INF 1e9
#define int long long

// Typedefs
typedef long long ll;
 
struct FlowEdge{
    int u;
    int v;
    ll capacity;
    int rev_idx;
    FlowEdge(int u, int v, ll capacity, int rev_idx) : u(u), v(v), capacity(capacity), rev_idx(rev_idx) {}
};

struct Dinics
{
    int n;
    int source;
    int sink;
    ll maxFlow;
    vector<vector<FlowEdge>> graph;
    vector<int> level;
    vector<int> visited;
    vector<int> next;

    void add_edge(int u, int v, ll capacity){
        graph[u].emplace_back(u,v,capacity, graph[v].size());
        graph[v].emplace_back(v,u,0,graph[u].size()-1);
    }

    bool bfs(){
        fill(level.begin(), level.end(), -1);
        level[source] = 0;
        queue<int> q;
        q.push(source);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(FlowEdge &edge : graph[u]){
                int cap = edge.capacity;
                int v = edge.v; 
                if(level[v] == -1 && cap > 0){
                    level[v] = level[u] + 1;
                    q.push(v);
                }
            }
        }
        return level[sink] != -1;
    }

    ll dfs(int node, ll pushFlow){
        if(node == sink) return pushFlow;
        for( ;next[node] < graph[node].size(); next[node]++){
            FlowEdge &edge = graph[node][next[node]];
            int v = edge.v;
            ll cap = edge.capacity;
            
            if(cap > 0 && level[v] == level[node] + 1){
                ll bottleNeck = dfs(v,min(pushFlow,cap));

                if(bottleNeck > 0){
                    edge.capacity -= bottleNeck;
                    graph[v][edge.rev_idx].capacity += bottleNeck;
                    return bottleNeck;
                }
            }
        }
        return 0;
    }

    int max_flow(){
        level.resize(n+1,-1);
        while(bfs()){
            fill(all(next),0);
            for(ll i = dfs(source,LINF); i > 0; i = dfs(source,LINF)){
                maxFlow += i;
            }
        }
        return maxFlow;
    }
    
    Dinics(int source, int sink, int n) : source(source), sink(sink), n(n){
        graph.resize(n+1);
        next.resize(n+1);
        maxFlow = 0;
    }
};
 

 
void solve() {
    int n,m;
    cin >> n >> m;

    Dinics d = Dinics(1,n,n);

    for(int i = 0; i < m; i++){
        int u,v,c;
        cin >> u >> v >> c;
        d.add_edge(u,v,c);
    }

    cout << d.max_flow() << endl;
}
 
signed main() {
    fastio;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}