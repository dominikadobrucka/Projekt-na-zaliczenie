#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <iostream>

class GameAudio {
private:
    sf::Music backgroundMusic;
    sf::SoundBuffer collectBuffer;
    sf::Sound collectSound;

    sf::SoundBuffer winBuffer;
    sf::Sound winSound;
    sf::SoundBuffer loseBuffer;
    sf::Sound loseSound;

public:
    GameAudio() {
        if (!backgroundMusic.openFromFile("soundtrack_dzwiek.mp3")) {
            std::cout << "Blad ladowania muzyki soundtrack_dzwiek.mp3! Upewnij sie, ze plik jest w folderze build." << std::endl;
        } else {
            backgroundMusic.setLoop(true);  
            backgroundMusic.setVolume(30);  
        }

        if (!collectBuffer.loadFromFile("podnoszenie_dzwiek.mp3")) {
            std::cout << "Blad ladowania dzwieku podnoszenie_dzwiek.mp3! Upewnij sie, ze plik jest w folderze build." << std::endl;
        } else {
            collectSound.setBuffer(collectBuffer);
            collectSound.setVolume(60);     
        }

        if (!winBuffer.loadFromFile("wygrana.mp3")) {
            std::cout << "Blad ladowania dzwieku wygrana.mp3! Upewnij sie, ze plik jest w folderze build." << std::endl;
        } else {
            winSound.setBuffer(winBuffer);
            winSound.setVolume(100);     
        }

        if (!loseBuffer.loadFromFile("przegrana.mp3")) {
            std::cout << "Blad ladowania dzwieku przegrana.mp3! Upewnij sie, ze plik jest w folderze build." << std::endl;
        } else {
            loseSound.setBuffer(loseBuffer);
            loseSound.setVolume(100);     
        }
    }

    void playMusic() {
        if (backgroundMusic.getStatus() != sf::Music::Playing) {
            backgroundMusic.play();
        }
    }

    void playCollect() {
        collectSound.play();
    }

    void playWin() {
        winSound.play();
    }

    void playLose() {
        loseSound.play();
    }
};

#endif