/*
 * algo_unity.c
 *
 *  Created on: 4 mar 2018
 *      Author: Zenc
 */
#include <stdint.h>
#include <stdbool.h>

#include "algo_internal.h"
#include "algo_If.h"
#include "unity_fixture.h"

void TESTALGO_checkSquare_input(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0, 0, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 0, 0, 0, 0, 9,
        0, 4, 0, 0, 0, 3, 1, 0, 0,
        7, 8, 0, 3, 0, 0, 0, 5, 2,
        0, 0, 2, 0, 0, 0, 9, 0, 0,
        5, 9, 0, 0, 0, 8, 0, 1, 6,
        0, 0, 7, 1, 0, 0, 0, 9, 0,
        6, 0, 0, 0, 0, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 11
    };
    bool state_b = false;
    bool result_ab[6] = {true, true, true, true, true, false};
    /* execute */
    result_ab[0] = ALGO_checkSquare(NULL, UINT8_MAX, UINT8_MAX, NULL);
    result_ab[1] = ALGO_checkSquare(NULL, UINT8_MAX, UINT8_MAX, &state_b);
    result_ab[2] = ALGO_checkSquare(NULL, UINT8_MAX, 0, &state_b);
    result_ab[3] = ALGO_checkSquare(NULL, UINT8_MAX, 1, &state_b);
    result_ab[4] = ALGO_checkSquare(NULL, 0, 1, &state_b);
    result_ab[5] = ALGO_checkSquare(grid_example_au8, 0, 1, &state_b);
    /* assert */
    TEST_ASSERT_FALSE(result_ab[0]);
    TEST_ASSERT_FALSE(result_ab[1]);
    TEST_ASSERT_FALSE(result_ab[2]);
    TEST_ASSERT_FALSE(result_ab[3]);
    TEST_ASSERT_FALSE(result_ab[4]);
    TEST_ASSERT_TRUE(result_ab[5]);
}

void TESTALGO_checkSquare_positive(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0,11, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 7, 0, 0, 0, 9,
        0, 4, 0, 0, 8, 3, 1, 0, 0,
        7, 8, 0, 3, 9, 6, 0, 5, 2,
        4, 6, 2, 7, 1, 5, 9, 8, 3,
        5, 9, 0, 2, 4, 8, 0, 1, 6,
        0, 0, 7, 1, 5, 0, 0, 9, 0,
        6, 0, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 0
    };
    bool state_ab[3] = {false, false, false};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkSquare(grid_example_au8, 0, 3, &state_ab[0]);
    result_ab[1] = ALGO_checkSquare(grid_example_au8, 1, 7, &state_ab[1]);
    result_ab[2] = ALGO_checkSquare(grid_example_au8, 4, 4, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_TRUE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_TRUE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_TRUE(state_ab[2]);
}

void TESTALGO_checkSquare_negative(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        1, 0,11, 2, 6, 1, 1, 0, 5,
        1, 3, 0, 2, 7, 2, 2, 0, 9,
        0, 4, 0, 2, 8, 3, 1, 0, 0,
        7, 8, 0, 3, 9, 3, 0, 5, 2,
        4, 6, 2, 7, 1, 5, 9, 3, 3,
        5, 9, 0, 2, 4, 8, 0, 1, 6,
        0, 0, 7, 1, 5, 0, 0, 9, 0,
        6, 0, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 0
    };
    bool state_ab[3] = {true, true, true};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkSquare(grid_example_au8, 0, 1, &state_ab[0]);
    result_ab[1] = ALGO_checkSquare(grid_example_au8, 1, 2, &state_ab[1]);
    result_ab[2] = ALGO_checkSquare(grid_example_au8, 4, 3, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_FALSE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_FALSE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_FALSE(state_ab[2]);
}

void TESTALGO_checkRow_input(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0, 0, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 0, 0, 0, 0, 9,
        0, 4, 0, 0, 0, 3, 1, 0, 0,
        7, 8, 0, 3, 0, 0, 0, 5, 2,
        0, 0, 2, 0, 0, 0, 9, 0, 0,
        5, 9, 0, 0, 0, 8, 0, 1, 6,
        0, 0, 7, 1, 0, 0, 0, 9, 0,
        6, 0, 0, 0, 0, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 11
    };
    bool state_b = false;
    bool result_ab[6] = {true, true, true, true, true, false};
    /* execute */
    result_ab[0] = ALGO_checkRow(NULL, UINT8_MAX, UINT8_MAX, NULL);
    result_ab[1] = ALGO_checkRow(NULL, UINT8_MAX, UINT8_MAX, &state_b);
    result_ab[2] = ALGO_checkRow(NULL, UINT8_MAX, 0, &state_b);
    result_ab[3] = ALGO_checkRow(NULL, UINT8_MAX, 1, &state_b);
    result_ab[4] = ALGO_checkRow(NULL, 0, 1, &state_b);
    result_ab[5] = ALGO_checkRow(grid_example_au8, 0, 1, &state_b);
    /* assert */
    TEST_ASSERT_FALSE(result_ab[0]);
    TEST_ASSERT_FALSE(result_ab[1]);
    TEST_ASSERT_FALSE(result_ab[2]);
    TEST_ASSERT_FALSE(result_ab[3]);
    TEST_ASSERT_FALSE(result_ab[4]);
    TEST_ASSERT_TRUE(result_ab[5]);
}

void TESTALGO_checkRow_positive(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0,11, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 7, 0, 0, 0, 9,
        0, 4, 0, 0, 8, 3, 1, 0, 0,
        7, 8, 0, 3, 9, 0, 0, 5, 2,
        4, 6, 2, 7, 1, 5, 9, 8, 3,
        5, 9, 0, 0, 4, 8, 0, 1, 6,
        0, 0, 7, 1, 5, 0, 0, 9, 0,
        6, 0, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 0
    };
    bool state_ab[3] = {false, false, false};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkRow(grid_example_au8, 0, 1, &state_ab[0]);
    result_ab[1] = ALGO_checkRow(grid_example_au8, 1, 2, &state_ab[1]);
    result_ab[2] = ALGO_checkRow(grid_example_au8, 4, 3, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_TRUE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_TRUE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_TRUE(state_ab[2]);
}

void TESTALGO_checkRow_negative(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0,11, 0, 6, 1, 1, 0, 5,
        0, 3, 0, 0, 7, 2, 2, 0, 9,
        0, 4, 0, 0, 8, 3, 1, 0, 0,
        7, 8, 0, 3, 9, 0, 0, 5, 2,
        4, 6, 2, 7, 1, 5, 9, 3, 3,
        5, 9, 0, 0, 4, 8, 0, 1, 6,
        0, 0, 7, 1, 5, 0, 0, 9, 0,
        6, 0, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 0
    };
    bool state_ab[3] = {true, true, true};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkRow(grid_example_au8, 0, 1, &state_ab[0]);
    result_ab[1] = ALGO_checkRow(grid_example_au8, 1, 2, &state_ab[1]);
    result_ab[2] = ALGO_checkRow(grid_example_au8, 4, 3, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_FALSE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_FALSE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_FALSE(state_ab[2]);
}

void TESTALGO_checkColumn_input(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0, 0, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 0, 0, 0, 0, 9,
        0, 4, 0, 0, 0, 3, 1, 0, 0,
        7, 8, 0, 3, 0, 0, 0, 5, 2,
        0, 0, 2, 0, 0, 0, 9, 0, 0,
        5, 9, 0, 0, 0, 8, 0, 1, 6,
        0, 0, 7, 1, 0, 0, 0, 9, 0,
        6, 0, 0, 0, 0, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 11
    };
    bool state_b = false;
    bool result_ab[6] = {true, true, true, true, true, false};
    /* execute */
    result_ab[0] = ALGO_checkColumn(NULL, UINT8_MAX, UINT8_MAX, NULL);
    result_ab[1] = ALGO_checkColumn(NULL, UINT8_MAX, UINT8_MAX, &state_b);
    result_ab[2] = ALGO_checkColumn(NULL, UINT8_MAX, 0, &state_b);
    result_ab[3] = ALGO_checkColumn(NULL, UINT8_MAX, 1, &state_b);
    result_ab[4] = ALGO_checkColumn(NULL, 0, 1, &state_b);
    result_ab[5] = ALGO_checkColumn(grid_example_au8, 0, 1, &state_b);
    /* assert */
    TEST_ASSERT_FALSE(result_ab[0]);
    TEST_ASSERT_FALSE(result_ab[1]);
    TEST_ASSERT_FALSE(result_ab[2]);
    TEST_ASSERT_FALSE(result_ab[3]);
    TEST_ASSERT_FALSE(result_ab[4]);
    TEST_ASSERT_TRUE(result_ab[5]);
}

void TESTALGO_checkColumn_positive(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0,11, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 7, 0, 0, 0, 9,
        0, 4, 0, 0, 8, 3, 1, 0, 0,
        7, 8, 0, 3, 9, 0, 0, 5, 2,
        4, 6, 0, 7, 1, 5, 9, 8, 3,
        5, 9, 0, 0, 4, 8, 0, 1, 6,
        0, 0, 7, 1, 5, 0, 0, 9, 0,
        6, 0, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 0
    };
    bool state_ab[3] = {false, false, false};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkColumn(grid_example_au8, 2, 2, &state_ab[0]);
    result_ab[1] = ALGO_checkColumn(grid_example_au8, 3, 3, &state_ab[1]);
    result_ab[2] = ALGO_checkColumn(grid_example_au8, 4, 4, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_TRUE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_TRUE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_TRUE(state_ab[2]);
}

void TESTALGO_checkColumn_negative(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        1,12,11, 0, 3, 1, 1, 0, 5,
        1, 3, 0, 0, 3, 2, 2, 0, 9,
        0, 4, 0, 0, 3, 3, 1, 0, 0,
        7, 8, 0, 3, 3, 0, 0, 5, 2,
        4, 6, 2, 7, 3, 5, 9, 3, 3,
        5, 9, 0, 0, 3, 8, 0, 1, 6,
        0, 2, 7, 1, 3, 0, 0, 9, 0,
        6, 2, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 3, 0, 0, 0, 0
    };
    bool state_ab[3] = {true, true, true};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkColumn(grid_example_au8, 0, 1, &state_ab[0]);
    result_ab[1] = ALGO_checkColumn(grid_example_au8, 1, 2, &state_ab[1]);
    result_ab[2] = ALGO_checkColumn(grid_example_au8, 4, 3, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_FALSE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_FALSE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_FALSE(state_ab[2]);
}

void TESTALGO_checkPoint_input(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0, 0, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 0, 0, 0, 0, 9,
        0, 4, 0, 0, 0, 3, 1, 0, 0,
        7, 8, 0, 3, 0, 0, 0, 5, 2,
        0, 0, 2, 0, 0, 0, 9, 0, 0,
        5, 9, 0, 0, 0, 8, 0, 1, 6,
        0, 0, 7, 1, 0, 0, 0, 9, 0,
        6, 0, 0, 0, 0, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 11
    };
    bool state_b = false;
    bool result_ab[7] = {true, true, true, true, true, true, false};
    /* execute */
    result_ab[0] = ALGO_checkPoint(NULL, 0, &state_b);
    result_ab[1] = ALGO_checkPoint(grid_example_au8, 0, NULL);
    result_ab[2] = ALGO_checkPoint(NULL, 0, NULL);
    result_ab[3] = ALGO_checkPoint(grid_example_au8, 0, &state_b);
    result_ab[4] = ALGO_checkPoint(grid_example_au8, 80, &state_b);
    result_ab[5] = ALGO_checkPoint(grid_example_au8, 81, &state_b);
    result_ab[6] = ALGO_checkPoint(grid_example_au8, 30, &state_b);
    /* assert */
    TEST_ASSERT_FALSE(result_ab[0]);
    TEST_ASSERT_FALSE(result_ab[1]);
    TEST_ASSERT_FALSE(result_ab[2]);
    TEST_ASSERT_FALSE(result_ab[3]);
    TEST_ASSERT_FALSE(result_ab[4]);
    TEST_ASSERT_FALSE(result_ab[5]);
    TEST_ASSERT_TRUE(result_ab[6]);
}
void TESTALGO_checkPoint_positive(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        0, 0,11, 0, 6, 1, 0, 0, 5,
        0, 3, 0, 0, 7, 0, 0, 0, 9,
        0, 4, 0, 0, 8, 3, 1, 0, 0,
        7, 8, 0, 3, 9, 0, 0, 5, 2,
        4, 6, 2, 7, 1, 5, 9, 8, 3,
        5, 9, 0, 0, 4, 8, 0, 1, 6,
        0, 0, 7, 1, 5, 0, 0, 9, 0,
        6, 0, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 0
    };
    bool state_ab[3] = {false, false, false};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkPoint(grid_example_au8, 10, &state_ab[0]);
    result_ab[1] = ALGO_checkPoint(grid_example_au8, 36, &state_ab[1]);
    result_ab[2] = ALGO_checkPoint(grid_example_au8, 40, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_TRUE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_TRUE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_TRUE(state_ab[2]);
}
void TESTALGO_checkPoint_negative(void)
{
    /* init */
    uint8_t grid_example_au8[81] = {
        10, 0, 0, 0, 1, 1, 0, 0, 5,
        0, 3, 0, 0, 7, 0, 0, 0, 9,
        0, 4, 0, 0, 8, 3, 1, 0, 0,
        7, 8, 4, 3, 9, 0, 0, 5, 2,
        4, 6, 2, 7, 1, 5, 9, 8, 3,
        5, 9, 0, 0, 4, 8, 0, 1, 6,
        0, 0, 7, 1, 5, 0, 0, 9, 0,
        6, 0, 0, 0, 3, 0, 0, 7, 0,
        9, 0, 0, 6, 2, 0, 0, 0, 0
    };
    bool state_ab[3] = {true, true, true};
    bool result_ab[3] = {false, false, false};
    /* execute */
    result_ab[0] = ALGO_checkPoint(grid_example_au8, 4, &state_ab[0]);
    result_ab[1] = ALGO_checkPoint(grid_example_au8, 36, &state_ab[1]);
    result_ab[2] = ALGO_checkPoint(grid_example_au8, 40, &state_ab[2]);
    /* assert */
    TEST_ASSERT_TRUE(result_ab[0]);
    TEST_ASSERT_FALSE(state_ab[0]);
    TEST_ASSERT_TRUE(result_ab[1]);
    TEST_ASSERT_FALSE(state_ab[1]);
    TEST_ASSERT_TRUE(result_ab[2]);
    TEST_ASSERT_FALSE(state_ab[2]);
}

void ALGO_runUnitTests(void)
{
    RUN_TEST(TESTALGO_checkSquare_input);
    RUN_TEST(TESTALGO_checkSquare_positive);
    RUN_TEST(TESTALGO_checkSquare_negative);

    RUN_TEST(TESTALGO_checkRow_input);
    RUN_TEST(TESTALGO_checkRow_positive);
    RUN_TEST(TESTALGO_checkRow_negative);

    RUN_TEST(TESTALGO_checkColumn_input);
    RUN_TEST(TESTALGO_checkColumn_positive);
    RUN_TEST(TESTALGO_checkColumn_negative);

    RUN_TEST(TESTALGO_checkPoint_input);
    RUN_TEST(TESTALGO_checkPoint_positive);
    RUN_TEST(TESTALGO_checkPoint_negative);
    return;
}
