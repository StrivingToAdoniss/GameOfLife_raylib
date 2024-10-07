//MusicManager.cpp
#include "MusicManager.hpp"

MusicManager::MusicManager(const std::vector<std::string>& musicFilePaths, float initialVolume)
    : volume(initialVolume), muted(false), currentTrackIndex(0) {
    InitAudioDevice();

    // Load all music tracks from file paths
    for (const auto& filePath : musicFilePaths) {
        Music music = LoadMusicStream(filePath.c_str());
        music.looping = true; // Set looping for each track
        musicTracks.push_back(music);
    }

    setVolume(volume);
    playTrack(currentTrackIndex); // Start playing the first track
}

MusicManager::~MusicManager() {
    unloadAllTracks();
    CloseAudioDevice();
}

void MusicManager::unloadAllTracks() {
    for (auto& track : musicTracks) {
        UnloadMusicStream(track);
    }
}

void MusicManager::play() {
    PlayMusicStream(musicTracks[currentTrackIndex]);
}

void MusicManager::update() {
    UpdateMusicStream(musicTracks[currentTrackIndex]);
}

void MusicManager::mute() {
    if (!muted) {
        muted = true;
        SetMusicVolume(musicTracks[currentTrackIndex], 0.0f); // Mute music
    }
}

void MusicManager::unmute() {
    if (muted) {
        muted = false;
        SetMusicVolume(musicTracks[currentTrackIndex], volume); // Restore volume
    }
}

void MusicManager::toggleMute() {
    if (muted) {
        unmute();
    } else {
        mute();
    }
}

void MusicManager::setVolume(float newVolume) {
    volume = newVolume;
    // Only change the actual music volume if not muted
    if (!muted) {
        SetMusicVolume(musicTracks[currentTrackIndex], volume);
    }
}

void MusicManager::nextTrack() {
    // Stop current track
    StopMusicStream(musicTracks[currentTrackIndex]);

    // Move to the next track, loop back if at the end
    currentTrackIndex = (currentTrackIndex + 1) % musicTracks.size();
    playTrack(currentTrackIndex);
}

void MusicManager::previousTrack() {
    // Stop current track
    StopMusicStream(musicTracks[currentTrackIndex]);

    // Move to the previous track, loop to last if at the start
    currentTrackIndex = (currentTrackIndex - 1 + musicTracks.size()) % musicTracks.size();
    playTrack(currentTrackIndex);
}

void MusicManager::playTrack(int index) {
    if (index >= 0 && index < musicTracks.size()) {
        currentTrackIndex = index;
        PlayMusicStream(musicTracks[currentTrackIndex]);
        setVolume(volume); // Apply volume to the new track
    }
}
