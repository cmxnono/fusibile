#pragma once
#include <string.h> // memset()
#include <stdlib.h> // malloc(), realloc(), free()
#include "algorithmparameters.h"
#include "cameraparameters.h"
#include "managed.h"
#include <vector>
#include <vector_types.h> // float4

class Point_li {
public:
    float4 normal; // Normal
    float4 coord; // Point coordinate
    float texture4[4]; // Average texture color
};


class PointCloudList {
public:
    Point_li *points;
    std::vector<std::vector<int>> ptsVisIdx;
    int rows;
    int cols;
    unsigned int size;
    unsigned int maximum;
    void resize(int n)
    {
        maximum=n;
        points = (Point_li *) malloc (sizeof(Point_li) * n);
        memset            (points,  0, sizeof(Point_li) * n);
        ptsVisIdx.clear();
        ptsVisIdx.resize(n);
        for(int i = 0; i < n; i++)
            ptsVisIdx[i].clear();
    }
    void increase_size(int n)
    {
        maximum=n;
        points = (Point_li *) realloc (points, n * sizeof(Point_li));
        ptsVisIdx.resize(n);
        printf("New size of point cloud list is %d\n", n);
    }
    ~PointCloudList()
    {
        ptsVisIdx.clear();
        free (points);
    }
};
