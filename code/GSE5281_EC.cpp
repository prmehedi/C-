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

    ifstream file("GSE5281-EC-normalised.csv", ios::in);
    ofstream fout("GSE5281_input.csv", ios::out);

    if(file.is_open()){

        content.clear();

        while(getline(file,line)){
            row.clear();
            stringstream str(line);

            while(getline(str,word,',')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }

    for(int i=0; i<content.size();i++){
        fout<<content[i][24];
        for(int j=1; j<content[i].size()-1; j++){
            fout<<','<<content[i][j];
        }
        fout<<endl;
    }

    file.close();
    fout.close();

}

void sort(){
    vector<string>row;
    string line;

    ifstream file("GSE5281_input.csv", ios::in);
    ofstream fout("GSE5281-EC_sort.csv", ios::out);
    ofstream pout("GSE5281-EC-avg.csv", ios::out);

    if(file.is_open()){
        getline(file,line);
        pout<<line<<endl;
        pout.close();

        while(getline(file,line)){
            row.push_back(line);
        }
    }
    else{
        cout<<"could not sort the file"<<endl;
    }

    sort(row.begin(),row.end());

    for(int i=0; i<row.size(); i++){
        fout<<row[i]<<endl;
    }

    file.close();
    fout.close();
}

void avg(){
    vector<vector<string>> content;
    vector<string> row;
    string line, word;

    ifstream file("GSE5281-EC_sort.csv", ios::in);
    ofstream fout("GSE5281-EC-avg.csv", ios::app);

    if(file.is_open()){
        content.clear();

        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,',')){
                row.push_back(word);
            }
            content.push_back(row);
        }
    }else{
        cout<<"average find could not processed"<<endl;
    }

    vector<bool> visited(content.size(),false);
    for( int i=0; i<content.size(); i++){
        if(visited[i]==true)
        continue;

        int count=1;

        for( int k=i+1; k<content.size(); k++){
            if(content[i][0]==content[k][0]){
                visited[k] = true;
                count++;
            }
        }

        fout<<content[i][0];
        for( int j=1; j<24; j++){

            double sum=0;
            for(int k=0; k<count; k++){
                sum += stod(content[i+k][j]);
            }
            double avg = sum/count;
            fout<<','<<avg;
        }
        fout<<endl;
    }
}

int main(){

    read();
    cout<<"file read sucessfully"<<endl;

    sort();
    cout<<"file sorted sucessfully"<<endl;

    avg();
    cout<<"program executed sucessfully"<<endl;
    

    return 0;
}