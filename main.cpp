#include <iostream>
#include<math.h>
using namespace std;


class UBigInt{


    public :
    //static int ins;

        int size;
        int *arr;

        void noramlize(){
            while(size>0 && arr[size-1] == 0)--size;
        }
    public:
        UBigInt(int a){
            //ins++;
            int cl = 0;
            if(a<0)a=-a;
            if(a==0)cl++;
            arr = new int[14];
            size = 14;
           while(cl<14)
           {
                arr[cl++] = a%10;
                a/=10;
            }
            while(size>0 && arr[size-1] == 0)--size;
        }
        UBigInt(const UBigInt& a){
            //ins++;
            size = a.size;
            arr = new int[size];
            for(int i=0;i<size;++i)
                arr[i] = a.arr[i];
        }


      /*  UBigInt(UBigInt a){
            size = a.size;
            arr = new int[size];
            for(int i=0;i<size;++i)
                arr[i] = a.arr[i];
        }*/

        int valAt(int pos){
            if(pos<0 || pos>=size)
                return 0;
            else
                return arr[pos];
        }
        UBigInt(){
            UBigInt(0);
        }

        UBigInt operator+=(UBigInt &x){
            int sz = max(x.size,size)+1;
            int *q = new int[sz+2];
            int add = 0;
            for(int i=0;i<sz || add>0;++i){
                add+= valAt(i) + x.valAt(i);
                q[i] = add%10;
                add/=10;
            }
            while(sz>0 && q[sz-1] == 0)--sz;
            //delete[] arr;
            arr = q;
            size = sz;
            return *this;
        }
        UBigInt operator+(UBigInt x){
            UBigInt a = *this;
            a+=x;
            return a;
        }

        UBigInt(string s){

            int cl = 0;

            size = s.length();
            arr = new int[size];
           // while(a>0 || cl<14)
           for(int i=s.length()-1;i>=0;--i)
           {
                int q = s[i]  - '0';
                if(q>9 || q<0)
                    continue;
                arr[cl++] = q;
            }
            while(size>0 && arr[size-1] == 0)--size;
        }


        UBigInt operator*=(UBigInt x){
            int sz = (x.size*size)+2;
            int *q = new int[sz+2];
            for(int i=0;i<sz+2;++i)
                q[i] = 0;
            int add = 0;
            for(int j=0;j<x.size;++j)
                for(int i=0;i<size || add>0;++i){
                    add+= valAt(i)*x.valAt(j);
                    q[i+j] += add;
                    add=q[i+j]/10;
                    q[i+j]%=10;
            }
            while(sz>0 && q[sz-1] == 0)--sz;
            //delete[] arr;
            arr = q;
            size = sz;
            return *this;
        }
        UBigInt operator*(UBigInt x){
            UBigInt r = *this;
            r*=x;
            return r;
        }
        void print(){

            for(int i=max(size-1,0);i>=0;--i)
                cout<<valAt(i);cout<<"";
        }

        bool operator>(UBigInt x){
            int pos = max(size,x.size)-1;
            while(pos>0 && valAt(pos) == x.valAt(pos))
                --pos;
            return valAt(pos)>x.valAt(pos);
        }
        bool operator<(UBigInt x){
            return x>*this;
        }

        bool operator>=(UBigInt x){
            return !(*this<x);
        }
        bool operator<=(UBigInt x){
            return !(*this>x) ;
        }

        bool operator==(UBigInt x){
            return *this>=x && *this<=x;
        }

        bool operator!=(UBigInt x){
            return *this<x || *this>x ;
        }
        UBigInt operator-=(UBigInt x){
            if(*this<=x)
                return (*this = UBigInt(0));

            int sz = max(size,x.size);
            int *q = new int[sz+2];
            for(int i=sz-1;i>=0;--i)
                q[i] = valAt(i) - x.valAt(i);


            int add = 0;
            for(int i=0;i<sz;++i){
                q[i]-=add;
                add = 0;
                while(q[i]<0){
                    ++add;
                    q[i]+=10;
                }
            }
            //delete[] arr;
            arr = q;
            while(sz>0 && arr[sz-1] == 0)--sz;
            size = sz;
            return *this;
        }
        UBigInt operator-(UBigInt u){
            UBigInt res = *this;
            res-=u;
            return res;
        }


        UBigInt med(UBigInt x,UBigInt y){
            x = x+y;
            int add = 0;
            for(int i=x.size-1;i>=0;--i){
                x.arr[i]+=add*10;
                add = x.arr[i]%2;
                x.arr[i]/=2;
            }
            x.noramlize();
            return x;

        }

        UBigInt operator/(UBigInt x){


            if(x.size <= 1 && x.arr[0] == 0){
                cout<<"Division by 0 cannot be performed\n";
                return *this;
            }

            UBigInt l = 0, r = *this,m = 0;
            //int oo = 1000;
            //cout<<"[";l.print();cout<<',';r.print();cout<<"]\n";
            while(r-l>0 ){

                m = med(l,r);
                if((m+1)*x>*this)
                    r = m;
                else
                    l = m + 1;
                //cout<<"[";l.print();cout<<',';r.print();cout<<"]\n";
            }
            //print();cout<<'/';x.print();cout<<'=';r.print();cout<<'\n';

            return l;
        }

        ~UBigInt(){
            //delete[] arr;
            arr = NULL;
        }
};


int abs(int a){
    return (a>0)?a:(-a);
}

class BigInt:public UBigInt{

public:
    bool negative;
    ~BigInt(){
        //delete[] arr;
        arr = NULL;
    }
    UBigInt abs(){
        UBigInt r(0);
        r.size = size;
        int *q = new int[size];
        for(int i=0;i<size;++i)
            q[i] = arr[i];


        //delete[] r.arr;
        r.arr = q;
        return r;
    }


    BigInt(UBigInt x){
        size = x.size;
        int * q = new int[size];
        negative  = 0;
        for(int i=0;i<size;++i)
            q[i] = x.arr[i];
        arr = q;

        //print();cout<<'\n';

    }

    void print(){
        if(negative)cout<<"-";
        UBigInt::print();
    }

    BigInt(int x):UBigInt(x){
        negative = (x<0);
        //if(x<0)x=-x;
        //UBigInt::UBigInt(x);
        //print();cout<<'\n';

    }
    BigInt neg(){
        BigInt r(0);
        r.negative = !negative;
        r.size = size;
        int *q = new int[size];
        for(int i=0;i<size;++i)
            q[i] = arr[i];
        r.arr = q;
        return r;
    }
    BigInt operator-(){
        BigInt r= *this;
        r.negative^=1;
        return r;
    }

    BigInt operator+(BigInt x){
        //print();cout<<"+";x.print();
        if(!negative)
        {
            if(!x.negative)
                return abs()+ x.abs();
            else
                return *this - x.neg();
        }
        else {
            if(x.negative)
                return -(BigInt)(abs()+x.abs());
            else
                return -(neg() + x.neg());

        }
    }
    BigInt operator-(BigInt x){
        if(x.negative)
            return *this + x.neg();
        if(negative)
            return -(BigInt)(abs()+x.abs());
        if(abs()>=x.abs())
            return (BigInt)(abs()-x.abs());
        else return -(BigInt)(x.abs()-abs());
    }

    BigInt operator*(BigInt x){
        BigInt r = x.abs()*abs();
        r.negative  = negative^x.negative;
        return r;
    }

    BigInt(string s)
        :UBigInt(s)
    {
        if(s[0] == '-'){
            negative = 1;
            s.erase(0,1);
        }
        else
            negative = 0;

       // UBigInt(s);
    }


    BigInt operator%(BigInt a){
        if(a<0)a= -a;
        BigInt d = *this/a;
        //d.print();cout<<'\n';
        BigInt r = *this - d*a;
        //r.print();cout<<'\n';(d*a).print();cout<<'\n';
        //d.print();cout<<'\n';a.print();cout<<'\n';r.print();cout<<'\n';(d*a).print();
        //r.print();
        if(negative)r=r  + a;
        return r;
    }

    BigInt operator/(BigInt x){


        if(x.size <= 1 && x.arr[0] == 0){
            cout<<"Divizion by 0 cannot be performed\n";
            return *this;
        }

        BigInt r = abs()/x.abs();
        r.negative = x.negative ^ negative;
/*
        while( ((r+(-2*r.negative+1))*x).abs()<= abs())r = r+(-2*r.negative+1);
        //r= r + BigInt(-2*r.negative-1);
        print();cout<<'/';x.print();cout<<'=';r.print();cout<<'\n';*/
        return r;
    }
};


UBigInt gcd(UBigInt a,UBigInt b){
    //a.print();cout<<"^";b.print();cout<<"\n";
    while(a!=b){

        if(a>b)
            a = a-b;
        else
            b = b-a;
        //a.print();cout<<"^";b.print();cout<<"\n";

    }
    return a;

}

BigInt gcd(BigInt a,BigInt b){
    return gcd(a.abs(),b.abs());

}

BigInt binpow(BigInt x,UBigInt p){
    BigInt r = 1;
    while(p>0){
        //x.print();cout<<' ';r.print();cout<<' ';p.print();cout<<'\n';
        if(p.arr[0]%2)
            r = r*x;
        x = x*x;
        p = p/2;
    }
    return r;
}

int main()
{
   // BigInt x = 10004354,y = 10000576;
    //BigInt z = x+y, u = x*y;
   // x.print();y.print();
   // z.print();u.print();
    //BigInt l = x-y,k = y-x;
    //l.print();k .print();
    //cout<< (x<y)<< " "<<(x>y)<< " "<<(x<=y)<<" "<<(x>=y)<<'\n';
    //cout << "Hello World!" << endl;
    //BigInt lq = (1000);
    //BigInt di= 225  ;
    //(lq/di).print`();

    //(UBigInt(756)-UBigInt(68)).print();
  //  gcd(BigInt(1024),BigInt(756)).print();
  //  BigInt x = 33,y = 0;
    //(x/y).print();
    //lq.print();
#define U UBigInt

    //U x =1000,y = 20;
    //U a1 =111111,a2=222222,a3=333333,a4=444444,a5= 5555555;
    //((a1*a2*a3)/(a4*a5)).print();
 //   (x/y).print();

   // U x=16,y=16;
   // x = x*y;
   // x.print();cs

    BigInt t = 10;
   // int n;cin>>n;
    t = binpow(t,1000);
    //(t/100).print();
    //t = t/100;
   // (-t/100).print();
  // cout<<'\n'<< UBigInt::ins<<'\n';

//        t.print();
  //   t = 1000;
 //    t = -t;
     //(t/17).print();

     cout<<'\n';


    // (binpow(BigInt("100"),100)%BigInt("101")).print();



   //  ((BigInt("2346517777713242365472134")*BigInt("587285923647"))/BigInt("587285923647"))  .print();
        gcd(BigInt(16384) ,BigInt(640)).print();
    return 0;

}

