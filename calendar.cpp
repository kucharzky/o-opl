#include <iostream>
#include <vector>
#include <string>

struct MonthDays{
    std::string fName{};
    int fDays{};
};

void SimpleCalendar(){
    const std::vector<MonthDays> calendar{
        {"January", 31},
        {"February", 28},
        {"March", 31},
        {"April", 30},
        {"May", 31},
        {"June", 30},
        {"July", 31},
        {"August", 31},
        {"September", 30},
        {"October", 31},
        {"November", 30},
        {"December", 31}
    };
    auto sum_days{0};
    for(auto month:calendar){
        sum_days+= month.fDays;
        std::cout << month.fName << " has " <<  month.fDays << " days\n";
    }
    std::cout << "\nTotal days: " << sum_days << std::endl;
}
int main(){
    SimpleCalendar();
}