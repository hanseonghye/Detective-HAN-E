#include <iostream>
#include <string>
#include <cstring>
#include <deque>
#include <set>

using namespace std;

class fun{
 public:
    string fun_name;
    deque<string> fun_list;
    set<string> call_fun_list;
};


deque<fun> all;
deque<string> last_q;


string return_fun_name(string str){
    string re_str=str.substr(1,str.size()-2);
    return re_str;
}

string change_call_fun_name(string str){
    string re_str=str.substr(1);
    int  is_not_fun=0;

    for(int i=0;i<all.size();++i){
        if(re_str==all[i].fun_name) {is_not_fun=1; break;}
    }

    if(is_not_fun==0){return "#"+re_str;}

    return str;
}

string is_recursive(string big_name, string s_name){
    string s=s_name.substr(1);
    if(big_name==s) return "#RE1";
    return s_name;
}


void call_function(string str){
    string fun_name=str.substr(1);
    for(int j=0;j<all.size();++j){
        if(all[j].fun_name==fun_name){
            for(int k=0;k<all[j].fun_list.size();++k){
                string ss=all[j].fun_list[k];
                if(ss[0]=='@') {
		    set<string>::iterator set_it=all[j].call_fun_list.find(ss);
		    if( set_it==all[j].call_fun_list.end() ){ all[j].call_fun_list.insert(ss); call_function(ss); }
		    else { last_q.push_back("#RE2"); }
		}
                else { last_q.push_back(ss); }
            }
            break;
        }
    }
}


int main(int argc, char* argv[])
{

    string fin_str;

    int main_point=-1;

                                                        /* 함수 별로 큐에 넣기 ! */
    while(1){
        cin>>fin_str;

        if(fin_str[0]=='$'){
                fun temp;
                temp.fun_name=return_fun_name(fin_str);

                while(1){
                    cin>>fin_str;
                    if(fin_str=="}") break;
	 	    if(fin_str[0]!='#'&&fin_str[0]!='@'){ cout<<"#NOTHING"; return 0;}
                    temp.fun_list.push_back(fin_str);
                }
                all.push_back(temp);
        }
        else break;
    }

    if(all.size()==0){ cout<<"#NOTHING"; return 0; }
                                                    // 저장된 함수 제외 함수 key로 변경
    for(int i=0;i<all.size();++i){
        if(all[i].fun_name=="main") main_point=i;
        for(int j=0;j<all[i].fun_list.size();++j){
            string call_fun_name=all[i].fun_list[j];
            if(call_fun_name[0]=='@') { all[i].fun_list[j]=change_call_fun_name(all[i].fun_list[j]); }
            if(call_fun_name[0]=='@') { all[i].fun_list[j]=is_recursive(all[i].fun_name, all[i].fun_list[j]); }
        }
    }

    if(main_point==-1){ cout<<"#0"; return 0 ;}

    for(int i=0;i<all[main_point].fun_list.size();++i){
        string last_s=all[main_point].fun_list[i];
        if(last_s[0]=='@'){call_function(last_s);}
        else {last_q.push_back(last_s);}
    }
	
    for(int i=0;i<last_q.size();++i)
	cout<<last_q[i];

    all.clear();
    last_q.clear();

    return 0;
}


