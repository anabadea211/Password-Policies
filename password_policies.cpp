#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <string>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
class Policy{
protected:
    bool isChecked;
public:
    virtual void check(const string& parola)=0;
    bool getCheck()const{
        return isChecked;
    }

};
class LengthPolicy:public Policy{
private:
    uint16_t minLength, maxLength;
public:
    LengthPolicy(uint16_t min){
        minLength=min;
        maxLength=255;
    }
    LengthPolicy(uint16_t min, uint16_t max){
        minLength=min;
        maxLength=max;
    }
    void check(const string &parola){
        if(minLength<=parola.size() && parola.size()<=maxLength){
            isChecked=true;
        }
        else isChecked=false;
    }
};
class ClassPolicy:public Policy{
private:
    uint16_t minClassCount;
public:
    ClassPolicy(uint16_t MminClassCount){
        minClassCount=MminClassCount;
    }
    // void check(const string &parola){
    //     int l=0, L=0, c=0, alt=0, cdif ;
    //     for(int i=0;i<parola.size(); i++){
    //         if (int(parola[i])>=97 && int(parola[i])<=122 && l!=1){
    //             l++;
    //         }
    //         if (int(parola[i])>=65 && int(parola[i])<=90 && L!=1){
    //             L++;
    //         }
    //         if (int(parola[i])>=48 && int(parola[i])<=57 && c!=1){
    //             c++;
    //         }
    //         if (int(parola[i])>=33 && int(parola[i])<=47 && alt!=1){
    //             alt++;
    //         }
    //         cdif=l+L+c+alt;
    //     }
    //     if(cdif>minClassCount)isChecked=true;
    //     else isChecked=false;
    // }
    void check(const string & parola){
        int c=0,m=0,M=0,alt=0;
        char x[256];
        int k=0;
        strcpy(x,parola.c_str());
        for(int i=0;i< strlen(x);i++){
            if(isalpha(x[i])){
                if(isupper(x[i])){
                    M++;
                }
                else m++;
            }
            if(isdigit(x[i])){
                c++;
            }
            if(!isalnum(x[i])){
                alt++;
            }
        }

        if(M!=0) k++;
        if(m!=0) k++;
        if(c!=0) k++;
        if(alt!=0) k++;
        if(k>=minClassCount)
            isChecked=true;
        else isChecked=false;
    }
};
class IncludePolicy:public Policy{
private:
    char characterType;
public:
    IncludePolicy(char caracter){
        characterType=caracter;
    }
    void check(const string &parola){
        if(characterType=='a'){
            for(int i=0; i<parola.size(); i++){
                if(int(parola[i])>=97 && int(parola[i])<=122){
                    isChecked=true;
                    return;
                }
            }
        }
        if(characterType=='A'){
            for(int i=0; i<parola.size(); i++){
                if(int(parola[i])>=65 && int(parola[i])<=90){
                    isChecked=true;
                    return;
                }
            }
        }
        if(characterType=='0'){
            for(int i=0; i<parola.size(); i++){
                if(parola[i]>=48 && parola[i]<=57){
                    isChecked=true;
                    return;
                }
            }
        }
        if(characterType=='$'){
            for(int i=0; i<parola.size(); i++){
                if(int(parola[i])>=33 && int(parola[i])<=47){
                    isChecked=true;
                    return;
                }
            }
        }
        isChecked=false;
    }
};
class NotIncludePolicy:public Policy{
private:
    char characterType;
public:
    NotIncludePolicy(char caracter){
        characterType=caracter;
    }
    void check(const string &parola){
        if(characterType=='a'){
            for(int i=0; i<parola.size(); i++){
                if(parola[i]>=97 && parola[i]<=122){
                    isChecked=false;
                    return;
                }

            }
        }
        if(characterType=='A'){
            for(int i=0; i<parola.size(); i++){
                if(parola[i]>=65 && parola[i]<=90){
                    isChecked=false;
                    return;
                }

            }
        }
        if(characterType=='0'){
            for(int i=0; i<parola.size(); i++){
                if(parola[i]>=48 && parola[i]<=57){
                    isChecked=false;
                    return;
                }
            }
        }
        if(characterType=='$'){
            for(int i=0; i<parola.size(); i++){
                if(!isalnum(parola[i])){
                    isChecked=false;
                    return;
                }

            }
        }
        isChecked=true;

    }
};
class RepetitionPolicy:public Policy{
private:
    uint16_t maxCount;
public:
    RepetitionPolicy(uint16_t nr_max){
        maxCount=nr_max;
    }
    void check(const string &parola){
        char s[256];
        int max=0;
        strcpy(s,parola.c_str());
        int k=1;
        for(int i=0; i<strlen(s)-1; i++){
            if(s[i]==s[i+1]) {
                k++;
                if(max<k) max=k;
            }
            else k=1;
        }
        if(max<=maxCount){
            isChecked=true;
        }
        else isChecked=false;
    }
};
class ConsecutivePolicy:public Policy{
private:
    uint16_t maxCount;
public:
    ConsecutivePolicy(uint16_t nr_max){
        maxCount=nr_max;
    }
    void check(const string &parola){
        char s[256];
        int max=0;
        strcpy(s,parola.c_str());
        int k=1;
        for(int i=0; i<strlen(s); i++){
            if(s[i]==s[i+1]-1) {
                k++;
                if(max<k) max=k;
            }
            else k=1;
        }
        if(max<=maxCount){
            isChecked=true;
        }
        else isChecked=false;
    }
};
string checkPassword(string parola, vector<Policy*> politici) {
    for (int i = 0; i < politici.size(); i++) {
        politici[i]->check(parola);
        if(politici[i]->getCheck()==false){
            // for(Policy*cerinta : politici){
            //     cerinta->check(parola);
            //     if(cerinta->getCheck()==false){
            return "NOK";
        }
    }
    return "OK";
}
int main(){
    int n;
    uint16_t min, max, m;
    string regula, parola;
    char clas, c;
    vector<Policy*>politici;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>regula;
        if(regula=="length"){
            cin>>min;
            if(getchar()==' '){
                cin>>max;
                politici.push_back(new LengthPolicy(min, max));
            }
            else
                politici.push_back(new LengthPolicy(min));
        }
        if(regula=="class"){
            cin>>m;
            politici.push_back(new ClassPolicy(m));
        }
        if(regula=="include"){
            cin>>clas;
            politici.push_back(new IncludePolicy(clas));
        }
        if(regula=="ninclude"){
            cin>>clas;
            politici.push_back(new NotIncludePolicy(clas));
        }
        if(regula=="repetition"){
            cin>>m;
            politici.push_back(new RepetitionPolicy(m));
        }
        if(regula=="consecutive"){
            cin>>m;
            politici.push_back(new ConsecutivePolicy(m));
        }
    }
    while(cin>>parola){
        int ok=0;
        for (int i = 0; i < politici.size(); i++) {
            politici[i]->check(parola);
            if(politici[i]->getCheck()==false){
                ok++;
            }
        }

        if(ok!=0) cout<<"NOK"<<endl;
        else cout<<"OK"<<endl;
    }
    return 0;
}