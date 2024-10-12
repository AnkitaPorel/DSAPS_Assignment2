#include <iostream>
#include <vector>

using namespace std;

long long primes[]={9973,20011,20021,40039,40063,80111,80141,160253,160309};

long long smallerPrime(long long x)
{
    long long y=9973;
    for(int i=8;i>=0;i--)
    {
        if(primes[i]<x)
            return primes[i];
    }
    return y;
}

long long nextPrime(long long x)
{
    int y=160309;
    for(int i=0;i<9;i++)
    {
        if(primes[i]>x)
            return primes[i];
    }
    return y;
}

class HashMap {
    private:
        vector<long long> keys,vals;
        vector<bool> isEmpty;
        long long tableSize,count;
    public:
        HashMap()
        {
            this->tableSize=10007;
            this->count=0;
            vals.assign(tableSize,0);
            keys.assign(tableSize,-1);
            isEmpty.assign(tableSize,true);
        }
        long long hash1(long long key)
        {
            long long hashval=0;
            while(key>0)
            {
                hashval=(hashval*37 + (key%10))%tableSize;
                key/=10;
            }
            if(hashval<0)
                hashval+=tableSize;
            return hashval;
        }
        long long hash2(long long key)
        {
            long long R=smallerPrime(tableSize);
            long long hashval=key%R;
            if(hashval==0)
                hashval=1;
            else if(hashval<0)
                hashval+=R;
            else
                hashval=R-(key%R);
            return hashval;
        }
        void rehash()
        {
            long long len=tableSize;
            this->tableSize=nextPrime(2*tableSize);
            vector<long long> prevK=keys;
            vector<long long> prevV=vals;
            vector<bool> prevEmp=isEmpty;
            keys.assign(tableSize,-1);
            vals.assign(tableSize,0);
            isEmpty.assign(tableSize,true);
            this->count=0;
            for(int i=0;i<len;i++)
            {
                if(!prevEmp[i])
                    insert(prevK[i],prevV[i]);
            }
        }
        int insert(long long key,long long val)
        {
            if(count>(tableSize * 0.5))
                rehash();
            long long index=hash1(key);
            long long sec=hash2(key);
            if(index<0)
                index+=tableSize;
            while(!isEmpty[index])
            {   
                if(keys[index]==key)
                {
                    vals[index]=val;
                    return 1;
                }
                index=(index+sec)%tableSize;
                if(index<0)
                    index+=tableSize;
            }
            if(index<0)
                index+=tableSize;
            keys[index]=key;
            vals[index]=val;
            isEmpty[index]=false;
            this->count++;
            return 0;
        }
        long long get(long long key)
        {
            long long index=hash1(key);
            long long sec=hash2(key);
            if(index<0)
                index+=tableSize;
            while(!isEmpty[index])
            {
                if(keys[index]==key)
                    return vals[index];
                index=(index+sec)%tableSize;
                if(index<0)
                    index+=tableSize;
            }
            return 0;
        }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    for(int i=0;i<t;i++)
    {
        int n;
        cin>>n;
        HashMap map;
        for(int j=0;j<n;j++)
        {
            int type;
            long long k,v,kq;
            cin>>type;
            if(type==0)
            {
                cin>>k>>v;
                cout<<map.insert(k,v)<<"\n";
            }
            else if(type==1)
            {
                cin>>kq;
                cout<<map.get(kq)<<"\n";
            }
        }
    }
    return 0;
}