//MusicManager.hpp
#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class MusicManager {
public:
    MusicManager(const std::vector<std::string>& musicFilePaths, float initialVolume = 0.5f);
    ~MusicManager();

    void play();
    void update();
    void mute();
    void unmute();
    void toggleMute();
    void setVolume(float volume);
    void nextTrack();
    void previousTrack();
    void playTrack(int index);
    bool isMuted() const { return muted; }
    int getCurrentTrackIndex() const { return currentTrackIndex; }

private:
    std::vector<Music> musicTracks;
    float volume;
    bool muted;
    int currentTrackIndex;

    void unloadAllTracks();
};
