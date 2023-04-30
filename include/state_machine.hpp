#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

enum game_states {
    BLUE_TURN = 0,
    RED_TURN,
    SIMULATING,
    MENU
};
int state = BLUE_TURN;

int cells_placed = 0;
float tick_time = 0;
int tick_count = 0;

#endif