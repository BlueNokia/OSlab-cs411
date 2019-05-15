#include <iostream> 
#include <unistd.h> 
#include<sys/wait.h>
using namespace std; 
bool isPrime(int num){
    bool flag=true;
    for(int i = 2; i <= num / 2; i++) {
       if(num % i == 0) {
          flag = false;
          break;
       }
    }
    return flag;
}  
// Driver code 
int main() 
{ 
    int max, n, i,j,l=2,h,x; 
    cin>>max>>n;
    l=2;
    h=max/n;
    x=h;
    for(j=0;j<n-1;j++)
    {
        if (fork() == 0) { 
            for (i = l; i <=h; i++) 
            { 
                if (isPrime(i)==true)
                {
                    //count++;
                    cout<<i<<" ";
                }
            } 
            exit(0);
        }
        
        else
            wait(NULL);
        l=h+1;
        h=h+x;
    }
    if(fork()==0)
    {
        for(i=h;i<=max;i++)
        {
            if (isPrime(i)==true)
            {
                //count++;
                cout<<i<<" ";
            }
        }
        exit(0);
    }
    else
        wait(NULL);
    //cout<<count;
    return 0; 
} 

