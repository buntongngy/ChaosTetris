#pragma once


#include "game.h"
#include <vector>

enum ChaosEffectType {
    SPEED_UP,
    DISABLE_HOLD,
    DISABLE_ROTATE,
    SLOW_DOWN,
};

struct ChaosEffect {
    ChaosEffectType type;
    double duration;
    double timeRemaining;
};

class ChaosEffects { 
public:
    ChaosEffects();

    const char* GetEffectName(ChaosEffectType effect) const;

    void ApplyEffect(Game& game); 
    void UpdateEffect(Game& game);
    void DrawChaosEffectUI(Font font) const;
    void ResetEffect(Game& game);
    void StartRandomEffect();
    
    bool IsEffectActive() const;

    

private:
    std::vector<ChaosEffect> activeEffects;
    ChaosEffectType currentEffect;
    double effectEndTime;
    int blockCounter;
   
};

