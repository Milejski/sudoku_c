/*
 * algo.c
 *
 *  Created on: 4 mar 2018
 *      Author: Zenc
 */


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "algo_internal.h"
#include "algo_If.h"

bool ALGO_checkGrid (uint8_t *grid_au8, bool *checkState_pb){}

bool ALGO_checkPoint (uint8_t *grid_au8, uint8_t pointNumber_u8, bool *checkState_pb)
{
    bool retVal_b = true;

    if ((NULL == grid_au8)
        || (NULL == checkState_pb)
        || (SUDOKU_SIZE <= pointNumber_u8)
        || (0U == grid_au8[pointNumber_u8])
        || (SUDOKU_MAX_VALUE < grid_au8[pointNumber_u8]))
    {
        retVal_b = false;
    }
    else
    {
        bool immediateState_ab[3] = {0};
        bool returnState_ab[3] = {0};
        uint8_t valueToCheck_u8 = grid_au8[pointNumber_u8];
        uint8_t rowNumber_u8 = pointNumber_u8 / SUDOKU_COLUMN_COUNT;
        uint8_t columnNumber_u8 = pointNumber_u8 % SUDOKU_ROW_COUNT;
        uint8_t squareNumber_u8 = (rowNumber_u8 / SUDOKU_SQUARE_PER_COLUMN * SUDOKU_SQUARE_PER_ROW)
                + (columnNumber_u8 / SUDOKU_SQUARE_PER_ROW);

        returnState_ab[0] = ALGO_checkRow    (grid_au8, rowNumber_u8   , valueToCheck_u8, &immediateState_ab[0]);
        returnState_ab[1] = ALGO_checkColumn (grid_au8, columnNumber_u8, valueToCheck_u8, &immediateState_ab[1]);
        returnState_ab[2] = ALGO_checkSquare (grid_au8, squareNumber_u8, valueToCheck_u8, &immediateState_ab[2]);

        if ((false == returnState_ab[0]) || (false == returnState_ab[1]) || (false == returnState_ab[2]))
        {
            *checkState_pb = false;
            retVal_b = false;
        }
        else if (immediateState_ab[0] && immediateState_ab[1] && immediateState_ab[2])
        {
            *checkState_pb = true;
            retVal_b = true;
        }
        else
        {
            *checkState_pb = false;
            retVal_b = true;
        }
    }

    return retVal_b;
}

bool ALGO_checkRow (uint8_t *grid_au8, uint8_t rowNumber_u8, uint8_t checkedValue_u8, bool *checkState_pb)
{
    bool retVal_b = true;

    if ((NULL == grid_au8)
        || (NULL == checkState_pb)
        || (SUDOKU_ROW_COUNT <= rowNumber_u8)
        || (0U == checkedValue_u8)
        || (SUDOKU_MAX_VALUE < checkedValue_u8))
    {
        retVal_b = false;
    }
    else
    {
        uint8_t i_u8;
        uint8_t countedValues_u8 = 0U;

        for (i_u8 = 0U; i_u8 < SUDOKU_COLUMN_COUNT; i_u8++)
        {
            uint8_t currentCell_u8 = (rowNumber_u8 * SUDOKU_COLUMN_COUNT)  + i_u8;

            if (checkedValue_u8 == grid_au8[currentCell_u8])
            {
                countedValues_u8++;
            }
        }

        if (countedValues_u8 > 1U)
        {
            *checkState_pb = false;
        }
        else
        {
            *checkState_pb = true;
        }

        retVal_b = true;
    }

    return retVal_b;
}

bool ALGO_checkColumn (uint8_t *grid_au8, uint8_t columnNumber_u8, uint8_t checkedValue_u8, bool *checkState_pb)
{
    bool retVal_b = true;

    if ((NULL == grid_au8)
        || (NULL == checkState_pb)
        || (SUDOKU_COLUMN_COUNT <= columnNumber_u8)
        || (0U == checkedValue_u8)
        || (SUDOKU_MAX_VALUE < checkedValue_u8))
    {
        retVal_b = false;
    }
    else
    {
        uint8_t i_u8;
        uint8_t countedValues_u8 = 0U;

        for (i_u8 = 0U; i_u8 < SUDOKU_ROW_COUNT; i_u8++)
        {
            uint8_t currentCell_u8 = columnNumber_u8 + (SUDOKU_COLUMN_COUNT * i_u8);

            if (checkedValue_u8 == grid_au8[currentCell_u8])
            {
                countedValues_u8++;
            }
        }

        if (countedValues_u8 > 1U)
        {
            *checkState_pb = false;
        }
        else
        {
            *checkState_pb = true;
        }

        retVal_b = true;
    }

    return retVal_b;
}

bool ALGO_checkSquare (uint8_t *grid_au8, uint8_t squareNumber_u8, uint8_t checkedValue_u8, bool *checkState_pb)
{
    bool retVal_b = true;

    if ((NULL == grid_au8)
        || (NULL == checkState_pb)
        || (SUDOKU_SQUARE_COUNT <= squareNumber_u8)
        || (0U == checkedValue_u8)
        || (SUDOKU_MAX_VALUE < checkedValue_u8))
    {
        retVal_b = false;
    }
    else
    {
        uint8_t i_u8;
        uint8_t countedValues_u8 = 0U;
        uint8_t squareOffset_u8 = ((squareNumber_u8 / SUDOKU_SQUARE_PER_ROW * SUDOKU_COLUMN_COUNT)
                + (squareNumber_u8 % SUDOKU_SQUARE_PER_ROW * SUDOKU_SQUARE_WIDTH));

        for (i_u8 = 0U; i_u8 < SUDOKU_SQUARE_SIZE; i_u8++)
        {
            uint8_t currentCell_u8 = squareOffset_u8 + (i_u8 % SUDOKU_SQUARE_WIDTH)
                    + (i_u8 / SUDOKU_SQUARE_WIDTH * SUDOKU_COLUMN_COUNT);

            if (checkedValue_u8 == grid_au8[currentCell_u8])
            {
                countedValues_u8++;
            }
        }

        if (countedValues_u8 > 1U)
        {
            *checkState_pb = false;
        }
        else
        {
            *checkState_pb = true;
        }

        retVal_b = true;
    }

    return retVal_b;
}

