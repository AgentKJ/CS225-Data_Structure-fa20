/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<3>> tiles;
    map<Point<3>, int> map;
    for (size_t i = 0; i < theTiles.size(); i++) {
        LUVAPixel color = theTiles[i].getAverageColor();
        Point<3> point = convertToXYZ(color);
        tiles.push_back(point);
        map[point] = i;
    }
    KDTree<3> tree = KDTree<3>(tiles);
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int i = 0; i < theSource.getRows(); i++) {
        for (int j = 0; j < theSource.getColumns(); j++) {
            LUVAPixel color = theSource.getRegionColor(i, j);
            Point<3> point = tree.findNearestNeighbor(convertToXYZ(color));
            canvas->setTile(i, j, &theTiles[map[point]]);
        }
    }
    return canvas;
}

