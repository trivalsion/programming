/*
	@author : eltertrias
	@brief : Conway's game of life implemented in c to be outputed to the terminal
*/


#include "include/conway_game_of_life.h"


struct coordinate_grid_point
{
	uint8_t x;
	uint8_t y;
};


static uint8_t playboard[40][40];
static struct coordinate_grid_point *alive_cell_coordinates;
static size_t alive_cell_coordinates_amount = 1;


static int outputError(char* error_message, uint8_t error_type, ...)
{
	va_list optional_arguments;
	va_start(optional_arguments, error_type);

	if (error_message == NULL)
	{
		va_end(optional_arguments);
		return RETURN_FAIL;
	}

	if (error_type == ERROR_TYPE_NORMAL)
	{
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "error: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_OFF);

		fprintf(stderr, "\n");
	}
	else if (error_type == ERROR_TYPE_LIB)
	{
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "library error: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, ": ");
		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_OFF);

		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_ON);
		perror(NULL);
		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_OFF);
	}
	else if (error_type == ERROR_TYPE_SYNTAX)
	{
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "syntax error: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_ON);
		fprintf(stderr, "%s", va_arg(optional_arguments, char*)); // file path
		fprintf(stderr, ": ");
		fprintf(stderr, "%lu", va_arg(optional_arguments, size_t)); // line number
		fprintf(stderr, ": ");
		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, TEXT_COLOR_EXTRA_MESSAGE_OFF);

		fprintf(stderr, "\n");
	}
	else if (error_type == ERROR_TYPE_DEBUG)
	{
		#ifdef DEBUG_MODE	// only print messages if the debug mode is on
		fprintf(stderr, TEXT_COLOR_ERROR_ON);
		fprintf(stderr, "debug: ");
		fprintf(stderr, TEXT_COLOR_ERROR_OFF);

		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_ON);
		vfprintf(stderr, error_message, optional_arguments);
		fprintf(stderr, TEXT_COLOR_MAIN_MESSAGE_OFF);

		fprintf(stderr, "\n");
		#endif
	}

	va_end(optional_arguments);
	return RETURN_FAIL;
}


static int parseCLIarguments(int argc, char** argv)
{
	int c;

	if (argc < 2)
	{
		outputError("Not enough arguments supplied, at least one point's coordinates are needed", ERROR_TYPE_NORMAL);
		printHelp();
	}

	if ((alive_cell_coordinates = malloc(sizeof(struct coordinate_grid_point) * alive_cell_coordinates_amount)) == NULL)
		return outputError("Failed to allocate the array for command line arguments", ERROR_TYPE_LIB);

	while (1)
	{
		static struct option long_options[] =	// available command line options
		{
			{"version", no_argument, 0, 'v'},
			{"help", 	no_argument, 0, 'h'},
			{0, 0, 0, 0}
		};
		int option_index = 0;

		if ((c = getopt_long(argc, argv, "vh", long_options, &option_index)) == -1)
			break;

		switch(c)	// find out what the currently parsed option is
		{
			case 0:	// returned if the current option sets a flag
				break;
			case 'h':
				printHelp();
				break;
			case 'v':
				printVersion();
				break;
			case '?':	// unknown option
				return outputError("Unknown command line option", ERROR_TYPE_NORMAL);
				break;
		}
	}

	if (argc > 1)
	{
		for (int i = 1, j = 0; i < argc; i++, j++)	/* find arguments that do not start with - and interpret them as coordinates */
		{
			if (argv[i][0] != '-')	/* if CLI argument does not start with '-' then interpret it as a coordinate grid point */
			{
				size_t comma_location = 0;
				char* temp_string_for_atoi = 0;

				alive_cell_coordinates_amount++;
				if ((alive_cell_coordinates = realloc(alive_cell_coordinates, sizeof(struct coordinate_grid_point) * alive_cell_coordinates_amount)) == NULL)
					return outputError("Failed to reallocate the array for CLI arguments", ERROR_TYPE_LIB);

				for (size_t k = 0; argv[i][k] != '\0'; k++)
				{
					if (argv[i][k] == ',')
					{
						comma_location = k;
						break;
					}
				}
				if (comma_location == 0)
					return outputError("Coordinates supplied in wrong format", ERROR_TYPE_NORMAL);

				if ((temp_string_for_atoi = strndup(argv[i], comma_location)) == NULL)
					return outputError("Failed to allocate an array for the string", ERROR_TYPE_NORMAL);
				alive_cell_coordinates[j].x = atoi(temp_string_for_atoi);
				free(temp_string_for_atoi);

				if ((temp_string_for_atoi = strdup(&(argv[i][comma_location+1]))) == NULL)
					return outputError("Failed to allocate an array for the string", ERROR_TYPE_NORMAL);
				alive_cell_coordinates[j].y = atoi(temp_string_for_atoi);
				free(temp_string_for_atoi);

				//printf("x - %u, y - %u\n", alive_cell_coordinates[j].x, alive_cell_coordinates[j].y);
			}
		}
		alive_cell_coordinates_amount--; // decrease the alive cell coordinate amount because it's number is increased each loop iteration and each time it accounts for next loop iteration, but on the last loop iteration it accounts for nothing as it is the last one and there will be no more iterations after it, so the alive cell coordinate amount is 1 larger then array and so it is decreased here
	}

	return RETURN_SUCCESS;
}

static void freeCLIarguments()
{
	if (alive_cell_coordinates != NULL)
	{
		free(alive_cell_coordinates);
		alive_cell_coordinates = NULL;
	}
}

static void printHelp()
{
	printf(
VERSION_INFO"\n"
"Usage: nas [option] file ...\n\
Options:\n\
	-v	--version	Prints out current version of the program and exits\n\
	-h	--help		Prints out this help message and exits\n");

	exit(EXIT_SUCCESS);
}

static void printVersion()
{
	printf(VERSION_INFO"\n");
	exit(EXIT_SUCCESS);
}

static void place_cell(uint8_t x, uint8_t y)
{
	MOVE_CURSOR_FIXED(x+1, y+1);
	printf(SET_BACKGROUND_COLOR_BLUE"0");
	playboard[x][y] = CELL_ALIVE;
	fflush(stdout);
	sleep(2);
}

static void remove_cell(uint8_t x, uint8_t y)
{
	MOVE_CURSOR_FIXED(x+1, y+1);
	printf(SET_BACKGROUND_COLOR_DEFAULT SET_FOREGROUND_COLOR_DEFAULT);
	fwrite("\x0", sizeof("\x0"), 1, stdout); // ouput a NULL character(as ASCII code 0 and not as a symbol 0) as it is invisible and is perfect for removing/clearing cells
	playboard[x][y] = CELL_DEAD;
	fflush(stdout);
	sleep(2);
}

static int place_initial_cells()
{
	for (size_t i = 0; i < alive_cell_coordinates_amount; i++)
	{
		if (alive_cell_coordinates[i].x > NUMBER_OF_COLUMNS || alive_cell_coordinates[i].y > NUMBER_OF_ROWS)
			return outputError("Failed to place a cell as it's coordinates exceed the playfield", ERROR_TYPE_NORMAL);
		place_cell(alive_cell_coordinates[i].x, alive_cell_coordinates[i].y);
	}

	return RETURN_SUCCESS;
}

static int main_game_loop()
{
	uint8_t initial_x = 0;
	uint8_t initial_y = 0;
	size_t number_of_changes = 0;

	for (size_t x = initial_x, y = initial_y; x < NUMBER_OF_COLUMNS && y < NUMBER_OF_ROWS;)
	{
		size_t temp_x = x;
		size_t temp_y = y;
		size_t alive_neighbours = 0;

		if (x != 0)
			temp_x -= 1;
		if (y != 0)
			temp_y -= 1;

		// Determine the amount of alive cell neighbours
		for (size_t x_neighbour_index = 0, y_neighbour_index = 0; 1; x_neighbour_index++)
		{
			if (playboard[temp_x+x_neighbour_index][temp_y+y_neighbour_index] == CELL_ALIVE)
				if ((temp_x+x_neighbour_index) != x && (temp_y+y_neighbour_index) != y) // make sure that the cell itself does not count as a neighbour
					alive_neighbours++;

			if (x_neighbour_index == 2)
			{
				if (y_neighbour_index == 2)
					break;

				y_neighbour_index++;
				x_neighbour_index = 0;
			}
		}

		// Apply rules to the cell and either leave it's current state, revive it or kill it
		if ((alive_neighbours < 2 || alive_neighbours > 3) && playboard[x][y] == CELL_ALIVE)
		{
			remove_cell(x, y);
			safe_stdin_print("remove x - %lu, y - %lu", x, y);
			number_of_changes++;
		}
		else if (alive_neighbours == 3)
		{
			place_cell(x, y);
			safe_stdin_print("add x - %lu, y - %lu", x, y);
			number_of_changes++;
		}

		if ((x+1) < NUMBER_OF_COLUMNS)
			x += 1;
		else if ((y+1) < NUMBER_OF_ROWS)
		{
			x = 0;
			y += 1;
		}
		else if (x == NUMBER_OF_COLUMNS-1 && y == NUMBER_OF_ROWS-1 && number_of_changes > 0)
		{
			number_of_changes = 0;
			x = 0;
			y = 0;
		}
		else if (x == NUMBER_OF_COLUMNS-1 && y == NUMBER_OF_ROWS-1 && number_of_changes == 0)
			break;
		else
			break;

		// if (number_of_changes > 0)
		// {
		// 	safe_stdin_print("nc - %lu, an - %lu, x - %lu, y - %lu", number_of_changes, alive_neighbours, x, y);
		// 	getchar();
		// }
	}

	return RETURN_SUCCESS;
}

static int safe_stdin_print(char* string, ...)
{
	va_list optional_arguments;
	va_start(optional_arguments, string);

	static size_t line = NUMBER_OF_ROWS+2; // +1 row is used in terminal size check function, so here it is +2 to not overwrite it
	MOVE_CURSOR_FIXED(0, line);
	printf(SET_BACKGROUND_COLOR_DEFAULT);
	printf(SET_FOREGROUND_COLOR_DEFAULT);
	vprintf(string, optional_arguments);
	line++;

	va_end(optional_arguments);
	return RETURN_SUCCESS;
}

static int terminal_size_check()
{
	for (size_t i = 1, x = 0, y = 0; y < NUMBER_OF_ROWS; y++, i++)	/* print numbers 1-40 at each x=0 cell of y axis from y=0-y=39 */
	{
		MOVE_CURSOR_FIXED(x, y);
		printf("%lu", i);
	}

	for (size_t i = 1, x = 0, y = NUMBER_OF_COLUMNS; x < NUMBER_OF_ROWS; x++, i++)
	{
		if (i == 10)
			i = 1;
		MOVE_CURSOR_FIXED(x, y);
		printf("%lu", i);
	}

	safe_stdin_print("Can you see numbers 1-%lu on the y(height) axis and %lu full sets of 1-9 numbers and %lu first numbers from the last set on the x(width) axis?(y/n): ", NUMBER_OF_ROWS, (size_t)(NUMBER_OF_COLUMNS / 9), (NUMBER_OF_COLUMNS % 9));
	if (getchar() == 'y')
	{
		printf(CLEAR_SCREEN);	// clears the screen
		return RETURN_SUCCESS;
	}
	else
	{
		safe_stdin_print("Your terminal is not large enough, if you can't see all of the numbers on y axis - extend your terminal downwards, if you can't see all of the numbers on x axis extend your terminal to the right. After adjusting the terminal you can try starting the game again. press Enter to continue: ");
		getchar();

		MOVE_CURSOR_FIXED(0, 0);
		printf(RESET_CURSOR);
		printf(CLEAR_WHOLE_LINE);
		return RETURN_FAIL;
	}
}

static void safe_exit(int exit_status)
{
	printf(RESET_CURSOR);
	printf(CLEAR_SCREEN);
	printf(SHOW_CURSOR);
	freeCLIarguments();

	exit(exit_status);
}

int main(int argc, char** argv)
{
	if (parseCLIarguments(argc, argv) == RETURN_FAIL)
		exit(EXIT_FAILURE);

	printf(CLEAR_SCREEN);	// clears the screen
	setbuf(stdout, NULL); 	// disables the current buffer so that stuff is outputted to the terminal immidiatly after being sent to stdout
	printf(HIDE_CURSOR);	// hides the cursor so it does not interupt the game

	if (terminal_size_check() == RETURN_FAIL)
		safe_exit(EXIT_FAILURE);

	if (place_initial_cells() == RETURN_SUCCESS)
		main_game_loop();

	safe_stdin_print("The game has finished, press enter to close the game: ");
	if (getchar() != -1)
		safe_exit(EXIT_SUCCESS);

}

// ./build/conway_game_of_life.o 25,30 26,28 26,30 27,29 27,30