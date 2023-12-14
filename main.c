/*
 * Copyright © 2023 - ReeceDeveloper
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files
 * (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Entity {
	int entityVelocity;
	int entityAcceleration;
	int entityStartPosition;
	int entityPosition;

	struct Projectile {
		int projectileVelocity;
		int projectilePosition;
	};
};

void parseArguments(struct Entity* entityLeft, struct Entity* entityRight, int argc, char* argv[]);

bool isValidEntity(const struct Entity* entity);

void runSimulation(struct Entity* entityLeft, struct Entity* entityRight);

void printState(const struct Entity* entityLeft, const struct Entity* entityRight, const int* simulationTime);

int main(int argc, char* argv[]) {
	// I'm using a whole int's worth of memory anyways, might as well have fun.
	struct Entity entityLeft = { 0xDEAD, 0xDEAD, 0xDEAD, 0xDEAD, 0xDEAD, 0xDEAD };
	struct Entity entityRight = { 0xDEAD, 0xDEAD, 0xDEAD, 0xDEAD, 0xDEAD, 0xDEAD };

	if (argc > 1) {
		parseArguments(&entityLeft, &entityRight, argc, argv);
	} else {
		printf("\n[ERROR]: No arguments were passed.\n"); return -1;
	}

	if (!isValidEntity(&entityLeft)) {
		printf("\n[ERROR]: Left-side entity is invalid.\n"); return -1;
	}

	if (!isValidEntity(&entityRight)) {
		printf("\n[ERROR]: Right-side entity is invalid.\n"); return -1;
	}

	runSimulation(&entityLeft, &entityRight);
}

void parseArguments(struct Entity* entityLeft, struct Entity* entityRight, int argc, char* argv[]) {
	for (int idx = 1; idx < argc; ++idx) {
		if (argv[idx][0] == '-' && strlen(argv[idx]) == 4) {
			char cvar[4]; // Create space for the console variable.
			strncpy(cvar, argv[idx] + 1, 3); // Copy it in...
			cvar[3] = '\0'; // Null-terminate the value.

			int value = atoi(argv[idx + 1]); // Get the value.

			switch (cvar[0]) {
				case 'l': {
					if (strcmp(cvar, "lev") == 0)
						entityLeft->entityVelocity = value;
					else if (strcmp(cvar, "lea") == 0)
						entityLeft->entityAcceleration = value;
					else if (strcmp(cvar, "les") == 0)
						entityLeft->entityStartPosition = value;
					else if (strcmp(cvar, "lpv") == 0)
						entityLeft->projectileVelocity = value;

					break;
				} case 'r': {
					if (strcmp(cvar, "rev") == 0)
						entityRight->entityVelocity = value;
					else if (strcmp(cvar, "rea") == 0)
						entityRight->entityAcceleration = value;
					else if (strcmp(cvar, "res") == 0)
						entityRight->entityStartPosition = value;
					else if (strcmp(cvar, "rpv") == 0)
						entityRight->projectileVelocity = value;

					break;
				} default: {
					printf("\n[ERROR]: Invalid argument.\n"); return;
				}
			}
		}
	}

	// Finalize entity and projectile data with the user's input.

	entityLeft->entityPosition = entityLeft->entityStartPosition;
	entityLeft->projectilePosition = entityLeft->entityStartPosition;
	entityLeft->projectileVelocity = entityLeft->projectileVelocity + entityLeft->entityVelocity;

	entityRight->entityPosition = entityRight->entityStartPosition;
	entityRight->projectilePosition = entityRight->entityStartPosition;
	entityRight->projectileVelocity = entityRight->projectileVelocity + entityRight->entityVelocity;
}

bool isValidEntity(const struct Entity* entity) {
	return (
		entity->entityVelocity != 0xDEAD &&
		entity->entityAcceleration != 0xDEAD &&
		entity->entityStartPosition != 0xDEAD &&
		entity->entityPosition != 0xDEAD &&
		entity->projectileVelocity != 0xDEAD &&
		entity->projectilePosition != 0xDEAD
	);
}

void runSimulation(struct Entity* entityLeft, struct Entity* entityRight) {
	printf("\n[INFO]: Beginning simulation...\n");

	int simulationTime = 0; // Start the simulation at zero seconds to print the initial state.

	while (simulationTime < 300) { // Three-hundred simulated seconds (five minutes) maximum.
		printState(entityLeft, entityRight, &simulationTime);

		if (entityLeft->projectilePosition >= entityRight->entityPosition) { // If the left-most projectile's position is at, or exceeds the right-most entity's position (contact).
			if (entityRight->projectilePosition <= entityLeft->entityPosition) { // If the right-most projectile's position is ALSO at, or exceeds, the left-most entity's position (contact).
				printf("\n[INFO]: Projectiles have made contact simultaneously.\n"); return;
			}

			printf("\n[INFO]: The left-most projectile made contact first.\n"); return;
		}

		if (entityRight->projectilePosition <= entityLeft->entityPosition) { // If the right-most projectile's position is at, or exceeds the left-most entity's position (contact).
			printf("\n[INFO]: The right-most projectile made contact first.\n"); return;
		}

		// Update values.
		entityLeft->entityPosition = entityLeft->entityPosition + entityLeft->entityVelocity;		// x_f = x_i + v.
		entityRight->entityPosition = entityRight->entityPosition + entityRight->entityVelocity;	// x_f = x_i + v.

		entityLeft->entityVelocity = entityLeft->entityVelocity + entityLeft->entityAcceleration;		// v_f = v_i + a.
		entityRight->entityVelocity = entityRight->entityVelocity + entityRight->entityAcceleration;	// v_f = v_i + a.

		entityLeft->projectilePosition = entityLeft->projectilePosition + entityLeft->projectileVelocity;		// x_f = x_i + v.
		entityRight->projectilePosition = entityRight->projectilePosition + entityRight->projectileVelocity;	// x_f = x_i + v.

		++simulationTime;
	}

	printf("\n[WARN]: No collisions occurred in the simulation.\n");
}

void printState(const struct Entity* entityLeft, const struct Entity* entityRight, const int* simulationTime) {
	printf("\n[INFO]: Simulation time is currently %i second(s).\n", *simulationTime);

	printf(
		"\n[INFO]: The left-most entity is currently at (x = %i units), with a velocity of (v = %i units/second) and acceleration of (a = %i units/second/second).\n",
		entityLeft->entityPosition, entityLeft->entityVelocity, entityLeft->entityAcceleration
	);

	printf(
		"[INFO]: The left-most projectile is currently at (x = %i units), with a velocity of (v = %i units/second).\n",
		entityLeft->projectilePosition, entityLeft->projectileVelocity
	);


	printf(
		"\n[INFO]: The right-most entity is currently at (x = %i units), with a velocity of (v = %i units/second) and acceleration of (a = %i units/second/second).\n",
		entityRight->entityPosition, entityRight->entityVelocity, entityRight->entityAcceleration
	);

	printf(
		"[INFO]: The right-most projectile is currently at (x = %i units), with a velocity of (v = %i units/second).\n",
		entityRight->projectilePosition, entityRight->projectileVelocity
	);
}