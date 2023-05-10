#ifndef CELL_HPP
#define CELL_HPP

#include <raylib.h>
#include <utils.hpp>
#include <vector>

enum team {
	TEAM_NONE = 0,
	TEAM_BLUE,
	TEAM_RED
};

#define COLOR_DEAD {0, 0, 0, 0}
#define COLOR_RED {255, 0, 0, 0}
#define COLOR_BLUE {0, 0, 255, 0}

typedef int Cell;

struct CellCount {
	int blues;
	int reds;
};

/// Description:        A function that returns a cell at a given position in the given world.
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world.
/// Argument 2:         Vector2I, a position on the world grid.
/// Return:             Cell(int), the state of the cell at the given position.
/// Example:         	get_cell( 
///								{ {TEAM_NONE, TEAM_BLUE, TEAM_NONE},
///								{TEAM_NONE, TEAM_RED, TEAM_NONE},
///								{TEAM_NONE, TEAM_BLUE, TEAM_NONE} },
///								{1, 1}
///						#===> TEAM_RED
Cell get_cell(std::vector<std::vector<Cell>>& world, Vector2I pos);

/// Description:        A function that sets the cell at a given position in the given world.
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world.
/// Argument 2:         Vector2I, a position on the world grid.
/// Argument 3:		Cell(int), the type you want to assign the given position to.
/// Return:             The state of the cell at the given position.
/// Example:         	get_cell( 
///								{ {TEAM_NONE, TEAM_BLUE, TEAM_NONE},
///								{TEAM_NONE, TEAM_RED, TEAM_NONE},
///								{TEAM_NONE, TEAM_BLUE, TEAM_NONE} },
///								{1, 1}
///						#===> TEAM_RED
void set_cell(std::vector<std::vector<Cell>>& world, Vector2I pos, Cell type);

/// Description:        A function that returns a struct (CellCount) that contains the number of blue and red cells neighbouring the given position (does not count itself) in the given world. 
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world
/// Argument 2:         Vector2I, a position on the world grid.
/// Return:             A struct of CellCount which contains blues and reds
/// Example:         	get_neighbours( 
///								{ {TEAM_RED, TEAM_BLUE, TEAM_NONE},
///								{TEAM_RED, TEAM_RED, TEAM_NONE},
///								{TEAM_NONE, TEAM_BLUE, TEAM_RED} },
///								{1, 1}
///						#===> {2, 3}
CellCount get_neighbours(std::vector<std::vector<Cell>>& world, Vector2I pos);

/// Description:        A function that updates one cell from the previous simulation step and places it in a new copy of the world
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world
/// Argument 2:         std::vector<std::vector<Cell>>, a 2d array containing a update copy of the world
/// Argument 3:		Vector2I, a integer vector representing the cell position you want to update
/// Return:             There is no return value for this function.
void tick_cell(std::vector<std::vector<Cell>>& world,
	       std::vector<std::vector<Cell>>& world_copy, Vector2I pos);

/// Description:	A function that returns a struct (CellCount) that contains the number of alive blue and red cells in the given world.
/// Argument 1:         std::vector<std::vector<Cell>>, a 2d array representing the world
/// Return:             A struct of CellCount which contains blues and reds
/// Example:         	count_cells( 
///								{ {TEAM_RED, TEAM_BLUE, TEAM_NONE},
///								{TEAM_RED, TEAM_RED, TEAM_NONE},
///								{TEAM_NONE, TEAM_BLUE, TEAM_NONE} },
///						#===> {2, 3}
CellCount count_cells(std::vector<std::vector<Cell>>& world);

#endif
