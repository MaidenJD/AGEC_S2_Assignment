#pragma once
#include "View.h"

class TestView : public View
{
public:
	TestView();
	~TestView();

	bool Init() override;
};

