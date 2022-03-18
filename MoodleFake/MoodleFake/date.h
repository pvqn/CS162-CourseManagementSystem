#pragma once
struct Date {
	int day, month, year;

	//Constructor
	//Dễ sử dụng hơn, không cần mỗi lần gọi Date phải code Date.day, Date.month, Date.year
	//Ví dụ 1/1/2022 thì Date(1, 1, 2022)
	Date(int day = -1, int month = -1, int year = -1) :
		day(day), month(month), year(year)
	{};

};