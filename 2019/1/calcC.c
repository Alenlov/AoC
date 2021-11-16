#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint32_t calculate_fuel(uint32_t mass);
uint32_t calculate_fuel_recursively(uint32_t mass);
void calculate_fuel_for_input_file(const char *file);

int main(int argc, char **argv)
{
	calculate_fuel_for_input_file("input_day1.txt");
	return EXIT_SUCCESS;
}

uint32_t calculate_fuel(uint32_t mass)
{
	return (mass / 3) - 2;
}

uint32_t calculate_fuel_recursively(uint32_t mass)
{
	uint32_t current_mass = mass;
	uint32_t total_fuel = 0;
	while (current_mass > 6) {
		current_mass = calculate_fuel(current_mass);
		total_fuel += current_mass;
	}
	return total_fuel;
}

void calculate_fuel_for_input_file(const char *file)
{
	uint32_t current_mass = 0;
	uint32_t total_fuel = 0, total_fuel_recursive = 0;

	FILE *fp = fopen(file, "r");
	if (!fp) {
		exit(EXIT_FAILURE);
	} else {
		while(fscanf(fp, "%u", &current_mass) == 1) {
			total_fuel += calculate_fuel(current_mass);
			total_fuel_recursive += calculate_fuel_recursively(current_mass);
		}
		fclose(fp);
		printf("Total fuel part 1: %u\n", total_fuel);
		printf("Total fuel part 2: %u\n", total_fuel_recursive);
	}
}