/**
 * @file gameView.h
 * @author Wiktor Wołos (wiktor_wolos@outlook.com)
 * @brief
 * @version 0.1
 * @date 2025-05-20
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <Pasjans/card.h>
#include <Pasjans/consts.h>

#include <iostream>
#include <rang/rang.hpp>
#include <vector>
class GameView {
   public:
    void normalDisplay(std::vector<std::vector<Card>> tableau, std::vector<std::vector<Card>> foundation,
                       std::vector<Card> waste, int wasteIndex);
    void safeDisplay(std::vector<std::vector<Card>> tableau, std::vector<std::vector<Card>> foundation,
                     std::vector<Card> waste, int wasteIndex);
    void winScreen();
    void giveUpScreen();

   private:
    int checkLongestColumn(std::vector<std::vector<Card>> tableau);
};

#endif