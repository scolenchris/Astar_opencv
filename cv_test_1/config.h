#pragma once
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <fstream>

class ConfigClass
{
public:
	const int getGridSize() const;
	const int getCellSize() const;
	void setGridSize();
	void setCellSize();
	void readConfig();

private:
	int _grid_size;
	int _cell_size;
};

#endif // !_CONFIG_H_
