#include <bits/stdc++.h>

using namespace std;
int n,qr;
long long f[100001];
int depth[100001];
int parent[100001];
int w[100001];
vector<int> v[100001];
int dp[100001][25];
void dfs(int cur,int prev)
{
    f[cur]=w[cur];
    if(prev>=0)
    {
        depth[cur]=depth[prev]+1;
        parent[cur]=prev;
    }
    for(auto node : v[cur])
    {
        if(node==prev)continue;
        dfs(node,cur);
        f[cur]+=f[node];
    }
}
void precalc()
{
    memset(dp,-1,sizeof(dp));
    for(int i=0;i<n;i++)
    {
        dp[i][0]=parent[i];
    }
    int lim=log2(n);
    for(int j=1;j<lim;j++)
    {
        for(int i=0;i<n;i++)
        {
            if(dp[i][j-1]!=-1)
            {
                dp[i][j]=dp[dp[i][j-1]][j-1];
            }
        }
    }
}
int getanc(int node,int k)
{
    int lim=log2(n);
    for(int i=lim;i>=0;i--)
    {
        if(dp[node][i]!=-1 && k>=(1<<i))
        {
            node=dp[node][i];
            k-=(1<<i);
        }
    }
    return node;
}
void calc(int p,int q)
{
    int lvl=depth[p]-depth[q]-1;
    if(lvl<0)
    {
        cout << f[q]<<'\n';
        return;
    }
    int anc=getanc(p,lvl);
    if(parent[anc]==q)
    {
        cout << f[0]-f[anc]<<'\n';
    }
    else
    {
        cout << f[q]<<'\n';
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> qr;
    for(int i=0;i<n;i++)
    {
        cin >> w[i];
    }
    int p,q;
    for(int i=0;i<n-1;i++)
    {
        cin >> p >> q;
        p--;
        q--;
        v[p].push_back(q);
        v[q].push_back(p);
    }
    depth[0]=0;
    parent[0]=0;
    dfs(0,-1);
    precalc();
    for(int i=0;i<qr;i++)
    {
        cin >> p >> q;
        p--;
        q--;
        if(p==q)
        {
            cout << f[0]<<'\n';
        }
        else
        {
            calc(p,q);
        }
    }
    return 0;
}
