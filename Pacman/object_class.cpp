#include "pch.h"
#include "object_class.h"


DynObject::DynObject(const string obj_type, int row, int col)
    : obj_{row, col, row, col, obj_type} {};

void DynObject::set_location_row(int row) { obj_.location_row = row; };

void DynObject::set_location_col(int col) { obj_.location_col = col; };

void DynObject::set_to_ressurection_row() { obj_.location_row = obj_.resurrection_row;};

void DynObject::set_to_ressurection_col() {obj_.location_col = obj_.resurrection_col;};

int DynObject::get_location_row() const { return obj_.location_row; };

int DynObject::get_location_col() const { return obj_.location_col; };

string DynObject::get_obj_type() const { return obj_.type; };