#include <iostream>
#include "DLL.h"
#include <limits>
#include <SFML/Audio.hpp>
using namespace std;

class Playlist {
    DLL track;
    bool isPlaying;
    sf::Music currentMusic;
    
public:
    Playlist() : isPlaying(false) {}

    void AddTrack(int id, string title, string artist, float duration, string path, int pos = 1) {
        RetroPlayer rp(id, title, artist, duration, path);

        if (pos == 1) {
            track.IAS(rp);
        }
        else if (pos == -1) {
            track.IAE(rp);
        }
        else {
            track.IAAP(rp, pos);
        }
        cout << "Track added successfully! " << endl;
    }

    void deleteTrack(int id) {
        int pos = track.getPosition(id);
        if (pos != -1) {
            track.DAAP(pos);
            if (isPlaying) {
                currentMusic.stop();
                isPlaying = false;
            }
        }
        else{
            cout << "Invalid track ID!" << endl;
        }
    }

    void Search(string t){
        bool result = track.search(t);
        if(result){
            track.display(t);
        }
        else{
            cout << "Track not found! " << endl;
        }
    }

    void displayTracks(){
        if(!track.isEmpty()){
            cout<< "------Playlist------" << endl;
            track.displayFwd();
        }
        else{
            cout<< "Playlist is empty!" << endl;
        }
    }

    void Play() {
    if (track.getLength() == 0) {
        cout << "Playlist is empty! Add tracks first." << endl;
        return;
    }
    
    cout << "=== Now Playing ===" << endl;
    track.displayCurrent();

    RetroPlayer currentTrack = track.getCurrent();
    string audioFile = currentTrack.getAudioPath(); 
    
    if (!currentMusic.openFromFile(audioFile)) {
        cout << "Error: Could not load audio file!" << endl;
        return;
    }
    
    currentMusic.play();
    isPlaying = true;
    
    char choice;
    cin.ignore();
    while (isPlaying) {
        cout << "Enter command (s=stop, p=pause, r=resume): ";
        cin >> choice;
        choice = tolower(choice);
        
        if (choice == 's') {
            currentMusic.stop();
            isPlaying = false;
            cout << "Stopped. Returning to main menu..." << endl;
            break;  // Exit to main menu
        }
        else if (choice == 'p') {
            if (currentMusic.getStatus() == sf::SoundSource::Status::Playing) {
                currentMusic.pause();
                cout << "Paused." << endl;
            }
        }
        else if (choice == 'r') {
            if (currentMusic.getStatus() == sf::SoundSource::Status::Paused) {
                currentMusic.play();
                cout << "Resumed." << endl;
            }
        }
        else {
            cout << "Invalid command! Use s, p, or r." << endl;
        }
    }
}

    void StopPlayback() {
        if (isPlaying) {
            currentMusic.stop();
            isPlaying = false;
        }
    }

    void NextTrack(){
        if (track.getLength() == 0) {
            cout << "Playlist is empty!" << endl;
            return;
        }
        else{
            track.MoveForward();
            Play();
        }
    }

    void PreviousTrack(){
        if (track.getLength() == 0) {
            cout << "Playlist is empty!" << endl;
            return;
        }
        else{
            track.MoveBackward();
            Play();
        }
    }

    void Metrics(){
        cout<< "This Playlist has " << track.getLength() << " songs in total." << endl;
    }

    ~Playlist() {}
};

int main(){
    Playlist pl;
    pl.AddTrack(1, "test", "anonymous", 50, "C:/Users/LENOVO/Downloads/song.mp3");
    pl.AddTrack(2, "Wildflower", "Bilie Eilish", 261, "C:/Users/LENOVO/Downloads/AudioTracks/WILDFLOWER.mp3");
    pl.AddTrack(3, "Haseen", "Talwinder", 174, "C:/Users/LENOVO/Downloads/AudioTracks/HASEEN.mp3", 3);
    pl.AddTrack(4, "9:45", "Jay", 122, "C:/Users/LENOVO/Downloads/AudioTracks/9-45.mp3");
    pl.AddTrack(5, "Safar", "Bayaan", 230, "C:/Users/LENOVO/Downloads/AudioTracks/Safar.mp3", 4);
    pl.AddTrack(6, "Scars to your beutiful", "Alessia",230 , "C:/Users/LENOVO/Downloads/AudioTracks/Scars To Your Beautiful.mp3");
    pl.AddTrack(7, "Kashish", "Omkar", 205, "C:/Users/LENOVO/Downloads/AudioTracks/Kashish.mp3");
    pl.AddTrack(8, "Maand", "Hassan Raheem", 205, "C:/Users/LENOVO/Downloads/AudioTracks/Maand.mp3", 2);
    pl.AddTrack(9, "Na Milay", "Havi", 293, "C:/Users/LENOVO/Downloads/AudioTracks/Na Milay.mp3");
    int choice = 0;
    cout<< "------ Welcome to Audio Player! -------"<< endl;
    cout<< "Select on of the following (-1 to exit): "<< endl;
    cout<< "1. Add new track" << endl;
    cout<< "2. Remove a track" << endl;
    cout<< "3. Search a track" << endl;
    cout<< "4. Display Playlist" << endl;
    cout<< "5. Get track count" << endl;
    cout<< "6. Play next track" << endl;
    cout<< "7. Play previous track" << endl;
    cout<< "8. Play current track" << endl;

    while(choice != -1){
        cout<< "Enter your choice: "; cin>> choice;

        int id; string t, art, path; float d;
        if(choice == 1){
            int pos = 1;
            cout<< "Enter the following values credentials: "<< endl;
            cout<< "ID: "; cin>> id;
            cout<< "Title: "; cin>> t;
            cout<< "Artist: "; cin>> art;
            cout<< "Duration(s): "; cin>> d;
            cout<< "Path: "; cin>> path;
            cout<< "Position: ";cin>> pos;
            pl.AddTrack(id, t, art, d, path, pos);
        }
        else if(choice == 2){
            cout<< "Enter track ID: "; cin >> id;
            pl.deleteTrack(id);
        }
        else if(choice == 3){
            cout<< "Enter title: "; cin>> t;
            pl.Search(t);
        }
        else if(choice == 4){
            pl.displayTracks();
        }
        else if(choice == 5){
            pl.Metrics();
        }
        else if(choice == 6){
            pl.NextTrack();
        }
        else if(choice == 7){
            pl.PreviousTrack();
        }
        else if(choice == 8){
            pl.Play();
        }
    }

    cout<< "------ Thank you for using Audio Player ------"<< endl;
    return 0;
}