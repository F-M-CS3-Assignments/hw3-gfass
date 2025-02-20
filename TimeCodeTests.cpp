#include <iostream>
#include <assert.h>

using namespace std;

#include "TimeCode.h"

// Tests whether ComponentsToSeconds correctly converts hours, minutes, and seconds into total seconds.
void TestComponentsToSeconds(){
	
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Basic test cases to verify correct conversion
	assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0);
	assert(TimeCode::ComponentsToSeconds(0, 1, 0) == 60);
	assert(TimeCode::ComponentsToSeconds(1, 0, 0) == 3600);
	assert(TimeCode::ComponentsToSeconds(0, 0, 1) == 1);
	assert(TimeCode::ComponentsToSeconds(2, 30, 15) == 9015);
	assert(TimeCode::ComponentsToSeconds(10, 20, 30) == 37230);
	assert(TimeCode::ComponentsToSeconds(3, 17, 42) == 11862);
	assert(TimeCode::ComponentsToSeconds(100, 59, 59) == 363599);
	
	// Additional test cases to cover edge cases and larger values
	assert(TimeCode::ComponentsToSeconds(0, 59, 59) == 3599); // Just before an hour rolls over
	assert(TimeCode::ComponentsToSeconds(5, 0, 0) == 18000); // Exactly 5 hours
	assert(TimeCode::ComponentsToSeconds(23, 59, 59) == 86399); // Just before a full day
	assert(TimeCode::ComponentsToSeconds(50, 0, 0) == 180000); // Large hour value


	cout << "PASSED!" << endl << endl;
}

// Tests whether the default constructor initializes a TimeCode object to 0:0:0
void TestDefaultConstructor(){
	
	cout << "Testing Default Constructor" << endl;
	
	TimeCode tc;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}

// Tests whether the component constructor correctly initializes TimeCode objects with rollovers.
void TestComponentConstructor(){
	
	cout << "Testing Component Constructor" << endl;
	
	// Ensuring correct conversion and roll-over handling
	TimeCode tc1 = TimeCode(3, 71, 3801);  // Should roll over to 5:14:21
	assert(tc1.ToString() == "5:14:21");
	TimeCode tc2 = TimeCode(10, 59, 59);
	assert(tc2.ToString() == "10:59:59");
	TimeCode tc3 = TimeCode(23, 59, 60);  // Should roll over to 24:0:0
	assert(tc3.ToString() == "24:0:0");
	TimeCode tc4 = TimeCode(50, 100, 200);  // Should correctly adjust minutes and seconds
	assert(tc4.ToString() == "51:43:20");
	TimeCode tc5 = TimeCode(0, 0, 86400);  // Should convert 86400 sec to exactly 24:0:0
	assert(tc5.ToString() == "24:0:0");
	
	cout << "PASSED!" << endl << endl;
}

// Tests whether GetComponents correctly extracts hours, minutes, and seconds from TimeCode.
void TestGetComponents(){
	
	cout << "Testing GetComponents" << endl;
	
	unsigned int h, m, s;
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	TimeCode tc2 = TimeCode(10, 30, 45);
	tc2.GetComponents(h, m, s);
	assert(h == 10 && m == 30 && s == 45);
	
	TimeCode tc3 = TimeCode(99, 59, 59);
	tc3.GetComponents(h, m, s);
	assert(h == 99 && m == 59 && s == 59);
	
	cout << "PASSED!" << endl << endl;
}

// Tests whether subtraction correctly handles valid cases and prevents negative results.
void TestSubtract(){
	
	cout << "Testing Subtract" << endl;
	
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	// Ensuring exception is thrown for negative result
	try{
		TimeCode tc4 = TimeCode(0, 30, 0);
		TimeCode tc5 = tc4 - tc1;
		assert(false);
	} catch(const invalid_argument& e) {}
	
	cout << "PASSED!" << endl << endl;
}

// Tests whether SetHours, SetMinutes, and SetSeconds correctly update only the respective component.
void TestSetMethods(){
	
	cout << "Testing Set Methods" << endl;
	
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15);
	assert(tc.ToString() == "8:15:9");
	
	try {
		tc.SetMinutes(80);
		assert(false);
	} catch (const invalid_argument &e) {}
	
	tc.SetSeconds(30);
	assert(tc.ToString() == "8:15:30");
	tc.SetHours(20);
	assert(tc.ToString() == "20:15:30");
	
	cout << "PASSED!" << endl << endl;
}

// Tests whether comparison operators correctly compare TimeCode objects.
void TestComparisonOperators(){
	
	cout << "Testing Comparison Operators" << endl;
	
	TimeCode tc1 = TimeCode(2, 30, 30);
	TimeCode tc2 = TimeCode(2, 30, 30);
	TimeCode tc3 = TimeCode(3, 0, 0);
	assert(tc1 == tc2);
	assert(tc1 != tc3);
	assert(tc1 < tc3);
	assert(tc3 > tc1);
	assert(tc1 <= tc2);
	assert(tc3 >= tc1);
	
	cout << "PASSED!" << endl << endl;
}

// Runs all test cases.
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestSubtract();
	TestSetMethods();
	TestComparisonOperators();
	
	cout << "PASSED ALL TESTS!!!" << endl;
	
	return 0;
}