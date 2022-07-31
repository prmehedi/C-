#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>


using namespace std;

void read(){
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    ifstream file("GSE3790_CB.txt", ios::in);
    ofstream fout("GSE3790_CB_input.txt", ios::out);

    if(file.is_open()){

        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,'\t')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }else{
        cout<<"File could not open"<<endl;
    }

    cout<<content[0].size()<<endl;
    int n = content[0].size()-1;
    cout<<content[0][68]<<"\t"<<content[0][68].length()<<endl;
    cout<<content[22242][67]<<"\t"<<content[22242][67].length()<<endl;
    cout<<content[22242][68]<<"\t"<<content[22242][68].length()<<endl;


    for( int i=0; i<content.size(); i++){
     //   fout<<content[i][n-1];
        if(content[i][n].length()!=0 && content[i][n-1].length()!=0){
            fout<<content[i][n];
            for(int j=1; j<content[i].size()-2; j++){
                fout<<"\t"<<content[i][j];
            }
            fout<<endl;
        }
        
    }
    file.close();
    fout.close();
}

void sort(){
    vector<string> row;
    string line;

    ifstream file("GSE3790_CB_input.txt", ios::in);
    ofstream fout("GSE3790_CB_sort.txt", ios::out);
    ofstream pout("GSE3790_CB_avg.txt", ios::out);

    if(file.is_open()){

            getline(file,line);
            pout<<line<<endl;
            pout.close();

            row.clear();
        while(getline(file,line)){
            row.push_back(line);
        }
    }else{
        cout<<"File could not sorted"<<endl;
    }

    sort(row.begin(),row.end());

    for(int i=0; i<row.size(); i++ ){
        fout<<row[i]<<endl;
    }
    file.close();
    fout.close();
}

void avg(){
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    ifstream file("GSE3790_CB_sort.txt", ios::in);
    ofstream fout("GSE3790_CB_avg.txt", ios::app);

    if(file.is_open()){

        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,'\t')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }else{
        cout<<"File could not open"<<endl;
    }
    int n = content[0].size();
    vector<bool> visited(content.size(),false);
    for(int i=0; i<content.size(); i++){
        if(visited[i]==true){
            continue;
        }

        int count=1;

        for(int k=i+1; k<content.size(); k++){
            if(content[i][0]==content[k][0]){
                visited[k]=true;
                count++;
            }
        }

        fout<<content[i][0];
        for( int j =1; j<n; j++){
            double sum=0;
            for( int k=0; k<count; k++){
                sum += stod(content[i][j]);
            }
            double avg = sum/count;
            fout<<"\t"<<avg;
        }
        fout<<endl;

    }
    file.close();
    fout.close();
    cout<<"Average find sucessfully all genes"<<endl;
}



int main(){
    
    read();
    cout<<"File read sucessfully"<<endl;

    sort();
    cout<<"File sorted sucessfully"<<endl;

    avg();

    return 0;
}