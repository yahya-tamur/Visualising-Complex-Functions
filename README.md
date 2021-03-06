Idea
----------

Complex functions essentially take two variables and return two variables,
which means they're hard to visualize since they're four dimensional.

You could graph the real and imaginary part separately as 3d graphs, but those are
often very related and graphing them separately doesn't make that fact obvious.

This is especially the case when trying to visualize complex differentiable
functions (or meromorphic functions, or functions with essential singularities etc):

f(a+bi) = a + bi is complex differentiable
f(a+bi) = a - bi is not

and you can't really tell why from graphing the real and imaginary parts
separately.

Another way to visualize them is through domain coloring -- assign one color to
each value of the argument of a complex number (t on z = r e^ti or arctan(b/a) on z = a + bi).

The reason it's color and not white to black or something is because it's nice
that the color is the same at values 0 and 2pi.

That approach is better, but I still found it confusing.

This is a variation on that: basically, instead of assigning a color to each
angle, a time period in a looping gif is assigned.

Compare a simple domain coloring of f(z) = z to the gif here --
basically, in this graph, at time t, z such that f(z) produces angles
in the range (t-e,t+e) for a given e are highlighted.

Also, the domain coloring approach doesn't capture the magnitude of the resulting
complex number very well -- it's sometimes done with contour lines or light-to-dark gradients.

In this approach, again, at time t, points such that t mod h = |f(z)| mod h
for a given h are highlighted.

The contour lines could be static, however, having them move from small to large
numbers means there is a bigger visual distinction between f(z) = z and f(z) = 1/z

One of the things I liked the best with this approach, especially when compared to domain
coloring, is the way it displays complex polynomials -- it's way easier to tell multiplicities
of zeroes and orders of poles.

Implementation
--------------

Usage:

`make` to compile

`./a.out` to run the executable file

`make clean` to remove files created by compilation



Graphing a given function:

edit params.cc to specify the function and the plot,

run `make` to compile (the whole program won't need to recompile if you only changed params.cc)

run `./a.out` to create the image.



This uses a cut down version of gifenc.c and gifenc.h from github.com/lecram/gifenc

I removed some optimizations I didn't need, removed windows support, and I think I made a few changes
to accomodate debugging tools I was using.

The rest of the project should still work with the original version, though I haven't tried
it.


Opening the gif's produced is actually pretty hard.

I've been using eog, the default image viewer on ubuntu. That has the advantage of showing more frames
per second but the disadvantage of having about 60% cpu utilisation on a nice cpu.

I've also tried chrome, firefox, and the windows image viewer. If I had to use those more commonly
available options, I would probably want to decrease the number of frames in params.cc so the images
loop faster.

When looking at them on chrome (or on github on chrome), some images loop before displaying every frame.
It does at least show the whole loop on firefox and windows image viewer.

Another option to view these images would be to convert them to a video format like mp4. This will lose quality --
gif's are lossless, which is probably why it's so hard to view these in the first place.


This is something I did in my free time.
