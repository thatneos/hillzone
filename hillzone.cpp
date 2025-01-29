#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to simulate playing a note (cross-platform placeholder)
void playTone(int frequency, int duration) {
    cout << "Playing tone: " << frequency << " Hz for " << duration << " ms" << endl;
    this_thread::sleep_for(chrono::milliseconds(duration));
}

// Function to play Green Hill Zone melody
void playGreenHillZoneMelody() {
    vector<pair<int, int>> melody = {
        {784, 300}, {784, 300}, {784, 150}, {659, 150}, {784, 150}, {987, 300},
        {784, 300}, {659, 150}, {698, 150}, {784, 300},
        {523, 300}, {587, 300}, {659, 300}, {784, 300}, {659, 300},
        {523, 150}, {698, 150}, {784, 300},
        {0, 200} // Pause
    };

    for (const auto &note : melody) {
        playTone(note.first, note.second);
    }
}

// Function to display glitch effect
void showGlitchEffect() {
    const string glitchChars = "#@$%&*!0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int rows = 10;
    const int cols = 40;

    srand(time(0)); // Seed random number generator

    for (int frame = 0; frame < 20; ++frame) {
        system("clear"); // Clear the console (use "cls" on Windows)
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                char c = glitchChars[rand() % glitchChars.length()];
                cout << c;
            }
            cout << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    cout << "Playing Green Hill Zone melody while showing glitch effect...\n";

    // Run the glitch effect and melody in parallel
    thread glitchThread(showGlitchEffect);
    thread melodyThread(playGreenHillZoneMelody);

    // Wait for both threads to finish
    glitchThread.join();
    melodyThread.join();

    cout << "Done!\n";
    return 0;
}
