/*
 * main.c
 *
 *  Created on: 4 mar 2018
 *      Author: Zenc
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define UNIT_TEST

#ifndef UNIT_TEST

int main(int argc, char **argv)
{
	return 1;
}

#else
#include "unity.h"
#include "algo_unit.h"

void runTests(void);

int main(int argc, char **argv)
{
	UNITY_BEGIN();
	runTests();
	return UNITY_END();
}

void runTests(void)
{
	ALGO_runUnitTests();
}
#endif
