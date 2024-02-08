#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

static int globalId = 0;

struct employee
{
	const int	id = ++globalId;
	char		name[10];
	double		hours;
};