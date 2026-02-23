# RetroPlayer - C++ Audio Player with SFML 🎵

I have designed an audio player in **C++** with the help of **SFML** (Simple and Fast Multimedia Library) – a cross-platform library that provides a simple, object-oriented API for building 2D games and multimedia applications. I primarily used the audio player features of the library.

The pausing, resuming and stopping of the audio is controlled through **keyboard input** by taking indicated commands from the user.

## ✨ Features

| # | Feature | Description |
|---|---------|-------------|
| 1 | **Add a new Track** | Insert at any desired position (beginning, middle, or end) |
| 2 | **Remove a Track** | Delete a track by ID or title |
| 3 | **Display all Tracks** | View complete tracklist with details |
| 4 | **Navigate between tracks** | Move forward and backward through the playlist |

## 🧱 Data Structure: Doubly Linked List

I implemented a **Doubly Linked List** because it provides:
- ✅ Two-way traversal (forward and backward navigation)
- ✅ Easy insertion/deletion at any position
- ✅ Dynamic memory allocation (no fixed size limitations)

## 💿 Main ADT: RetroPlayer

The `RetroPlayer` class holds all track data with the following attributes:

```cpp
class RetroPlayer{
    int id;                 // unique identifier
    string title;           // song title
    string artist;          // artist name
    int duration;           // length in seconds
    string path;            // file path to audio
};# RetroPlayer - C++ Audio Player with SFML 🎵
