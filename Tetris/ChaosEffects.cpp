#include "ChaosEffects.h"
#include "raylib.h"
#include <cstdlib>

ChaosEffects::ChaosEffects() : currentEffect(), effectEndTime(0), blockCounter(0) {}

void ChaosEffects::ApplyEffect(Game& game) {
    if (!IsEffectActive()) {
        StartRandomEffect();
    }

    switch (currentEffect) {
    case SPEED_UP:
        game.SetSpeed(0.1);
        break;
    case DISABLE_HOLD:
        game.canHold = false;
        break;
    case DISABLE_ROTATE:
        game.canRotate = false;
        break;
        // Handle more effects here
    default:
        break;
    }
}

void ChaosEffects::UpdateEffect(Game& game) {
    if (IsEffectActive()) {
        if (GetTime() >= effectEndTime || blockCounter >= activeEffects.front().blockLimit) {
            ResetEffect(game);
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
    default:
        return "None";
    }
}

void ChaosEffects::DrawChaosEffectUI(Font font) const {
    if (IsEffectActive()) {
        // Draw effect name
        const char* effectName = GetEffectName(currentEffect);
        DrawTextEx(font, effectName, { 565, 500 }, 38, 2, WHITE);

        // Calculate remaining time
        float remainingTime = effectEndTime - GetTime();
        char effectTimerText[20];
        sprintf_s(effectTimerText, "Time: %.1f", remainingTime);
        DrawTextEx(font, effectTimerText, { 565, 550 }, 38, 2, WHITE);
    }
}

bool ChaosEffects::IsEffectActive() const {
    return !activeEffects.empty();
}

void ChaosEffects::ResetEffect(Game& game) {
    switch (currentEffect) {
    case SPEED_UP:
        game.SetSpeed(0.6);
        break;
    case DISABLE_HOLD:
        game.canHold = true;
        break;
    case DISABLE_ROTATE:
        game.canRotate = true;
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
        blockCounter = 0;
    }
    else {
        currentEffect = static_cast<ChaosEffectType>(-1);
    }
}

void ChaosEffects::StartRandomEffect() {
    ChaosEffectType newEffect = static_cast<ChaosEffectType>(rand() % 3);
    double duration = 10; 
    int blockLimit = 3 + (rand() % 3); // Last for 3-5 blocks

    activeEffects.push_back({ newEffect, duration, blockLimit });
    currentEffect = newEffect;
    effectEndTime = GetTime() + duration;
    blockCounter = 0;
}
