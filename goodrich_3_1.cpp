#include <string>
#include <iostream>
#include <exception>

using namespace std;

class GameEntry {
    public:
        GameEntry(const string& n="", int s = 0);
        string getName() const;
        int getScore() const;

    private:
        string name;
        int score;
};

GameEntry::GameEntry(const string& n, int s) : name(n), score(s) {}
int GameEntry::getScore() const {
    return score;
}
string GameEntry::getName() const {
    return name;
}


class Scores {
    public:
        Scores(int maxEnt = 10);
        ~Scores();
        void add(const GameEntry& e);
        GameEntry remove(int i);
        void printScores();
        int numEnt();

    private:
        int maxEntries;
        int numEntries;
        GameEntry* entries;
};

Scores::Scores(int maxEnt) {
           maxEntries = maxEnt;
           entries = new GameEntry[maxEntries];
           numEntries = 0;
       }

Scores::~Scores() {
    delete[] entries;
}

void Scores::add(const GameEntry& e) {
    int newScore = e.getScore();
    if(numEntries == maxEntries) {
        if(newScore <= entries[maxEntries - 1].getScore()) return;
    }
    else numEntries++;

    int i = numEntries - 2;
    while (i >= 0 && newScore > entries[i].getScore()) {
        entries[i+1] = entries[i];
        i--;
    }
    entries[i+1] = e;
}

GameEntry Scores::remove(int i) {
    try {
        if ((i < 0) || (i >= numEntries)) 
            throw "Invalid index";
    }
    catch (const char* e) {
        cout << " IndexOutOfBound" << endl;
    }
    GameEntry e = entries[i];
    for(int j = i + 1; j < numEntries; ++j) {
        entries[j - 1] = entries[j];
    }
    numEntries--;
    return e;
}

void Scores::printScores() {
    cout << "Top Player's List" << endl;
    for(int i = 0; i < numEntries; ++i) {
        cout << "Name: " << entries[i].getName() << "\t\t\tscore: "<< entries[i].getScore() << endl;
    }
    return;
}

int Scores::numEnt() {
    return numEntries;
}

void insertionSort(char *A,int n){
  for(int i=1; i< n;i++){
    char cur=A[i];
    int j= i-1;
    while( j>=0 && (A[j]>cur)){
        A[j+1]=A[j];
        j--;
    }
    A[j+1]=cur;
  }

}
int main(void){

    GameEntry bhav("Bhavana", 10000);
    GameEntry afrid("Afrid", 1000);
    GameEntry mohit("mohith", 100);

    Scores BAM;
    BAM.add(bhav);
    BAM.add(afrid);

    cout<<BAM.numEnt()<<endl;

    //char arr[]={5,4,3,2,1};
    //insertionSort(arr,5);
    //for(int i=0;i<5;i++)
    // printf("%d ",arr[i]);
     //cout<<arr[i]<<endl;
    return 0;

}