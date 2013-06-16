/// @file main.cpp  @version 1.0 @date 06/10/2013
/// @author BlahGeek@Gmail.com

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <cstdio>
using namespace std;

#include "common.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "geometry.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "PngOutput.h"
#include "ball.hpp"
#include "light.hpp"
#include "body.hpp"
#include "imagesurface.hpp"
#include "gridsurface.hpp"

#include "OptionParser.h"
using namespace optparse;


int main ( int argc, char *argv[] )
{

    OptionParser parser = OptionParser()
        .usage("Usage: %prog [OPTION] Input Output")
        .description("Input .json scene file.\nOutput .png image file.");
    parser.add_option("-w", "--width").action("store").type("int").set_default(640)
        .help("width of output image. default: %default.");
    parser.add_option("-h", "--height").action("store").type("int").set_default(480)
        .help("height of output image. default: %default.");
    parser.add_option("-d", "--distance").action("store").type("int").set_default(1000)
        .help("distance from view point to screen. default: %default.");
    parser.add_option("-e", "--epsilon").action("store").type("float").set_default(0.01)
        .help("stop tracing after the intensity of ray reaches epsilon. default: %default.");

    Values & options = parser.parse_args(argc, argv);
    vector<string> args = parser.args();
    assert(args.size() == 2);

    Scene scene;
    scene.loadFromJson(args[0].c_str());

    int width = (int)options.get("width");
    int height = (int)options.get("height");
    Number epsilon = (float)options.get("epsilon");
    PngOutput * out = new PngOutput(width, height, args[1].c_str());

    Vec view_point(width / 2, height / 2, -(int)options.get("distance"));
#pragma omp parallel for schedule(dynamic)
    for(int i = 0 ; i < width ; i += 1){
        cerr << i << endl;
        for(int j = 0 ; j < height ; j += 1){
            Color color(0, 0, 0);
            vector<RayWithCoef> views;
            views.push_back(RayWithCoef(Ray(view_point, Vec(i, j, 0) - view_point), 1.0));
            while(!views.empty()){
                RayWithCoef view = views.back();
                views.pop_back();
                RayWithCoef view_reflect(view);
                RayWithCoef view_refract(view);
                if(view.second < epsilon) continue;
                color += scene.phong(view, view_reflect, view_refract);
                if(!isAlmostSame(view.first.start, view_reflect.first.start))
                    views.push_back(view_reflect);
                if(!isAlmostSame(view.first.start, view_refract.first.start))
                    views.push_back(view_refract);
            }
            out->draw(i, j, color);
        }
    }
    out->finish();

    return EXIT_SUCCESS;
}
