#include <stdio.h>

void initLevel(void) {
	memset(&level.map, 0, sizeof(int) * MAP_WIDTH * MAP_HEIGHT);

	loadTiles();

	loadMap();
}

static void loadTiles(void) {
	int i;
	// char filename[MAX_FILE_LEN];
	
	for (i = 1, i < MAX_TILES; i++) {
		// sprintf(filename, assets/floortile.png, i);
		// tiles[i] = loadTexture(filename);
	}
}

static void loadMap(const char *filename) {
	char *data, *p;
	int x, y;

	data = readFile(filename);
	p = data;

	for (y = 0; y < MAP_HEIGHT; y++) {
		for (x = 0; x < MAP_WIDTH; x++) {
			sscanf(p, "%d", &level.map[x][y]);
			do {p++;} while (*p != ' ' && *p != '\n');
		}
	}

	free(data);
}

void drawMap(void) {
	int x, y, n;

}
