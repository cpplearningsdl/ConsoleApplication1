#pragma once
#include "rainStorm.h"




inline void growW(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualSpawnParams.type) {
        case  rainSpawnTypeEnum::RECTANGLE:
            s.actualSpawnParams.rect.width += aSeq.sequence[aSeq.step].speed * dt;
            break;
        case rainSpawnTypeEnum::RADIUS:
            s.actualSpawnParams.radius += aSeq.sequence[aSeq.step].speed * dt;
            break;
        case rainSpawnTypeEnum::ELLIPSE:
            s.actualSpawnParams.radiusX += aSeq.sequence[aSeq.step].speed * dt;
            break;
    }
    if (s.actualSpawnParams.rect.width > 1800) { s.actualSpawnParams.rect.width = 1800; }  
}

inline void growH(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualSpawnParams.type) {
    case  rainSpawnTypeEnum::RECTANGLE:
        s.actualSpawnParams.rect.height += aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainSpawnTypeEnum::RADIUS:
        s.actualSpawnParams.radius += aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainSpawnTypeEnum::ELLIPSE:
        s.actualSpawnParams.radiusX += aSeq.sequence[aSeq.step].speed * dt;
        break;
    } 
    if (s.actualSpawnParams.rect.height > 1600) { s.actualSpawnParams.rect.height = 1600; }

}

inline void shrinkW(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualSpawnParams.type) {
        case  rainSpawnTypeEnum::RECTANGLE:
            s.actualSpawnParams.rect.width -= aSeq.sequence[aSeq.step].speed * dt;
            break;
        case rainSpawnTypeEnum::RADIUS:
            s.actualSpawnParams.radius -= aSeq.sequence[aSeq.step].speed * dt;
            break;
        case rainSpawnTypeEnum::ELLIPSE:
            s.actualSpawnParams.radiusX -= aSeq.sequence[aSeq.step].speed * dt;
            break;
    } 
    if (s.actualSpawnParams.rect.width < 0) { s.actualSpawnParams.rect.width = 0; }  
}

inline void shrinkH(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualSpawnParams.type) {
    case  rainSpawnTypeEnum::RECTANGLE:
        s.actualSpawnParams.rect.height -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainSpawnTypeEnum::RADIUS:
        s.actualSpawnParams.radius -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainSpawnTypeEnum::ELLIPSE:
        s.actualSpawnParams.radiusX -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    } 
    if (s.actualSpawnParams.rect.height < 0) { s.actualSpawnParams.rect.height = 0; } 
}


inline void growKillW(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualKillParams.type) {
    case  rainKillType::RECTANGLE:
        s.actualKillParams.rect.width += aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::CIRCLE:
        s.actualKillParams.radius += aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::ELLIPSE:
        s.actualKillParams.radiusX += aSeq.sequence[aSeq.step].speed * dt;
        break;
    }
    if (s.actualKillParams.rect.width > 1800) { s.actualKillParams.rect.width = 1800; }
}

inline void growKillH(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualKillParams.type) {
    case  rainKillType::LOWER_Y:
        s.actualKillParams.lowerY += aSeq.sequence[aSeq.step].speed * dt;
        break;
    case  rainKillType::RECTANGLE:
        s.actualKillParams.rect.height += aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::CIRCLE:
        s.actualKillParams.radius += aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::ELLIPSE:
        s.actualKillParams.radiusX += aSeq.sequence[aSeq.step].speed * dt;
        break;
    }
    if (s.actualKillParams.rect.height > 1600) { s.actualKillParams.rect.height = 1600; }

}

inline void shrinkKillW(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualKillParams.type) {
    case  rainKillType::RECTANGLE:
        s.actualKillParams.rect.width -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::CIRCLE:
        s.actualKillParams.radius -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::ELLIPSE:
        s.actualKillParams.radiusX -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    }
    if (s.actualKillParams.rect.width < 0) { s.actualKillParams.rect.width = 0; }
}

inline void shrinkKillH(rainStorm& s, float dt, rainStormSizeAnimationSequence& aSeq) {
    switch (s.actualKillParams.type) {
    case  rainKillType::LOWER_Y:
        s.actualKillParams.lowerY -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    case  rainKillType::RECTANGLE:
        s.actualKillParams.rect.height -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::CIRCLE:
        s.actualKillParams.radius -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    case rainKillType::ELLIPSE:
        s.actualKillParams.radiusX -= aSeq.sequence[aSeq.step].speed * dt;
        break;
    }
    if (s.actualKillParams.rect.height < 0) { s.actualKillParams.rect.height = 0; }
}

inline void changeSize(rainStorm& s, float dt) {
    rainStormSizeAnimationSequence& aSeq = s.def.config.sizeAnimationSequence;
    //SPAWN AREA
    //width
    if (aSeq.sequence[aSeq.step].growW) {
        growW(s, dt, aSeq);
    } 
    else if (aSeq.sequence[aSeq.step].shrinkW) {
        shrinkW(s, dt, aSeq);
    }
    //height
    if (aSeq.sequence[aSeq.step].growH) {
        growH(s, dt, aSeq);
    }
    else if (aSeq.sequence[aSeq.step].shrinkH) {
        shrinkH(s, dt, aSeq);
    }
    //KILL AREA
    //width
    if (aSeq.sequence[aSeq.step].growKillW) {
        growKillW(s, dt, aSeq);
    }
    else if (aSeq.sequence[aSeq.step].shrinkKillW) {
        shrinkKillW(s, dt, aSeq);
    }
    //height
    if (aSeq.sequence[aSeq.step].growKillH) {
        growKillH(s, dt, aSeq);
    }
    else if (aSeq.sequence[aSeq.step].shrinkKillH) {
        shrinkKillH(s, dt, aSeq);
    }
}