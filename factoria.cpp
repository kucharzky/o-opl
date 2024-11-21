#include <iostream>

int rec_fact(int n){
return (n==0) || (n==1) ? 1 : n*rec_fact(n-1);
}
int iter_fact(int n){
    int result{1};
    if(n==0) result=1;
    for (auto i=1; i<=n; ++i){
        result*=i;
    }
    return result;
}


int main(){
    auto x{4};
    

    std::cout<<rec_fact(x)<<std::endl;
    std::cout<<iter_fact(x)<<std::endl;
}