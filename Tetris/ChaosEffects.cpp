
#include "ChaosEffects.h"
#include "raylib.h"
#include <cstdlib>

ChaosEffects::ChaosEffects() : currentEffect(), effectEndTime(0), chaosEndTime(0) {}

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
        }
    }
}

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
        return "S & Z Block Only";
    case REVERSE_CONTROL:
        return "Reverse Control";

    }
}

void ChaosEffects::DrawChaosEffectUI(Font font) const {
    if (IsEffectActive()) {
        // Draw effect name
     
            const char* effectName = GetEffectName(currentEffect);
            DrawTextEx(font, effectName, { 600, 500 }, 26, 2, WHITE);

            // Calculate remaining time
            float remainingTime = activeEffects.front().timeRemaining;
            char effectTimerText[20];
            sprintf_s(effectTimerText, "Time: %.1f", remainingTime);
            DrawTextEx(font, effectTimerText, { 600, 550 }, 26, 2, WHITE);
        
    }
}

bool ChaosEffects::IsEffectActive() const {
    return !activeEffects.empty();
}

bool ChaosEffects::IsChaosModeActive() const {
    return GetTime() < chaosEndTime;
}

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
    case REVERSE_CONTROL:
        game.ReverseControl(false);
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

void ChaosEffects::StartRandomEffect() {
    ChaosEffectType newEffect = static_cast<ChaosEffectType>(rand() % 8);
    double duration = 10.0; 

    switch (newEffect) {
    case SPEED_UP:
        duration = 1.0;
        break;
    case SLOW_DOWN:
        duration = 5.0;
        break;
    case BIG_BLOCK:
        duration = 5.0;
        break;
    default:
        duration = 10.0;
        break;
    }

    activeEffects.push_back({ newEffect, duration, duration });
    currentEffect = newEffect;
    effectEndTime = GetTime() + duration;
}

void ChaosEffects::StartChaosMode(double duration) {
    chaosEndTime = GetTime() + duration;
}
