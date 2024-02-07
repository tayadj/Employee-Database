#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>

static int globalId = 0;

struct employee
{
	const int	id;
	char		name[10];
	double		hours;
};