#pragma once
struct Mark {
	float totalMark;
	float finalMark;
	float midtermMark;
	float otherMark;

	Mark(float totalMark, float finalMark, float midtermMark, float otherMark) :
		totalMark(totalMark), finalMark(finalMark), midtermMark(midtermMark), otherMark(otherMark) {};
	Mark() {};
};

