#include <iostream>
#include <vector>

using namespace std;

long long primes[]={9973,20011,20021,40039,40063,80111,80141,160253,160309};

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

class CHashMap {
    private:
        vector<string> t1,t2;
        vector<bool> isEmpty1,isEmpty2;
        long long tableSize,count;
    public:
        CHashMap()
        {
            this->tableSize=10007;
            t1.assign(tableSize,"");
            t2.assign(tableSize,"");
            isEmpty1.assign(tableSize,true);
            isEmpty2.assign(tableSize,true);
            count=0;
        }
        void rehash()
        {
            if(tableSize!=nextPrime(2*tableSize))
            {
                long long len=tableSize;
                vector<string> pT1=t1,pT2=t2;
                vector<bool> pisEmpty1=isEmpty1,pisEmpty2=isEmpty2;
                this->tableSize=nextPrime(2*tableSize);
                t1.assign(tableSize,"");
                t2.assign(tableSize,"");
                isEmpty1.assign(tableSize,true);
                isEmpty2.assign(tableSize,true);
                count=0;
                for(int i=0;i<len;i++)
                {
                    if(!pisEmpty1[i])
                        insert(pT1[i]);
                    if(!pisEmpty2[i])
                        insert(pT2[i]);
                }
            }
        }
        long long hash1(const string &key)
        {
            long long hashval=0;
            for(char ch:key)
                hashval=(hashval*37 + ch)%tableSize;
            hashval%=tableSize;
            if(hashval<0)
                hashval+=tableSize;
            return hashval;
        }
        long long hash2(const string &key)
        {
            long long hashval=0;
            for(char ch:key)
                hashval=(hashval*41 + ch)%tableSize;
            hashval%=tableSize;
            if(hashval<0)
                hashval+=tableSize;
            return hashval;
        }
        int retrieve(const string &key)
        {
            long long pos1=hash1(key),pos2=hash2(key);
            if(!isEmpty1[pos1] && t1[pos1]==key)
                return 1;
            if(!isEmpty2[pos2] && t2[pos2]==key)
                return 1;
            return 0;
        }
        int remove(const string &key)
        {
            long long pos1=hash1(key),pos2=hash2(key);
            if(!isEmpty1[pos1] && t1[pos1]==key)
            {
                isEmpty1[pos1]=true;
                count--;
                return 1;
            }
            if(!isEmpty2[pos2] && t2[pos2]==key)
            {
                isEmpty2[pos2]=true;
                count--;
                return 1;
            }
            return 0;
        }
        int insert(const string &key)
        {
            int p1,p2,disp=0;
            if(retrieve(key)==1)
                return 1;
            if(count>(tableSize*0.5))
                rehash();
            string currKey=key;
            while(disp<500)
            {
                p1=hash1(currKey);
                if(isEmpty1[p1])
                {
                    t1[p1]=currKey;
                    isEmpty1[p1]=false;
                    count++;
                    return 0;
                }
                else
                {
                    string temp=t1[p1];
                    t1[p1]=currKey;
                    currKey=temp;
                }
                p2=hash2(currKey);
                if(isEmpty2[p2])
                {
                    t2[p2]=currKey;
                    isEmpty2[p2]=false;
                    count++;
                    return 0;
                }
                else
                {
                    string temp=t2[p2];
                    t2[p2]=currKey;
                    currKey=temp;
                }
                disp++;
            }
            rehash();
            return insert(currKey);
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
        CHashMap map;
        for(int j=0;j<n;j++)
        {
            int type;
            string si;
            cin>>type>>si;
            switch(type)
            {
                case 0:
                    cout<<map.insert(si)<<"\n";
                    break;
                case 1:
                    cout<<map.retrieve(si)<<"\n";
                    break;
                case 2:
                    cout<<map.remove(si)<<"\n";
                    break;
            }
        }
    }
    return 0;
}