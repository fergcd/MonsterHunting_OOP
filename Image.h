#pragma once
#include <string>

using namespace std;

struct Image final
{
	enum { MAX_ROW = 11 };
	string rows[MAX_ROW];
};