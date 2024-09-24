
#include "ChaosEffects.h"
#include "raylib.h"
#include <random>
#include <chrono>


ChaosEffects::ChaosEffects() : currentEffect(), effectEndTime(0), chaosEndTime(0) 
{
    std::random_device rd;
    randomEngine.seed(rd());
}

//Apply Chaos Effect Method
void ChaosEffects::ApplyEffect(Game& game) {
    if (IsChaosModeActive() && !IsEffectActive()) {
        StartRandomEffect();
    }

    if (IsEffectActive()) {
        switch (currentEffect) {
        case DISABLE_HOLD:
            game.canHold = false;
            break;
        case DISABLE_ROTATE:
            game.canRotate = false;
            break;
        case SPEED_UP:
            game.SetSpeed(0.03);
            break;
        case SLOW_DOWN:
            game.SetSpeed(2.0);
            game.canDrop = false;
            break;
        case BIG_BLOCK:
            game.SetBigBlockMod(true);
            break;
        case LINE_BLOCK:
            game.SetLineBlock(true);
            break;
        case SZ_BLOCK:
            game.SetSZBlock(true);
            break;
        case REVERSE_CONTROL:
            game.ReverseControl(true);
            break;
        case PENTRIX:
            game.SetPentrix(true);
            break;
        case RAIN:
            game.SetRain(true);
            game.SetSpeed(0.05);
            break;
        }
    }
}

//Update the chaos timer effect methdo
void ChaosEffects::UpdateEffect(Game& game) {
   
     
        if (IsEffectActive()) {
            double currentTime = GetTime();
            double elapsedTime = currentTime - (effectEndTime - activeEffects.front().timeRemaining);

            if (elapsedTime > 0) {
                activeEffects.front().timeRemaining -= elapsedTime;

                if (activeEffects.front().timeRemaining <= 0) {
                    ResetEffect(game);
                }
                else {
                    effectEndTime = currentTime + activeEffects.front().timeRemaining;
                }
            }
        }

      
}

//Method to get the effect name
const char* ChaosEffects::GetEffectName(ChaosEffectType effect) const {
    switch (effect) {
    case SPEED_UP:
        return "Speed Up";
    case DISABLE_HOLD:
        return "Disable Hold";
    case DISABLE_ROTATE:
        return "Disable Rotate";
    case SLOW_DOWN:
        return "Slow Down!!";
    case BIG_BLOCK:
        return "BIG BLOCK";
    case LINE_BLOCK:
        return "LINE BLOCK!!!";
    case SZ_BLOCK:
        return "ZigZag";
    case REVERSE_CONTROL:
        return "Swap Control";
    case PENTRIX:
        return "Pentrix Mode";
    case RAIN:
        return "Rain";
    }
 
}



//Check if there is an active effect
bool ChaosEffects::IsEffectActive() const {
    return !activeEffects.empty();
}

//Check if the the chaos effect duration is over
bool ChaosEffects::IsChaosModeActive() const {
    return GetTime() < chaosEndTime;
}

//Reset method that reset the effect when the effect duration is end
void ChaosEffects::ResetEffect(Game& game) {
    switch (currentEffect) {
    case SPEED_UP:
        game.SetSpeed(0.2);
        break;
    case BIG_BLOCK:
        game.SetBigBlockMod(false);
        break;
    case DISABLE_ROTATE:
        game.canRotate = true;
        break;
    case SLOW_DOWN:
        game.SetSpeed(0.2);
        game.canDrop = true;
        break;
    case DISABLE_HOLD:
        game.canHold = true;
        break;
    case LINE_BLOCK:
        game.SetLineBlock(false);
        break;
    case SZ_BLOCK:
        game.SetSZBlock(false);
        break;
    case PENTRIX:
        game.SetPentrix(false);
        break;
    case REVERSE_CONTROL:
        game.ReverseControl(false);
        break;
    case RAIN:
        game.SetRain(false);
        game.SetSpeed(0.2);
        break;
    default:
        break;
    }

    if (!activeEffects.empty()) {
        activeEffects.erase(activeEffects.begin());
    }

    if (!activeEffects.empty()) {
        currentEffect = activeEffects.front().type;
        effectEndTime = GetTime() + activeEffects.front().duration;
    }
    else {
        currentEffect = static_cast<ChaosEffectType>(-1);
    }
}

//Method that start a random effect
void ChaosEffects::StartRandomEffect() {
    
    std::uniform_int_distribution<int> dist(0, static_cast<int>(ChaosEffectType::MAX_EFFECT) - 1);

    ChaosEffectType newEffect;
    do
    {
        newEffect = static_cast<ChaosEffectType>(dist(randomEngine));
    } while (newEffect == currentEffect);
    double duration = 10.0;
    switch (newEffect)
    {
    case SPEED_UP:
        duration = 1.0;
        break;
    case DISABLE_ROTATE: case SLOW_DOWN: case BIG_BLOCK:
        duration = 5.0;
        break;
    default:
        break;
    }

    activeEffects.push_back({ newEffect, duration ,duration });
    currentEffect = newEffect;
    effectEndTime = GetTime() + duration;
}

//Method that handle chaos effect count down
void ChaosEffects::StartChaosMode(double duration) {
    chaosEndTime = GetTime() + duration;
}
