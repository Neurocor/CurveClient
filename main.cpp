
#include "Curve.h"


/*For detecting memory leaks*/
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include <random>
#include <vector>
#include <string>

/*include PI const*/
#define _USE_MATH_DEFINES
#include "math.h"
#include <ctime>

using namespace std;

int randomizeValue(int From, int To, bool Include = true);
void randomizeCoefs(int& Numerator, int& Denominator);


/*for manual sorting*/

int partition(vector<shared_ptr<Circle>>&arr, int start, int end);
void quicksort(vector<shared_ptr<Circle>>& arr, int start, int end);




int main(int argc, char* argv[])
{
	vector <shared_ptr<Curve>> curves;
	vector <shared_ptr<Circle>> circles;

	srand(time(0));

	/*TASK 2*/

	for (int index = 0; index < 10; ++index) {
	
		switch (randomizeValue(1, 2))
		{
		case 1:
			curves.push_back(make_shared<Circle>(randomizeValue(1, 10)));
			break;		
		case 2:
			curves.push_back(make_shared<Ellipse>(randomizeValue(1, 10), randomizeValue(1, 10)));
			break;		
		case 3:
			curves.push_back(make_shared<Helix>());
			break;
		default:
			break;
		}
	}

	/*TASK 3*/

	for (auto& curve : curves) {


		auto tmpPoint = curve->GetPoint(M_PI_4);

		cout << "Point (" << tmpPoint.x << ", " << tmpPoint.y << ", " << tmpPoint.z << ")" << std::endl;;

	}

	/*TASK 4*/

	for (auto &curve : curves) {

		auto& inf = typeid(*curve);

		auto name = inf.name();

		string str = name;


		int res = 0;

		res = str.find("Circle");

		if (res > 0) {
			circles.push_back(dynamic_pointer_cast<Circle>(curve));
		}
	}


	/*TASK 5*/

	sort(circles.begin(), circles.end(), [](shared_ptr<Circle>& l, shared_ptr<Circle>& r) {
		return l->GetRadius1() < r->GetRadius1();
		});

	/*TASK 6*/

	float Total = 0;

	for (auto circle : circles) {
		Total += circle->GetRadius1();
	}

	cout << "Total radii: " << Total << endl;

	return 0;
}

int randomizeValue(int From, int To, bool Include)
{
	return rand() % (To - From + Include) + From;
}

void randomizeCoefs(int& Numerator, int& Denominator)
{

	Numerator = 0;
	Denominator = 1;

	srand(time(0));

	Numerator = randomizeValue(1, 10);
	Denominator = randomizeValue(1, 10);
}

int partition(vector<shared_ptr<Circle>>& arr, int start, int end)
{
	int pivot = arr[end]->GetRadius1();

	int pIndex = start;

	for (int i = start; i < end; i++)
	{
		if (arr[i]->GetRadius1() <= pivot)
		{
			swap(arr[i], arr[pIndex]);
			pIndex++;
		}
	}

	swap(arr[pIndex], arr[end]);

	return pIndex;
}

void quicksort(vector<shared_ptr<Circle>>& arr, int start, int end)
{
	if (start >= end) {
		return;
	}

	int pivot = partition(arr, start, end);

	quicksort(arr, start, pivot - 1);
	quicksort(arr, pivot + 1, end);

}
