#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

//Class ygy v
class Profile {
//Data Encapsulation ygy v
//Abstraction Type ygy v

private:
    //Attribute ygy v
    string Username;
    string Savedpass;
    long long int Pass;
    long long int BackupPass;
    ofstream DataWrite;
    ifstream DataRead;

public:
    //Default Constructor ygy v
    Profile() {
        Username = " ";
        Pass = 0;
        BackupPass = 0;
        DataWrite.open("Data.txt", ios::app);
        DataRead.open("Data.txt");
    }

    //Method ygy v
    void SignUp() {
        cout << "New to Musicfy? Create an Account\n" << "Enter Your Username: ";
        //Setter ygy v
        cin >> Username;
        while(1){
            cout << "Enter Your Password (Consist of 7 Digits): ";
            cin >> Pass;
            if(Pass > 999999 && Pass < 10000000) {
                break;
            }
            else {
                cout << "Password must be 7 digits!" << endl;
            }
        }
        

        while (1) {
            cout << "Re-Enter Your Password: ";
            cin >> BackupPass;
            if(Pass == BackupPass) {
                break;
            }
            else if (Pass != BackupPass) {
                cout << "Password doesn't match!" << endl;
            }
        }

        DataWrite << Username << " " << Pass << "\n";
        DataWrite.close();
    
        cout << "Account Created Successfully!" << endl;
    }

    void LogIn() {
        string Contain;
        bool UsernameFound = 0;

        cout << "\nLog In to your Account\n" << "Enter Your Username: ";
        cin >> Username;
        cout << "Enter Your Password: ";
        cin >> Savedpass;

        while (getline(DataRead, Contain)) {
            if (Contain.find(Username) != string::npos) {
                UsernameFound = 1;
                if (Contain.find(Savedpass) != string::npos) {
                    cout << "Log In Successful!" << endl;
                    return;
                } 
                else {
                cout << "Invalid Password!" << endl;
                return LogIn();
                }
            }
        }

        if (!UsernameFound) {
        cout << "\nUsername not found. Would you like to sign up?" << endl;
        SignUp();
        }
    }
    //Getter ygy v
    string GetName(){
        return Username;
    }
};

class Music {
    public:
        string Title;
        string Artist;
        string Genre;
        string Album;
        string Year;
        int Duration;
    
    virtual void displayInfo() {
        cout << "Music Info: " << Title << " by " << Artist << endl;
    }
};

//Inheritance ygy v
class Songs: public Music {
    public:
        //Parameterized Constructor ygy v
        Songs(string judul, string artis, string genre, string album, string tahun, int durasi) {
            Title = judul;
            Artist = artis;
            Genre = genre;
            Album = album;
            Year = tahun;
            Duration = durasi;
        }
        //Overriding ygy v
        void displayInfo() override {
        cout << "Song Info: " << Title << " by " << Artist << " from the album " << Album << " (" << Year << ") "<< endl;
        }   
};

class LaguQueue {
public:
    Songs* UrutanLagu;
    LaguQueue* next;

    LaguQueue(Songs* t){
        UrutanLagu = t;
        next = nullptr;
    }
};

class Queue {
//Access Modifier ygy v
protected:
    LaguQueue* front;
    LaguQueue* rear;

public:
    Queue(){
        front = nullptr;
        rear = nullptr;
    } 

    void AddSong(Songs* UrutanLagu) {
        LaguQueue* newNode = new LaguQueue(UrutanLagu);
        if (rear == nullptr) {
            front = rear = newNode;
        } 
        else {
            rear->next = newNode;
            rear = newNode;
        }
        cout << "Track \"" << UrutanLagu->Title << "\" by " << UrutanLagu->Artist << " has been added to the queue." << endl;
    }

    void SkipSong() {
        if (front == nullptr) {
            cout << "Queue is empty. Cannot Skip." << endl;
            return;
        }

        LaguQueue* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        cout << "Track \"" << temp->UrutanLagu->Title << "\" by " << temp->UrutanLagu->Artist << " skipped" << endl;
        delete temp->UrutanLagu;
        delete temp;
    }

    void display() {
        int urutan = 1;

        if (front == nullptr) {
            cout << "Queue is empty." << endl;
            return;
        }

        LaguQueue* temp = front;
        while (temp != nullptr) {
            cout << urutan << ". Track: " << temp->UrutanLagu->Title << ", Artist: " << temp->UrutanLagu->Artist << ", Genre: " << temp->UrutanLagu->Genre << ", Album: " << temp->UrutanLagu->Album << ", Year: " << temp->UrutanLagu->Year << ", Duration: " << temp->UrutanLagu->Duration << " seconds" << endl;
            urutan++;
            temp = temp->next;
        }
    }
    //Polymorphism ygy v
    void SearchSong(string Search) {
        LaguQueue* temp = front;
        
        while (temp != nullptr) {
            if (temp->UrutanLagu->Title == Search) {
                cout << "Track: " << temp->UrutanLagu->Title << "\nArtist: " << temp->UrutanLagu->Artist << "\nGenre: " << temp->UrutanLagu->Genre << "\nAlbum: " << temp->UrutanLagu->Album << "\nYear: " << temp->UrutanLagu->Year << "\nDuration: " << temp->UrutanLagu->Duration << " seconds" << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Song not found." << endl;
    }

    void SearchSong(int Search) {
        LaguQueue* temp = front;
        int urutan = 1;

        while (temp != nullptr) {

            if (urutan == Search) {
                cout << "\nTrack: " << temp->UrutanLagu->Title << "\nArtist: " << temp->UrutanLagu->Artist << "\nGenre: " << temp->UrutanLagu->Genre << "\nAlbum: " << temp->UrutanLagu->Album << "\nYear: " << temp->UrutanLagu->Year << "\nDuration: " << temp->UrutanLagu->Duration << " seconds" << endl;
                return;
            }

            temp = temp->next;
            urutan++;
        }

        cout << "Song not found." << endl;
    }

    void PlaySong() {
        if (front == nullptr) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Now playing: " << front->UrutanLagu->Title << " by " << front->UrutanLagu->Artist << endl;
    }

    void ChangeInfo(int Choice){
        if (front == nullptr) {
            cout << "Queue is empty." << endl;
            return;
        }
        if (Choice == 1) {
            cout << "Enter New Title: ";
            cin >> front->UrutanLagu->Title;
        }
        else if (Choice == 2) {
            cout << "Enter New Artist: ";
            cin >> front->UrutanLagu->Artist;
        }
        else if (Choice == 3) {
            cout << "Enter New Genre: ";
            cin >> front->UrutanLagu->Genre;
        }
        else if (Choice == 4) {
            cout << "Enter New Album: ";
            cin >> front->UrutanLagu->Album;
        }
        else if (Choice == 5) {
            cout << "Enter New Year: ";
            cin >> front->UrutanLagu->Year;
        }
        else if (Choice == 6) {
            cout << "Enter New Duration: ";
            cin >> front->UrutanLagu->Duration;
        }
        else {
            cout << "Invalid Choice!" << endl;
        }
        cout << "Song Info Updated!" << endl;
    }

    void CurSongInfo() {
        if (front == nullptr) {
            cout << "Queue is empty." << endl;
            return;
        }
        front->UrutanLagu->displayInfo();
    }
};

int main() {
    Profile pf;
    Queue set;
    int Choice, Status = 0;

    cout << "\033[32m" << " __  __   _   _   ____    ___    ____   _____  __   __\n";
    cout << R"(|  \/  | | | | | / ___|  |_ _|  / ___| |  ___| \ \ / /)" << endl;
    cout << R"(| |\/| | | | | | \___ \   | |  | |     | |_     \ V /)" << endl;
    cout << R"(| |  | | | |_| |  ___) |  | |  | |___  |  _|     | |)" << endl;
    cout << R"(|_|  |_|  \___/  |____/  |___|  \____| |_|       |_|)" << "\033[0m" << endl << endl;


    //Login Menu
    while(1){

        cout << "\nWelcome to Musicfy\n" << "1. Sign Up\n" << "2. Log In\n" << "3. Exit\n" << "Choose: ";
        cin >> Choice;

        if (Choice == 1) {
            pf.SignUp();
        }
        else if (Choice == 2){
            pf.LogIn();
            cout << "\nWelcome " << pf.GetName() << "!!!"<< endl;
            Status = 1;
            break;
        }
        else if (Choice == 3) {
            cout << "Thank You for using Musicfy!" << endl;
            return 0;
        }
        else {
            cout << "Invalid Choice!" << endl;
        }
    }

    //Main Menu
    while(1 && Status == 1) {
        cout << "\nMain Menu\n" << "1. Add Song\n" << "2. Show Queue\n" << "3. Play Song\n" << "4. Skip Song\n" << "5. Search Song\n" << "6. Current Song Info\n" << "7. Modify Song\n" <<"8. Exit\n" << "Choose: ";
        cin >> Choice;

        if (Choice == 1) {
            string judul, artis, genre, album, tahun;
            int durasi;

            cout << "\nAdd Song\n";
            cout << "Title: ";
            getline(cin >> ws, judul);
            cout << "Artist: ";
            cin >> artis;
            cout << "Genre: ";
            cin >> genre;
            cout << "Album: ";
            cin >> album;
            cout << "Year: ";
            cin >> tahun;
            cout << "Duration (In Seconds): ";
            cin >> durasi;

            //Object ygy v
            Songs* UrutanLagu = new Songs(judul, artis, genre, album, tahun, durasi);
            set.AddSong(UrutanLagu);
            cout << "Song Added\n";
        }

        else if (Choice == 2) {
            cout << "Current Queue:\n";
            set.display();
        }

        else if (Choice == 3) {  
            set.PlaySong();
        }

        else if (Choice == 4) {
            set.SkipSong();
        }

        else if (Choice == 5) {
            cout << "\nSearch Song\n" << "1. Search by Queue Number\n" << "2. Search by Song Title\n" << "Choose: ";
            cin >> Choice;
            if(Choice == 1) {
                int Search;
                cout << "Enter Queue Number: ";
                cin >> Search;
                set.SearchSong(Search);
            }
            else if(Choice == 2) {
                string Search;
                cout << "Enter Song Title: ";
                getline(cin >> ws, Search);
                set.SearchSong(Search);
            }
            else {
                cout << "Invalid Choice!" << endl;
            }
        }
        else if (Choice == 6) {
            set.CurSongInfo();
        }
        else if (Choice == 7) {
            cout << "\nModify Song\n" << "1. Modify Title\n" << "2. Modify Artist\n" << "3. Modify Genre\n" << "4. Modify Album\n" << "5. Modify Year\n" << "6. Modify Duration\n" << "Choose: ";
            cin >> Choice;
            set.ChangeInfo(Choice);
        }
        else if (Choice == 8) {
            cout << "Thank You for using Musicfy!" << endl;
            break;
        }
        else {
            cout << "Invalid Choice!" << endl;
            break;
        }

    }

    return 0;
}
