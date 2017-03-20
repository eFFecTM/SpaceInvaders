#include "Player.h"

int* Player::getScore()
{
    return &score;
}

void Player::setScore(int score)
{
    this->score = score;
}

int* Player::getLives()
{
    return &lives;
}

void Player::setLives(int lives)
{
    this->lives = lives;
}
