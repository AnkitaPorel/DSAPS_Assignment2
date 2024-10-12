#include <iostream>
#include <vector>

using namespace std;

long long tableSize=1e7+9;

long long hash1(const string &str)
{
    long long hashval=0;
    long long p=1;
    for(char ch:str)
    {
        hashval=(hashval+(ch-'a'+1)*p)%tableSize;
        p=(p*31)%tableSize;
    }
    return hashval%tableSize;
}

long long hash2(const string &str)
{
    long long hashval=0;
    long long p=1;
    for(char ch:str)
    {
        hashval=(hashval+(ch-'a'+1)*p)%tableSize;
        p=(p*37)%tableSize;
    }
    return hashval%tableSize;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int n;
        cin>>n;
        vector<bool> bloomFilter(tableSize,false);
        for(int j=0;j<n;j++)
        {
            string s;
            cin>>s;
            long long hashval1=hash1(s);
            long long hashval2=hash2(s);
            if(bloomFilter[hashval1] && bloomFilter[hashval2])
                cout<<1<<"\n";
            else
            {
                cout<<0<<"\n";
                bloomFilter[hashval1]=true;
                bloomFilter[hashval2]=true;
            }
        }
    }
    return 0;
}