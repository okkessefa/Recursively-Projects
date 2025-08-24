#include <iostream>
#include <string>

std::string reverstring(const std::string& input){
    // define the base case | stopping condition 
    if(input.empty())
    {
        return "";
    }
    // continue with ssub-problems
    return reverstring(input.substr(1))+ input[0];
}

bool polindrome(const std::string& input){
    //define the base case | stop condition
    if(input.length() == 0 || input.length() == 1 ){
        return true;
    }
    // Do some work to shrink the problem space
    if(input[0] == input[input.length()-1]){
        return polindrome(input.substr(1, input.length() - 1));
    }
    // additional base case to handle non-polindomes
    return false;
}

// std::string input = "kayak";
// std::cout<<reverstring(input)<<std::endl;
// if(polindrome(input)){
    //     std::cout<<"This work is polindrome\n";
    // }else{
        //     std::cout<<"This work is polindrome\n";
        // }
        
        
std::string findbinary(int decimal, std::string result){
    if(decimal == 0){
        return result;
    }
    result = std::to_string(decimal % 2) + result;
    return findbinary(decimal / 2, result);
}

int main(){
    std::string binary = findbinary(233,"");

    return 0;
}



