#include "Playlist.h"
#include <iostream>
#include <string>

// Constructor for PlaylistNode class with default values
PlaylistNode::PlaylistNode() {
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}

// Constructor for PlaylistNode class with specified values
PlaylistNode::PlaylistNode(string newUniqueID, string newSongName, string newArtistName, int newSongLength) {
    uniqueID = newUniqueID;
    songName = newSongName;
    artistName = newArtistName;
    songLength = newSongLength;
    nextNodePtr = 0;
}

// Function to insert a node after a given node
void PlaylistNode::InsertAfter(PlaylistNode* data) {
    // Temporarily store the pointer to the next node
    PlaylistNode* temp = 0;
    temp = nextNodePtr;
    // Set the next node pointer of the current node to the new node
    nextNodePtr = data;
    // Set the next node pointer of the new node to the previously next node
    data->SetNext(temp);
    
    return;
}

// Function to set the next node pointer
void PlaylistNode::SetNext(PlaylistNode* next) {
    nextNodePtr = next;
    
    return;
}

// Function to get the unique ID of the current node
string PlaylistNode::GetID() const {
    return uniqueID;
}

// Function to get the song name of the current node
string PlaylistNode::GetSongName() const {
    return songName;
}

// Function to get the artist name of the current node
string PlaylistNode::GetArtistName() const {
    return artistName;
}

// Function to get the song length of the current node
int PlaylistNode::GetSongLength() const {
    return songLength;
}

// Function to get the pointer to the next node
PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

// Function to print the details of the current node
void PlaylistNode::PrintPlaylistNode(PlaylistNode *nextData) const {
    cout << "Unique ID: " << nextData->GetID() << endl;
    cout << "Song Name: " << nextData->GetSongName() << endl;
    cout << "Artist Name: " << nextData->GetArtistName() << endl;
    cout << "Song Length (in seconds): " << nextData->GetSongLength() << endl << endl;
    
    return;
}