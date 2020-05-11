#pragma once
class CollisionObject2D
{
private:
	double x;
	double y;
	double width;
	double height;
	double angle;

public:
	/* Moves the collision object into a specified direction
	This does not change the angle of the collision object itself */
	void move(double distance, double direction);

	/* Moves the collision object according to its current angle while applying an offset to the direction
	This does not change the angle of the collision object itself */
	void moveWithOffset(double distance, double directionOffset);

	double getX();

	double getY();
};

