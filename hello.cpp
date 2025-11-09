#include<iostream>
#include<string>
using namespace std;
void bonjour(){
    cout<<"输入您的名字";
    string name;
    cin>>name;
    cout<<"bonjour "<<name<<'\n';
}

int main(){
    bonjour();
    return 0;
}