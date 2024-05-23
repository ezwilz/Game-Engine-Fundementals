#pragma once
class MyCustomEngine
{
	friend class XCube2Engine; //make sure
private:
	MyCustomEngine();
public:
	~MyCustomEngine();
	void otherfunction();
};

