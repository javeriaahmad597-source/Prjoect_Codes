#ifndef RETROPLAYER_H
#define RETROPLAYER_H

#include <iostream>
using namespace std;

class RetroPlayer {
    int TrackID;
    string title;
    string artist;
    float duration;  
    string audioFilePath;  
    
public:
    RetroPlayer(int id, string t, string art, float dur, string audioPath) 
        : TrackID(id), title(t), artist(art), duration(dur), audioFilePath(audioPath) {}

    string getTitle() const { return title; }
    int getTrackID() const { return TrackID; }
    string getArtist() const { return artist; }
    float getDuration() const { return duration; }
    string getAudioPath() const { return audioFilePath; }
    
    void setAudioPath(string path) { audioFilePath = path; }

    friend ostream& operator<<(ostream& out, const RetroPlayer& rp) {
        out << "Track ID:  " << rp.TrackID << endl;
        out << "Title:     " << rp.title << endl;
        out << "Artist:    " << rp.artist << endl;
        out << "Duration:  " << rp.duration << " seconds" << endl;
        return out;
    }
};

#endif