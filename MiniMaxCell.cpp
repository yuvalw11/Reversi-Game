/*
 * MiniMaxCell.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: ofir
 */

#include "MiniMaxCell.h"

namespace std {

MiniMaxCell::MiniMaxCell(Cell cell, int gradeForInputCell) {
	this->gradeForThisCell = gradeForInputCell;
	this->cellToPut = Cell(cell.getX() + 1, cell.getY() + 1);
}

}

