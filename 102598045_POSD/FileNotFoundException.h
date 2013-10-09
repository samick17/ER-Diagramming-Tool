#pragma once

#include "Exception.h"

class FileNotFoundException : public Exception{
public:
	FileNotFoundException();
	~FileNotFoundException();
};