// ChaosEffects.h

#pragma once

#include "game.h"
#include <vector>

enum ChaosEffectType {
    SPEED_UP,
    DISABLE_HOLD,
    DISABLE_ROTATE,
    SLOW_DOWN,
    BIG_BLOCK,
    LINE_BLOCK,
    REVERSE_CONTROL,
    SZ_BLOCK,
};

struct ChaosEffect {
    ChaosEffectType type;
    double duration;
    double timeRemaining;
};

class ChaosEffects {
public:
    ChaosEffects();
    ChaosEffectType currentEffect;

    const char* GetEffectName(ChaosEffectType effect) const;

    void ApplyEffect(Game& game);
    void UpdateEffect(Game& game);
    void DrawChaosEffectUI(Font font) const;
    void ResetEffect(Game& game);
    void StartRandomEffect();
    void StartChaosMode(double duration); // New method to start chaos mode

    bool IsEffectActive() const;
    bool IsChaosModeActive() const; // New method to check chaos mode status

private:
    std::vector<ChaosEffect> activeEffects;
    double effectEndTime;
    double chaosEndTime; // New variable for chaos mode end time
    int blockCounter;
};
