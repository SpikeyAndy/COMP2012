#include <iostream>
#include "PointSet.h"
using namespace std;

PointSet::PointSet(int capacity)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's conversion constructor" << endl;

  // TODO #1: add your code here
  this->capacity = capacity;
  Point *arr = new Point[capacity];
  this->points = arr;
  this->numPoints = 0;

}

PointSet::PointSet(const Point points[], int numPoints)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's other constructor" << endl;

  // TODO #2: add your code here
  this->points = new Point[numPoints];
  this->capacity = numPoints;
  this->numPoints = numPoints;
  for (int i = 0; i < numPoints; i++) {
      this->points[i] = points[i];
  }
}

PointSet::PointSet(const PointSet& s)
{
  // This cout statement is for learning purpose only, which shows when the constructor will be invoked
  cout << "Initialized by PointSet's copy constructor" << endl;

  // TODO #3: add your code here
  this->points = new Point[s.capacity];
  this->capacity = s.capacity;
  this->numPoints = s.numPoints;
  for (int i = 0; i < numPoints; i++) {
      this->points[i] = s.points[i];
  }
}

PointSet::~PointSet()
{
  // TODO #4: add your code here
  delete [] this->points;
}

void PointSet::addPoint(const Point& p)
{
  // TODO #5: add your code here
  if (this->numPoints >= this->capacity) {
    cout << "Insufficient array space";
    return;
  }
  this->points[this->numPoints++] = p;
}

void PointSet::removeLastPoint()
{
  // TODO #6: add your code here
  if (this->numPoints == 0)
  {
    cout << "No points";
    return;
  }
  this->numPoints--;

}

// Return true if the all the points in the point set is collinear; return false otherwise
bool PointSet::isCollinear() const
{
  // TODO #7: add your code here
  if (this->numPoints < 3)
  {
    return true;
  }
  for (int i = 2; i < this->numPoints; i++)
  {
    if (!isCollinear_3points(this->points[i-2],this->points[i-1],this->points[i]))
    {
      return false;
    }
  }
  return true;
}

// return true if 3 given points are on the same straight line
bool PointSet::isCollinear_3points(const Point p1, const Point p2, const Point p3) const
{
  // TODO #8: add your code here
  double area = 0.5 * (p1.getX() * (p2.getY() - p3.getY()) + p2.getX() * (p3.getY() - p1.getY()) + p3.getX()*(p1.getY() - p2.getY()));
  if (area == 0) {return true;}
  else {return false;}
}

void PointSet::print() const
{
  // This function is already completed.
  if (numPoints == 0) {
    cout << "The PointSet is empty!" << endl;
    return;
  }
  cout << "Number of points: " << numPoints << endl;;
  cout << "points: " << endl;
  for(int i = 0; i < numPoints; i++)
  {
    points[i].print();
    cout << endl;
  }
}
