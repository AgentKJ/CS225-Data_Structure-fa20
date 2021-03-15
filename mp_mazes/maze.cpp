/* Your code here! */
#include "maze.h"
#include <queue>

using std::queue;
using std::pair;
using namespace cs225;

SquareMaze::SquareMaze() {
  _width = 0;
  _height = 0;
}

void SquareMaze::makeMaze(int width, int height) {
  _width = width;
  _height = height;
  _dsets.addelements(width * height);
  _walls.resize(width * height);

  for (int i = 0; i < width * height; i++) {
    _walls[i].first = true;
    _walls[i].second = true;
  }

  while (_dsets.size(0) < width * height) {
    int x = rand() % _width;
    int y = rand() % _height;
    if (rand() % 2 == 0) {
      if (x < _width - 1 && _dsets.find(x + y * _width) != _dsets.find(x + y * _width + 1)) {
        _dsets.setunion(x + y * _width, x + y * _width + 1);
        _walls[x + y * _width].first = false;
      }
    } else {
      if (y < _height - 1 && _dsets.find(x + y * _width) != _dsets.find(x + (y + 1) * _width)) {
        _dsets.setunion(x + y * _width, x + (y + 1) * _width);
        _walls[x + y * _width].second = false;
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  if (dir == 0 && x != _width - 1) {
    // Check right
    return !_walls[x + y * _width].first;
  } else if (dir == 1 && y != _height - 1) {
    // Check down
    return !_walls[x + y * _width].second;
  } else if (dir == 2 && x != 0) {
    // Check left
    return !_walls[(x - 1) + y * _width].first;
  } else if (dir == 3 && y != 0) {
    // Check up
    return !_walls[x + (y - 1) * _width].second;
  }

  return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)	{
  if (dir == 0) {
    // Set right wall
    _walls[x + y * _width].first = exists;
  } else if (dir == 1) {
    // Set bottom wall
    _walls[x + y * _width].second = exists;
  } else {
    return;
  }
}

vector<int> SquareMaze::solveMaze() {

  // Track the next possible step
  queue<int> path;
  vector<pair<int, int>> pd(_width * _height);
  path.push(0);

  for (int i = 0; i < _width * _height; i++) {
    pd[i].first = -1;
    pd[i].second = 0;
  }

  int current = 0;
  int x = 0;
  int y = 0;
  while (!path.empty()) {
    current = path.front();
    path.pop();
    x = current % _width;
    y = current / _height;

    if (canTravel(x, y, 0) && pd[current + 1].first == -1) {
      path.push(current + 1);
      pd[current + 1].first = current;
      pd[current + 1].second = pd[current].second + 1;
    }
    if (canTravel(x, y, 1) && pd[current + _width].first == -1) {
      path.push(current + _width);
      pd[current + _width].first = current;
      pd[current + _width].second = pd[current].second + 1;
    }
    if (canTravel(x, y, 2) && pd[current - 1].first == -1) {
      path.push(current-1);
      pd[current - 1].first = current;
      pd[current - 1].second = pd[current].second + 1;
    }
    if (canTravel(x, y, 3) && pd[current - _width].first == -1) {
      path.push(current - _width);
      pd[current - _width].first = current;
      pd[current - _width].second = pd[current].second + 1;
    }
  }
  vector<int> result;
  int temp = _width * (_height - 1);
  for (int i = temp; i < _width * _height; i++) {
    if (pd[i].second > pd[temp].second) {
      temp = i;
    }
  }

  while (temp != 0) {
    if (pd[temp].first == temp - 1) {
      result.push_back(0);
    } else if (pd[temp].first == temp - _width) {
      result.push_back(1);
    } else if (pd[temp].first == temp + 1) {
      result.push_back(2);
    } else {
      result.push_back(3);
    }
    temp = pd[temp].first;
  }

  reverse(result.begin(), result.end());

  return result;
}

PNG *SquareMaze::drawMaze() const {
  PNG *maze = new PNG(_width * 10 + 1, _height * 10 + 1);
  for (int i = 0; i < _height * 10 + 1; i++) {
    HSLAPixel &pixel = maze->getPixel(0, i);
    pixel.h = 0;
    pixel.s = 0;
    pixel.l = 0;
  }
  for (int i = 10; i < _width * 10 + 1; i++) {
    HSLAPixel &pixel = maze->getPixel(i,0);
    pixel.h = 0;
    pixel.s = 0;
    pixel.l = 0;
  }
  for (int x = 0; x < _width; x++) {
    for (int y = 0; y < _height; y++) {
      if (_walls[x + y * _width].first) {
        for (unsigned i = 0; i < 11; i++) {
          HSLAPixel &pixel = maze->getPixel((x + 1) * 10, y * 10 + i);
          pixel.h = 0;
          pixel.s = 0;
          pixel.l = 0;
        }
      }
      if (_walls[x + y * _width].second) {
        for (unsigned i = 0; i < 11; i++) {
          HSLAPixel &pixel = maze->getPixel(x * 10 + i, (y + 1) * 10);
          pixel.h = 0;
          pixel.s = 0;
          pixel.l = 0;
        }
      }
    }
  }
  
  return maze;
}

PNG *SquareMaze::drawMazeWithSolution() {
  PNG *maze = drawMaze();
  vector<int> path = solveMaze();

  int x = 5;
  int y = 5;

  for (size_t j = 0; j < path.size(); j++) {
    if (path[j] == 0) {
      for (int i = 0; i < 11; i++) {
        HSLAPixel &pixel = maze->getPixel(x + i, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
      }
      x += 10;
    }
    if (path[j] == 1) {
      for (int i = 0; i < 11; i++) {
        HSLAPixel &pixel = maze->getPixel(x, y + i);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
      }
      y += 10;
    }
    if (path[j] == 2) {
      for (int i = 0; i < 11; i++) {
        HSLAPixel &pixel = maze->getPixel(x - i, y);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
      }
      x -= 10;
    }
    if (path[j] == 3) {
      for (int i = 0; i < 11; i++) {
        HSLAPixel &pixel = maze->getPixel(x, y - i);
        pixel.h = 0;
        pixel.s = 1;
        pixel.l = 0.5;
      }
      y -= 10;
    }
  }
  
  x -= 5;
  y -= 5;
  for (int i = 1; i < 10; i++) {
    HSLAPixel &pixel = maze->getPixel(x + i, y + 10);
    pixel.l = 1;
  }

  return maze;
}
