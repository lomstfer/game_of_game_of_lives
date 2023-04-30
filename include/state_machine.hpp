#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

enum game_states {
    BLUE_TURN = 0,
    RED_TURN,
    SIMULATING,
    MENU
};
static int state = BLUE_TURN;

#define CELLS_PER_TURN 5
#define TICKS_PER_TURN 3

static int cells_placed = 0;
static float tick_time = 0;
static int tick_count = 0;

#endif