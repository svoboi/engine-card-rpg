#include "Effect.h"

Effect::Effect(const int change)
        : m_change(change) {}

int Effect::change() const {
    return m_change;
}