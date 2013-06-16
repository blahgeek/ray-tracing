# 简介

代码实现了一个简单的光线追踪模型，能将输入的场景描述文件计算生成图片。

特性：

- 从Json文件中读入场景描述文件
- 支持球体、平面（支持网格或图片纹理）、三角形组成的复杂物体（从.obj文件读入）
- 使用phone模型，支持反射、折射效果
- 使用层次包围盒加速
- 良好的代码可扩展性、可读性

# 样例

![](https://github.com/blahgeek/ray-tracing/raw/master/scene/scene1.png)\


![](https://github.com/blahgeek/ray-tracing/raw/master/scene/rose_heart.png)\


另外，`video/5000.avi`是一段三体运行视频。

# 编译和运行

通过`make`编译，需要安装opencv库。

编译后可以运行`./ray-tracing input.json output.png`测试。程序接受的一些参数如下：

    Usage: ray-tracing [OPTION] Input Output

    Input .json scene file.
    Output .png image file.

    Options:
      -h, --help            show this help message and exit
      -w INT, --width=INT   width of output image. default: 640.
      -h INT, --height=INT  height of output image. default: 480.
      -d INT, --distance=INT
                            distance from view point to screen. default: 1000.
      -e FLOAT, --epsilon=FLOAT
                            stop tracing after the intensity of ray reaches epsilon.
                            default: 0.01.

## 参数说明

- 宽度： 输出图片的宽度。
- 高度： 输出图片的高度。
- 视点距离： 假象视点距离屏幕的距离，单位为像素值。
- 递归深度： 当每条光线强度减小为一定倍数后停止追踪，默认为1%。

## 输入文件格式

程序接受输入Json格式的场景文件，文件中描述了物体和光源的属性。参见`scene/`文件夹中的样例。

每个Json文件包含三个部分：`objects`, `lights`, `points`, 每个部分对应一个Array。

### objects

该部分包含了场景中的物体，`type`值表示物体的类型，其取值有以下几种：

- `ball`: 球体，另外需要`center`和`radius`两个值分别表示圆心和半径。圆心用一个三维数组表示(x, y, z)值，以下所有坐标点都如此。
- `GridSurface`: 网格纹理平面，另外需要`triangle`, `colors`和`grid_width`三个值，`triangles`包含三个点确定该平面，`colors`包含两个颜色，后者表示网格边长。颜色使用一个三维数组表示rgb值，取值为0-1。
- `ImageSurface`: 图片纹理品面，另外需要`triangle`, `img`两个值，前者包含三个点确定该平面，并且三个点(a, b, c)中`a->b`和`a->c`分别为图片长宽两个方向的基，即可以对图片进行放缩。
- `Body`: 由三角面片组成的物体，另外需要`triangles`描述其三角面片。`triangles`中的每个三角面片的表示可以由三个坐标点构成，也可以由三个字符串表示，每个字符串表示`points`中对应的点。另外，也可以指定`objfile`即物体的.obj描述文件而不需要`triangles`。

对于`Body`中使用obj文件的情况，另外可以指定以下值对物体缩放或移动：

- `rotate_x`, `rotate_y`, `rotate_z`：沿x, y, z轴对物体旋转，角度制。
- `resize`：对物体放缩的倍数。
- `move`：一个三维数组，表示沿xyz方向移动的值。

另外，对于以上四种物体还有一些通用的属性，如下：

- `N`: 物体的折射率，默认为1.2。
- `reflection_fact`: 经过该物体反射后光线衰减的系数。
- `refraction_fact`: 经过该物体折射后光线衰减的系数。
- `specular_power`: 镜面反射的一个系数，越大表示物体越光滑。
- `specular_fact`: 一个三维数组，表示对rgb三种颜色分别的镜面反射系数。
- `diffuse_fact`: 一个三维数组，表示对rgb三种颜色分别的漫反射系数（通常表现为物体的颜色）。

### lights

该部分包含了场景中的灯光，每个灯光由`point`和`color`组成，分别代表光源的位置和颜色。前者为一个三维数组表示坐标，后者为一个三维数组表示颜色，颜色从0-255（也可以超过255表示更强的光）。

### points

包含若干个字符串对应的点，被objects中的Body使用。


# 代码基本结构

几个类的继承和包含关系如下。

![](https://github.com/blahgeek/ray-tracing/raw/master/doc/classes.png)\


## Geometry类

这是一个描述几何物体的基类，继承出Sphere和Triangle两个子类。 该基类包含以下两个函数：

    virtual Number closestIntersection(Ray & ray) = 0;
    virtual Vec getLawVec(const Vec & p) = 0;

`closestIntersection`函数用于计算一条光线与该几何体最近的交点，`getLawVec`计算一个点的法向量。

## Object类

这是一个描述物体的基类，包含折射率、各种反射系数、各种折射系数等信息，继承出Surface，Ball，Body等子类。该基类包含以下函数：

    virtual Number closestIntersection(HandlingRay & h) = 0;
    virtual Vec getDiffuseFace(const Vec & p) const;
    Ray reflect(HandlingRay & h);
    Ray refract(HandlingRay & h);
    Color lambert(HandlingRay & h, const Color & light_color);

其中，只有`closestIntersection`这个用于计算光线交点的函数，与不同物体的本身属性有关，是纯虚函数，其余函数均不需要子类另外实现。

- `getDiffuseFace`函数返回一个点的漫反射折射率，需要时子类可以重载从而产生纹理。
- `reflect`函数根据入射光和物体在该点的法向量返回出射光。
- `refract`函数返回折射的出射光，同时考虑从外面进入和从物体内部射出的情况。
- `lambert`函数返回该点的lambert模型计算出的颜色值。

## 其他

- `Scene`: 表示一个场景，包含所有物体和光源。
- `Ray`: 表示一条光线，包含起始点、方向、所处介质的折射率。
- `Light`: 表示一个光源，包含位置和颜色。
- `Output`: 输出用，继承出`PngOutput`。
- `ContainBox`: 层次包围盒（八叉树），在下面的加速实现中会提到。


# 基本算法

对于屏幕上的每一个像素，算法流程如下：

1. 构造一条从视点到屏幕上该像素的光线。
2. 计算该光线与场景中所有物体最近的交点，若没有交点则结束。
3. 对于场景中每个光源，若光源到该点之间没有其他物体，则根据Phong模型计算该光源对该点的颜色贡献值。
4. 计算这个物体对光线的折射和反射，若光线强度值不小于阈值则对两条光线分别执行步骤2。

# 其他特性

代码中实现了几个常见的加速技术，对于一个拥有三个球体、数万三角面的物体的场景，在一台Linode 512服务器上渲染640x480像素的图片需要时间仅为数十秒。

- 层次包围盒：使用八叉树实现，若一个包围盒中三角面的数量大于5个则将其继续分割为8个包围盒，分割后每个包围盒根据自身包含的三角面调整自己的大小。
- 多线程：使用OpenMP实现多线程，由于光线跟踪算法高并行的特性，多线程加速效果很好。由于场景不同地方物体数量差距很大，计算每行像素所花时间差距很大，因此OpenMP使用动态任务分配。

另外，考虑到颜色值可能大于255造成过曝，最后使用$1-e^x$公式进行曝光修正。

# 感谢

使用了以下开源代码：

- Hong Jiang <hong@hjiang.net> 等的`jsonxx`库。
- Johannes Weißl <jargon@molb.org> 的`OptionParse`库。

参考了http://www.codermind.com/articles/Raytracer-in-C++-Part-I-First-rays.html的代码。

感谢老师和助教。

