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
    PENTRIX,
    RAIN,
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
    void StartChaosMode(double duration); 

    bool IsEffectActive() const;
    bool IsChaosModeActive() const;

private:
    std::vector<ChaosEffect> activeEffects;
    double effectEndTime;
    double chaosEndTime; 
    int blockCounter;
};
