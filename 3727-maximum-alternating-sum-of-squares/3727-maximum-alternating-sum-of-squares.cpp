constexpr int M=4e4+1;
int freq[M];
class Solution {
public:
    static long long maxAlternatingSum(vector<int>& nums) {
        const int n=nums.size(), h=n/2;
        int xMin=1e5, xMax=-1e5;
        for(int& x : nums){
            x=abs(x);
            freq[x]++;
            xMin=min(x, xMin);
            xMax=max(x, xMax);
        }
        long long ans=0;
        int cntF=0, prvF=0;
        for(long long x=xMin; x<=xMax; x++, prvF=cntF){
            int f=freq[x];
            if (f==0) continue;
            cntF+=f;
            bool neg=cntF-1<h, pos=prvF>=h;
            ans-=(-neg & f*x*x);
            ans+=(-pos & f*x*x);
            ans+=(-(!pos && !neg) & (prvF+cntF-2*h)*x*x);
          
        }
        for(int x: nums) freq[x]=0;
        return ans;
    }
};
auto init = []()
{ 
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 'c';
}();