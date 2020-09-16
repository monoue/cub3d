const TILE_SIZE = 32;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

const EDGE_COLOR = "#15d";
const INNER_COLOR = "#d51";

const NEUTRAL = 0;
const LEFT = -1;
const RIGHT = 1;
const BACK = -1;
const FRONT = 1;

class Map {
	constructor() {
		this.grid = [
			[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
		];
	}
	hasWallAt(pixelX, pixelY) {
		const gridX = Math.floor(pixelX / TILE_SIZE);
		const gridY = Math.floor(pixelY / TILE_SIZE);
		return this.grid[gridY][gridX] === 1 ? true : false;
	}
	render() {
		for (let y = 0; y < MAP_NUM_ROWS; y++) {
			for (let x = 0; x < MAP_NUM_COLS; x++) {
				const tileX = x * TILE_SIZE;
				const tileY = y * TILE_SIZE;
				const tileColor = this.grid[y][x] === 1 ? EDGE_COLOR : INNER_COLOR;
				stroke(EDGE_COLOR);
				fill(tileColor);
				rect(tileX, tileY, TILE_SIZE, TILE_SIZE);
			}
		}
	}
}

class	Player {
	constructor() {
		this.x = WINDOW_WIDTH / 2;
		this.y = WINDOW_HEIGHT / 2;
		this.radius = 3;
		this.turnDirection = NEUTRAL;
		this.walkDirection = NEUTRAL;
		this.rotationAngle = Math.PI / 2;
		this.moveSpeed = 2.0;
		this.rotationSpeed = 2 * (Math.PI / 180);

	}
	update() {
		this.rotationAngle += this.turnDirection * this.rotationSpeed;

		const moveStep = this.walkDirection * this.moveSpeed;

		let newPlayerX = this.x + Math.cos(this.rotationAngle) * moveStep;
		let newPlayerY = this.y + Math.sin(this.rotationAngle) * moveStep;

		if (grid.hasWallAt(newPlayerX, this.y)) {
			newPlayerX = this.x;
		}
		if (grid.hasWallAt(this.x, newPlayerY)) {
			newPlayerY = this.y;
		}
		[this.x, this.y] = [newPlayerX, newPlayerY];
		// if (grid.isSpaceAt(newPlayerX, newPlayerY)) {
		// 	this.x = newPlayerX;
		// 	this.y = newPlayerY;
		// }
	}
	render() {
		noStroke();
		fill("yellow");
		circle(this.x, this.y, this.radius);
		stroke("yellow");
		line(
			this.x,
			this.y,
			this.x + Math.cos(this.rotationAngle) * 30,
			this.y + Math.sin(this.rotationAngle) * 30
		);
	}
}

const grid = new Map();
const player = new Player();

function keyPressed() {
	switch (keyCode) {
		case UP_ARROW:
			player.walkDirection = FRONT;
			break;
		case DOWN_ARROW:
			player.walkDirection = BACK;
			break;
		case LEFT_ARROW:
			player.turnDirection = LEFT;
			break;
		case RIGHT_ARROW:
			player.turnDirection = RIGHT;
			break;
	}
}

function keyReleased() {
	switch (keyCode) {
		case UP_ARROW:
		case DOWN_ARROW:
			player.walkDirection = NEUTRAL;
			break;
		case LEFT_ARROW:
		case RIGHT_ARROW:
			player.turnDirection = NEUTRAL;
			break;
	}
}

function setup() {
	createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function update() {
	player.update();
	// console.log(player.turnDirection);
}

function draw() {
	update();

	grid.render();
	player.render();
}