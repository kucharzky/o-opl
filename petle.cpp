#include <iostream>
#include <vector>
int main(){
std::vector< double > vec( 123 );
    for( auto k { 0 }; k < vec.size(); ++ k )
    {
    vec[ k ] = 2 * k + 1;
    }
    
    auto k{0};
    while(k<vec.size()){
        vec[k] = 2*k+1;
        k++;
    }

    do{
        vec[k] = 2*k+1;
        k++;
    }while(k<vec.size());
}
