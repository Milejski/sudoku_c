/*
 * algo_internal.h
 *
 *  Created on: 4 mar 2018
 *      Author: Zenc
 */

#ifndef SOURCE_ALGO_ALGO_INTERNAL_H_
#define SOURCE_ALGO_ALGO_INTERNAL_H_

bool ALGO_checkGrid	  (uint8_t *grid_au8, bool *checkState_pb);
bool ALGO_checkPoint  (uint8_t *grid_au8, uint8_t pointNumber_u8,  bool *checkState_pb);
bool ALGO_checkRow    (uint8_t *grid_au8, uint8_t rowNumber_u8,    uint8_t checkedValue_u8, bool *checkState_pb);
bool ALGO_checkColumn (uint8_t *grid_au8, uint8_t columnNumber_u8, uint8_t checkedValue_u8, bool *checkState_pb);
bool ALGO_checkSquare (uint8_t *grid_au8, uint8_t squareNumber_u8, uint8_t checkedValue_u8, bool *checkState_pb);


#endif /* SOURCE_ALGO_ALGO_INTERNAL_H_ */
