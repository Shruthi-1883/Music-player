#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Class representing a Song
class Song {
public:
    string title;
    string filePath;

    Song(string t, string fp) : title(t), filePath(fp) {}
};

// Music Player Class
class MusicPlayer {
private:
    vector<Song> playlist;
    int currentSongIndex;
    sf::Music music;
    float volume;

public:
    MusicPlayer() : currentSongIndex(-1), volume(100.0f) {}

    // Add a song to the playlist
    void addSong(const string& title, const string& filePath) {
        playlist.emplace_back(title, filePath);
        cout << "Added: " << title << "\n";
    }

    // Display the playlist
    void displayPlaylist() const {
        if (playlist.empty()) {
            cout << "Playlist is empty.\n";
            return;
        }
        cout << "\n--- Playlist ---\n";
        for (size_t i = 0; i < playlist.size(); ++i) {
            cout << i + 1 << ". " << playlist[i].title << "\n";
        }
    }

    // Play a song by index
    void play(int index) {
        if (index < 0 || index >= static_cast<int>(playlist.size())) {
            cout << "Invalid song index!\n";
            return;
        }

        if (currentSongIndex != index) {
            if (!music.openFromFile(playlist[index].filePath)) {
                cout << "Error: Could not load " << playlist[index].title << "\n";
                return;
            }
            music.setVolume(volume);
            music.play();
            currentSongIndex = index;
            cout << "Now Playing: " << playlist[index].title << "\n";
        } else {
            if (music.getStatus() != sf::Music::Playing) {
                music.play();
                cout << "Resumed: " << playlist[index].title << "\n";
            } else {
                cout << "Song is already playing.\n";
            }
        }
    }

    // Pause the current song
    void pause() {
        if (music.getStatus() == sf::Music::Playing) {
            music.pause();
            cout << "Music paused.\n";
        } else {
            cout << "No music is playing.\n";
        }
    }

    // Stop the current song
    void stop() {
        if (music.getStatus() != sf::Music::Stopped) {
            music.stop();
            cout << "Music stopped.\n";
        } else {
            cout << "No music is playing.\n";
        }
    }

    // Play the next song in the playlist
    void next() {
        if (playlist.empty()) {
            cout << "Playlist is empty.\n";
            return;
        }
        int nextIndex = (currentSongIndex + 1) % playlist.size();
        play(nextIndex);
    }

    // Play the previous song in the playlist
    void previous() {
        if (playlist.empty()) {
            cout << "Playlist is empty.\n";
            return;
        }
        int prevIndex = (currentSongIndex - 1 + playlist.size()) % playlist.size();
        play(prevIndex);
    }

    // Adjust the volume
    void setVolume(float vol) {
        if (vol < 0.0f) vol = 0.0f;
        if (vol > 100.0f) vol = 100.0f;
        volume = vol;
        music.setVolume(volume);
        cout << "Volume set to " << volume << "%\n";
    }

    // Get current volume
    float getVolume() const {
        return volume;
    }

    // Check if music is playing
    bool isPlaying() const {
        return music.getStatus() == sf::Music::Playing;
    }
};

// Function to display the main menu
void displayMenu() {
    cout << "\n--- Music Player Menu ---\n";
    cout << "1. Add Song to Playlist\n";
    cout << "2. Display Playlist\n";
    cout << "3. Play Song\n";
    cout << "4. Pause\n";
    cout << "5. Stop\n";
    cout << "6. Next Song\n";
    cout << "7. Previous Song\n";
    cout << "8. Set Volume\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

// Function to get user input safely
int getInput() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number: ";
    }
    return choice;
}

int main() {
    MusicPlayer player;
    int choice;

    cout << "=== Welcome to the C++ Music Player ===\n";

    do {
        displayMenu();
        choice = getInput();

        switch (choice) {
        case 1: {
            string title, filePath;
            cout << "Enter song title: ";
            cin.ignore(); // Clear newline character from input buffer
            getline(cin, title);
            cout << "Enter file path (e.g., C:\\Music\\song.ogg): ";
            getline(cin, filePath);
            player.addSong(title, filePath);
            break;
        }
        case 2:
            player.displayPlaylist();
            break;
        case 3: {
            player.displayPlaylist();
            if (player.isPlaying()) {
                cout << "A song is already playing. Stop it before playing another song.\n";
                break;
            }
            if (player.isPlaying()) {
                cout << "A song is already playing.\n";
                break;
            }
            cout << "Enter the song number to play: ";
            int songNumber;
            songNumber = getInput();
            player.play(songNumber - 1);
            break;
        }
        case 4:
            player.pause();
            break;
        case 5:
            player.stop();
            break;
        case 6:
            player.next();
            break;
        case 7:
            player.previous();
            break;
        case 8: {
            float vol;
            cout << "Enter volume (0 to 100): ";
            while (!(cin >> vol) || vol < 0.0f || vol > 100.0f) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid volume! Enter a value between 0 and 100: ";
            }
            player.setVolume(vol);
            break;
        }
        case 9:
            cout << "Exiting Music Player. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
