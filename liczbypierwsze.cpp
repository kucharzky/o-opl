#include <iostream>
#include <vector>
#include <cmath>

int main(){
    auto n{0};
    std::cin>>n;
    /*std::vector<bool> num(n, true);
    for (int i=2; i< sqrt(n);++i){
        if (num[i]){
            for (int j = i*i;j<n;j+=i){
                num[j]=false;
            }
        }
    }
    for (int i =2;i<n;++i){
        if (num[i]){
            std::cout<<i<<std::endl;
        }
    }*/
   std::vector<std::tuple<int, bool>> num;
   for (int i=0; i<n; ++i){
    num.emplace_back(i,i>=2);
   }
   for (int i=2; i< sqrt(n);++i){
        if (std::get<1>(num[i])){
            for (int j = i*i;j<n;j+=i){
                std::get<1>(num[j])=false;
            }
        }
    }
    std::cout << "Liczby pierwsze mniejsze od " << n << " to: ";
    for (const auto& [value, is_prime] : num) {
        if (is_prime) {
            std::cout << value << " ";
        }
    }
}