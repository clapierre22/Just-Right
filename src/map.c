#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

void initMap(void);
static void loadTiles(void);
static void loadMap(void);
void drawMap(void);

void initMap(void) {

	// memset(&level.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);

	loadTiles();

	loadMap();
}

static void loadTiles(void) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            level.room.map[x][y] = GROUND;
        }
    }
}d

static void loadMap(const char *filename) {
	char *data = readFile(filename); 
	char *p;
	int x, y;

	if (!data) {
		printf(
			stderr, 
			"Failed to load map file: %s\n", 
			filename);
		return 1;
	}

	p = data;

	for (y = 0; y < MAP_HEIGHT; y++) {
		for (x = 0; x < MAP_WIDTH; x++) {
			if (sscanf(p, "%d", &level.map[x][y]) != 1) {
				printf(
					stderr,
					"Error parsing at (%d, %d)\n",
					x, y);
			}

			while (*p && *p != ' ' && *p != '\n') p++;
			// This skips delimiter
			if (*p) p++;
			
		}
	}

	free(data);
}

void drawMap(void) {
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			// Draw each tile here
			// Based on level.map[x][y]
			// Debug Output:
			printf("%d", level.map[x][y]);
		}
		printf("\n");
	}

}
