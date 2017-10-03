#! /bin/env python
import sys
import argparse
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
from log_parser import parse_log

arg_parser = argparse.ArgumentParser()
arg_parser.add_argument('filename')
arg_parser.add_argument('-nl', type=int)
arg_parser.add_argument('--only-locale')
arg_parser.add_argument('--draw-local-subdomains', action='store_true')

args = arg_parser.parse_args()
num_locs = args.nl
only_locale = args.only_locale
filename = args.filename
dirname = '__aal/'+filename
locale_log_prefix = dirname+'/'+filename+'locale_'

# We just subclass Rectangle so that it can be called with an Axes
# instance, causing the rectangle to update its shape to match the
# bounds of the Axes
# class UpdatingRect(Rectangle):
    # def __call__(self, ax):
        # self.set_bounds(*ax.viewLim.bounds)
        # ax.figure.canvas.draw_idle()

# FIXME get rid of this by figuring out where the padding comes from
pad_comp = 0.15

def inc_color(cur, inc):
    return (cur[0], cur[1]-inc, cur[2]-inc)

# A class that will regenerate a fractal set as we zoom in, so that you
# can actually see the increasing detail.  A box in the left panel will show
# the area to which we are zoomed.
class Display(object):
    def __init__(self, filename, h=500, w=500):
        self.filename = filename
        self.rank, self.whole_lims, self.subdom_lims, self.access_mat, self.max_access = parse_log(filename)

        self.height = h
        self.width = w

    def get_locsubdom_rect(self):
        x = self.subdom_lims[0][0] - pad_comp
        width = self.subdom_lims[0][1] - x + 1

        y = self.subdom_lims[1][0] - pad_comp
        height = self.subdom_lims[1][1] - y + 1

        x *= self.ratio
        y *= self.ratio
        width *= self.ratio
        height *= self.ratio

        return Rectangle((x,y), width, height, fill=False)

    def get_image(self):

        # self.x = np.linspace(xstart, xend, self.width)
        # self.y = np.linspace(ystart, yend, self.height)

        access_mat_h = len(self.access_mat)
        access_mat_w = len(self.access_mat[0])
        if access_mat_h == access_mat_w:
            if access_mat_h < self.height:
                # good we are going to scale-up access data onto image

                # find the nearest multiple to 500
                rem = self.height%access_mat_h;
                self.height -= rem
                self.width = self.height
                self.ratio = int(self.height/access_mat_h)
                binning=False
                scaleup=True
            else:
                # data is larger than the image we'll do binning
                binning=True
                scaleup=False
                ratio = access_mat_h/self.height

        self.x = np.linspace(0, self.width-1, self.width)
        self.y = np.linspace(0, self.height-1, self.height)

        self.tick_labels = [int(access_mat_h*r) for r in [0., 0.25, 0.5, 0.75, 1.]] 

        image = [[(1.0, 1.0, 1.0) for x in range(self.width)] for y in
            range(self.height)]

        per_access_delta = 1.0/self.max_access

        r = self.ratio
        for row in range(access_mat_h):
            for col in range(access_mat_w):
                access_count = self.access_mat[row][col]
                if access_count > 0:
                    for i in range(row*r, (row+1)*r):
                        for j in range(col*r, (col+1)*r):
                            # if image[i][j] == (1.0, 1.0, 1.0):
                                # image[i][j] = (0.0, 1.0, 0.0)
                            image[i][j] = inc_color(image[i][j],
                                    per_access_delta*access_count)
        

        return image

    # def ax_update(self, ax):
        # ax.set_autoscale_on(False)  # Otherwise, infinite loop

        # # Get the number of points from the number of pixels in the window
        # dims = ax.patch.get_window_extent().bounds
        # self.width = int(dims[2] + 0.5)
        # self.height = int(dims[2] + 0.5)

        # # Get the range for the new area
        # xstart, ystart, xdelta, ydelta = ax.viewLim.bounds
        # xend = xstart + xdelta
        # yend = ystart + ydelta

        # # Update the image object with our new data and extent
        # im = ax.images[-1]
        # im.set_data(self.__call__(xstart, xend, ystart, yend))
        # im.set_extent((xstart, xend, ystart, yend))
        # ax.figure.canvas.draw_idle()

def do_plot(i, a):
    d = Display(filename=locale_log_prefix+str(i))
    Z = d.get_image()
    
    img_shape = (d.x.min(), d.x.max(),
        d.y.min(), d.y.max())

    a.set_xlim(0.0, d.x.max());
    a.set_ylim(0., d.y.max());

    a.imshow(Z, origin='lower', extent=img_shape)
    a.add_patch(d.get_locsubdom_rect())
    a.set_ylim(a.get_ylim()[::-1])
    a.set_xticks([d.x.max()*r for r in tick_locs])
    a.set_xticklabels(d.tick_labels, fontsize=14)
    a.set_yticks([d.y.max()*r for r in tick_locs])
    a.set_yticklabels(d.tick_labels, fontsize=14)
    a.grid(linestyle='dotted')

# this should be done mathematically or through target locales FIXME
factors_dict = {1: (1,1),
                2: (2,1),
                4: (2,2),
                8: (4,2),
                16: (4,4),
                32: (8,4)}

plot_dist = factors_dict[num_locs]


# tick_locs = [0., 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875, 1.]
# TODO parametrize this
tick_locs = [0., 0.25, 0.5, 0.75, 1.]

if only_locale != None:
    fig1, ax = plt.subplots(1,1)
    do_plot(only_locale, ax)
else:
    fig1, axes = plt.subplots(plot_dist[0], plot_dist[1])
    for i,(idx,a) in zip(range(num_locs), np.ndenumerate(axes)):
        do_plot(i, a)

# rect = UpdatingRect([0, 0], 0, 0, facecolor='None', edgecolor='black', linewidth=1.0)
# rect.set_bounds(*ax2.viewLim.bounds)
# ax1.add_patch(rect)

# Connect for changing the view limits
# ax2.callbacks.connect('xlim_changed', rect)
# ax2.callbacks.connect('ylim_changed', rect)

# ax2.callbacks.connect('xlim_changed', d1.ax_update)
# ax2.callbacks.connect('ylim_changed', d1.ax_update)
# ax2.set_title("Zoom here")

plt.margins(0,0)
plt.show()
