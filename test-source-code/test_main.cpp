#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "TestPlayer.hpp"
#include "TestMonster.hpp"
#include "TestRock.hpp"
#include "TestHarpoon.hpp"
#include "TestGame.hpp"
#include "TestBonusItem.hpp"

int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    return context.run();
}