#pragma once


#include "game.h"
#include <vector>

enum ChaosEffectType {
    SPEED_UP,
    DISABLE_HOLD,
    DISABLE_ROTATE,
    // Add more effects as needed
};

struct ChaosEffect {
    ChaosEffectType type;
    double duration; 
    int blockLimit; 
};

class ChaosEffects { 
public:
    ChaosEffects();
    void ApplyEffect(Game& game); 
    void UpdateEffect(Game& game);
    const char* GetEffectName(ChaosEffectType effect) const;
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

