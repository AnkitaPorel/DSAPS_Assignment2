#include <iostream>
#include <vector>

using namespace std;

long long tableSize=1e6+3;

class HashTable {
    private:
        vector<long long> keys;
        vector<string> stringPool;
        vector<long long> keyPool;
        int count;
    public:
        HashTable()
        {
            keys.assign(tableSize,-1);
            count=0;
        }
        void put(long long key,const string &str)
        {
            int i=0;
            long long hashval;
            while(i<tableSize)
            {
                hashval=((key%tableSize)+i*i)%tableSize;
                if(keys[hashval]==-1)
                {
                    keys[hashval]=count;
                    stringPool.push_back(str);
                    keyPool.push_back(key);
                    count++;
                    return;
                }
                else if(keyPool[keys[hashval]]==key)
                {
                    stringPool[keys[hashval]]=str;
                    return;
                }
                i++;
            }
        }
        string get(long long key)
        {
            int i=0;
            long long hashval;
            while(i<tableSize)
            {
                hashval=((key%tableSize)+i*i)%tableSize;
                if(keys[hashval]==-1)
                    return "0";
                else if(keyPool[keys[hashval]]==key)
                    return stringPool[keys[hashval]];
                i++;
            }
            return "0";
        }
};

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
        HashTable map;
        for(int j=0;j<n;j++)
        {
            int type;
            cin>>type;
            long long k;
            string v;
            switch(type)
            {
                case 0:
                    cin>>k>>v;
                    map.put(k,v);
                    break;
                case 1:
                    cin>>k;
                    cout<<map.get(k)<<"\n";
                    break;
            }
        }
    }
    return 0;
}